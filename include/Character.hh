#include <map>

#include <Status.hh>

#ifndef GENSHINCALC_INCLUDE_CHARACTER
#define GENSHINCALC_INCLUDE_CHARACTER

namespace GenshinCalc {

class Character {
public:
	using AtkID = std::pair<DmgTalent, unsigned int>;
	using Abilities = std::map<AtkID, Hit>;

	Character(Status);

	virtual Hit get_hit(DmgTalent, unsigned int hit_num) const = 0;
	virtual void apply_effects(Status&) const = 0;

	const Status status;
};

// -------------------------------------------------- Ayaka --------------------------------------------------

class Ayaka : public Character {
public:
	bool AmatsumiKunitsumiSanctification = true;
	bool KantenSenmyouBlessing = true;
	bool CryoInfused = true;

	Ayaka() :
			Character{
				{ .base_hp = 12858.0,
				  .base_atk = 342.0,
				  .base_def = 784.0,
				  .crit_rate = 5.0,
				  .crit_dmg = 88.4,
				  .energy_recharge = 100.0 }
			} {
		DEBUG("___Ayaka___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 90.4 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 96.2 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 123.8 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 44.8 * 3.0 } },
		{ { DmgTalent::Normal, 5 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 154.5 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Cryo, 109.0 * 3.0 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Cryo, 431.0 } },
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Cryo, 202.0 * 19.0 + 303.0 } }
	};
};

// -------------------------------------------------- Baal --------------------------------------------------

class Baal : public Character {
public:
	unsigned int energy_consumed = 80 + 80 + 60;

	Baal() :
			Character{
				{ .base_hp = 12090,
				  .base_atk = 316,
				  .base_def = 739,
				  .crit_rate = 5.0,
				  .crit_dmg = 50.0,
				  .energy_recharge = 132.0 }
			} {
		DEBUG("___Baal___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 57.6 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 57.8 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 72.5 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 42.1 + 42.1 } },
		{ { DmgTalent::Normal, 5 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 95.1 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Phys, 144.8 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 187.5 } },		 // initial hit
		{ { DmgTalent::Skill, 2 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 67.2 } },		 // coord. attack
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 681.0 } },		 // initial hit
		{ { DmgTalent::Burst, 2 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 75.2 } },		 // N1
		{ { DmgTalent::Burst, 3 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 73.9 } },		 // N2
		{ { DmgTalent::Burst, 4 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 90.5 } },		 // N3
		{ { DmgTalent::Burst, 5 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 51.9 + 52.1 } },  // N4
		{ { DmgTalent::Burst, 6 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 124.4 } },		 // N5
		{ { DmgTalent::Burst, 7 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 103.6 + 125.1 } } // charged
	};
};

}

#endif