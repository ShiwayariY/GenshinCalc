#include <map>

#include <Status.hh>

#ifndef GENSHINCALC_INCLUDE_CHARACTER
#define GENSHINCALC_INCLUDE_CHARACTER

namespace GenshinCalc {

class Character {

protected:
	using AtkID = std::pair<DmgTalent, unsigned int>;
	struct DmgDealt {
		DmgElement element;
		ScalingType scaling;
		float value;
	};
	using Abilities = std::map<AtkID, DmgDealt>;

	static Hit to_hit(DmgTalent, DmgDealt);

public:
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
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 90.39 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 96.24 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 123.79 } },
		{ { DmgTalent::Normal, 4 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 44.77 * 3.0 } },
		{ { DmgTalent::Normal, 5 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 154.55 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 108.97 * 3.0 } },
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 430.56 } },
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 202.14 } }, // Cutting dmg (19 hits)
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 303.21 } }  // Explosion dmg

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
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 57.6 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 57.8 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 72.5 } },
		{ { DmgTalent::Normal, 4 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 42.1 + 42.1 } },
		{ { DmgTalent::Normal, 5 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 95.1 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 144.8 } },
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 187.5 } },		   // initial hit
		{ { DmgTalent::Skill, 2 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 67.2 } },		   // coord. attack
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 721.44 } },		   // initial hit
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 79.82 } },		   // N1
		{ { DmgTalent::Burst, 3 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 78.42 } },		   // N2
		{ { DmgTalent::Burst, 4 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 96.02 } },		   // N3
		{ { DmgTalent::Burst, 5 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 55.11 + 55.26 } }, // N4
		{ { DmgTalent::Burst, 6 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 131.92 } },		   // N5
		{ { DmgTalent::Burst, 7 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 109.9 + 132.67 } } // charged
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
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 164.86 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 171.87 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 2.0 * 104.35 } },
		{ { DmgTalent::Normal, 4 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 206.95 } },
		{ { DmgTalent::Normal, 5 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 2.0 * 131.97 } },
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 248.88 } }, // Press
		{ { DmgTalent::Skill, 2 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 417.52 } }, // Hold
		{ { DmgTalent::Skill, 3 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 163.2 } },  // Icewhirl Brand
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Cryo, ScalingType::Atk, 417.52 } }, // Initial hit
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 337.17 } }, // Shattered Lightfall Sword (passive)
		{ { DmgTalent::Burst, 3 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 674.34 } }  // Lightfall Sword base dmg
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
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 156.62 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 150.96 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 181.15 } },
		{ { DmgTalent::Normal, 4 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 231.72 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 180.2 } },  // Arataki Kesagiri Combo Slash
		{ { DmgTalent::Charged, 2 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 377.4 } },  // Arataki Kesagiri Final Slash
		{ { DmgTalent::Charged, 3 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 178.84 } }, // Saichimonji Slash
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Geo, ScalingType::Atk, 552.96 } }
	};
};

// -------------------------------------------------- Hu Tao --------------------------------------------------

class HuTao : public Character { // 10 10 9
public:
	bool GuideToAfterlife = true;
	bool SanguineRouge = true;

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
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 83.6 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 86.1 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 108.9 } },
		{ { DmgTalent::Normal, 4 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 117.1 } },
		{ { DmgTalent::Normal, 5 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 59.4 + 62.8 } },
		{ { DmgTalent::Normal, 6 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 153.4 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 242.6 } },
		{ { DmgTalent::Plunge, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 116.7 } },
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 115.0 } }, // Blood Blossom
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 470.0 } }, // high HP
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 588.0 } }  // low HP
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
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 67.42 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 65.48 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 96.71 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 242.92 } },
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 103.14 } },
		{ { DmgTalent::Skill, 2 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 128.93 } },
		{ { DmgTalent::Skill, 3 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 161.16 } },
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 442.0 } },
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Electro, ScalingType::Atk, 567.49 } }
	};
};

// -------------------------------------------------- Yelan --------------------------------------------------

class Yelan : public Character { // 9 9 10
public:
	unsigned TurnControl_stacks = 3;

	Yelan() :
			Character{
				{ .base_hp = 14450.0,
				  .base_atk = 244.0,
				  .base_def = 548.0,
				  .crit_rate = 24.2,
				  .crit_dmg = 50.0,
				  .energy_recharge = 100.0 }
			} {
		DEBUG("___Yelan___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const std::vector<float> TurnControl_bonus = { 6.0, 12.0, 18.0, 30.0 };
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 74.73 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 71.73 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 94.8 } },
		{ { DmgTalent::Normal, 4 }, DmgDealt{ DmgElement::Phys, ScalingType::Atk, 39.82 * 3.0 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 19.68 } }, // Breakthrough Barb
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 38.44 } },
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 13.15 } }, // Activation
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 8.77 } }   // Exquisite Throw
	};
};

// -------------------------------------------------- Klee --------------------------------------------------

class Klee : public Character { // 9 9 9
public:
	Klee() :
			Character{
				{ .base_hp = 10287.0,
				  .base_atk = 311.0,
				  .base_def = 615.0,
				  .crit_rate = 5.0,
				  .crit_dmg = 50.0,
				  .energy_recharge = 100.0,
				  .pyro_bonus = 28.8 }
			} {
		DEBUG("___Klee___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override {}

private:
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Normal, 1 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 122.67 } },
		{ { DmgTalent::Normal, 2 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 106.08 } },
		{ { DmgTalent::Normal, 3 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 152.86 } },
		{ { DmgTalent::Charged, 1 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 267.51 } },
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 161.84 } }, // bounce
		{ { DmgTalent::Skill, 2 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 55.76 } },  // mine
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Pyro, ScalingType::Atk, 72.49 } }
	};
};

// -------------------------------------------------- Nilou --------------------------------------------------

class Nilou : public Character { // 9 9 9
public:
	bool GoldenChalice = true;

	Nilou() :
			Character{
				{ .base_hp = 15185.0,
				  .hp_perc = 28.8,
				  .base_atk = 229.61,
				  .base_def = 728.59,
				  .crit_rate = 5.0,
				  .crit_dmg = 50.0,
				  .energy_recharge = 100.0 }
			} {
		DEBUG("___Nilou___\n"
			  << status);
	}

	Hit get_hit(DmgTalent, unsigned int hit_num) const override;
	void apply_effects(Status&) const override;

private:
	inline static const Abilities ABILITIES{
		{ { DmgTalent::Skill, 1 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 5.68 } },
		{ { DmgTalent::Skill, 2 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 7.74 } },  // sword dance 1
		{ { DmgTalent::Skill, 3 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 8.75 } },  // sword dance 2
		{ { DmgTalent::Skill, 4 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 12.19 } }, // sword dance 3
		{ { DmgTalent::Skill, 5 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 5.55 } },  // whirling steps 1
		{ { DmgTalent::Skill, 6 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 6.73 } },  // whirling steps 2
		{ { DmgTalent::Skill, 7 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 8.6 } },   // whirling steps 3
		{ { DmgTalent::Burst, 1 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 31.33 } },
		{ { DmgTalent::Burst, 2 }, DmgDealt{ DmgElement::Hydro, ScalingType::HP, 38.3 } }
	};
};

}

#endif
