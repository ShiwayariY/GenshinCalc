#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <algorithm>

#include <Status.hh>
#include <Character.hh>
#include <Weapon.hh>
#include <Artifact.hh>
#include <Calc.hh>

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;
using StatusRoll = Artifact::StatusRoll;

bool has_min_stats(const Status& stats, const Status& min) {
	return stats.base_hp >= min.base_hp					   //
		   && stats.flat_hp >= min.flat_hp				   //
		   && stats.hp_perc >= min.hp_perc				   //
		   && stats.base_atk >= min.base_atk			   //
		   && stats.flat_atk >= min.flat_atk			   //
		   && stats.atk_perc >= min.atk_perc			   //
		   && stats.base_def >= min.base_def			   //
		   && stats.flat_def >= min.flat_def			   //
		   && stats.def_perc >= min.def_perc			   //
		   && stats.crit_rate >= min.crit_rate			   //
		   && stats.crit_dmg >= min.crit_dmg			   //
		   && stats.energy_recharge >= min.energy_recharge //
		   && stats.elem_mastery >= min.elem_mastery	   //
		   && stats.healing_bonus >= min.healing_bonus	 //
		   && stats.pyro_bonus >= min.pyro_bonus		   //
		   && stats.hydro_bonus >= min.hydro_bonus		   //
		   && stats.cryo_bonus >= min.cryo_bonus		   //
		   && stats.electro_bonus >= min.electro_bonus	 //
		   && stats.anemo_bonus >= min.anemo_bonus		   //
		   && stats.geo_bonus >= min.geo_bonus			   //
		   && stats.phys_bonus >= min.phys_bonus		   //
		   && stats.normal_bonus >= min.normal_bonus	   //
		   && stats.charged_bonus >= min.charged_bonus	 //
		   && stats.plunge_bonus >= min.plunge_bonus	   //
		   && stats.skill_bonus >= min.skill_bonus		   //
		   && stats.burst_bonus >= min.burst_bonus		   //
		   && stats.reaction_bonus >= min.reaction_bonus   //
		   && stats.additional_dmg >= min.additional_dmg;
}

struct ArtifactCollection {
	std::vector<Artifact> flowers, feathers, sands, goblets, heads;
};
ArtifactCollection collect_artifacts(const std::vector<Artifact>& arts) {
	ArtifactCollection coll;
	auto copy_arts = [&arts](std::vector<Artifact>& to, std::set<Main> mains) {
		std::copy_if(arts.begin(), arts.end(), std::back_inserter(to),
		  [&mains](const auto& a) { return mains.contains(a.main()); });
	};
	copy_arts(coll.flowers, { Main::Flower });
	copy_arts(coll.feathers, { Main::Feather });
	copy_arts(coll.sands, { Main::SandAtk, Main::SandDef, Main::SandEM, Main::SandER, Main::SandHP });
	copy_arts(coll.goblets, { Main::GobletAtk, Main::GobletDef, Main::GobletHP, Main::GobletEM,
							  Main::GobletAnemo, Main::GobletCryo, Main::GobletElectro, Main::GobletGeo, Main::GobletHydro, Main::GobletPyro, Main::GobletPhys });
	copy_arts(coll.heads, { Main::HeadAtk, Main::HeadDef, Main::HeadHP, Main::HeadEM, Main::HeadCRate, Main::HeadCDmg, Main::HeadHealing });
	return coll;
}

// returns avg_dmg on best set
float list_sets_by_dmg(
  const Character& chara,
  const Weapon& weapon,
  const std::vector<Artifact>& arts,
  const Combo& combo,
  const Status& min_stats = Status{},
  void (*modifier)(Status&) = [](Status&) {}) {

	auto coll = collect_artifacts(arts);
	std::vector<std::pair<float, std::vector<Artifact>>> results;
	for (const auto& flower : coll.flowers)
		for (const auto& feather : coll.feathers)
			for (const auto& sand : coll.sands)
				for (const auto& goblet : coll.goblets)
					for (const auto& head : coll.heads) {
						Calc calc(chara, weapon, flower, feather, sand, goblet, head);
						const float avg_dmg = calc.avg_dmg(combo, modifier);
						if (has_min_stats(calc.status(), min_stats))
							results.push_back({ avg_dmg, { flower, feather, sand, goblet, head } });
					}

	std::sort(results.begin(), results.end(), [](const auto& lhs, const auto& rhs) { return lhs.first > rhs.first; });
	const char newline = '\n'; // outsmart clang-format
	for (const auto& [dmg, set] : results) {
		std::cout << "Average dmg: " << dmg << "\n"
				  << "___Flower___" << newline << set[0] << "\n"
				  << "___Feather__" << newline << set[1] << "\n"
				  << "___Sand_____" << newline << set[2] << "\n"
				  << "___Goblet___" << newline << set[3] << "\n"
				  << "___Head_____" << newline << set[4] << "\n"
				  << "*************************************************************************************************\n";
	}
	return (results.empty() ? 0.0 : results[0].first);
}

