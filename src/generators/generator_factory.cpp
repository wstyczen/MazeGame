#include "generator_factory.hpp"

#include <memory>

#include "generator.hpp"
#include "kruskals_generator.hpp"
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
    case GeneratorType::KRUSKALS:
      return std::unique_ptr<Generator>(new KruskalsGenerator);
    case GeneratorType::RECURSIVE_BACKGTRACKING:
      return std::unique_ptr<Generator>(new RecursiveBacktrackingGenerator);
  }
  return nullptr;
}

}  // namespace maze
