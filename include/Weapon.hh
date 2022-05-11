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
				  .normal_bonus = 40.0f,
				  .charged_bonus = 40.0f }
			} {
		DEBUG("___Black Sword___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Blackcliff Longsword --------------------------------------------------

class BlackcliffLongsword : public Weapon {
public:
	BlackcliffLongsword() :
			Weapon{
				{ .base_atk = 565.0f,
				  .crit_dmg = 36.8f }
			} {
		DEBUG("___Blackcliff Longsword___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Amenoma Kageuchi --------------------------------------------------

class AmenomaKageuchi : public Weapon {
public:
	AmenomaKageuchi() :
			Weapon{
				{ .base_atk = 454.0f,
				  .atk_perc = 55.1f }
			} {
		DEBUG("___Amenoma Kageuchi___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Mistsplitter --------------------------------------------------

class Mistsplitter : public Weapon {
public:
	Mistsplitter(unsigned stacks = 3) :
			Weapon{
				{ .base_atk = 674.0f,
				  .crit_dmg = 44.1f,
				  .pyro_bonus = 12.0f + 8.0f * stacks + (stacks == 3 ? 4.0f : 0.0f),
				  .hydro_bonus = 12.0f + 8.0f * stacks + (stacks == 3 ? 4.0f : 0.0f),
				  .cryo_bonus = 12.0f + 8.0f * stacks + (stacks == 3 ? 4.0f : 0.0f),
				  .electro_bonus = 12.0f + 8.0f * stacks + (stacks == 3 ? 4.0f : 0.0f),
				  .anemo_bonus = 12.0f + 8.0f * stacks + (stacks == 3 ? 4.0f : 0.0f),
				  .geo_bonus = 12.0f + 8.0f * stacks + (stacks == 3 ? 4.0f : 0.0f) }
			} {
		DEBUG("___Mistsplitter ___\n"
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

// -------------------------------------------------- Serpent Spine --------------------------------------------------

class SerpentSpine : public Weapon {
	float DMG_per_stack = 0.0;

public:
	unsigned stacks = 5;

	SerpentSpine(unsigned refine = 1) :
			Weapon{
				{ .base_atk = 510.0f,
				  .crit_rate = 27.6f }
			},
			DMG_per_stack{ 5.0f + static_cast<float>(refine) } {

		DEBUG("___Serpent Spine___\n"
			  << status);
	}

	void apply_effects(Status&) const override;
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

// -------------------------------------------------- Deathmatch --------------------------------------------------

class Deathmatch : public Weapon {
public:
	Deathmatch(unsigned int refine = 1, bool single_opponent = false) :
			Weapon{
				{ .base_atk = 454.0f,
				  .atk_perc = (single_opponent ? 18.0f : 12.0f) + static_cast<float>(refine) * (single_opponent ? 6.0f : 4.0f),
				  .def_perc = single_opponent ? 0.0f : (12.0f + static_cast<float>(refine) * 4.0f),
				  .crit_rate = 36.8f }
			} {
		DEBUG("___Deathmatch___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Lost Prayer --------------------------------------------------

class LostPrayer : public Weapon { // R1
public:
	unsigned int stacks = 0;
	LostPrayer() :
			Weapon{
				{ .base_atk = 608.0f,
				  .crit_rate = 33.1f }
			} {
		DEBUG("___Lost Prayer___\n"
			  << status);
	}

	void apply_effects(Status&) const override;

private:
	inline static const float bonus_per_stack = 8.0;
	inline static const unsigned max_stacks = 4;
};

// -------------------------------------------------- Widsith --------------------------------------------------

class Widsith : public Weapon {
public:
	enum class ThemeSong {
		None,
		Recitative,
		Aria,
		Interlude
	};
	ThemeSong Song = ThemeSong::None;

	Widsith(unsigned refine = 1) :
			Weapon{
				{ .base_atk = 510.0f,
				  .crit_dmg = 55.1f }
			},
			Recitative_atk_perc{ 45.0f + 15.0f * refine },
			Aria_elem_bonus{ 36.0f + 12.0f * refine },
			Interlude_elem_mastery{ 180.0f + 60.0f * refine } {
		DEBUG("___Widsith___\n"
			  << status);
	}

	void apply_effects(Status&) const override;

private:
	float Recitative_atk_perc = 0.0;
	float Aria_elem_bonus = 0.0;
	float Interlude_elem_mastery = 0.0;
};

// -------------------------------------------------- Stringless --------------------------------------------------

class Stringless : public Weapon {
public:
	Stringless() :
			Weapon{
				{ .base_atk = 510.0f,
				  .elem_mastery = 165.0f,
				  .skill_bonus = 24.0f,
				  .burst_bonus = 24.0f }
			} {
		DEBUG("___Stringless___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- ViridescentHunt --------------------------------------------------

class ViridescentHunt : public Weapon {
public:
	ViridescentHunt() :
			Weapon{
				{ .base_atk = 510.0f,
				  .crit_rate = 27.6f }
			} {
		DEBUG("___Viridescent Hunt___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- Sacrificial Bow --------------------------------------------------

class SacrificialBow : public Weapon {
public:
	SacrificialBow() :
			Weapon{
				{ .base_atk = 565.0f,
				  .energy_recharge = 30.6f }
			} {
		DEBUG("___Sacrificial Bow___\n"
			  << status);
	}

	void apply_effects(Status&) const override {}
};

// -------------------------------------------------- The Unforged --------------------------------------------------

class Unforged : public Weapon {
	static const unsigned MAX_STACKS = 5u;
	float m_atk_perc_bonus_per_stack = 4.0;

public:
	unsigned stacks = 0;
	bool shielded = false;

	Unforged(unsigned refine = 1) :
			Weapon{
				{ .base_atk = 608.0f,
				  .atk_perc = 49.6f }
			},
			m_atk_perc_bonus_per_stack{ 3.0f + refine } {
		DEBUG("___Unforged___\n"
			  << status);
	}

	void apply_effects(Status&) const override;
};

}

#endif