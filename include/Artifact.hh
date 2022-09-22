#include <iostream>
#include <utility>
#include <map>

#include <Status.hh>

#ifndef GENSHINCALC_INCLUDE_ARTIFACT
#define GENSHINCALC_INCLUDE_ARTIFACT

namespace GenshinCalc {

class Artifact {
public:
	enum class Main {
		Flower,
		Feather,
		SandHP,
		SandAtk,
		SandDef,
		SandEM,
		SandER,
		GobletHP,
		GobletAtk,
		GobletDef,
		GobletEM,
		GobletPyro,
		GobletHydro,
		GobletCryo,
		GobletElectro,
		GobletAnemo,
		GobletGeo,
		GobletDendro,
		GobletPhys,
		HeadHP,
		HeadAtk,
		HeadDef,
		HeadCRate,
		HeadCDmg,
		HeadEM,
		HeadHealing
	};

	enum class SetType {
		Gladiator,
		WanderersTroupe,
		Noblesse,
		Bloodstained,
		Emblem,
		Shimenawa,
		HeartOfDepth,
		BlizzardStrayer,
		PaleFlame,
		Millileth,
		CrimsonWitch,
		Lavawalker,
		Venerer,
		Maiden,
		Bolide,
		ThunderingFury,
		Thundersoother,
		HuskOfOpulentDreams,
		OceanHuedClam,
		DeepwoodMemories,
		GildedDreams
	};

	Artifact(Main, SetType);

	Artifact(Main, SetType,
	  std::pair<StatusRoll, float>,
	  std::pair<StatusRoll, float>,
	  std::pair<StatusRoll, float>,
	  std::pair<StatusRoll, float>);

	static void apply_effects(Status&, SetType, int piece_count);

	Main main() const {
		return m_main;
	}
	SetType type() const {
		return m_type;
	}
	Status status() const {
		return m_status;
	}

	friend std::ostream& operator<<(std::ostream&, const Artifact&);

private:
	static void use_set_Gladiator(Status&, int piece_count);
	static void use_set_WanderersTroupe(Status&, int piece_count);
	static void use_set_Noblesse(Status&, int piece_count);
	static void use_set_BloodstainedChivalry(Status&, int piece_count);
	static void use_set_Emblem(Status&, int piece_count);
	static void use_set_Shimenawa(Status&, int piece_count);
	static void use_set_HeartOfDepth(Status&, int piece_count);
	static void use_set_BlizzardStrayer(Status&, int piece_count);
	static void use_set_PaleFlame(Status&, int piece_count);
	static void use_set_Millileth(Status&, int piece_count);
	static void use_set_Venerer(Status&, int piece_count);
	static void use_set_ThunderingFury(Status&, int piece_count);
	static void use_set_HuskOfOpulentDreams(Status&, int piece_count);
	static void use_set_DeepwoodMemories(Status&, int piece_count);
	static void use_set_GildedDreams(Status&, int piece_count);

	void set_main();

	const Main m_main;
	const SetType m_type;
	Status m_status;
};

std::ostream& operator<<(std::ostream&, const Artifact&);
inline std::string to_string(Artifact::SetType type) {
	static const std::map<Artifact::SetType, std::string> type_str{
		{ Artifact::SetType::Gladiator, "Gladiator's Finale" },
		{ Artifact::SetType::WanderersTroupe, "Wanderer's Troupe" },
		{ Artifact::SetType::Noblesse, "Noblesse Oblige" },
		{ Artifact::SetType::Bloodstained, "Bloodstained Chivalry" },
		{ Artifact::SetType::Emblem, "Emblem of Severed Fate" },
		{ Artifact::SetType::Shimenawa, "Shimenawa's Reminiscence" },
		{ Artifact::SetType::HeartOfDepth, "Heart of Depth" },
		{ Artifact::SetType::BlizzardStrayer, "Blizzard Strayer" },
		{ Artifact::SetType::PaleFlame, "Pale Flame" },
		{ Artifact::SetType::Millileth, "Tenacity of the Millelith" },
		{ Artifact::SetType::CrimsonWitch, "Crimson Witch of Flames" },
		{ Artifact::SetType::Lavawalker, "Lavawalker" },
		{ Artifact::SetType::Venerer, "Viridescent Venerer" },
		{ Artifact::SetType::Maiden, "Maiden Beloved" },
		{ Artifact::SetType::Bolide, "Retracing Bolide" },
		{ Artifact::SetType::ThunderingFury, "Thundering Fury" },
		{ Artifact::SetType::Thundersoother, "Thundersoother" },
		{ Artifact::SetType::HuskOfOpulentDreams, "Husk of Opulent Dreams" },
		{ Artifact::SetType::OceanHuedClam, "Ocean-Hued Clam" },
		{ Artifact::SetType::DeepwoodMemories, "Deepwood Memories" },
		{ Artifact::SetType::GildedDreams, "Gilded Dreams" }
	};
	return type_str.at(type);
}

}

#endif