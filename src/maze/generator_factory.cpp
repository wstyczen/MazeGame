#include "generator_factory.hpp"

#include <memory>

#include "aldous_broder_generator.hpp"
#include "generator.hpp"
#include "growing_tree_generator.hpp"
#include "kruskals_generator.hpp"
#include "prims_generator.hpp"
#include "recursive_backtracking_generator.hpp"

namespace maze {

GeneratorFactory* GeneratorFactory::instance_ = nullptr;

GeneratorFactory::GeneratorFactory() = default;

GeneratorFactory::~GeneratorFactory() = default;

GeneratorFactory* GeneratorFactory::GetInstance() {
  if (!instance_)
    instance_ = new GeneratorFactory;
  return instance_;
}

std::unique_ptr<Generator> GeneratorFactory::GetGenerator(
    const GeneratorType& generator_type
) {
  switch (generator_type) {
    case GeneratorType::ALDOUS_BRODER:
      return std::unique_ptr<Generator>(new AldousBroderGenerator);
    case GeneratorType::GROWING_TREE:
      return std::unique_ptr<Generator>(new GrowingTreeGenerator);
    case GeneratorType::KRUSKALS:
      return std::unique_ptr<Generator>(new KruskalsGenerator);
    case GeneratorType::PRIMS:
      return std::unique_ptr<Generator>(new PrimsGenerator);
    case GeneratorType::RECURSIVE_BACKGTRACKING:
      return std::unique_ptr<Generator>(new RecursiveBacktrackingGenerator);
  }
  return nullptr;
}

}  // namespace maze
