#include <iostream>
#include <iomanip>
#include <vector>

#ifndef GENSHINCALC_INCLUDE_STATUS
#define GENSHINCALC_INCLUDE_STATUS

#define DEBUG(x) do {} while (0)
// #define DEBUG(x) do { std::cerr << x << std::endl; } while (0)

namespace GenshinCalc {

enum class DmgElement {
	Phys,
	Pyro,
	Hydro,
	Cryo,
	Electro,
	Anemo,
	Geo
};

enum class DmgTalent {
	Normal,
	Charged,
	Plunge,
	Skill,
	Burst
};

enum class Reaction {
	None,
	MeltByPyro,
	MeltByCryo,
	VapeByHydro,
	VapeByPyro
};

struct Hit {
	DmgTalent talent = DmgTalent::Normal;
	DmgElement element = DmgElement::Phys;
	float scaling_perc = 100.0;
	bool can_crit = true;
	Reaction reaction = Reaction::None;
};
using Combo = std::vector<Hit>;

struct Status {
	// [..._perc, ..._bonus, crit_..., energy_recharge] are %-values (i.e. pyro_bonus = 46.0 for 46%)
	float
	  base_hp = 0.0,
	  flat_hp = 0.0,
	  hp_perc = 0.0,

	  base_atk = 0.0,
	  flat_atk = 0.0,
	  atk_perc = 0.0,

	  base_def = 0.0,
	  flat_def = 0.0,
	  def_perc = 0.0,

	  crit_rate = 0.0,
	  crit_dmg = 0.0,
	  energy_recharge = 0.0,
	  elem_mastery = 0.0,
	  healing_bonus = 0.0,

	  pyro_bonus = 0.0,
	  hydro_bonus = 0.0,
	  cryo_bonus = 0.0,
	  electro_bonus = 0.0,
	  anemo_bonus = 0.0,
	  geo_bonus = 0.0,
	  phys_bonus = 0.0,

	  normal_bonus = 0.0,
	  charged_bonus = 0.0,
	  plunge_bonus = 0.0,
	  skill_bonus = 0.0,
	  burst_bonus = 0.0,
	  reaction_bonus = 0.0,
	  
	  additional_dmg = 0.0; // like flat atk, but without talent scaling

	Status operator+(const Status& other) const {
		return Status{
			.base_hp = base_hp + other.base_hp,
			.flat_hp = flat_hp + other.flat_hp,
			.hp_perc = hp_perc + other.hp_perc,

			.base_atk = base_atk + other.base_atk,
			.flat_atk = flat_atk + other.flat_atk,
			.atk_perc = atk_perc + other.atk_perc,

			.base_def = base_def + other.base_def,
			.flat_def = flat_def + other.flat_def,
			.def_perc = def_perc + other.def_perc,

			.crit_rate = crit_rate + other.crit_rate,
			.crit_dmg = crit_dmg + other.crit_dmg,

			.energy_recharge = energy_recharge + other.energy_recharge,
			.elem_mastery = elem_mastery + other.elem_mastery,
			.healing_bonus = healing_bonus + other.healing_bonus,

			.pyro_bonus = pyro_bonus + other.pyro_bonus,
			.hydro_bonus = hydro_bonus + other.hydro_bonus,
			.cryo_bonus = cryo_bonus + other.cryo_bonus,
			.electro_bonus = electro_bonus + other.electro_bonus,
			.anemo_bonus = anemo_bonus + other.anemo_bonus,
			.geo_bonus = geo_bonus + other.geo_bonus,
			.phys_bonus = phys_bonus + other.phys_bonus,

			.normal_bonus = normal_bonus + other.normal_bonus,
			.charged_bonus = charged_bonus + other.charged_bonus,
			.plunge_bonus = plunge_bonus + other.plunge_bonus,
			.skill_bonus = skill_bonus + other.skill_bonus,
			.burst_bonus = burst_bonus + other.burst_bonus,

			.reaction_bonus = reaction_bonus + other.reaction_bonus,

			.additional_dmg = additional_dmg + other.additional_dmg
		};
	};
};

inline std::ostream& operator<<(std::ostream& os, const Status& s) {
	os << "HP base               " << std::setw(10) << s.base_hp << "   |   "
	   << "HP%                   " << std::setw(10) << s.hp_perc << "   |   "
	   << "HP                    " << std::setw(10) << s.flat_hp << "   |\n"
	   << "ATK base              " << std::setw(10) << s.base_atk << "   |   "
	   << "ATK%                  " << std::setw(10) << s.atk_perc << "   |   "
	   << "ATK                   " << std::setw(10) << s.flat_atk << "   |\n"
	   << "DEF base              " << std::setw(10) << s.base_atk << "   |   "
	   << "DEF%                  " << std::setw(10) << s.def_perc << "   |   "
	   << "DEF                   " << std::setw(10) << s.flat_def << "   |\n"
	   << "CRIT Rate             " << std::setw(10) << s.crit_rate << "   |   "
	   << "CRIT DMG              " << std::setw(10) << s.crit_dmg << "   |   "
	   << "Energy Recharge       " << std::setw(10) << s.energy_recharge << "   |\n"
	   << "Elemental Mastery     " << std::setw(10) << s.elem_mastery << "   |   "
	   << "Healing Bonus         " << std::setw(10) << s.elem_mastery << "   |\n"
	   << "Pyro DMG              " << std::setw(10) << s.pyro_bonus << "   |   "
	   << "Hydro DMG             " << std::setw(10) << s.hydro_bonus << "   |   "
	   << "Cryo DMG              " << std::setw(10) << s.cryo_bonus << "   |\n"
	   << "Electro DMG           " << std::setw(10) << s.electro_bonus << "   |   "
	   << "Anemo DMG             " << std::setw(10) << s.anemo_bonus << "   |   "
	   << "Geo DMG               " << std::setw(10) << s.geo_bonus << "   |\n"
	   << "Physical DMG          " << std::setw(10) << s.phys_bonus << "   |\n"
	   << "Normal DMG            " << std::setw(10) << s.normal_bonus << "   |   "
	   << "Charged DMG           " << std::setw(10) << s.charged_bonus << "   |   "
	   << "Plunge DMG            " << std::setw(10) << s.plunge_bonus << "   |\n"
	   << "Skill DMG             " << std::setw(10) << s.skill_bonus << "   |   "
	   << "Burst DMG             " << std::setw(10) << s.burst_bonus << "   |   "
	   << "Reaction DMG          " << std::setw(10) << s.reaction_bonus << "   |\n"
	   << "Additional DMG        " << std::setw(10) << s.additional_dmg << "   |\n";
	return os;
}

}

#endif
