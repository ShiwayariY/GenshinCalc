#include <Artifact.hh>

#ifndef GENSHINCALC_INCLUDE_ARTIFACT_CONSTANTS
#define GENSHINCALC_INCLUDE_ARTIFACT_CONSTANTS

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;

const std::vector<Artifact> AYAKA_ARTS{
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 6.6 },
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::DefPerc, 10.2 },
	  { StatusRoll::CDmg, 21.8 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 11.3 },
	  { StatusRoll::EM, 93.0 },
	  { StatusRoll::CDmg, 7.0 },
	  { StatusRoll::HPPerc, 5.3 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::Def, 37.0 },
	  { StatusRoll::AtkPerc, 15.2 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::CRate, 7.4 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 6.6 },
	  { StatusRoll::HPPerc, 8.7 },
	  { StatusRoll::ER, 17.5 },
	  { StatusRoll::AtkPerc, 5.3 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 10.9 },
	  { StatusRoll::CDmg, 7.0 },
	  { StatusRoll::AtkPerc, 14.6 },
	  { StatusRoll::Def, 19.0 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::AtkPerc, 9.3 },
	  { StatusRoll::EM, 21.0 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::CDmg, 25.7 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::AtkPerc, 10.5 },
	  { StatusRoll::CRate, 5.8 },
	  { StatusRoll::Atk, 33.0 },
	  { StatusRoll::CDmg, 11.7 } },
	{ Main::Flower, SetType::BlizzardStrayer,
	  { StatusRoll::CDmg, 6.2 },
	  { StatusRoll::CRate, 10.9 },
	  { StatusRoll::Atk, 49.0 },
	  { StatusRoll::AtkPerc, 5.3 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::ER, 22.7 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::CRate, 7.0 },
	  { StatusRoll::CDmg, 7.8 } },

	{ Main::Feather, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 10.9 },
	  { StatusRoll::ER, 11.7 },
	  { StatusRoll::EM, 65.0 },
	  { StatusRoll::HPPerc, 4.7 } },
	{ Main::Feather, SetType::BlizzardStrayer,
	  { StatusRoll::AtkPerc, 5.3 },
	  { StatusRoll::CRate, 7.4 },
	  { StatusRoll::Def, 35.0 },
	  { StatusRoll::CDmg, 20.2 } },
	{ Main::Feather, SetType::BlizzardStrayer,
	  { StatusRoll::HP, 239.0 },
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::CRate, 10.5 },
	  { StatusRoll::CDmg, 19.4 } },
	{ Main::Feather, SetType::BlizzardStrayer,
	  { StatusRoll::CDmg, 14.0 },
	  { StatusRoll::ER, 13.0 },
	  { StatusRoll::AtkPerc, 10.5 },
	  { StatusRoll::CRate, 6.2 } },
	{ Main::Feather, SetType::BlizzardStrayer,
	  { StatusRoll::Def, 39.0 },
	  { StatusRoll::ER, 14.9 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::CRate, 7.0 } },

	{ Main::SandAtk, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 9.3 },
	  { StatusRoll::HPPerc, 10.5 },
	  { StatusRoll::CDmg, 14.8 },
	  { StatusRoll::HP, 568.0 } },
	{ Main::SandAtk, SetType::BlizzardStrayer,
	  { StatusRoll::Def, 15.0 },
	  { StatusRoll::ER, 15.5 },
	  { StatusRoll::Atk, 47.0 },
	  { StatusRoll::CDmg, 7.8 } },
	{ Main::SandAtk, SetType::BlizzardStrayer,
	  { StatusRoll::CDmg, 14.0 },
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::Atk, 29.0 },
	  { StatusRoll::DefPerc, 13.1 } },
	{ Main::SandAtk, SetType::BlizzardStrayer,
	  { StatusRoll::HPPerc, 9.3 },
	  { StatusRoll::ER, 11.7 },
	  { StatusRoll::CRate, 10.1 },
	  { StatusRoll::EM, 21.0 } },
	{ Main::SandAtk, SetType::Gladiator,
	  { StatusRoll::CDmg, 7.0 },
	  { StatusRoll::DefPerc, 12.4 },
	  { StatusRoll::ER, 22.7 },
	  { StatusRoll::EM, 19.0 } },

	{ Main::GobletCryo, SetType::BlizzardStrayer,
	  { StatusRoll::Atk, 68.0 },
	  { StatusRoll::ER, 5.2 },
	  { StatusRoll::AtkPerc, 5.3 },
	  { StatusRoll::Def, 17.5 } },
	{ Main::GobletCryo, SetType::HuskOfOpulentDreams,
	  { StatusRoll::CRate, 6.2 },
	  { StatusRoll::Atk, 14.0 },
	  { StatusRoll::EM, 54.0 },
	  { StatusRoll::AtkPerc, 9.9 } },
	{ Main::GobletCryo, SetType::Millileth,
	  { StatusRoll::ER, 23.3 },
	  { StatusRoll::HP, 209.0 },
	  { StatusRoll::CDmg, 5.4 },
	  { StatusRoll::Def, 32.0 } },
	{ Main::GobletCryo, SetType::Venerer,
	  { StatusRoll::AtkPerc, 12.8 },
	  { StatusRoll::Atk, 19.0 },
	  { StatusRoll::HP, 239.0 },
	  { StatusRoll::CRate, 9.3 } },
	{ Main::GobletCryo, SetType::Gladiator,
	  { StatusRoll::Def, 19.0 },
	  { StatusRoll::CRate, 8.6 },
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::AtkPerc, 9.3 } },

	{ Main::HeadCDmg, SetType::BlizzardStrayer,
	  { StatusRoll::CRate, 10.1 },
	  { StatusRoll::HP, 209.0 },
	  { StatusRoll::Atk, 53.0 },
	  { StatusRoll::DefPerc, 12.4 } },
	// { Main::HeadCDmg, SetType::BlizzardStrayer,
	//   { StatusRoll::AtkPerc, 14.6 },
	//   { StatusRoll::CRate, 7.4 },
	//   { StatusRoll::HP, 448.0 },
	//   { StatusRoll::HPPerc, 4.1 } },
	{ Main::HeadCDmg, SetType::BlizzardStrayer,
	  { StatusRoll::EM, 40.0 },
	  { StatusRoll::AtkPerc, 8.2 },
	  { StatusRoll::Atk, 53.0 },
	  { StatusRoll::ER, 5.2 } },
	{ Main::HeadCDmg, SetType::Wanderer,
	  { StatusRoll::AtkPerc, 21.6 },
	  { StatusRoll::HP, 239.0 },
	  { StatusRoll::EM, 21.0 },
	  { StatusRoll::Def, 65.0 } },
	{ Main::HeadCDmg, SetType::Emblem,
	  { StatusRoll::Atk, 35.0 },
	  { StatusRoll::HP, 717.0 },
	  { StatusRoll::CRate, 2.7 },
	  { StatusRoll::AtkPerc, 10.5 } },
	{ Main::HeadCDmg, SetType::HeartOfDepth,
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::HP, 866.0 },
	  { StatusRoll::AtkPerc, 8.7 },
	  { StatusRoll::DefPerc, 11.7 } }

};

