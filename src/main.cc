#include <iostream>

#include <Status.hh>
#include <Character.hh>
#include <Weapon.hh>
#include <Artifact.hh>
#include <Calc.hh>

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;
using StatusRoll = Artifact::StatusRoll;

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

}

int main() {
	using namespace GenshinCalc;
	calc_Baal();
}
