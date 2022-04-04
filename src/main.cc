
#include <iostream>
#include <vector>
#include <set>
#include <array>
#include <algorithm>
#include <memory>
#include <iomanip>

#include <Status.hh>
#include <Character.hh>
#include <Weapon.hh>
#include <Artifact.hh>
#include <Calc.hh>
#include <Artifact_constants.hh>
#include <StatusGenerator.hh>

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;

float find_max_potential(
  const Character& chara,
  const Weapon& weapon,
  const Combo& combo,
  SetType flower_set, SetType feather_set, SetType sands_set, SetType goblet_set, SetType circlet_set,
  const std::vector<Main>& sands_mains,
  const std::vector<Main>& goblet_mains,
  const std::vector<Main>& circlet_mains,
  const std::vector<StatusRoll>& priority_rolls,
  unsigned rolls,
  void (*modifier)(Status&) = [](Status&) {}) {

	float best_dmg = 0.0;
	Status best_stats;

	Artifact dummy_flower{ Main::Flower, flower_set };
	Artifact dummy_feather{ Main::Feather, feather_set };

	std::cout << "Checking stat combinations ...\n"
			  << std::left << std::setw(10) << "Main"
			  << "Sub [million]\n";
	unsigned iteration_main = 0;

	for (const auto& sands_main : sands_mains) {
		Artifact dummy_sands{ sands_main, sands_set };

		for (const auto& goblet_main : goblet_mains) {
			Artifact dummy_goblet{ goblet_main, goblet_set };

			for (const auto& circlet_main : circlet_mains) {
				Artifact dummy_circlet{ circlet_main, circlet_set };

				++iteration_main;

				Calc calc{ chara, weapon,
					dummy_flower, dummy_feather, dummy_sands, dummy_goblet, dummy_circlet };
				StatusGenerator gen{ sands_main, goblet_main, circlet_main, priority_rolls, rolls };

				unsigned long iteration_sub_mil = 0;
				unsigned iteration_sub = 0;
				do {
					if (++iteration_sub >= 1000000) {
						iteration_sub = 0;
						std::cout << std::setw(10) << iteration_main << ++iteration_sub_mil
								  << std::setw(10) << ""
								  << "\r";
					}

					const auto curr_stats = gen.get();
					auto avg_dmg = calc.avg_dmg(combo,
					  [&curr_stats, &modifier](Status& stats) {
						  stats = stats + curr_stats;
						  modifier(stats);
					  });

					if (avg_dmg > best_dmg) {
						best_dmg = avg_dmg;
						best_stats = calc.status();
					}
				} while (gen.next());
			}
		}
	}

	std::cout << "\n"
			  << best_stats << std::endl;
	return best_dmg;
}

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

struct SetResult {
	float dmg = 0.0;
	Status stats;
	std::vector<Artifact> artifacts;
};
std::ostream& operator<<(std::ostream& os, const SetResult& set) {
	const char newline = '\n'; // outsmart clang-format
	std::cout << "Average dmg: " << set.dmg << "\n"
			  << "___Flower___" << newline << set.artifacts[0] << "\n"
			  << "___Feather__" << newline << set.artifacts[1] << "\n"
			  << "___Sand_____" << newline << set.artifacts[2] << "\n"
			  << "___Goblet___" << newline << set.artifacts[3] << "\n"
			  << "___Head_____" << newline << set.artifacts[4] << "\n"
			  << "____________" << newline << set.stats
			  << "*************************************************************************************************\n";
	return os;
}

std::vector<SetResult> list_sets_by_dmg(
  const Character& chara,
  const Weapon& weapon,
  const std::vector<Artifact>& arts,
  const Combo& combo,
  const Status& min_stats = Status{},
  void (*modifier)(Status&) = [](Status&) {}) {

	auto coll = collect_artifacts(arts);
	std::vector<SetResult> results;
	for (const auto& flower : coll.flowers)
		for (const auto& feather : coll.feathers)
			for (const auto& sand : coll.sands)
				for (const auto& goblet : coll.goblets)
					for (const auto& head : coll.heads) {
						Calc calc(chara, weapon, flower, feather, sand, goblet, head);
						const float avg_dmg = calc.avg_dmg(combo, modifier);
						if (has_min_stats(calc.status(), min_stats))
							results.push_back({ avg_dmg, calc.status(), { flower, feather, sand, goblet, head } });
					}

	std::sort(results.begin(), results.end(), [](const auto& lhs, const auto& rhs) { return lhs.dmg > rhs.dmg; });
	return results;
}

