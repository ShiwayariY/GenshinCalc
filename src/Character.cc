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



}