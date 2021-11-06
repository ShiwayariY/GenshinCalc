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
}

#endif