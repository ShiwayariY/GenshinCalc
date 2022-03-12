#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>

#include <StatusGenerator.hh>

namespace GenshinCalc {

using Main = Artifact::Main;
using SetType = Artifact::SetType;

StatusGenerator::StatusGenerator(
  const Main& sands_main,
  const Main& goblet_main,
  const Main& circlet_main,
  const std::vector<StatusRoll>& priority_rolls,
  unsigned sub_roll_num) :
		m_total_sub_rolls{ sub_roll_num },
		m_prio_rolls{ priority_rolls } {

	const auto prio_num = priority_rolls.size();
	m_initial_rolls.resize(prio_num);
	m_max_initial_rolls.resize(prio_num);
	m_sub_rolls.resize(prio_num);
	m_max_sub_rolls.resize(prio_num);

	resolve_max_initial_rolls(sands_main, goblet_main, circlet_main);
	reset_range(m_initial_rolls, m_max_initial_rolls, m_initial_rolls.size() - 1, 20u);
	resolve_max_sub_rolls();
	reset_range(m_sub_rolls, m_max_sub_rolls, m_sub_rolls.size() - 1, m_total_sub_rolls);
}

bool StatusGenerator::next() {
	if (next_rolls(m_sub_rolls, m_max_sub_rolls))
		return true;

	if (!next_rolls(m_initial_rolls, m_max_initial_rolls))
		return false;

	resolve_max_sub_rolls();
	reset_range(m_sub_rolls, m_max_sub_rolls, m_sub_rolls.size() - 1, m_total_sub_rolls);
	return true;
}

Status StatusGenerator::get() const {
	Status stats;
	for (std::size_t i = 0; i < m_prio_rolls.size(); ++i) {
		const auto& type = m_prio_rolls[i];
		stats.add_roll(type, max_roll(type) *
							   (m_initial_rolls[i] + m_sub_rolls[i]));
	}
	return stats;
}

// private

bool StatusGenerator::is_same_stat(Main main, StatusRoll roll) {
	switch (main) {
		case Main::Flower:
			return roll == StatusRoll::HP;
		case Main::Feather:
			return roll == StatusRoll::Atk;
		case Main::SandAtk:
		case Main::GobletAtk:
		case Main::HeadAtk:
			return roll == StatusRoll::AtkPerc;
		case Main::SandDef:
		case Main::GobletDef:
		case Main::HeadDef:
			return roll == StatusRoll::DefPerc;
		case Main::SandHP:
		case Main::GobletHP:
		case Main::HeadHP:
			return roll == StatusRoll::HPPerc;
		case Main::SandER:
			return roll == StatusRoll::ER;
		case Main::SandEM:
		case Main::GobletEM:
		case Main::HeadEM:
			return roll == StatusRoll::EM;
		case Main::HeadCDmg:
			return roll == StatusRoll::CDmg;
		case Main::HeadCRate:
			return roll == StatusRoll::CRate;
		default:
			return false;
	}
}

float StatusGenerator::max_roll(StatusRoll roll) {
	static const std::map<StatusRoll, float> MAX_ROLLS{
		{ StatusRoll::Atk, 19.45 },
		{ StatusRoll::AtkPerc, 5.83 },
		{ StatusRoll::Def, 23.15 },
		{ StatusRoll::DefPerc, 7.29 },
		{ StatusRoll::HP, 298.75 },
		{ StatusRoll::HPPerc, 5.83 },
		{ StatusRoll::EM, 23.31 },
		{ StatusRoll::ER, 6.48 },
		{ StatusRoll::CRate, 3.89 },
		{ StatusRoll::CDmg, 7.77 }
	};
	return MAX_ROLLS.at(roll);
}

void StatusGenerator::resolve_max_initial_rolls(
  const Main& sands_main,
  const Main& goblet_main,
  const Main& circlet_main) {
	std::ranges::fill(m_max_initial_rolls, 5u);

	const auto mains = { sands_main, goblet_main, circlet_main };
	for (std::size_t i = 0; i < m_prio_rolls.size(); ++i)
		for (const auto& main : mains)
			if (is_same_stat(main, m_prio_rolls[i])) --m_max_initial_rolls[i];
}

void StatusGenerator::resolve_max_sub_rolls() {
	for (std::size_t i = 0; i < m_max_sub_rolls.size(); ++i)
		m_max_sub_rolls[i] = m_initial_rolls[i] * 6u;
}

void StatusGenerator::reset_range(
  std::vector<unsigned>& rolls,
  const std::vector<unsigned>& max_rolls,
  std::size_t max_index, unsigned roll_num) {

	max_index = std::min(max_index, rolls.size() - 1);

	for (std::size_t i = 0; i <= max_index; ++i) {
		auto available_rolls = std::min(max_rolls[i], roll_num);
		rolls[i] = available_rolls;
		roll_num -= available_rolls;
	}
}

bool StatusGenerator::next_rolls(
  std::vector<unsigned>& rolls,
  const std::vector<unsigned>& max_rolls) {
	for (std::size_t i = 1; i < rolls.size(); ++i) {
		if (rolls[i] >= max_rolls[i]) continue; // should never be >

		const auto rolls_available_to_redistribute =
		  std::accumulate<std::vector<unsigned>::iterator, unsigned>(
			rolls.begin(),
			std::next(rolls.begin(), i),
			0u);
		if (rolls_available_to_redistribute < 1) continue;

		++rolls[i];
		reset_range(rolls, max_rolls, i - 1, rolls_available_to_redistribute - 1);

		return true;
	}

	return false;
}

}