const std::vector<Artifact> HUTAO_ARTS{
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::CRate, 6.2 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::HPPerc, 14.0 },
	  { StatusRoll::CDmg, 11.7 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::AtkPerc, 9.9 },
	  { StatusRoll::CDmg, 28.7 },
	  { StatusRoll::EM, 21 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::Def, 42 },
	  { StatusRoll::CRate, 7.0 },
	  { StatusRoll::EM, 33 },
	  { StatusRoll::CDmg, 14.0 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::EM, 21.0 },
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::CRate, 15.2 },
	  { StatusRoll::HPPerc, 5.8 } },

	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::EM, 54 },
	  { StatusRoll::CDmg, 14.0 },
	  { StatusRoll::HPPerc, 5.3 },
	  { StatusRoll::CRate, 10.1 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::EM, 19 },
	  { StatusRoll::CDmg, 14.0 },
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::CRate, 13.6 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::DefPerc, 5.8 },
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::CDmg, 21.8 },
	  { StatusRoll::HPPerc, 4.1 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::EM, 23 },
	  { StatusRoll::DefPerc, 20.4 },
	  { StatusRoll::CDmg, 14.0 },
	  { StatusRoll::AtkPerc, 11.1 } },

	{ Main::SandHP, SetType::Shimenawa,
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::HP, 866 },
	  { StatusRoll::Def, 19 },
	  { StatusRoll::ER, 17.5 } },
	{ Main::SandHP, SetType::HeartOfDepth,
	  { StatusRoll::CDmg, 15.5 },
	  { StatusRoll::CRate, 9.3 },
	  { StatusRoll::HP, 478 },
	  { StatusRoll::EM, 16 } },

	{ Main::GobletPyro, SetType::HeartOfDepth,
	  { StatusRoll::HPPerc, 5.3 },
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::CDmg, 20.2 },
	  { StatusRoll::EM, 58 } },
	{ Main::GobletPyro, SetType::Shimenawa,
	  { StatusRoll::CDmg, 21.0 },
	  { StatusRoll::HPPerc, 10.5 },
	  { StatusRoll::Def, 19 },
	  { StatusRoll::CRate, 6.6 } },

	{ Main::HeadCDmg, SetType::Shimenawa,
	  { StatusRoll::HPPerc, 14.0 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::EM, 40 },
	  { StatusRoll::CRate, 5.4 } },
	{ Main::HeadCRate, SetType::Shimenawa,
	  { StatusRoll::ER, 16.2 },
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::CDmg, 5.4 },
	  { StatusRoll::HP, 239 } },
	{ Main::HeadCRate, SetType::Shimenawa,
	  { StatusRoll::HP, 478 },
	  { StatusRoll::Def, 56 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::CDmg, 14.0 } }
};

