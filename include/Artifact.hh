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
		ThunderingFury
	};

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

	Artifact(Main, SetType,
	  std::pair<StatusRoll, float>,
	  std::pair<StatusRoll, float>,
	  std::pair<StatusRoll, float>,
	  std::pair<StatusRoll, float>);

	static void apply_effects(Status&, SetType, int piece_count);

	SetType type() const {
		return m_type;
	}
	Status status() const {
		return m_status;
	}

private:
	static void use_set_Gladiator(Status&, int piece_count);
	static void use_set_BlizzardStrayer(Status&, int piece_count);
	static void use_set_Emblem(Status&, int piece_count);
	static void use_set_Shimenawa(Status&, int piece_count);

	void set_main(Main);
	void add_status(StatusRoll, float value);

	Status m_status;
	SetType m_type;
};

}

#endif