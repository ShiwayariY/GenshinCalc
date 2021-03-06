#include <Status.hh>
#include <Character.hh>
#include <Weapon.hh>
#include <Artifact.hh>

#ifndef GENSHINCALC_INCLUDE_CALC
#define GENSHINCALC_INCLUDE_CALC

namespace GenshinCalc {

class Calc {

public:
	Calc(
	  const Character&,
	  const Weapon&,
	  Artifact flower,
	  Artifact feather,
	  Artifact sand,
	  Artifact goblet,
	  Artifact head);

	static float dmg_dealt(
	  float dmg_applied,
	  unsigned int char_level,
	  unsigned int enemy_level,
	  float def_reduction_perc,
	  float res_perc);

	template<typename Callable>
	float avg_dmg(
	  const Combo& combo,
	  Callable modifier = [](Status&) {}) {
		m_stats = Status{};
		modifier(m_stats);
		init_stats();
		return calc_avg_dmg(combo);
	}

	// retrieve total stats after calculating avg_dmg(...
	Status status() const;

	static void pyro_resonance_modifier(Status&);
	static void cryo_resonance_modifier(Status&);
	static void geo_resonance_modifier(Status&);

private:
	Status m_stats;
	void init_stats();
	float calc_avg_dmg(const Combo&);
	void apply_artifact_sets();

	static float def_multiplier(
	  unsigned int char_level,
	  unsigned int enemy_level,
	  float def_reduction_perc);
	static float res_multiplier(float res_perc);

	float total_atk() const;
	float additional_dmg(DmgTalent) const;
	float dmg_bonus(DmgElement, DmgTalent) const;
	float amplifying_multiplier(Reaction) const;

	const Character& m_char;
	const Weapon& m_weapon;
	const Artifact m_flower;
	const Artifact m_feather;
	const Artifact m_sand;
	const Artifact m_goblet;
	const Artifact m_head;
};

}

#endif