const std::vector<Artifact> EULA_ARTS = {
	{ Main::Flower, SetType::PaleFlame,
	  { StatusRoll::Def, 46 },
	  { StatusRoll::ER, 9.7 },
	  { StatusRoll::CRate, 14.0 },
	  { StatusRoll::EM, 23 } },
	{ Main::Flower, SetType::PaleFlame,
	  { StatusRoll::DefPerc, 10.9 },
	  { StatusRoll::CDmg, 13.2 },
	  { StatusRoll::ER, 16.2 },
	  { StatusRoll::Atk, 19 } },
	{ Main::Feather, SetType::PaleFlame,
	  { StatusRoll::Def, 42 },
	  { StatusRoll::CDmg, 5.4 },
	  { StatusRoll::CRate, 13.2 },
	  { StatusRoll::HP, 269 } },
	{ Main::SandAtk, SetType::PaleFlame,
	  { StatusRoll::EM, 35 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::Atk, 31 },
	  { StatusRoll::CDmg, 17.1 } },
	{ Main::SandAtk, SetType::PaleFlame,
	  { StatusRoll::CRate, 3.5 },
	  { StatusRoll::CDmg, 7.8 },
	  { StatusRoll::HP, 568 },
	  { StatusRoll::Def, 83 } },
	{ Main::SandAtk, SetType::PaleFlame,
	  { StatusRoll::HP, 299 },
	  { StatusRoll::EM, 56 },
	  { StatusRoll::CRate, 8.6 },
	  { StatusRoll::Atk, 14 } },
	{ Main::GobletPhys, SetType::Millileth,
	  { StatusRoll::AtkPerc, 10.5 },
	  { StatusRoll::ER, 16.8 },
	  { StatusRoll::Def, 19 },
	  { StatusRoll::CRate, 6.2 } },
	{ Main::GobletPhys, SetType::Millileth,
	  { StatusRoll::CDmg, 12.4 },
	  { StatusRoll::ER, 21.4 },
	  { StatusRoll::HP, 299 },
	  { StatusRoll::Def, 19 } },
	{ Main::HeadCRate, SetType::PaleFlame,
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::HPPerc, 4.1 },
	  { StatusRoll::DefPerc, 5.8 },
	  { StatusRoll::CDmg, 28.0 } }
};

