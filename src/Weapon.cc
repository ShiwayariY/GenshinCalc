#include <cmath>

#include <Weapon.hh>

namespace GenshinCalc {

Weapon::Weapon(Status stats) :
		status{ stats } {}

// -------------------------------------------------- Serpent Spine --------------------------------------------------

void SerpentSpine::apply_effects(Status& stats) const {
	auto curr_stacks = std::min(5u, stacks);
	stats.normal_bonus += DMG_per_stack * curr_stacks;
	stats.charged_bonus += DMG_per_stack * curr_stacks;
	stats.plunge_bonus += DMG_per_stack * curr_stacks;
	stats.skill_bonus += DMG_per_stack * curr_stacks;
	stats.burst_bonus += DMG_per_stack * curr_stacks;
}

// -------------------------------------------------- Redhorn Stonethresher --------------------------------------------------

void RedhornStonethresher::apply_effects(Status& stats) const {
	const float total_def = (stats.base_def * (1.0 + stats.def_perc / 100.0) + stats.flat_def);
	stats.additional_dmg += (0.3f + static_cast<float>(m_refine) * 0.1f) * total_def;
}

// -------------------------------------------------- Lost Prayer --------------------------------------------------

void LostPrayer::apply_effects(Status& stats) const {
	auto bonus = bonus_per_stack * std::min(stacks, max_stacks);
	stats.pyro_bonus += bonus;
	stats.hydro_bonus += bonus;
	stats.cryo_bonus += bonus;
	stats.electro_bonus += bonus;
	stats.anemo_bonus += bonus;
	stats.geo_bonus += bonus;
}

// -------------------------------------------------- Widsith --------------------------------------------------

void Widsith::apply_effects(Status& stats) const {
	switch (Song) {
		case ThemeSong::None:
			break;
		case ThemeSong::Recitative:
			stats.atk_perc += Recitative_atk_perc;
			break;
		case ThemeSong::Aria:
			stats.pyro_bonus += Aria_elem_bonus;
			stats.hydro_bonus += Aria_elem_bonus;
			stats.cryo_bonus += Aria_elem_bonus;
			stats.electro_bonus += Aria_elem_bonus;
			stats.anemo_bonus += Aria_elem_bonus;
			stats.geo_bonus += Aria_elem_bonus;
			break;
		case ThemeSong::Interlude:
			stats.elem_mastery += Interlude_elem_mastery;
			break;
	};
}

// -------------------------------------------------- The Unforged --------------------------------------------------

void Unforged::apply_effects(Status& stats) const {
	const auto stacks_bounded = std::min(stacks, 5u);
	auto atk_perc_bonus = stacks_bounded * m_atk_perc_bonus_per_stack;
	if (shielded) atk_perc_bonus *= 2;
	stats.atk_perc += atk_perc_bonus;
}

}
