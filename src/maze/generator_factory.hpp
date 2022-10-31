#ifndef GENERATOR_FACTORY_
#define GENERATOR_FACTORY_

#include <memory>

#include "generator.hpp"

namespace maze {

enum class GeneratorType {
  KRUSKALS,
  GROWING_TREE,
  PRIMS,
  RECURSIVE_BACKGTRACKING,
};

class GeneratorFactory {
 public:
  ~GeneratorFactory();
  static GeneratorFactory* GetInstance();

  std::unique_ptr<Generator> GetGenerator(const GeneratorType& generator_type);

 private:
  GeneratorFactory();

  static GeneratorFactory* instance_;
};

}  // namespace maze

#endif  // GENERATOR_FACTORY_