const std::vector<Artifact> YAE_ARTS{
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::AtkPerc, 9.9 },
	  { StatusRoll::CDmg, 28.7 },
	  { StatusRoll::EM, 21 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::Def, 51 },
	  { StatusRoll::CRate, 7.0 },
	  { StatusRoll::EM, 35 },
	  { StatusRoll::CDmg, 7.0 } },
	{ Main::Flower, SetType::Gladiator,
	  { StatusRoll::CRate, 2.7 },
	  { StatusRoll::CDmg, 22.5 },
	  { StatusRoll::DefPerc, 19.0 },
	  { StatusRoll::Atk, 19 } },
	{ Main::Flower, SetType::ThunderingFury,
	  { StatusRoll::HPPerc, 9.3 },
	  { StatusRoll::CRate, 10.5 },
	  { StatusRoll::CDmg, 13.2 },
	  { StatusRoll::DefPerc, 13.9 } },
	{ Main::Feather, SetType::Gladiator,
	  { StatusRoll::DefPerc, 12.4 },
	  { StatusRoll::CRate, 17.1 },
	  { StatusRoll::EM, 16 },
	  { StatusRoll::CDmg, 6.2 } },
	{ Main::Feather, SetType::Gladiator,
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::CRate, 2.7 },
	  { StatusRoll::CDmg, 12.4 },
	  { StatusRoll::HP, 837 } },
	{ Main::Feather, SetType::Gladiator,
	  { StatusRoll::CRate, 6.6 },
	  { StatusRoll::AtkPerc, 9.9 },
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::HP, 508 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::EM, 19 },
	  { StatusRoll::CDmg, 14.0 },
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::CRate, 13.6 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::DefPerc, 5.8 },
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::CDmg, 21.8 },
	  { StatusRoll::HPPerc, 4.1 } },
	{ Main::SandAtk, SetType::Shimenawa,
	  { StatusRoll::Atk, 19 },
	  { StatusRoll::HP, 807 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::CRate, 9.3 } },
	{ Main::SandAtk, SetType::Gladiator,
	  { StatusRoll::Def, 16 },
	  { StatusRoll::CDmg, 21.0 },
	  { StatusRoll::Atk, 64 },
	  { StatusRoll::ER, 5.2 } },
	{ Main::SandAtk, SetType::Gladiator,
	  { StatusRoll::EM, 35 },
	  { StatusRoll::ER, 6.5 },
	  { StatusRoll::Def, 42 },
	  { StatusRoll::CDmg, 27.2 } },
	{ Main::SandAtk, SetType::ThunderingFury,
	  { StatusRoll::HP, 478 },
	  { StatusRoll::HPPerc, 11.7 },
	  { StatusRoll::CRate, 6.2 },
	  { StatusRoll::ER, 11.0 } },
	{ Main::GobletElectro, SetType::HeartOfDepth,
	  { StatusRoll::CRate, 3.1 },
	  { StatusRoll::Atk, 66 },
	  { StatusRoll::ER, 14.9 },
	  { StatusRoll::EM, 21 } },
	{ Main::GobletElectro, SetType::Wanderer,
	  { StatusRoll::HP, 568 },
	  { StatusRoll::DefPerc, 11.7 },
	  { StatusRoll::ER, 12.3 },
	  { StatusRoll::CDmg, 14.0 } },
	{ Main::HeadCRate, SetType::Shimenawa,
	  { StatusRoll::ER, 16.2 },
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::CDmg, 5.4 },
	  { StatusRoll::HP, 239 } },
	{ Main::HeadCDmg, SetType::Gladiator,
	  { StatusRoll::EM, 40 },
	  { StatusRoll::AtkPerc, 9.3 },
	  { StatusRoll::Atk, 19 },
	  { StatusRoll::ER, 14.9 } },
	{ Main::HeadCRate, SetType::Gladiator,
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::Atk, 16 },
	  { StatusRoll::Def, 44 },
	  { StatusRoll::HP, 747 } },
	{ Main::HeadCRate, SetType::Gladiator,
	  { StatusRoll::HPPerc, 9.3 },
	  { StatusRoll::CDmg, 18.7 },
	  { StatusRoll::Def, 42 },
	  { StatusRoll::Atk, 18 } }
};

