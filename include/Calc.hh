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

	float avg_dmg(
	  const Combo&,
	  void (*modifier)(Status&) = [](Status&) {}) const;

	static void geo_resonance_modifier(Status&);

private:
	mutable Status m_stats; // not part of state / only used for intermediate results
	void init_stats() const;
	void apply_artifact_sets() const;

	static float def_multiplier(
	  unsigned int char_level,
	  unsigned int enemy_level,
	  float def_reduction_perc);
	static float res_multiplier(float res_perc);

	float total_atk() const;
	float dmg_bonus(DmgElement, DmgTalent) const;
	float amplifying_mutliplier(Reaction) const;

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