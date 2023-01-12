#include <iostream>

#include "game/difficulty.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/paths.hpp"
#include "maze/solvers/solver_factory.hpp"

#ifndef GAME_SETTINGS_HPP_
#define GAME_SETTINGS_HPP_

namespace game {

// Can be provided via command line switches
// Usage: --<switch>=<value>
struct Settings {
  friend std::ostream& operator<<(std::ostream& os, const Settings& settings);

  maze::GeneratorType generator_type;  // --generator, --generator_type
  maze::SolverType solver_type;        // --solver, --solver_type
  maze::PathType path_type;            // --path, --path_type
  DifficultyLevel difficulty;          // --difficulty, --difficulty_level
  maze::CellSize starting_size;        // --size={rows, cols}
};
using Flags = Settings;

Flags GetDefaultFlags();
Flags ReadFlags(int argc, char* argv[]);

}  // namespace game

#endif  // GAME_SETTINGS_HPP_
