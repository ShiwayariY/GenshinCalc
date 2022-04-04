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

class Ayaka : public Character { // 10 10 10
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
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 90.39 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 96.24 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 123.79 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 44.77 * 3.0 } },
		{ { DmgTalent::Normal, 5 }, Hit{ DmgTalent::Normal, DmgElement::Cryo, 154.55 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Cryo, 108.97 * 3.0 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Cryo, 430.56 } },
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Cryo, 202.14 } }, // Cutting dmg (19 hits)
		{ { DmgTalent::Burst, 2 }, Hit{ DmgTalent::Burst, DmgElement::Cryo, 303.21 } }  // Explosion dmg

	};
};

// -------------------------------------------------- Baal --------------------------------------------------

class Baal : public Character { // 6 8 10
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
	inline static const float BalefulOmen_burst_bonus = 0.29;
	inline static const float MusouShinsetsu_resolve_per_energy = 0.2;
	inline static const float MusouShinsetsu_resolve_bonus_initial = 7.0;
	inline static const float MusouShinsetsu_resolve_bonus_normal = 1.31;
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 57.6 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 57.8 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 72.5 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 42.1 + 42.1 } },
		{ { DmgTalent::Normal, 5 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 95.1 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Phys, 144.8 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 187.5 } },		  // initial hit
		{ { DmgTalent::Skill, 2 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 67.2 } },		  // coord. attack
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 721.44 } },		  // initial hit
		{ { DmgTalent::Burst, 2 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 79.82 } },		  // N1
		{ { DmgTalent::Burst, 3 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 78.42 } },		  // N2
		{ { DmgTalent::Burst, 4 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 96.02 } },		  // N3
		{ { DmgTalent::Burst, 5 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 55.11 + 55.26 } }, // N4
		{ { DmgTalent::Burst, 6 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 131.92 } },		  // N5
		{ { DmgTalent::Burst, 7 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 109.9 + 132.67 } } // charged
	};
};

// -------------------------------------------------- Eula --------------------------------------------------

class Eula : public Character { // 9 9 9
public:
	inline static const float Resistance_down = -24.0;
	unsigned Lightfall_stacks = 13;

	Eula() :
			Character{
				{ .base_hp = 13226,
				  .base_atk = 342,
				  .base_def = 751,
				  .crit_rate = 5.0,
				  .crit_dmg = 88.4 }
			} {
		DEBUG("___Eula___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override {}

private:
	inline static const float Lightfall_dmg_per_stack = 137.78;

	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 164.86 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 171.87 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 2.0 * 104.35 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 206.95 } },
		{ { DmgTalent::Normal, 5 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 2.0 * 131.97 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Cryo, 248.88 } }, // Press
		{ { DmgTalent::Skill, 2 }, Hit{ DmgTalent::Skill, DmgElement::Cryo, 417.52 } }, // Hold
		{ { DmgTalent::Skill, 3 }, Hit{ DmgTalent::Skill, DmgElement::Cryo, 163.2 } },  // Icewhirl Brand
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Cryo, 417.52 } }, // Initial hit
		{ { DmgTalent::Burst, 2 }, Hit{ DmgTalent::Burst, DmgElement::Phys, 337.17 } }, // Shattered Lightfall Sword (passive)
		{ { DmgTalent::Burst, 3 }, Hit{ DmgTalent::Burst, DmgElement::Phys, 674.34 } }  // Lightfall Sword base dmg
	};
};

// -------------------------------------------------- Itto --------------------------------------------------

class Itto : public Character { // 10 10 10
public:
	bool RoyalDescent = true;
	bool SuperlativeSuperstrength = true;

	Itto() :
			Character{
				{ .base_hp = 12858.0,
				  .base_atk = 227.0,
				  .base_def = 959.0,
				  .crit_rate = 24.2,
				  .crit_dmg = 50.0,
				  .energy_recharge = 100.0 }
			} {
		DEBUG("___Itto___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const float RoyalDescent_atk_bonus = 1.0368;
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Geo, 156.62 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Geo, 150.96 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Geo, 181.15 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Geo, 231.72 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Geo, 180.2 } },  // Arataki Kesagiri Combo Slash
		{ { DmgTalent::Charged, 2 }, Hit{ DmgTalent::Charged, DmgElement::Geo, 377.4 } },  // Arataki Kesagiri Final Slash
		{ { DmgTalent::Charged, 3 }, Hit{ DmgTalent::Charged, DmgElement::Geo, 178.84 } }, // Saichimonji Slash
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Geo, 552.96 } }
	};
};

// -------------------------------------------------- Hu Tao --------------------------------------------------

class HuTao : public Character { // 10 10 9
public:
	bool GuideToAfterlife = true;

	HuTao() :
			Character{
				{ .base_hp = 15552.0,
				  .base_atk = 106.0,
				  .base_def = 876.0,
				  .crit_rate = 5.0,
				  .crit_dmg = 88.4,
				  .energy_recharge = 100.0 }
			} {
		DEBUG("___Hu Tao___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const float GuideToAfterlife_atk_ratio = 0.0626;
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 83.6 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 86.1 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 108.9 } },
		{ { DmgTalent::Normal, 4 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 117.1 } },
		{ { DmgTalent::Normal, 5 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 59.4 + 62.8 } },
		{ { DmgTalent::Normal, 6 }, Hit{ DmgTalent::Normal, DmgElement::Phys, 153.4 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Phys, 242.6 } },
		{ { DmgTalent::Plunge, 1 }, Hit{ DmgTalent::Plunge, DmgElement::Phys, 116.7 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Pyro, 115.0 } }, // Blood Blossom
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Pyro, 470.0 } }, // high HP
		{ { DmgTalent::Burst, 2 }, Hit{ DmgTalent::Burst, DmgElement::Pyro, 588.0 } }  // low HP
	};
};

// -------------------------------------------------- Yae Miko --------------------------------------------------

class YaeMiko : public Character { // 9 9 9
public:
	YaeMiko() :
			Character{
				{ .base_hp = 10372.0,
				  .base_atk = 340.0,
				  .base_def = 569.0,
				  .crit_rate = 24.2,
				  .crit_dmg = 50.0,
				  .energy_recharge = 100.0 }
			} {
		DEBUG("___Yae Miko___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const float EnlightenedBlessing_skill_bonus = 0.15;
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, Hit{ DmgTalent::Normal, DmgElement::Electro, 67.42 } },
		{ { DmgTalent::Normal, 2 }, Hit{ DmgTalent::Normal, DmgElement::Electro, 65.48 } },
		{ { DmgTalent::Normal, 3 }, Hit{ DmgTalent::Normal, DmgElement::Electro, 96.71 } },
		{ { DmgTalent::Charged, 1 }, Hit{ DmgTalent::Charged, DmgElement::Electro, 242.92 } },
		{ { DmgTalent::Skill, 1 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 103.14 } },
		{ { DmgTalent::Skill, 2 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 128.93 } },
		{ { DmgTalent::Skill, 3 }, Hit{ DmgTalent::Skill, DmgElement::Electro, 161.16 } },
		{ { DmgTalent::Burst, 1 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 442.0 } },
		{ { DmgTalent::Burst, 2 }, Hit{ DmgTalent::Burst, DmgElement::Electro, 567.49 } }
	};
};

}

#endif