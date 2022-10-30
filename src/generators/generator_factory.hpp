#ifndef GENERATOR_FACTORY_
#define GENERATOR_FACTORY_

#include <memory>

#include "generator.hpp"

namespace maze {

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
