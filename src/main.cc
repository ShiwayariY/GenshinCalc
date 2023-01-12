
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
		   && stats.dendro_bonus >= min.dendro_bonus	   //
		   && stats.phys_bonus >= min.phys_bonus		   //
		   && stats.normal_bonus >= min.normal_bonus	   //
		   && stats.charged_bonus >= min.charged_bonus	 //
		   && stats.plunge_bonus >= min.plunge_bonus	   //
		   && stats.skill_bonus >= min.skill_bonus		   //
		   && stats.burst_bonus >= min.burst_bonus		   //
		   && stats.reaction_bonus >= min.reaction_bonus   //
		   && stats.additional_dmg >= min.additional_dmg;
}

struct MainStats {
	Main sand = Main::SandAtk;
	Main goblet = Main::GobletAtk;
	Main circlet = Main::HeadAtk;
};

std::ostream& operator<<(std::ostream& os, const MainStats& mains) {
	std::cout << to_string(mains.sand) << ", "
			  << to_string(mains.goblet) << ", "
			  << to_string(mains.circlet);
			  return os;
}

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
  StatusGenerator::Quality quality = StatusGenerator::Quality::BEST,
  const DmgContext& context = {},
  Status min_stats = {},
  void (*modifier)(Status&) = [](Status&) {}) {

	float best_dmg = 0.0;
	Status best_stats;

	Artifact dummy_flower{ Main::Flower, flower_set };
	Artifact dummy_feather{ Main::Feather, feather_set };

	std::cout << "Checking stat combinations ...\n"
			  << std::left << std::setw(10) << "Main"
			  << "Sub [million]\n";
	unsigned iteration_main = 0;

	MainStats chosen_mains;
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
				gen.set_quality(quality);

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

					auto applied_dmg = calc.avg_dmg(combo, context.char_level,
					  [&curr_stats, &modifier](Status& stats) {
						  stats = stats + curr_stats;
						  modifier(stats);
					  });

					auto dealt_dmg = Calc::dmg_dealt(applied_dmg, context);
					const auto tot_stats = calc.status();
					if (has_min_stats(tot_stats, min_stats) && dealt_dmg > best_dmg) {
						best_dmg = dealt_dmg;
						best_stats = tot_stats;
						chosen_mains.sand = sands_main;
						chosen_mains.goblet = goblet_main;
						chosen_mains.circlet = circlet_main;
					}
				} while (gen.next());
			}
		}
	}

	std::cout << "\n"
			  << chosen_mains << "\n"
			  << best_stats << std::endl;
	return best_dmg;
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
  const DmgContext& context = {},
  const Status& min_stats = {},
  void (*modifier)(Status&) = [](Status&) {}) {

	auto coll = collect_artifacts(arts);
	std::vector<SetResult> results;
	for (const auto& flower : coll.flowers)
		for (const auto& feather : coll.feathers)
			for (const auto& sand : coll.sands)
				for (const auto& goblet : coll.goblets)
					for (const auto& head : coll.heads) {
						Calc calc(chara, weapon, flower, feather, sand, goblet, head);
						const auto avg_dmg = Calc::dmg_dealt(calc.avg_dmg(combo, context.char_level, modifier), context);

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
  const DmgContext& context = {},
  const Status& min_stats = {},
  void (*modifier)(Status&) = [](Status&) {},
  bool print = true) {
	const auto sets = list_sets_by_dmg(chara, weapon, arts, combo, context, min_stats, modifier);
	if (!sets.empty()) {
		if (print) std::cout << sets[0];
		return sets[0].dmg;
	}
	return 0.0;
}

void Nilou_potential() {
	Nilou nilou;
	IronSting weapon{ 5 };
	DmgContext context{
		.char_level = 90,
		.enemy_level = 100,
		.def_reduction_perc = 0.0,
		.res_perc = {
		  { DmgElement::Hydro, 10.0 },
		  { DmgElement::Dendro, -20.0 } }
	};
	Combo combo{
		nilou.get_hit(DmgTalent::Skill, 1),
		nilou.get_hit(DmgTalent::Skill, 2),
		nilou.get_hit(DmgTalent::Skill, 3),
		nilou.get_hit(DmgTalent::Skill, 4),
		nilou.get_hit(DmgTalent::Skill, 2),
		nilou.get_hit(DmgTalent::Skill, 3),
		nilou.get_hit(DmgTalent::Skill, 4),
		nilou.get_hit(DmgTalent::Skill, 2),
		nilou.get_hit(DmgTalent::Skill, 3),
		nilou.get_hit(DmgTalent::Skill, 4),
		nilou.get_hit(DmgTalent::Burst, 1),
		nilou.get_hit(DmgTalent::Burst, 2),
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
		TrafoReaction::Bloom,
	};
	auto max_dmg = find_max_potential(
	  nilou, weapon, combo,
	  SetType::Millileth, SetType::Millileth, SetType::Millileth,
	  SetType::WanderersTroupe, SetType::WanderersTroupe,
	  { Main::SandHP, Main::SandEM },
	  { Main::GobletHydro, Main::GobletHP, Main::GobletEM },
	  { Main::HeadHP, Main::HeadEM, Main::HeadCRate, Main::HeadCDmg },
	  { StatusRoll::HPPerc, StatusRoll::HP, StatusRoll::CRate, StatusRoll::CDmg, StatusRoll::EM },
	  25, StatusGenerator::Quality::AVERAGE, context, {},
	  [](Status& stats) {
		  Calc::dendro_resonance_modifier(stats);
		  Calc::hydro_resonance_modifier(stats);
	  });
	std::cout << "Combo dmg: " << max_dmg << std::endl;
}

void Raiden_potential() {
	Baal raiden;
	TheCatch thecatch;
	DmgContext context{
		.char_level = 90,
		.enemy_level = 100,
		.def_reduction_perc = 0.0,
		.res_perc = { { DmgElement::Electro, -15.0 } }
	};
	Combo combo {
		raiden.get_hit(DmgTalent::Burst, 1),
		raiden.get_hit(DmgTalent::Burst, 2),
		raiden.get_hit(DmgTalent::Burst, 3),
		raiden.get_hit(DmgTalent::Burst, 4),
		raiden.get_hit(DmgTalent::Burst, 7),
		raiden.get_hit(DmgTalent::Burst, 1),
		raiden.get_hit(DmgTalent::Burst, 2),
		raiden.get_hit(DmgTalent::Burst, 3),
		raiden.get_hit(DmgTalent::Burst, 4),
		raiden.get_hit(DmgTalent::Burst, 7),
		raiden.get_hit(DmgTalent::Burst, 1),
		raiden.get_hit(DmgTalent::Burst, 2),
		raiden.get_hit(DmgTalent::Burst, 3),
		raiden.get_hit(DmgTalent::Burst, 4),
		raiden.get_hit(DmgTalent::Burst, 7)
	};
	auto max_dmg = find_max_potential(
		raiden, thecatch, combo,
		SetType::Emblem, SetType::Emblem, SetType::Emblem, SetType::Emblem, SetType::Emblem,
		{Main::SandER},
		{Main::GobletElectro},
		{Main::HeadCDmg, Main::HeadCRate},
		{StatusRoll::CRate, StatusRoll::CDmg, StatusRoll::AtkPerc, StatusRoll::ER, StatusRoll::Atk},
		25, StatusGenerator::Quality::AVERAGE, context, { .energy_recharge = 250.0 },
		[](Status&){
			// s.flat_atk += 1000.0f;
	});
	std::cout << "Combo dmg: " << max_dmg << std::endl
		<< max_dmg / 656134.0f << std::endl;
}

void Yae_potential() {
	YaeMiko yae;
	KagurasVerity kagura;
	DmgContext context {
		.char_level = 90,
		.enemy_level = 100,
		.def_reduction_perc = 0.0,
		.res_perc = { { DmgElement::Electro, -15.0 } }
	};

	auto skill_aggr = yae.get_hit(DmgTalent::Skill, 3);
	skill_aggr.reaction = AmplifyReaction::Aggravate;
	auto burst_init = yae.get_hit(DmgTalent::Burst, 1);
	burst_init.reaction = AmplifyReaction::Aggravate;
	auto burst_extra = yae.get_hit(DmgTalent::Burst, 2);
	burst_extra.reaction = AmplifyReaction::Aggravate;

	Combo combo {
		yae.get_hit(DmgTalent::Skill, 3),
		yae.get_hit(DmgTalent::Skill, 3),
		skill_aggr,
		yae.get_hit(DmgTalent::Skill, 3),
		yae.get_hit(DmgTalent::Skill, 3),
		skill_aggr,
		yae.get_hit(DmgTalent::Skill, 3),
		yae.get_hit(DmgTalent::Skill, 3),
		skill_aggr,
		yae.get_hit(DmgTalent::Skill, 3),
		yae.get_hit(DmgTalent::Skill, 3),
		skill_aggr,
		yae.get_hit(DmgTalent::Skill, 3),
		yae.get_hit(DmgTalent::Skill, 3),
		skill_aggr,
		burst_init,
		burst_extra,
		burst_extra,
		burst_extra
	};
	auto max_dmg = find_max_potential(
		yae, kagura, combo,
		SetType::GildedDreams, SetType::GildedDreams, SetType::GildedDreams, SetType::GildedDreams, SetType::GildedDreams,
		{Main::SandEM},
		{Main::GobletEM},
		{Main::HeadEM},
		{StatusRoll::CRate, StatusRoll::CDmg, StatusRoll::AtkPerc, StatusRoll::EM, StatusRoll::Atk},
		25, StatusGenerator::Quality::AVERAGE, context, { .energy_recharge = 100.0 },
		[](Status& s) {
			s.electro_bonus += 40.0f; // Kazuha
			s.elem_mastery += 0.002f * 30000.0f + 40.0f; // Kuki Key 30k HP + Nahida Thousand Floating Dreams
			// s.flat_atk += 1000.0f;
	});
	std::cout << "Combo dmg: " << max_dmg << std::endl;
}

}

int main() {
	using namespace GenshinCalc;
	Yae_potential();
}
