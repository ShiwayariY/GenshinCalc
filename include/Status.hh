#include <iostream>
#include <iomanip>
#include <vector>

#ifndef GENSHINCALC_INCLUDE_STATUS
#define GENSHINCALC_INCLUDE_STATUS

#define DEBUG(x) do {} while (0)
// #define DEBUG(x) do { std::cerr << x << std::endl; } while (0)

namespace GenshinCalc {

enum class StatusRoll {
	Atk,
	AtkPerc,
	Def,
	DefPerc,
	HP,
	HPPerc,
	CRate,
	CDmg,
	EM,
	ER
};

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

enum class Crit {
	Normal,
	Never,
	Always
};

struct Hit {
	DmgTalent talent = DmgTalent::Normal;
	DmgElement element = DmgElement::Phys;
	float scaling_perc = 100.0;
	Crit crit = Crit::Normal;
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

	void add_roll(StatusRoll type, float value) {
		switch (type) {
			case StatusRoll::HP:
				flat_hp += value;
				break;
			case StatusRoll::HPPerc:
				hp_perc += value;
				break;
			case StatusRoll::Atk:
				flat_atk += value;
				break;
			case StatusRoll::AtkPerc:
				atk_perc += value;
				break;
			case StatusRoll::Def:
				flat_def += value;
				break;
			case StatusRoll::DefPerc:
				def_perc += value;
				break;
			case StatusRoll::CRate:
				crit_rate += value;
				break;
			case StatusRoll::CDmg:
				crit_dmg += value;
				break;
			case StatusRoll::EM:
				elem_mastery += value;
				break;
			case StatusRoll::ER:
				energy_recharge += value;
				break;
		}
	}

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
	auto print_value = [&os](const auto& descr, const auto& val, const auto& sfx) {
		os << std::setw(19) << std::left;
		if (val > 0.001)
			os << descr << std::setw(8) << std::right << val;
		else
			os << std::setfill('-') << descr << std::setw(8) << "" << std::setfill(' ');
		os << "   |" << sfx;
	};
	print_value("HP base", s.base_hp, "   ");
	print_value("HP%", s.hp_perc, "   ");
	print_value("HP", s.flat_hp, "\n");
	print_value("ATK base", s.base_atk, "   ");
	print_value("ATK%", s.atk_perc, "   ");
	print_value("ATK", s.flat_atk, "\n");
	print_value("DEF base", s.base_def, "   ");
	print_value("DEF%", s.def_perc, "   ");
	print_value("DEF", s.flat_def, "\n");
	print_value("CRIT Rate", s.crit_rate, "   ");
	print_value("CRIT DMG", s.crit_dmg, "   ");
	print_value("Energy Recharge", s.energy_recharge, "\n");
	print_value("Elemental Mastery", s.elem_mastery, "   ");
	print_value("Healing Bonus", s.healing_bonus, "   ");
	print_value("", 0, "\n");
	print_value("Pyro DMG", s.pyro_bonus, "   ");
	print_value("Hydro DMG", s.hydro_bonus, "   ");
	print_value("Cryo DMG", s.cryo_bonus, "\n");
	print_value("Electro DMG", s.electro_bonus, "   ");
	print_value("Anemo DMG", s.anemo_bonus, "   ");
	print_value("Geo DMG", s.geo_bonus, "\n");
	print_value("Physical DMG", s.phys_bonus, "   ");
	print_value("", 0, "   ");
	print_value("", 0, "\n");
	print_value("Normal DMG", s.normal_bonus, "   ");
	print_value("Charged DMG", s.charged_bonus, "   ");
	print_value("Plunge DMG", s.plunge_bonus, "\n");
	print_value("Skill DMG", s.skill_bonus, "   ");
	print_value("Burst DMG", s.burst_bonus, "   ");
	print_value("Reaction DMG", s.reaction_bonus, "\n");
	print_value("Additional DMG", s.additional_dmg, "   ");
	print_value("", 0, "   ");
	print_value("", 0, "\n");
	return os;
}

}

#endif
