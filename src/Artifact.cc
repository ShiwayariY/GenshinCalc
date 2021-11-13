#include <cmath>

#include <Artifact.hh>

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;
using StatusRoll = Artifact::StatusRoll;

Artifact::Artifact(Main main, SetType set,
  std::pair<StatusRoll, float> stat1,
  std::pair<StatusRoll, float> stat2,
  std::pair<StatusRoll, float> stat3,
  std::pair<StatusRoll, float> stat4) :
		m_type{ set } {
	set_main(main);
	for (const auto& [type, value] : { stat1, stat2, stat3, stat4 })
		add_status(type, value);
}

void Artifact::apply_effects(Status& stats, SetType type, int piece_count) {
	switch (type) {
		case SetType::Gladiator:
			use_set_Gladiator(stats, piece_count);
			break;
		case SetType::BlizzardStrayer:
			use_set_BlizzardStrayer(stats, piece_count);
			break;
		case SetType::HeartOfDepth:
			use_set_HeartOfDepth(stats, piece_count);
			break;
		case SetType::Emblem:
			use_set_Emblem(stats, piece_count);
			break;
		case SetType::Shimenawa:
			use_set_Shimenawa(stats, piece_count);
			break;
		case SetType::HuskOfOpulentDreams:
			use_set_HuskOfOpulentDreams(stats, piece_count);
			break;

		default:
			throw "NOT IMPLEMENTED";
	}
}

void Artifact::use_set_Gladiator(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.atk_perc += 18.0;
	if (piece_count >= 4) stats.normal_bonus += 35.0;
}

void Artifact::use_set_WanderersTroupe(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.elem_mastery += 80;
	if (piece_count >= 4) stats.charged_bonus += 35.0;
}

void Artifact::use_set_BlizzardStrayer(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.cryo_bonus += 15.0;
	if (piece_count >= 4) stats.crit_rate += 40.0;
}

void Artifact::use_set_HeartOfDepth(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.hydro_bonus += 15.0;
	if (piece_count >= 4) {
		stats.normal_bonus += 30.0;
		stats.charged_bonus += 30.0;
	}
}

void Artifact::use_set_Emblem(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.energy_recharge += 20.0;
	if (piece_count >= 4) stats.burst_bonus += std::min(75.0, 0.25 * stats.energy_recharge);
}

void Artifact::use_set_Shimenawa(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.atk_perc += 18.0;
	if (piece_count >= 4) {
		stats.normal_bonus += 50.0;
		stats.charged_bonus += 50.0;
		stats.plunge_bonus += 50.0;
	}
}

void Artifact::use_set_HuskOfOpulentDreams(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.def_perc += 30.0;
	if (piece_count >= 4) {
		stats.def_perc += 24.0;
		stats.geo_bonus += 24.0;
	}
}

void Artifact::set_main(Main main) {
	switch (main) {
		case Main::Flower:
			m_status.flat_hp = 4780.0;
			break;

		case Main::Feather:
			m_status.flat_atk = 311.0;
			break;

		case Main::SandHP:
			m_status.hp_perc = 46.6;
			break;
		case Main::SandAtk:
			m_status.atk_perc = 46.6;
			break;
		case Main::SandDef:
			m_status.def_perc = 58.3;
			break;
		case Main::SandEM:
			m_status.elem_mastery = 186.5;
			break;
		case Main::SandER:
			m_status.energy_recharge = 51.8;
			break;

		case Main::GobletHP:
			m_status.hp_perc = 46.6;
			break;
		case Main::GobletAtk:
			m_status.atk_perc = 46.6;
			break;
		case Main::GobletDef:
			m_status.def_perc = 58.3;
			break;
		case Main::GobletEM:
			m_status.elem_mastery = 186.5;
			break;
		case Main::GobletPyro:
			m_status.pyro_bonus = 46.6;
			break;
		case Main::GobletHydro:
			m_status.hydro_bonus = 46.6;
			break;
		case Main::GobletCryo:
			m_status.cryo_bonus = 46.6;
			break;
		case Main::GobletElectro:
			m_status.electro_bonus = 46.6;
			break;
		case Main::GobletAnemo:
			m_status.anemo_bonus = 46.6;
			break;
		case Main::GobletGeo:
			m_status.geo_bonus = 46.6;
			break;
		case Main::GobletPhys:
			m_status.geo_bonus = 58.3;
			break;

		case Main::HeadHP:
			m_status.hp_perc = 46.6;
			break;
		case Main::HeadAtk:
			m_status.atk_perc = 46.6;
			break;
		case Main::HeadDef:
			m_status.def_perc = 58.3;
			break;
		case Main::HeadEM:
			m_status.elem_mastery = 186.5;
			break;
		case Main::HeadCRate:
			m_status.crit_rate = 31.1;
			break;
		case Main::HeadCDmg:
			m_status.crit_dmg = 62.2;
			break;
		case Main::HeadHealing:
			m_status.healing_bonus = 35.9;
			break;
	}
}

void Artifact::add_status(StatusRoll type, float value) {
	switch (type) {
		case StatusRoll::HP:
			m_status.flat_hp += value;
			break;
		case StatusRoll::HPPerc:
			m_status.hp_perc += value;
			break;
		case StatusRoll::Atk:
			m_status.flat_atk += value;
			break;
		case StatusRoll::AtkPerc:
			m_status.atk_perc += value;
			break;
		case StatusRoll::Def:
			m_status.flat_def += value;
			break;
		case StatusRoll::DefPerc:
			m_status.def_perc += value;
			break;
		case StatusRoll::CRate:
			m_status.crit_rate += value;
			break;
		case StatusRoll::CDmg:
			m_status.crit_dmg += value;
			break;
		case StatusRoll::EM:
			m_status.elem_mastery += value;
			break;
		case StatusRoll::ER:
			m_status.energy_recharge += value;
			break;
	}
}

}