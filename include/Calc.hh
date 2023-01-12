#include <map>

#include <Status.hh>
#include <Character.hh>
#include <Weapon.hh>
#include <Artifact.hh>

#ifndef GENSHINCALC_INCLUDE_CALC
#define GENSHINCALC_INCLUDE_CALC

namespace GenshinCalc {

class Calc {

public:
	struct AppliedDmg {
		std::map<DmgElement, float> regular;
		std::map<DmgElement, float> ignores_def;
	};

	Calc(
	  const Character&,
	  const Weapon&,
	  Artifact flower,
	  Artifact feather,
	  Artifact sand,
	  Artifact goblet,
	  Artifact head);

	static float dmg_dealt(const AppliedDmg& dmg_applied, DmgContext context = {});

	template<typename Callable>
	AppliedDmg avg_dmg(
	  const Combo& combo,
	  unsigned int char_level = 90,
	  Callable modifier = [](Status&) {}) {
		m_stats = Status{};
		modifier(m_stats);
		init_stats();
		return calc_avg_dmg(combo, char_level);
	}

	template<typename Callable>
	float traforeaction_dmg(
	  TrafoReaction reaction,
	  unsigned int char_level = 90,
	  Callable modifier = [](Status&) {}) {
		m_stats = Status{};
		modifier(m_stats);
		init_stats();
		return calc_traforeaction(reaction, char_level);
	}

	// retrieve total stats after calculating avg_dmg(.. / traforeaction_dmg(..
	Status status() const;

	static void pyro_resonance_modifier(Status&);
	static void hydro_resonance_modifier(Status&);
	static void cryo_resonance_modifier(Status&);
	static void geo_resonance_modifier(Status&);
	static void dendro_resonance_modifier(Status&);

private:
	Status m_stats;
	void init_stats();
	AppliedDmg calc_avg_dmg(const Combo&, unsigned int char_level);
	float calc_traforeaction(TrafoReaction, unsigned int char_level);
	void apply_artifact_sets();

	static float def_multiplier(
	  unsigned int char_level,
	  unsigned int enemy_level,
	  float def_reduction_perc);
	static float res_multiplier(float res_perc);

	float total_hp() const;
	float total_atk() const;
	float total_def() const;
	float additional_dmg(Hit) const;
	float dmg_bonus(DmgElement, DmgTalent) const;
	float amplifying_multiplier(AmplifyReaction) const;

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