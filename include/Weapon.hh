#include <Status.hh>

#ifndef GENSHINCALC_INCLUDE_WEAPON
#define GENSHINCALC_INCLUDE_WEAPON

namespace GenshinCalc {

class Weapon {
public:
	Weapon(Status);

	virtual void apply_effects(Status&) const = 0;

	const Status status;
};

// -------------------------------------------------- Black Sword --------------------------------------------------

class BlackSword : public Weapon {
public:
	BlackSword() :
			Weapon{
				{ .base_atk = 510,
				  .crit_rate = 27.6,
				  .normal_bonus = 35.0,
				  .charged_bonus = 35.0 }
			} {
		DEBUG("___Black Sword___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- The Catch --------------------------------------------------

class TheCatch : public Weapon {
public:
	TheCatch() :
			Weapon{
				{ .base_atk = 510,
				  .crit_rate = 12.0,
				  .energy_recharge = 45.9,
				  .burst_bonus = 32.0 }
			} {}

	void apply_effects(Status&) const override {}
};

}

#endif