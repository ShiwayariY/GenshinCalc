#include <cmath>
#include <exception>

#include <Artifact.hh>

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;

Artifact::Artifact(Main main, SetType set) :
		m_main{ main },
		m_type{ set } {
	set_main();
}

Artifact::Artifact(Main main, SetType set,
  std::pair<StatusRoll, float> stat1,
  std::pair<StatusRoll, float> stat2,
  std::pair<StatusRoll, float> stat3,
  std::pair<StatusRoll, float> stat4) :
		Artifact{ main, set } {
	for (const auto& [type, value] : { stat1, stat2, stat3, stat4 })
		m_status.add_roll(type, value);
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
		case SetType::PaleFlame:
			use_set_PaleFlame(stats, piece_count);
			break;
		case SetType::Millileth:
			use_set_Millileth(stats, piece_count);
			break;
		case SetType::Bloodstained:
			use_set_BloodstainedChivalry(stats, piece_count);
			break;
		case SetType::ThunderingFury:
			use_set_ThunderingFury(stats, piece_count);
			break;
		case SetType::Wanderer:
			use_set_Wanderer(stats, piece_count);
			break;
		case SetType::Venerer:
			use_set_Venerer(stats, piece_count);
			break;
		case SetType::Noblesse:
			use_set_Noblesse(stats, piece_count);
			break;

		default:
			throw std::logic_error{ "Artifact set not implemented" };
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

void Artifact::use_set_PaleFlame(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.phys_bonus += 25.0;
	if (piece_count >= 4) {
		stats.atk_perc += 18.0;
		stats.phys_bonus += 25.0;
	}
}

void Artifact::use_set_Millileth(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.hp_perc += 20.0;
	if (piece_count >= 4) stats.atk_perc += 20.0;
}

void Artifact::use_set_BloodstainedChivalry(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.phys_bonus += 25.0;
	if (piece_count >= 4) stats.charged_bonus += 50.0;
}

void Artifact::use_set_ThunderingFury(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.electro_bonus += 15.0;
	if (piece_count >= 4)
		throw std::logic_error{
			"ThunderingFury 4 set not implemented (transformative reactions not implemented)"
		};
}

void Artifact::use_set_Wanderer(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.elem_mastery += 80.0;
	if (piece_count >= 4) stats.charged_bonus += 35.0;
}

void Artifact::use_set_Venerer(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.anemo_bonus += 15.0;
	if (piece_count >= 4) throw std::logic_error{ "4 piece Venerer not implemented" };
}

void Artifact::use_set_Noblesse(Status& stats, int piece_count) {
	if (piece_count >= 2) stats.burst_bonus += 20.0;
	if (piece_count >= 4) throw std::logic_error{ "4 piece Noblesse not implemented" };
}

void Artifact::set_main() {
	switch (m_main) {
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

std::ostream& operator<<(std::ostream& os, const Artifact& a) {
	os << to_string(a.m_type) << "\n"
	   << a.status();
	return os;
}

}