float best_set(
  const Character& chara,
  const Weapon& weapon,
  const std::vector<Artifact>& arts,
  const Combo& combo,
  const Status& min_stats = Status{},
  void (*modifier)(Status&) = [](Status&) {}) {
	const auto sets = list_sets_by_dmg(chara, weapon, arts, combo, min_stats, modifier);
	if (!sets.empty()) {
		std::cout << sets[0];
		return sets[0].dmg;
	}
	return 0.0;
}

void calc_Ayaka_team() {
	Ayaka ayaka;
	BlackSword black_sword;
	Mistsplitter mistsplitter{ 1 };
	Combo combo{ ayaka.get_hit(DmgTalent::Normal, 1) };

	auto best = [&](void (*modifier)(Status&)) {
		return best_set(ayaka, mistsplitter, AYAKA_ARTS, combo, Status{}, modifier);
	};

	const auto dmg = best(Calc::cryo_resonance_modifier);
	const auto dmg_shenhe = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.cryo_bonus += 10.0;
		stats.skill_bonus += 15.0;
		stats.burst_bonus += 15.0;
		stats.normal_bonus += 15.0;
		stats.charged_bonus += 15.0;
		// stats.additional_dmg += 1200.0;
	});
	const auto dmg_kokomi = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.atk_perc += 68.0;
	});
	const auto dmg_baal = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.burst_bonus += 0.29 * 80.0;
	});
	const auto dmg_ganyu = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.cryo_bonus += 20.0;
	});
	const auto dmg_kazuha = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.cryo_bonus += 0.04 * (3.0 * 187.0 + 115.0 + 165.0);
	});
	const auto team_baal = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.cryo_bonus += 20.0;
		stats.burst_bonus += 0.29 * 80.0;
		stats.atk_perc += 68.0; // TTDS + Millileth
	});
	const auto team_shenhe = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.cryo_bonus += 30.0;	// Ganyu + Shenhe
		stats.skill_bonus += 15.0;   // <Shenhe>
		stats.burst_bonus += 15.0;   //
		stats.normal_bonus += 15.0;  //
		stats.charged_bonus += 15.0; // </Shenhe>
		stats.atk_perc += 68.0;		 // TTDS + Millileth
	});
	const auto team_shenhe_kazuha = best([](Status& stats) {
		Calc::cryo_resonance_modifier(stats);
		stats.cryo_bonus += 10.0 + 0.04 * (3.0 * 187.0 + 115.0 + 165.0); // Shenhe + Kazuha
		stats.skill_bonus += 15.0;										 // <Shenhe>
		stats.burst_bonus += 15.0;										 //
		stats.normal_bonus += 15.0;										 //
		stats.charged_bonus += 15.0;									 // </Shenhe>
		stats.atk_perc += 68.0;											 // TTDS + Millileth
	});
	auto print_dmg_with_res = [&](const float& ENEMY_RES) {
		std::cout << "_____Enemy resistance: " << ENEMY_RES << "%_____\n"
				  << "Ayaka solo: " << Calc::dmg_dealt(dmg, 90, 90, 0.0, ENEMY_RES) << "\n"
				  << "with Kokomi: " << Calc::dmg_dealt(dmg_kokomi, 90, 90, 0.0, ENEMY_RES) << "\n"
				  << "with Baal: " << Calc::dmg_dealt(dmg_baal, 90, 90, 0.0, ENEMY_RES) << "\n"
				  << "with Ganyu: " << Calc::dmg_dealt(dmg_ganyu, 90, 90, 0.0, ENEMY_RES) << "\n"
				  << "with Kazuha: " << Calc::dmg_dealt(dmg_kazuha, 90, 90, 0.0, ENEMY_RES - 40.0) << "\n"
				  << "with Shenhe: " << Calc::dmg_dealt(dmg_shenhe, 90, 90, 0.0, ENEMY_RES - 14.0) << "\n"
				  << "Ayaka / Kokomi / Ganyu / Baal: " << Calc::dmg_dealt(team_baal, 90, 90, 0.0, ENEMY_RES) << "\n"
				  << "Ayaka / Kokomi / Ganyu / Shenhe: " << Calc::dmg_dealt(team_shenhe, 90, 90, 0.0, ENEMY_RES - 14.0) << "\n"
				  << "Ayaka / Kokomi / Kazuha / Shenhe: " << Calc::dmg_dealt(team_shenhe_kazuha, 90, 90, 0.0, ENEMY_RES - 54.0) << "\n";
	};
	print_dmg_with_res(10.0);
	print_dmg_with_res(50.0);
}

