#include <iostream>
#include <utility>

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
		Wanderer,
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
		OceanHuedClam
	};


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
	static void use_set_BlizzardStrayer(Status&, int piece_count);
	static void use_set_HeartOfDepth(Status&, int piece_count);
	static void use_set_Emblem(Status&, int piece_count);
	static void use_set_Shimenawa(Status&, int piece_count);
	static void use_set_HuskOfOpulentDreams(Status&, int piece_count);
	static void use_set_PaleFlame(Status&, int piece_count);
	static void use_set_Millileth(Status&, int piece_count);
	static void use_set_BloodstainedChivalry(Status&, int piece_count);
	static void use_set_ThunderingFury(Status&, int piece_count);
	static void use_set_Wanderer(Status&, int piece_count);

	void set_main();

	const Main m_main;
	const SetType m_type;
	Status m_status;
};

std::ostream& operator<<(std::ostream&, const Artifact&);

}

#endif