const std::vector<Artifact> BAAL_ARTS{
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::Atk, 16 },
	  { StatusRoll::CRate, 3.5 },
	  { StatusRoll::CDmg, 32.6 },
	  { StatusRoll::AtkPerc, 5.8 } },
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::Atk, 49 },
	  { StatusRoll::Def, 23 },
	  { StatusRoll::CDmg, 23.3 },
	  { StatusRoll::CRate, 3.5 } },
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::HPPerc, 5.3 },
	  { StatusRoll::AtkPerc, 16.9 },
	  { StatusRoll::CRate, 2.7 },
	  { StatusRoll::ER, 10.4 } },
	{ Main::Feather, SetType::Emblem,
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::CRate, 10.1 },
	  { StatusRoll::Def, 19 },
	  { StatusRoll::CDmg, 20.2 } },
	{ Main::SandER, SetType::Emblem,
	  { StatusRoll::HPPerc, 16.3 },
	  { StatusRoll::HP, 508 },
	  { StatusRoll::CDmg, 14.8 },
	  { StatusRoll::Def, 23 } },
	{ Main::GobletAtk, SetType::HeartOfDepth,
	  { StatusRoll::HP, 508 },
	  { StatusRoll::CRate, 10.1 },
	  { StatusRoll::ER, 6.5 },
	  { StatusRoll::CDmg, 14.8 } },
	{ Main::HeadCDmg, SetType::Emblem,
	  { StatusRoll::Atk, 16 },
	  { StatusRoll::CRate, 17.1 },
	  { StatusRoll::EM, 40 },
	  { StatusRoll::HPPerc, 4.7 } }
};

const std::vector<Artifact> ITTO_ARTS{
	{ Main::Flower, SetType::HuskOfOpulentDreams,
	  { StatusRoll::DefPerc, 7.29 },
	  { StatusRoll::AtkPerc, 5.83 },
	  { StatusRoll::CDmg, 23.31 },
	  { StatusRoll::CRate, 15.56 } },
	{ Main::Feather, SetType::HuskOfOpulentDreams,
	  { StatusRoll::DefPerc, 7.29 },
	  { StatusRoll::CRate, 11.67 },
	  { StatusRoll::AtkPerc, 5.83 },
	  { StatusRoll::CDmg, 31.08 } },
	{ Main::SandDef, SetType::HuskOfOpulentDreams,
	  { StatusRoll::AtkPerc, 5.83 },
	  { StatusRoll::CRate, 11.67 },
	  { StatusRoll::CDmg, 31.08 },
	  { StatusRoll::Def, 23.15 } },
	{ Main::GobletGeo, SetType::HuskOfOpulentDreams,
	  { StatusRoll::DefPerc, 7.29 },
	  { StatusRoll::CRate, 11.67 },
	  { StatusRoll::AtkPerc, 5.83 },
	  { StatusRoll::CDmg, 31.08 } },
	{ Main::HeadCDmg, SetType::HuskOfOpulentDreams,
	  { StatusRoll::DefPerc, 7.29 },
	  { StatusRoll::CRate, 23.34 },
	  { StatusRoll::AtkPerc, 5.83 },
	  { StatusRoll::Def, 23.15 } }
};