void calc_Ayaka_solo() {
	Ayaka ayaka;
	BlackSword black_sword;
	Mistsplitter mistsplitter;
	Combo combo{ ayaka.get_hit(DmgTalent::Normal, 3) };

	const auto dmg = best_set(ayaka, mistsplitter, AYAKA_ARTS, combo, Status{},
	  [](Status& stats) {
		  stats.atk_perc += 48.0 + 20.0;   // TTDS + Noblesse/Millileth
		  stats.cryo_bonus += 15.0 + 40.0; // Shenhe + Kazu
		  stats.burst_bonus += 15.0;	   // Shenhe
		  Calc::cryo_resonance_modifier(stats);
	  });
	std::cout << Calc::dmg_dealt(dmg, 90, 95, 0.0, -15.0) << std::endl;
}

void calc_Ayaka_potential() {
	Ayaka ayaka;
	Mistsplitter mistsplitter;
	Combo combo{ ayaka.get_hit(DmgTalent::Burst, 1) };

	auto blizz = SetType::BlizzardStrayer;
	const auto max_potential_dmg = find_max_potential(
	  ayaka, mistsplitter, combo,
	  blizz, blizz, blizz, blizz, blizz,
	  { Main::SandAtk }, { Main::GobletCryo, Main::GobletAtk }, { Main::HeadCDmg, Main::HeadCRate, Main::HeadAtk },
	  { StatusRoll::CRate,
		StatusRoll::CDmg,
		StatusRoll::AtkPerc,
		StatusRoll::Atk,
		StatusRoll::ER },
	  22, [](Status& stats) {
		  Calc::cryo_resonance_modifier(stats);
		  stats.cryo_bonus += 0.04 * (3.0 * 187.0 + 115.0 + 165.0) + 10.0; // Kazuha + <Shenhe>
		  stats.skill_bonus += 15.0;									   //
		  stats.burst_bonus += 15.0;									   //
		  stats.normal_bonus += 15.0;									   //
		  stats.charged_bonus += 15.0;									   // </Shenhe>
		  stats.atk_perc += 68.0;										   // TTDS + Millileth (Kokomi)
	  });
	std::cout << "outgoing: " << max_potential_dmg << "\n"
			  << "dealt: " << Calc::dmg_dealt(max_potential_dmg, 90, 100, 0, -30.0) << std::endl;
}

void calc_Baal() {
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

	const auto avg_dmg = best_set(baal, thecatch, BAAL_ARTS, combo);
	const auto dmg_dealt = Calc::dmg_dealt(avg_dmg, 81, 91, 0, 10);

	std::cout << dmg_dealt << std::endl;
}

