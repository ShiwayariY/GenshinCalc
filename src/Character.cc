#include <cmath>

#include <Character.hh>

namespace GenshinCalc {

Character::Character(Status stats) :
		status{ stats } {}

// -------------------------------------------------- AYAKA --------------------------------------------------

Hit Ayaka::get_hit(DmgTalent talent, unsigned int hit_num) const {
	auto hit = ABILITIES.at({ talent, hit_num });
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
	auto hit = ABILITIES.at({ talent, hit_num });
	if (hit.talent == DmgTalent::Burst) {
		const float resolve = std::min(60.0, static_cast<float>(energy_consumed) * 0.19);
		const float resolve_bonus = (hit_num == 1 ? 6.61 : 1.23) * resolve;
		hit.scaling_perc += resolve_bonus;
		if (hit_num == 5 || hit_num == 7) hit.scaling_perc += resolve_bonus; // these have two hits
	}
	return hit;
}

void Baal::apply_effects(Status& stats) const {
	stats.electro_bonus += 0.4 * (stats.energy_recharge - 100.0);
	stats.burst_bonus += 0.29 * 90;
}

}