const std::vector<Artifact> YELAN_ARTS{
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::HPPerc, 15.7 },
	  { StatusRoll::Atk, 29.0 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::CRate, 7.0 } },
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::Atk, 49.0 },
	  { StatusRoll::Def, 23.0 },
	  { StatusRoll::CDmg, 23.3 },
	  { StatusRoll::CRate, 3.5 } },
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::CRate, 3.1 },
	  { StatusRoll::CDmg, 19.4 },
	  { StatusRoll::EM, 40.0 } },
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::HPPerc, 9.9 },
	  { StatusRoll::CRate, 6.6 },
	  { StatusRoll::Atk, 51 } },
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::HPPerc, 4.7 },
	  { StatusRoll::CDmg, 28.7 },
	  { StatusRoll::ER, 9.1 },
	  { StatusRoll::CRate, 3.1 } },
	{ Main::Flower, SetType::Emblem, // Xingqiu
	  { StatusRoll::EM, 44.0 },
	  { StatusRoll::HPPerc, 10.5 },
	  { StatusRoll::CDmg, 12.4 },
	  { StatusRoll::CRate, 6.2 } },
	{ Main::Flower, SetType::Emblem, // Beidou
	  { StatusRoll::Atk, 49.0 },
	  { StatusRoll::Def, 23.0 },
	  { StatusRoll::CDmg, 23.3 },
	  { StatusRoll::CRate, 3.5 } },
	{ Main::Flower, SetType::Millileth,
	  { StatusRoll::HPPerc, 9.9 },
	  { StatusRoll::Def, 35.0 },
	  { StatusRoll::CDmg, 18.7 },
	  { StatusRoll::CRate, 3.5 } },
	{ Main::Flower, SetType::HeartOfDepth, // Mona
	  { StatusRoll::CRate, 7.4 },
	  { StatusRoll::EM, 40.0 },
	  { StatusRoll::ER, 9.7 },
	  { StatusRoll::CDmg, 12.4 } },
	{ Main::Flower, SetType::HeartOfDepth, // Lvl 16
	  { StatusRoll::CDmg, 7.8 },
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::ER, 16.2 },
	  { StatusRoll::HPPerc, 9.3 } },

	{ Main::Feather, SetType::Emblem,
	  { StatusRoll::CRate, 6.2 },
	  { StatusRoll::ER, 18.1 },
	  { StatusRoll::EM, 19.0 },
	  { StatusRoll::AtkPerc, 8.2 } },
	{ Main::Feather, SetType::Emblem,
	  { StatusRoll::HP, 209.0 },
	  { StatusRoll::HPPerc, 20.0 },
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::CDmg, 21.0 } },
	{ Main::Feather, SetType::Emblem, // Beidou
	  { StatusRoll::CRate, 9.7 },
	  { StatusRoll::Def, 46.0 },
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::CDmg, 7.8 } },
	{ Main::Feather, SetType::Emblem, // Xingqiu
	  { StatusRoll::ER, 5.2 },
	  { StatusRoll::CDmg, 19.4 },
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::EM, 61 } },
	{ Main::Feather, SetType::HeartOfDepth, // Lv 16
	  { StatusRoll::CRate, 7.8 },
	  { StatusRoll::CDmg, 5.4 },
	  { StatusRoll::HP, 299.0 },
	  { StatusRoll::ER, 18.1 } },
	{ Main::Feather, SetType::HeartOfDepth,
	  { StatusRoll::AtkPerc, 9.3 },
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::CDmg, 12.4 },
	  { StatusRoll::HPPerc, 12.2 } },
	{ Main::Feather, SetType::HeartOfDepth,
	  { StatusRoll::AtkPerc, 10.5 },
	  { StatusRoll::HP, 777.0 },
	  { StatusRoll::CRate, 5.8 },
	  { StatusRoll::CDmg, 15.5 } },

	{ Main::SandHP, SetType::Emblem,
	  { StatusRoll::Atk, 47.0 },
	  { StatusRoll::CDmg, 7.8 },
	  { StatusRoll::CRate, 3.1 },
	  { StatusRoll::EM, 61.0 } },
	{ Main::SandHP, SetType::Emblem,
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::Atk, 16.0 },
	  { StatusRoll::Def, 39.0 },
	  { StatusRoll::CDmg, 19.4 } },
	{ Main::SandHP, SetType::Emblem,
	  { StatusRoll::DefPerc, 12.4 },
	  { StatusRoll::HP, 269 },
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::ER, 19.4 } },
	{ Main::SandHP, SetType::Millileth,
	  { StatusRoll::AtkPerc, 8.2 },
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::Atk, 39.0 },
	  { StatusRoll::CDmg, 11.7 } },
	{ Main::SandHP, SetType::HeartOfDepth,
	  { StatusRoll::CDmg, 15.5 },
	  { StatusRoll::CRate, 9.3 },
	  { StatusRoll::HP, 478.0 },
	  { StatusRoll::EM, 16.0 } },

	{ Main::GobletHydro, SetType::Emblem,
	  { StatusRoll::Atk, 35.0 },
	  { StatusRoll::HPPerc, 21.6 },
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::EM, 37.0 } },
	{ Main::GobletHydro, SetType::Shimenawa,
	  { StatusRoll::HP, 598.0 },
	  { StatusRoll::AtkPerc, 8.7 },
	  { StatusRoll::CRate, 7.4 },
	  { StatusRoll::HPPerc, 9.3 } },
	{ Main::GobletHydro, SetType::Shimenawa,
	  { StatusRoll::ER, 11.7 },
	  { StatusRoll::CDmg, 18.7 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::Def, 39.0 } },
	{ Main::GobletHydro, SetType::Shimenawa,
	  { StatusRoll::HP, 209.0 },
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::HPPerc, 20.4 },
	  { StatusRoll::Def, 35.0 } },
	{ Main::GobletHydro, SetType::Bloodstained,
	  { StatusRoll::Atk, 29.0 },
	  { StatusRoll::CDmg, 10.9 },
	  { StatusRoll::Def, 23.0 },
	  { StatusRoll::HPPerc, 16.3 } },
	{ Main::GobletHydro, SetType::BlizzardStrayer,
	  { StatusRoll::HP, 508.0 },
	  { StatusRoll::CDmg, 7.8 },
	  { StatusRoll::ER, 21.4 },
	  { StatusRoll::EM, 16.0 } },

	{ Main::HeadCRate, SetType::BlizzardStrayer,
	  { StatusRoll::ER, 9.1 },
	  { StatusRoll::HPPerc, 5.8 },
	  { StatusRoll::CDmg, 11.7 },
	  { StatusRoll::HP, 1016.0 } },
	{ Main::HeadCDmg, SetType::Emblem,
	  { StatusRoll::Atk, 35.0 },
	  { StatusRoll::HP, 717.0 },
	  { StatusRoll::CRate, 2.7 },
	  { StatusRoll::AtkPerc, 10.5 } },
	{ Main::HeadCDmg, SetType::Emblem,
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::HPPerc, 14.0 },
	  { StatusRoll::Atk, 58 },
	  { StatusRoll::ER, 5.8 } },
	{ Main::HeadHP, SetType::Millileth,
	  { StatusRoll::Def, 63.0 },
	  { StatusRoll::ER, 17.5 },
	  { StatusRoll::AtkPerc, 4.7 },
	  { StatusRoll::CRate, 2.7 } },
	{ Main::HeadHP, SetType::Millileth,
	  { StatusRoll::AtkPerc, 9.3 },
	  { StatusRoll::ER, 5.8 },
	  { StatusRoll::HP, 807.0 },
	  { StatusRoll::CRate, 6.6 } },
	{ Main::HeadCDmg, SetType::HeartOfDepth,
	  { StatusRoll::HPPerc, 11.1 },
	  { StatusRoll::CRate, 7.4 },
	  { StatusRoll::DefPerc, 13.9 },
	  { StatusRoll::Def, 42.0 } },
	{ Main::HeadCRate, SetType::Noblesse,
	  { StatusRoll::EM, 16.0 },
	  { StatusRoll::ER, 9.7 },
	  { StatusRoll::CDmg, 22.5 },
	  { StatusRoll::HPPerc, 16.9 } }
};

