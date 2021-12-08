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

}