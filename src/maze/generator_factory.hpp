#ifndef GENERATOR_FACTORY_
#define GENERATOR_FACTORY_

#include <memory>

#include "generator.hpp"

namespace maze {

enum class GeneratorType {
  FIRST,
  ALDOUS_BRODER = FIRST,
  GROWING_TREE,
  ELLERS,
  KRUSKALS,
  PRIMS,
  RECURSIVE_BACKTRACKING,
  WILSONS_GENERATOR,
  LAST = WILSONS_GENERATOR,
};

class GeneratorFactory {
 public:
  ~GeneratorFactory();
  static GeneratorFactory* GetInstance();

  std::string GetGeneratorName(const GeneratorType& generator_type) const;
  std::unique_ptr<Generator> GetGenerator(const GeneratorType& generator_type
  ) const;

 private:
  GeneratorFactory();

  static GeneratorFactory* instance_;
};

}  // namespace maze

#endif  // GENERATOR_FACTORY_
