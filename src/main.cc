#include <iostream>

#include <Status.hh>
#include <Character.hh>
#include <Weapon.hh>
#include <Artifact.hh>
#include <Calc.hh>

int main() {
	using namespace GenshinCalc;

	using Main = Artifact::Main;
	using SetType = Artifact::SetType;
	using StatusRoll = Artifact::StatusRoll;

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

	Calc calc{
		ayaka,
		black_sword,
		flower,
		feather,
		sand,
		goblet,
		head
	};

	Combo combo{ ayaka.get_hit(DmgTalent::Normal, 1) };
	const auto avg_dmg = calc.avg_dmg(combo);
	std::cout << Calc::dmg_dealt(avg_dmg, 90, 88, 0.0, 10.0) << std::endl;
}