void calc_Ayaka() {
	Artifact flower{
		Main::Flower,
		SetType::BlizzardStrayer,
		{ StatusRoll::AtkPerc, 9.3 },
		{ StatusRoll::EM, 21 },
		{ StatusRoll::ER, 5.8 },
		{ StatusRoll::CDmg, 25.7 }
	};
	Artifact feather{
		Main::Feather,
		SetType::BlizzardStrayer,
		{ StatusRoll::CDmg, 14.0 },
		{ StatusRoll::ER, 13.0 },
		{ StatusRoll::AtkPerc, 10.5 },
		{ StatusRoll::CRate, 6.2 }
	};
	Artifact sand{
		Main::SandAtk,
		SetType::BlizzardStrayer,
		{ StatusRoll::CDmg, 14.0 },
		{ StatusRoll::ER, 11.0 },
		{ StatusRoll::Atk, 29 },
		{ StatusRoll::DefPerc, 13.1 }
	};
	Artifact goblet{
		Main::GobletCryo,
		SetType::Gladiator,
		{ StatusRoll::Def, 19 },
		{ StatusRoll::CRate, 8.6 },
		{ StatusRoll::ER, 11.0 },
		{ StatusRoll::AtkPerc, 9.3 }
	};
	Artifact head{
		Main::HeadCDmg,
		SetType::BlizzardStrayer,
		{ StatusRoll::EM, 40 },
		{ StatusRoll::AtkPerc, 8.2 },
		{ StatusRoll::Atk, 53 },
		{ StatusRoll::ER, 5.2 }
	};
	Ayaka ayaka;
	BlackSword black_sword;

	Calc calc{ ayaka, black_sword, flower, feather, sand, goblet, head };

	ayaka.AmatsumiKunitsumiSanctification = false;
	Combo combo{ ayaka.get_hit(DmgTalent::Normal, 1) };
	const auto avg_dmg = calc.avg_dmg(combo);
	Calc::dmg_dealt(avg_dmg, 90, 87, 0.0, 10.0);
}

void calc_Baal() {
	Artifact flower_1{
		Main::Flower,
		SetType::Emblem,
		{ StatusRoll::Atk, 49 },
		{ StatusRoll::Def, 23 },
		{ StatusRoll::CDmg, 23.3 },
		{ StatusRoll::CRate, 3.5 }
	};
	Artifact flower_2{
		Main::Flower,
		SetType::Emblem,
		{ StatusRoll::HPPerc, 5.3 },
		{ StatusRoll::AtkPerc, 16.9 },
		{ StatusRoll::CRate, 2.7 },
		{ StatusRoll::ER, 10.4 }
	};
	Artifact feather{
		Main::Feather,
		SetType::Emblem,
		{ StatusRoll::ER, 11.0 },
		{ StatusRoll::CRate, 10.1 },
		{ StatusRoll::Def, 19 },
		{ StatusRoll::CDmg, 20.2 }
	};
	Artifact sand{
		Main::SandER,
		SetType::Emblem,
		{ StatusRoll::HPPerc, 16.3 },
		{ StatusRoll::HP, 508 },
		{ StatusRoll::CDmg, 14.8 },
		{ StatusRoll::Def, 23 },
	};
	Artifact goblet{
		Main::GobletAtk,
		SetType::HeartOfDepth,
		{ StatusRoll::HP, 508 },
		{ StatusRoll::CRate, 10.1 },
		{ StatusRoll::ER, 6.5 },
		{ StatusRoll::CDmg, 14.8 }
	};
	Artifact head{
		Main::HeadCDmg,
		SetType::Emblem,
		{ StatusRoll::Atk, 16 },
		{ StatusRoll::CRate, 17.1 },
		{ StatusRoll::EM, 40 },
		{ StatusRoll::HPPerc, 4.7 }
	};
	Baal baal;
	baal.energy_consumed = 80 + 70 + 60;
	Combo combo{
		baal.get_hit(DmgTalent::Burst, 1),
		baal.get_hit(DmgTalent::Burst, 2),
		baal.get_hit(DmgTalent::Burst, 3),
		baal.get_hit(DmgTalent::Burst, 4),
		baal.get_hit(DmgTalent::Burst, 7),
		baal.get_hit(DmgTalent::Burst, 2),
		baal.get_hit(DmgTalent::Burst, 3),
		baal.get_hit(DmgTalent::Burst, 4),
		baal.get_hit(DmgTalent::Burst, 7),
		baal.get_hit(DmgTalent::Burst, 2),
		baal.get_hit(DmgTalent::Burst, 3),
		baal.get_hit(DmgTalent::Burst, 4),
		baal.get_hit(DmgTalent::Burst, 7)
	};
	TheCatch thecatch;

	Calc calc{ baal, thecatch, flower_1, feather, sand, goblet, head };
	const auto avg_dmg = calc.avg_dmg(combo);
	const auto dmg_dealt = Calc::dmg_dealt(avg_dmg, 81, 91, 0, 10);

	std::cout << dmg_dealt << std::endl;
}

