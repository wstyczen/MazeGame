#include "maze/generators/generator_factory.hpp"

#include <cassert>
#include <memory>

#include "maze/generators/aldous_broder_generator.hpp"
#include "maze/generators/ellers_generator.hpp"
#include "maze/generators/generator.hpp"
#include "maze/generators/growing_tree_generator.hpp"
#include "maze/generators/hunt_and_kill_generator.hpp"
#include "maze/generators/kruskals_generator.hpp"
#include "maze/generators/prims_generator.hpp"
#include "maze/generators/recursive_backtracking_generator.hpp"
#include "maze/generators/recursive_division_generator.hpp"
#include "maze/generators/sidewinder_generator.hpp"
#include "maze/generators/wilsons_generator.hpp"

namespace maze {

GeneratorFactory* GeneratorFactory::instance_ = nullptr;

GeneratorFactory::GeneratorFactory() = default;

GeneratorFactory::~GeneratorFactory() = default;

GeneratorFactory* GeneratorFactory::GetInstance() {
  if (!instance_)
    instance_ = new GeneratorFactory;
  return instance_;
}

std::string GeneratorFactory::GetGeneratorName(
    const GeneratorType& generator_type) const {
  switch (generator_type) {
    case GeneratorType::ALDOUS_BRODER:
      return "Aldous-Broder";
    case GeneratorType::ELLERS:
      return "Eller's";
    case GeneratorType::GROWING_TREE:
      return "Growing Tree";
    case GeneratorType::HUNT_AND_KILL:
      return "Hunt and Kill";
    case GeneratorType::KRUSKALS:
      return "Kruskal's";
    case GeneratorType::PRIMS:
      return "Prim's";
    case GeneratorType::RECURSIVE_BACKTRACKING:
      return "Recursive Backtracking";
    case GeneratorType::RECURSIVE_DIVISION:
      return "Recursive Division";
    case GeneratorType::SIDEWINDER:
      return "Sidewinder";
    case GeneratorType::WILSONS:
      return "Wilson's";
  }
  assert(0 && "No such generator type.");
  return "";
}

std::unique_ptr<Generator> GeneratorFactory::GetGenerator(
    const GeneratorType& generator_type) const {
  switch (generator_type) {
    case GeneratorType::ALDOUS_BRODER:
      return std::unique_ptr<Generator>(new AldousBroderGenerator);
    case GeneratorType::ELLERS:
      return std::unique_ptr<Generator>(new EllersGenerator);
    case GeneratorType::GROWING_TREE:
      return std::unique_ptr<Generator>(new GrowingTreeGenerator);
    case GeneratorType::HUNT_AND_KILL:
      return std::unique_ptr<Generator>(new HuntAndKillGenerator);
    case GeneratorType::KRUSKALS:
      return std::unique_ptr<Generator>(new KruskalsGenerator);
    case GeneratorType::PRIMS:
      return std::unique_ptr<Generator>(new PrimsGenerator);
    case GeneratorType::RECURSIVE_BACKTRACKING:
      return std::unique_ptr<Generator>(new RecursiveBacktrackingGenerator);
    case GeneratorType::RECURSIVE_DIVISION:
      return std::unique_ptr<Generator>(new RecursiveDivisionGenerator);
    case GeneratorType::SIDEWINDER:
      return std::unique_ptr<Generator>(new SidewinderGenerator);
    case GeneratorType::WILSONS:
      return std::unique_ptr<Generator>(new WilsonsGenerator);
  }
  assert(0 && "No such generator type.");
  return nullptr;
}

}  // namespace maze