const std::vector<Artifact> YELAN_ARTS_EQUIPPED{
	{ Main::Flower, SetType::Emblem,
	  { StatusRoll::HPPerc, 4.7 },
	  { StatusRoll::CDmg, 28.7 },
	  { StatusRoll::ER, 9.1 },
	  { StatusRoll::CRate, 3.1 } },
	{ Main::Feather, SetType::Emblem,
	  { StatusRoll::HP, 209.0 },
	  { StatusRoll::HPPerc, 20.0 },
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::CDmg, 21.0 } },
	{ Main::SandHP, SetType::Emblem,
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::Atk, 16.0 },
	  { StatusRoll::Def, 39.0 },
	  { StatusRoll::CDmg, 19.4 } },
	{ Main::GobletHydro, SetType::Emblem,
	  { StatusRoll::Atk, 35.0 },
	  { StatusRoll::HPPerc, 21.6 },
	  { StatusRoll::ER, 4.5 },
	  { StatusRoll::EM, 37.0 } },
	{ Main::HeadCRate, SetType::Noblesse,
	  { StatusRoll::EM, 16.0 },
	  { StatusRoll::ER, 9.7 },
	  { StatusRoll::CDmg, 22.5 },
	  { StatusRoll::HPPerc, 16.9 } }
};

