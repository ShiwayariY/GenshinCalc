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

float Calc::dmg_dealt(
  float dmg_applied,
  unsigned int char_level,
  unsigned int enemy_level,
  float def_reduction_perc,
  float res_perc) {
	return dmg_applied * def_multiplier(char_level, enemy_level, def_reduction_perc) * res_multiplier(res_perc);
}

float Calc::calc_avg_dmg(const Combo& combo) {
	float dmg = 0.0;

	const std::map<ScalingType, float> power{
		{ ScalingType::HP, total_hp() },
		{ ScalingType::Atk, total_atk() },
		{ ScalingType::Def, total_def() }
	};

	for (const Hit& hit : combo) {
		const float hit_power = power.at(hit.scaling_type) * hit.scaling_perc / 100.0 + additional_dmg(hit.talent);
		DEBUG("Hit Atk: " << hit_atk);

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

		dmg += hit_dmg;
	}
	return dmg;
}

Status Calc::status() const {
	return m_stats;
}

void Calc::pyro_resonance_modifier(Status& stats) {
	stats.atk_perc += 25.0;
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

float Calc::additional_dmg(DmgTalent talent) const {
	float add_dmg = m_stats.additional_dmg;
	switch (talent) {
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
	return add_dmg;
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

float Calc::amplifying_multiplier(Reaction reaction) const {
	float reaction_multiplier = 1.0;
	switch (reaction) {
		case Reaction::None:
			return reaction_multiplier;

		case Reaction::MeltByCryo:
		case Reaction::VapeByPyro:
			reaction_multiplier = 1.5;
			break;

		case Reaction::MeltByPyro:
		case Reaction::VapeByHydro:
			reaction_multiplier = 2.0;
			break;
	}
	const float EM_bonus_multiplier = 2.78 * m_stats.elem_mastery / (m_stats.elem_mastery + 1400);
	const float amp_mult = reaction_multiplier * (1.0 + EM_bonus_multiplier + m_stats.reaction_bonus / 100.0);
	DEBUG("Amplifying multiplier: " << amp_mult);
	return amp_mult;
}

}