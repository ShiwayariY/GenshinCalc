#include <cmath>

#include <Character.hh>

namespace GenshinCalc {

Character::Character(Status stats) :
		status{ stats } {}

Hit Character::to_hit(DmgTalent talent, DmgDealt dmg_dealt) {
	return {
		.talent = talent,
		.element = dmg_dealt.element,
		.scaling_type = dmg_dealt.scaling,
		.scaling_perc = dmg_dealt.value
	};
}

// -------------------------------------------------- Ayaka --------------------------------------------------

Hit Ayaka::get_hit(DmgTalent talent, unsigned int hit_num) const {
	auto hit = to_hit(talent, ABILITIES.at({ talent, hit_num }));
	if (!CryoInfused && hit.talent == DmgTalent::Normal) hit.element = DmgElement::Phys;
	return hit;
}

void Ayaka::apply_effects(Status& stats) const {
	if (AmatsumiKunitsumiSanctification) {
		stats.normal_bonus += 30.0;
		stats.charged_bonus += 30.0;
	}
	if (KantenSenmyouBlessing) stats.cryo_bonus += 18.0;
}

// -------------------------------------------------- Baal --------------------------------------------------

Hit Baal::get_hit(DmgTalent talent, unsigned int hit_num) const {
	auto hit = to_hit(talent, ABILITIES.at({ talent, hit_num }));
	if (hit.talent == DmgTalent::Burst) {
		const float resolve = std::min(60.0f, static_cast<float>(energy_consumed) * MusouShinsetsu_resolve_per_energy);
		const float resolve_bonus = (hit_num == 1
										? MusouShinsetsu_resolve_bonus_initial
										: MusouShinsetsu_resolve_bonus_normal) *
									resolve;
		hit.scaling_perc += resolve_bonus;
		if (hit_num == 5 || hit_num == 7) hit.scaling_perc += resolve_bonus; // these have two hits
	}
	return hit;
}

void Baal::apply_effects(Status& stats) const {
	stats.electro_bonus += 0.4 * (stats.energy_recharge - 100.0);
	stats.burst_bonus += BalefulOmen_burst_bonus * 90;
}

// -------------------------------------------------- Eula --------------------------------------------------

Hit Eula::get_hit(DmgTalent talent, unsigned int hit_num) const {
	auto hit = to_hit(talent, ABILITIES.at({ talent, hit_num }));
	if (talent == DmgTalent::Burst && hit_num == 3)
		hit.scaling_perc += static_cast<float>(Lightfall_stacks) * Lightfall_dmg_per_stack;
	return hit;
}

// -------------------------------------------------- Itto --------------------------------------------------

Hit Itto::get_hit(DmgTalent talent, unsigned int hit_num) const {
	auto hit = to_hit(talent, ABILITIES.at({ talent, hit_num }));
	if (!RoyalDescent && hit.talent == DmgTalent::Normal) hit.element = DmgElement::Phys;
	return hit;
}

void Itto::apply_effects(Status& stats) const {
	const float total_def = stats.base_def * (1.0 + stats.def_perc / 100.0) + stats.flat_def;
	if (RoyalDescent)
		stats.flat_atk += RoyalDescent_atk_bonus * total_def;
	if (SuperlativeSuperstrength)
		stats.additional_dmg += 0.35 * total_def;
}

// -------------------------------------------------- HuTao --------------------------------------------------

Hit HuTao::get_hit(DmgTalent talent, unsigned int hit_num) const {
	auto hit = to_hit(talent, ABILITIES.at({ talent, hit_num }));
	if (GuideToAfterlife &&
		(talent == DmgTalent::Normal ||
		  talent == DmgTalent::Charged ||
		  talent == DmgTalent::Plunge)) {
		hit.element = DmgElement::Pyro;
	}
	return hit;
}

void HuTao::apply_effects(Status& stats) const {
	if (GuideToAfterlife) {
		const float total_hp = stats.base_hp * (1.0 + stats.hp_perc / 100.0) + stats.flat_hp;
		const float atk_bonus = GuideToAfterlife_atk_ratio * total_hp;
		stats.flat_atk += std::min(4.0f * stats.base_atk, atk_bonus);
	}
	if (SanguineRouge) stats.pyro_bonus += 33.0;
}

// -------------------------------------------------- Yae Miko --------------------------------------------------

Hit YaeMiko::get_hit(DmgTalent talent, unsigned int hit_num) const {
	return to_hit(talent, ABILITIES.at({ talent, hit_num }));
}

void YaeMiko::apply_effects(Status& stats) const {
	stats.skill_bonus += EnlightenedBlessing_skill_bonus * stats.elem_mastery;
}

// -------------------------------------------------- Yelan --------------------------------------------------

Hit Yelan::get_hit(DmgTalent talent, unsigned int hit_num) const {
	return to_hit(talent, ABILITIES.at({ talent, hit_num }));
}

void Yelan::apply_effects(Status& stats) const {
	auto stacks = std::max(TurnControl_stacks, 1u);
	stacks = std::min(stacks, static_cast<unsigned>(TurnControl_bonus.size()));

	stats.hp_perc += TurnControl_bonus[stacks - 1];
}

// -------------------------------------------------- Klee --------------------------------------------------

Hit Klee::get_hit(DmgTalent talent, unsigned int hit_num) const {
	return to_hit(talent, ABILITIES.at({ talent, hit_num }));
}

// -------------------------------------------------- Nilou --------------------------------------------------

Hit Nilou::get_hit(DmgTalent talent, unsigned int hit_num) const {
	return to_hit(talent, ABILITIES.at({ talent, hit_num }));
}

void Nilou::apply_effects(Status& stats) const {
	if (GoldenChalice) {
		stats.elem_mastery += 60.0;
		const auto total_hp = stats.base_hp * (1.0f + stats.hp_perc / 100.0f) + stats.flat_hp;
		stats.reaction_bonus += std::min(std::max(0.0f, total_hp - 30000.0f) * 0.007f, 300.0f);
	}
}

}