const std::vector<Artifact> KLEE_ARTS{
	{ Main::Flower, SetType::Gladiator,
	  { StatusRoll::Atk, 14.0 },
	  { StatusRoll::ER, 6.5 },
	  { StatusRoll::CRate, 13.2 },
	  { StatusRoll::AtkPerc, 15.2 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::Def, 42.0 },
	  { StatusRoll::CRate, 7.0 },
	  { StatusRoll::EM, 33.0 },
	  { StatusRoll::CDmg, 14.0 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::ER, 22.7 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::CRate, 7.0 },
	  { StatusRoll::CDmg, 7.8 } },
	{ Main::Flower, SetType::Shimenawa,
	  { StatusRoll::CRate, 6.2 },
	  { StatusRoll::AtkPerc, 4.1 },
	  { StatusRoll::HPPerc, 14.0 },
	  { StatusRoll::CDmg, 11.7 } },

	{ Main::Feather, SetType::Gladiator,
	  { StatusRoll::CRate, 9.3 },
	  { StatusRoll::AtkPerc, 9.9 },
	  { StatusRoll::HP, 598.0 },
	  { StatusRoll::CDmg, 12.4 } },
	{ Main::Feather, SetType::Gladiator,
	  { StatusRoll::CRate, 6.6 },
	  { StatusRoll::AtkPerc, 9.9 },
	  { StatusRoll::ER, 11.0 },
	  { StatusRoll::HP, 508.0 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::DefPerc, 5.8 },
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::CDmg, 21.8 },
	  { StatusRoll::HPPerc, 4.1 } },
	{ Main::Feather, SetType::Shimenawa,
	  { StatusRoll::CRate, 13.6 },
	  { StatusRoll::AtkPerc, 5.3 },
	  { StatusRoll::ER, 10.4 },
	  { StatusRoll::DefPerc, 12.4 } },

	{ Main::SandAtk, SetType::Gladiator,
	  { StatusRoll::Def, 16.0 },
	  { StatusRoll::CDmg, 21.0 },
	  { StatusRoll::Atk, 64.0 },
	  { StatusRoll::ER, 5.2 } },
	{ Main::SandAtk, SetType::Gladiator,
	  { StatusRoll::CDmg, 7.0 },
	  { StatusRoll::DefPerc, 12.4 },
	  { StatusRoll::ER, 22.7 },
	  { StatusRoll::EM, 19.0 } },
	{ Main::SandAtk, SetType::Shimenawa,
	  { StatusRoll::EM, 19.0 },
	  { StatusRoll::DefPerc, 19.0 },
	  { StatusRoll::CRate, 10.5 },
	  { StatusRoll::Def, 23.0 } },

	{ Main::GobletPyro, SetType::HeartOfDepth,
	  { StatusRoll::HPPerc, 5.3 },
	  { StatusRoll::CRate, 3.9 },
	  { StatusRoll::CDmg, 20.2 },
	  { StatusRoll::EM, 58.0 } },

	{ Main::HeadCRate, SetType::Gladiator,
	  { StatusRoll::AtkPerc, 15.7 },
	  { StatusRoll::Atk, 16.0 },
	  { StatusRoll::Def, 44.0 },
	  { StatusRoll::HP, 747.0 } },
	{ Main::HeadCRate, SetType::Gladiator,
	  { StatusRoll::HPPerc, 9.3 },
	  { StatusRoll::CDmg, 18.7 },
	  { StatusRoll::Def, 42.0 },
	  { StatusRoll::Atk, 18.0 } },
	{ Main::HeadCRate, SetType::Shimenawa,
	  { StatusRoll::Atk, 33.0 },
	  { StatusRoll::AtkPerc, 10.5 },
	  { StatusRoll::Def, 42.0 },
	  { StatusRoll::CDmg, 22.5 } }
};

}

#endif