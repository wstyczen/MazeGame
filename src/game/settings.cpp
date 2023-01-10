#include "game/settings.hpp"

#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

namespace game {

namespace {

std::string to_string(const maze::GeneratorType& generator_type) {
  switch (generator_type) {
    case maze::GeneratorType::ALDOUS_BRODER:
      return "ALDOUS_BRODER";
    case maze::GeneratorType::ELLERS:
      return "ELLERS";
    case maze::GeneratorType::GROWING_TREE:
      return "GROWING_TREE";
    case maze::GeneratorType::HUNT_AND_KILL:
      return "HUNT_AND_KILL";
    case maze::GeneratorType::KRUSKALS:
      return "KRUSKALS";
    case maze::GeneratorType::PRIMS:
      return "PRIMS";
    case maze::GeneratorType::RECURSIVE_BACKTRACKING:
      return "RECURSIVE_BACKTRACKING";
    case maze::GeneratorType::RECURSIVE_DIVISION:
      return "RECURSIVE_DIVISION";
    case maze::GeneratorType::SIDEWINDER:
      return "SIDEWINDER";
    case maze::GeneratorType::WILSONS:
      return "WILSONS";
  }
  assert(0 && "No such generator type.");
  return "";
}

std::string to_string(const maze::SolverType& solver_type) {
  switch (solver_type) {
    case maze::SolverType::BREADTH_FIRST_SEARCH:
      return "BREADTH_FIRST_SEARCH";
    case maze::SolverType::A_STAR:
      return "A_STAR";
    case maze::SolverType::DJIKSTRA:
      return "DJIKSTRA";
  }
  assert(0 && "No such solver type.");
  return "";
}

std::string to_string(const maze::PathType& path_type) {
  switch (path_type) {
    case maze::PathType::BOTTOM_TO_TOP:
      return "BOTTOM_TO_TOP";
    case maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT:
      return "BOTTOM_LEFT_TO_TOP_RIGHT";
    case maze::PathType::LEFT_TO_RIGHT:
      return "LEFT_TO_RIGHT";
    case maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT:
      return "TOP_LEFT_TO_BOTTOM_RIGHT";
    case maze::PathType::TOP_TO_BOTTOM:
      return "TOP_TO_BOTTOM";
  }
  assert(0 && "No such path type.");
  return "";
}

std::string to_string(const DifficultyLevel& difficulty) {
  switch (difficulty) {
    case DifficultyLevel::EASY:
      return "EASY";
    case DifficultyLevel::NORMAL:
      return "NORMAL";
    case DifficultyLevel::HARD:
      return "HARD";
  }
  assert(0 && "No such difficulty level.");
  return "";
}

std::string to_upper(const std::string& str) {
  std::string upper_case_str;
  for (const char c : str)
    upper_case_str += toupper(c);
  return upper_case_str;
}

maze::GeneratorType GetGeneratorType(const std::string& str) {
  for (int i = static_cast<int>(maze::GeneratorType::FIRST);
       i <= static_cast<int>(maze::GeneratorType::LAST); ++i) {
    const auto generator_type = static_cast<maze::GeneratorType>(i);
    if (to_string(generator_type) == str)
      return generator_type;
  }
  throw std::invalid_argument("Invalid generator type: '" + str + "'\n");
}

maze::SolverType GetSolverType(const std::string& str) {
  for (int i = static_cast<int>(maze::SolverType::FIRST);
       i <= static_cast<int>(maze::SolverType::LAST); ++i) {
    const auto solver_type = static_cast<maze::SolverType>(i);
    if (to_string(solver_type) == str)
      return solver_type;
  }
  throw std::invalid_argument("Invalid solver type: '" + str + "'\n");
}

maze::PathType GetPathType(const std::string& str) {
  for (int i = static_cast<int>(maze::PathType::FIRST);
       i <= static_cast<int>(maze::PathType::LAST); ++i) {
    const auto path_type = static_cast<maze::PathType>(i);
    if (to_string(path_type) == str)
      return path_type;
  }
  throw std::invalid_argument("Invalid path type: '" + str + "'\n");
}

DifficultyLevel GetDifficulty(const std::string& str) {
  for (int i = static_cast<int>(DifficultyLevel::FIRST);
       i <= static_cast<int>(DifficultyLevel::LAST); ++i) {
    const auto difficulty_level = static_cast<DifficultyLevel>(i);
    if (to_string(difficulty_level) == str)
      return difficulty_level;
  }
  throw std::invalid_argument("Invalid difficulty level: '" + str + "'\n");
}

void InterpretFlag(Flags& flags, const std::string& cmd_arg) {
  const static std::regex generator_type_regex(
      "^--(generator|generator_type)=([A-Za-z_]+)");
  const static std::regex solver_type_regex(
      "^--(solver|solver_type)=([A-Za-z_]+)");
  const static std::regex path_type_regex("^--(path|path_type)=([A-Za-z_]+)");
  const static std::regex difficulty_regex(
      "^--(difficulty|difficulty_level)=([A-Za-z]+)");
  const static std::regex size_regex("^--size=[{]([0-9]+), ?([0-9]+)[}]");
  std::smatch match;
  if (std::regex_search(cmd_arg, match, generator_type_regex)) {
    flags.generator_type = GetGeneratorType(to_upper(match[2].str()));
    return;
  }
  if (std::regex_search(cmd_arg, match, solver_type_regex)) {
    flags.solver_type = GetSolverType(to_upper(match[2].str()));
    return;
  }
  if (std::regex_search(cmd_arg, match, path_type_regex)) {
    flags.path_type = GetPathType(to_upper(match[2].str()));
    return;
  }
  if (std::regex_search(cmd_arg, match, difficulty_regex)) {
    flags.difficulty = GetDifficulty(to_upper(match[2].str()));
    return;
  }
  if (std::regex_search(cmd_arg, match, size_regex)) {
    flags.starting_size =
        maze::CellSize(std::stoi(match[1].str()), std::stoi(match[2].str()));
    return;
  }

  throw std::invalid_argument("Invalid command line argument: '" + cmd_arg +
                              "'\n");
}
}  // namespace

Flags GetDefaultFlags() {
  return {maze::GeneratorType::GROWING_TREE, maze::SolverType::A_STAR,
          maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT, DifficultyLevel::NORMAL,
          maze::CellSize(5, 5)};
}

Flags ReadFlags(int argc, char* argv[]) {
  Flags flags = GetDefaultFlags();
  for (int i = 1; i != argc; ++i) {
    const std::string cmd_arg = argv[i];
    InterpretFlag(flags, cmd_arg);
  }
  return flags;
}

}  // namespace game
