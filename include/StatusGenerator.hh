#include <Artifact.hh>

#ifndef GENSHINCALC_INCLUDE_STATUSGENERATOR
#define GENSHINCALC_INCLUDE_STATUSGENERATOR

namespace GenshinCalc {

class StatusGenerator {
public:
	StatusGenerator(
	  const Artifact::Main& sands_main,
	  const Artifact::Main& goblet_main,
	  const Artifact::Main& circlet_main,
	  const std::vector<StatusRoll>& priority_rolls,
	  unsigned roll_num);

	enum class Quality {
		BEST,
		BETTER,
		AVERAGE,
		WORSE,
		WORST
	};
	void set_quality(Quality);

	bool next();
	Status get() const;

private:
	Quality m_quality = Quality::BEST;
	unsigned m_total_sub_rolls;
	std::vector<StatusRoll> m_prio_rolls;
	std::vector<unsigned> m_initial_rolls;
	std::vector<unsigned> m_max_initial_rolls;
	std::vector<unsigned> m_sub_rolls;
	std::vector<unsigned> m_max_sub_rolls;

	float max_roll(StatusRoll) const;
	static bool is_same_stat(Artifact::Main, StatusRoll);
	static void reset_range(
	  std::vector<unsigned>& rolls,
	  const std::vector<unsigned>& max_rolls,
	  std::size_t max_index, unsigned roll_num);

	void resolve_max_initial_rolls(
	  const Artifact::Main& sands_main,
	  const Artifact::Main& goblet_main,
	  const Artifact::Main& circlet_main);

	void resolve_max_sub_rolls();

	bool next_rolls(
	  std::vector<unsigned>& rolls,
	  const std::vector<unsigned>& max_rolls);
};

}

#endif