void calc_Itto() {
	Artifact f{
		Main::Flower,
		SetType::HuskOfOpulentDreams,
		{ StatusRoll::DefPerc, 7.29 },
		{ StatusRoll::AtkPerc, 5.83 },
		{ StatusRoll::CDmg, 23.31 },
		{ StatusRoll::CRate, 15.56 }
	};
	Artifact p{
		Main::Feather,
		SetType::HuskOfOpulentDreams,
		{ StatusRoll::DefPerc, 7.29 },
		{ StatusRoll::CRate, 11.67 },
		{ StatusRoll::AtkPerc, 5.83 },
		{ StatusRoll::CDmg, 31.08 }
	};
	Artifact s{
		Main::SandDef,
		SetType::HuskOfOpulentDreams,
		{ StatusRoll::AtkPerc, 5.83 },
		{ StatusRoll::CRate, 11.67 },
		{ StatusRoll::CDmg, 31.08 },
		{ StatusRoll::Def, 23.15 },
	};
	Artifact g{
		Main::GobletGeo,
		SetType::HuskOfOpulentDreams,
		{ StatusRoll::DefPerc, 7.29 },
		{ StatusRoll::CRate, 11.67 },
		{ StatusRoll::AtkPerc, 5.83 },
		{ StatusRoll::CDmg, 31.08 }
	};
	Artifact h{
		Main::HeadCDmg,
		SetType::HuskOfOpulentDreams,
		{ StatusRoll::DefPerc, 7.29 },
		{ StatusRoll::CRate, 23.34 },
		{ StatusRoll::AtkPerc, 5.83 },
		{ StatusRoll::Def, 23.15 }
	};

	Itto itto;
	Whiteblind whiteblind{ 5 };
	SkywardPride skyward_pride{ 1 };
	auto arataki_combo = itto.get_hit(DmgTalent::Charged, 1);
	auto final_slash = itto.get_hit(DmgTalent::Charged, 2);
	Combo combo{
		arataki_combo,
		arataki_combo,
		arataki_combo,
		arataki_combo,
		final_slash
	};
	Calc calc{ itto, whiteblind, f, p, s, g, h };
	const auto avg_dmg = calc.avg_dmg(combo, [](Status& stats) {
		Calc::geo_resonance_modifier(stats);
		stats.geo_bonus += 15.0; // Gorou skill
		stats.flat_def += 350;   // Gorou skill
		stats.def_perc += 25.0;  // Gorou burst passive
	});

	const unsigned CHAR_LVL = 90;
	const unsigned ENEMY_LVL = 90;
	const float ENEMY_RES = 10.0;
	const float DEF_REDUCTION = 0.0;
	const auto dmg_dealt = Calc::dmg_dealt(avg_dmg,
	  CHAR_LVL,
	  ENEMY_LVL,
	  DEF_REDUCTION,
	  ENEMY_RES - 40.0); // geo reso -20% resistance + zhongli shield

	std::cout << dmg_dealt << std::endl;
}

}

int main() {
	using namespace GenshinCalc;
	calc_Itto();
}
