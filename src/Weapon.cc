#include <Weapon.hh>

namespace GenshinCalc {

Weapon::Weapon(Status stats) :
		status{ stats } {}

// -------------------------------------------------- Redhorn Stonethresher --------------------------------------------------

void RedhornStonethresher::apply_effects(Status& stats) const {
	const float total_def = (stats.base_def * (1.0 + stats.def_perc / 100.0) + stats.flat_def);
	stats.additional_dmg += (0.3f + static_cast<float>(m_refine) * 0.1f) * total_def;
}

}