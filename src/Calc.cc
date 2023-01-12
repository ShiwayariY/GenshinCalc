#include <map>
#include <cmath>

#include <Calc.hh>

namespace GenshinCalc {

Calc::Calc(
  const Character& character,
  const Weapon& weapon,
  Artifact flower,
  Artifact feather,
  Artifact sand,
  Artifact goblet,
  Artifact head) :
		m_char{ character },
		m_weapon{ weapon },
		m_flower{ flower },
		m_feather{ feather },
		m_sand{ sand },
		m_goblet{ goblet },
		m_head{ head } {
}

float Calc::dmg_dealt(const AppliedDmg& dmg_applied, DmgContext context) {
	float dealt = 0.0;

	for (const auto& [elem, dmg] : dmg_applied.regular)
		dealt += dmg * res_multiplier(context.res_perc[elem]);
	dealt *= def_multiplier(context.char_level, context.enemy_level, context.def_reduction_perc);

	for (const auto& [elem, dmg] : dmg_applied.ignores_def)
		dealt += dmg * res_multiplier(context.res_perc[elem]);

	return dealt;
}

Calc::AppliedDmg Calc::calc_avg_dmg(const Combo& combo, unsigned int char_level) {
	AppliedDmg dmg;

	const std::map<ScalingType, float> power{
		{ ScalingType::HP, total_hp() },
		{ ScalingType::Atk, total_atk() },
		{ ScalingType::Def, total_def() }
	};

	auto talent_dmg = [*this, &power](const Hit& hit) {
		const float hit_power = power.at(hit.scaling_type) * hit.scaling_perc / 100.0 + additional_dmg(hit);
		DEBUG("Hit Atk: " << hit_power);

		const float bonus_mult = 1.0 + dmg_bonus(hit.element, hit.talent) / 100.0;
		DEBUG("Bonus mult: " << bonus_mult);

		float hit_dmg = hit_power * bonus_mult * amplifying_multiplier(hit.reaction);
		DEBUG("Base dmg hit: " << hit_dmg);

		switch (hit.crit) {
			case Crit::Normal:
				hit_dmg *= 1.0 + std::min(100.0f, m_stats.crit_rate) * m_stats.crit_dmg / 10000.0;
				break;
			case Crit::Always:
				hit_dmg *= 1.0 + m_stats.crit_dmg / 100.0;
				break;
			case Crit::Never:
				break;
		}
		DEBUG("Crit avg hit: " << hit_dmg << '\n');
		return hit_dmg;
	};

	for (const auto& hit : combo) {
		if (std::holds_alternative<Hit>(hit)) {
			const auto& talent_hit = std::get<Hit>(hit);
			dmg.regular[talent_hit.element] += talent_dmg(talent_hit);
		}
		if (std::holds_alternative<TrafoReaction>(hit)) {
			TrafoReaction trafo_hit = std::get<TrafoReaction>(hit);
			dmg.ignores_def[TRAFOREACTION_ELEMENT.at(trafo_hit)] += calc_traforeaction(trafo_hit, char_level);
		}
	}
	return dmg;
}

float Calc::calc_traforeaction(TrafoReaction reaction, unsigned int char_level) {
	static const std::map<TrafoReaction, float> multiplier{
		{ TrafoReaction::Bloom, 2.0 },
		{ TrafoReaction::HyperbloomBurgeon, 3.0 }
	};
	static const std::map<unsigned int, float> base{
		{ 10, 34.14 }, { 20, 80.58 }, { 30, 136.29 },
		{ 40, 207.38 }, { 50, 323.60 }, { 60, 492.88 },
		{ 70, 765.64 }, { 80, 1077.44 }, { 90, 1446.85 }
	};
	char_level = std::max(char_level, 11u);
	char_level = std::min(char_level, 90u);
	char_level = (char_level / 10u) * 10u;
	return base.at(char_level) * multiplier.at(reaction) *
		   (1.0f + m_stats.reaction_bonus / 100.0f +
			 16.0f * m_stats.elem_mastery / (2000.0f + m_stats.elem_mastery));
}

Status Calc::status() const {
	return m_stats;
}

void Calc::pyro_resonance_modifier(Status& stats) {
	stats.atk_perc += 25.0;
}

void Calc::hydro_resonance_modifier(Status& stats) {
	stats.hp_perc += 25.0;
}

void Calc::cryo_resonance_modifier(Status& stats) {
	stats.crit_rate += 15.0;
}

void Calc::geo_resonance_modifier(Status& stats) {
	stats.normal_bonus += 15.0;
	stats.charged_bonus += 15.0;
	stats.plunge_bonus += 15.0;
	stats.skill_bonus += 15.0;
	stats.burst_bonus += 15.0;
}

void Calc::dendro_resonance_modifier(Status& stats) {
	// base -> +50 EM
	// burn / quicken / bloom -> + 30 EM
	// aggrv / spread / hyperbl / brgn -> +20 EM
	stats.elem_mastery += 80.0;
}

// private

void Calc::init_stats() {
	m_stats = m_stats + m_char.status + m_weapon.status + m_flower.status() + m_feather.status() + m_sand.status() + m_goblet.status() + m_head.status();
	DEBUG("___Base stats___\n"
		  << m_stats);

	apply_artifact_sets();
	DEBUG("___after artifact sets___\n"
		  << m_stats);

	m_weapon.apply_effects(m_stats);
	DEBUG("___after weapon effects___\n"
		  << m_stats);

	m_char.apply_effects(m_stats);
	DEBUG("___after char effects___\n"
		  << m_stats);
}

void Calc::apply_artifact_sets() {
	std::map<Artifact::SetType, int> piece_count;
	piece_count[m_flower.type()]++;
	piece_count[m_feather.type()]++;
	piece_count[m_sand.type()]++;
	piece_count[m_goblet.type()]++;
	piece_count[m_head.type()]++;
	for (const auto& [type, count] : piece_count)
		Artifact::apply_effects(m_stats, type, count);
}

float Calc::def_multiplier(
  unsigned int char_level,
  unsigned int enemy_level,
  float def_reduction_perc) {
	const float char_val = static_cast<float>(char_level) + 100.0;
	const float enemy_val = static_cast<float>(enemy_level) + 100.0;
	const float reduction = 1.0 - def_reduction_perc / 100.0;
	const float def_mult = char_val / (reduction * enemy_val + char_val);
	DEBUG("Def multiplier: " << def_mult);
	return def_mult;
}

float Calc::res_multiplier(float res_perc) {
	float res_mult = 1.0;
	if (res_perc < 0.0)
		res_mult -= res_perc / 200.0;
	else if (res_perc < 75.0)
		res_mult -= res_perc / 100.0;
	else
		res_mult = 1.0 / (4.0 * res_perc / 100.0 + 1.0);

	DEBUG("Resistance multiplier: " << res_mult);
	return res_mult;
}

float Calc::total_hp() const {
	float tot = m_stats.base_hp * (1.0 + m_stats.hp_perc / 100.0) + m_stats.flat_hp;
	DEBUG("Total HP: " << tot);
	return tot;
}

float Calc::total_atk() const {
	float tot = m_stats.base_atk * (1.0 + m_stats.atk_perc / 100.0) + m_stats.flat_atk;
	DEBUG("Total ATK: " << tot);
	return tot;
}

float Calc::total_def() const {
	float tot = m_stats.base_def * (1.0 + m_stats.def_perc / 100.0) + m_stats.flat_def;
	DEBUG("Total DEF: " << tot);
	return tot;
}

float Calc::additional_dmg(Hit hit) const {
	float add_dmg = m_stats.additional_dmg;
	switch (hit.talent) {
		case DmgTalent::Normal:
			add_dmg += m_stats.additional_normal_dmg;
			break;
		case DmgTalent::Charged:
			add_dmg += m_stats.additional_charged_dmg;
			break;
		case DmgTalent::Plunge:
			break;
		case DmgTalent::Skill:
			add_dmg += m_stats.additional_skill_dmg;
			break;
		case DmgTalent::Burst:
			add_dmg += m_stats.additional_burst_dmg;
			break;
	}
	float reaction_dmg = 0.0f;
	switch (hit.reaction) {
		case AmplifyReaction::Aggravate:
			reaction_dmg += 1.15f;
		break;
		case AmplifyReaction::Spread:
			reaction_dmg += 1.25f;
		break;
		default:
		reaction_dmg = 0.0f;
	}
	reaction_dmg *= 1446.85f; // level multiplier for lv. 90 character
	reaction_dmg *= 1 + m_stats.reaction_bonus + 5.0f * m_stats.elem_mastery / (1200.0f + m_stats.elem_mastery);
	return add_dmg + reaction_dmg;
}

float Calc::dmg_bonus(DmgElement elem, DmgTalent talent) const {
	float bonus = 0.0;
	switch (elem) {
		case DmgElement::Pyro:
			bonus += m_stats.pyro_bonus;
			break;
		case DmgElement::Hydro:
			bonus += m_stats.hydro_bonus;
			break;
		case DmgElement::Cryo:
			bonus += m_stats.cryo_bonus;
			break;
		case DmgElement::Electro:
			bonus += m_stats.electro_bonus;
			break;
		case DmgElement::Anemo:
			bonus += m_stats.anemo_bonus;
			break;
		case DmgElement::Geo:
			bonus += m_stats.geo_bonus;
			break;
		case DmgElement::Dendro:
			bonus += m_stats.dendro_bonus;
			break;
		case DmgElement::Phys:
			bonus += m_stats.phys_bonus;
			break;
	}
	switch (talent) {
		case DmgTalent::Normal:
			bonus += m_stats.normal_bonus;
			break;
		case DmgTalent::Charged:
			bonus += m_stats.charged_bonus;
			break;
		case DmgTalent::Plunge:
			bonus += m_stats.plunge_bonus;
			break;
		case DmgTalent::Skill:
			bonus += m_stats.skill_bonus;
			break;
		case DmgTalent::Burst:
			bonus += m_stats.burst_bonus;
			break;
	}
	DEBUG("Bonus: " << bonus);
	return bonus;
}

float Calc::amplifying_multiplier(AmplifyReaction reaction) const {
	float reaction_multiplier = 1.0;
	switch (reaction) {
		case AmplifyReaction::None:
		case AmplifyReaction::Aggravate:
		case AmplifyReaction::Spread:
			return reaction_multiplier;

		case AmplifyReaction::MeltByCryo:
		case AmplifyReaction::VapeByPyro:
			reaction_multiplier = 1.5;
			break;

		case AmplifyReaction::MeltByPyro:
		case AmplifyReaction::VapeByHydro:
			reaction_multiplier = 2.0;
			break;
	}
	const float EM_bonus_multiplier = 2.78 * m_stats.elem_mastery / (m_stats.elem_mastery + 1400);
	const float amp_mult = reaction_multiplier * (1.0 + EM_bonus_multiplier + m_stats.reaction_bonus / 100.0);
	DEBUG("Amplifying multiplier: " << amp_mult);
	return amp_mult;
}

}