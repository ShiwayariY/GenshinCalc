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
				{ .base_atk = 510.0f,
				  .crit_rate = 27.6f,
				  .normal_bonus = 35.0f,
				  .charged_bonus = 35.0f }
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
				{ .base_atk = 510.0f,
				  .crit_rate = 12.0f,
				  .energy_recharge = 45.9f,
				  .burst_bonus = 32.0f }
			} {
		DEBUG("___The Catch___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Whiteblind --------------------------------------------------

class Whiteblind : public Weapon {
public:
	Whiteblind(unsigned int refine = 1) :
			Weapon{
				{ .base_atk = 510.0f,
				  .atk_perc = 18.0f + static_cast<float>(refine) * 6.0f,
				  .def_perc = 51.7f + 18.0f + static_cast<float>(refine) * 6.0f }
			} {
		DEBUG("___Whiteblind___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Skyward Pride --------------------------------------------------

class SkywardPride : public Weapon {
public:
	SkywardPride(unsigned int refine = 1) :
			Weapon{
				{ .base_atk = 674.0f,
				  .energy_recharge = 36.8f,
				  .normal_bonus = 6.0f + static_cast<float>(refine) * 2.0f,
				  .charged_bonus = 6.0f + static_cast<float>(refine) * 2.0f,
				  .plunge_bonus = 6.0f + static_cast<float>(refine) * 2.0f,
				  .skill_bonus = 6.0f + static_cast<float>(refine) * 2.0f,
				  .burst_bonus = 6.0f + static_cast<float>(refine) * 2.0f }
			} {
		DEBUG("___Skyward Pride___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Snowtombed Starsilver --------------------------------------------------

class SnowtombedStarsilver : public Weapon {
public:
	SnowtombedStarsilver() :
			Weapon{
				{ .base_atk = 565.0f,
				  .phys_bonus = 34.5f }
			} {
		DEBUG("___Snowtombed Starsilver___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Redhorn Stonethresher --------------------------------------------------

class RedhornStonethresher : public Weapon {
public:
	RedhornStonethresher(unsigned int refine = 1) :
			Weapon{
				{ .base_atk = 542.0f,
				  .def_perc = 21.0f + static_cast<float>(refine) * 7.0f,
				  .crit_dmg = 88.2f }
			},
			m_refine{ refine } {
		DEBUG("___Redhorn Stonethresher___\n"
			  << status);
	}

	void apply_effects(Status&) const override;

private:
	const unsigned int m_refine = 1;
};
}

#endif