void calc_Itto() {
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

	const auto avg_dmg = best_set(itto, whiteblind, ITTO_ARTS, combo, {},
	  [](Status& stats) {
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

void calc_Eula() {
	Eula eula;
	SnowtombedStarsilver starsilver;
	SerpentSpine serpentspine{ 1 };
	Combo burst_rotation{
		eula.get_hit(DmgTalent::Skill, 1),
		eula.get_hit(DmgTalent::Burst, 1),
		eula.get_hit(DmgTalent::Normal, 1),
		eula.get_hit(DmgTalent::Normal, 2),
		eula.get_hit(DmgTalent::Normal, 3),
		eula.get_hit(DmgTalent::Normal, 4),
		eula.get_hit(DmgTalent::Skill, 2),
		eula.get_hit(DmgTalent::Skill, 3),
		eula.get_hit(DmgTalent::Skill, 3),
		eula.get_hit(DmgTalent::Burst, 2),
		eula.get_hit(DmgTalent::Normal, 1),
		eula.get_hit(DmgTalent::Normal, 2),
		eula.get_hit(DmgTalent::Normal, 3),
		eula.get_hit(DmgTalent::Burst, 3)
	};
	Combo normal_atk{ eula.get_hit(DmgTalent::Normal, 1) };

	auto weapon_dmg = [&](Weapon& w) {
		return best_set(eula, w, EULA_ARTS, burst_rotation, {}, Calc::cryo_resonance_modifier);
	};
	auto dmg_dealt = [&](auto& dmg) {
		return Calc::dmg_dealt(dmg, 90, 90, 0, 10.0 + Eula::Resistance_down);
	};

	const auto dmg_starsilver = weapon_dmg(starsilver);
	const auto dealt_starsilver = dmg_dealt(dmg_starsilver);
	std::cout << "___Starsilver___\n"
			  << "raw: " << dmg_starsilver << ", dealt: " << dealt_starsilver << "\n"
			  << "___Serpent Spine___\n";

	for (unsigned stacks = 0; stacks <= 5; ++stacks) {
		serpentspine.stacks = stacks;
		const auto dmg_spine = weapon_dmg(serpentspine);
		const auto dealt = dmg_dealt(dmg_spine);
		std::cout << stacks << " stacks | raw: " << dmg_spine << ", dealt: " << dealt << "\n";
	}
}

void calc_HuTao() {
	constexpr static float SUCROSE_EM = 864.0;
	constexpr static int ENEMY_LVL = 95;
	constexpr static float ENEMY_RES = 10.0;

	const HuTao hutao;
	const Deathmatch deathmatch{ 1, true };
	Combo combo{
		hutao.get_hit(DmgTalent::Normal, 1),
		hutao.get_hit(DmgTalent::Charged, 1)
	};
	combo[1].reaction = Reaction::VapeByPyro;

	auto modifiers = [](Status& stats) {
		Calc::pyro_resonance_modifier(stats);
		stats.elem_mastery += 50.0 + 0.2 * SUCROSE_EM;
	};

	auto best_result = list_sets_by_dmg(hutao, deathmatch, HUTAO_ARTS, combo, Status{}, modifiers).at(0);
	std::cout << best_result
			  << "dealt (Sucrose + VV): " << Calc::dmg_dealt(best_result.dmg, 90, ENEMY_LVL, 0.0, ENEMY_RES - 40.0) << std::endl;
}

void calc_Yae() {
	constexpr static int ENEMY_LVL = 95;
	constexpr static float ENEMY_RES = 10.0;

	const YaeMiko yae;
	const LostPrayer lost_prayer;
	Widsith widsith{ 1 };
	widsith.Song = Widsith::ThemeSong::Recitative;

	Combo skill{
		yae.get_hit(DmgTalent::Skill, 3)
	};
	Combo burst{
		yae.get_hit(DmgTalent::Burst, 1),
		yae.get_hit(DmgTalent::Burst, 2),
		yae.get_hit(DmgTalent::Burst, 2),
		yae.get_hit(DmgTalent::Burst, 2)
	};
	Combo normal{
		yae.get_hit(DmgTalent::Normal, 1),
		yae.get_hit(DmgTalent::Normal, 2),
		yae.get_hit(DmgTalent::Normal, 3)
	};
	Combo charged{
		yae.get_hit(DmgTalent::Charged, 1)
	};
	auto avg_dmg = best_set(yae, lost_prayer, YAE_ARTS, skill, Status{},
	  [](Status& stats) {
		  //   stats.electro_bonus += 58; // Mona burst
		  //   stats.electro_bonus += 34.52; // Kazu C0
		  //   stats.electro_bonus += 42.52; // Kazu C2
		  //   stats.elem_mastery += 200; // Kazu C2
		  //   stats.flat_atk += 798; // Bennet C1
		  stats.flat_atk += 551; // Sara C1
								 //   stats.elem_mastery += 222; // Sucrose
								 //   stats.skill_bonus += 15;   // Shenhe
								 //   stats.atk_perc += 68; // Kokomi
	  });
	std::cout << "avg dmg: " << Calc::dmg_dealt(avg_dmg, 90, ENEMY_LVL, 0.0, ENEMY_RES) << std::endl;
}

}

int main() {
	using namespace GenshinCalc;
	calc_Ayaka_potential();
}
