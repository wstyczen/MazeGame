#include "generator_factory.hpp"

#include <cassert>
#include <memory>

#include "aldous_broder_generator.hpp"
#include "generator.hpp"
#include "growing_tree_generator.hpp"
#include "kruskals_generator.hpp"
#include "prims_generator.hpp"
#include "recursive_backtracking_generator.hpp"
#include "wilsons_generator.hpp"

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
    const GeneratorType& generator_type
) const {
  switch (generator_type) {
    case GeneratorType::ALDOUS_BRODER:
      return "Aldous-Broder";
    case GeneratorType::GROWING_TREE:
      return "Growing Tree";
    case GeneratorType::KRUSKALS:
      return "Kruskal's";
    case GeneratorType::PRIMS:
      return "Prim's";
    case GeneratorType::RECURSIVE_BACKTRACKING:
      return "Recursive Backtracking";
    case GeneratorType::WILSONS_GENERATOR:
      return "Wilson's";
  }
  assert(0 && "No such generator type.");
  return "";
}

std::unique_ptr<Generator> GeneratorFactory::GetGenerator(
    const GeneratorType& generator_type
) const {
  switch (generator_type) {
    case GeneratorType::ALDOUS_BRODER:
      return std::unique_ptr<Generator>(new AldousBroderGenerator);
    case GeneratorType::GROWING_TREE:
      return std::unique_ptr<Generator>(new GrowingTreeGenerator);
    case GeneratorType::KRUSKALS:
      return std::unique_ptr<Generator>(new KruskalsGenerator);
    case GeneratorType::PRIMS:
      return std::unique_ptr<Generator>(new PrimsGenerator);
    case GeneratorType::RECURSIVE_BACKTRACKING:
      return std::unique_ptr<Generator>(new RecursiveBacktrackingGenerator);
    case GeneratorType::WILSONS_GENERATOR:
      return std::unique_ptr<Generator>(new WilsonsGenerator);
  }
  assert(0 && "No such generator type.");
  return nullptr;
}

}  // namespace maze
