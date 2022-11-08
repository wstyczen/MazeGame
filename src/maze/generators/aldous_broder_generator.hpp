#ifndef ALDOUS_BRODER_GENERATOR_HPP_
#define ALDOUS_BRODER_GENERATOR_HPP_

#include <memory>

#include "maze/generators/generator.hpp"
#include "maze/unvisited.hpp"

namespace maze {

class Layout;

class AldousBroderGenerator : public Generator, public Unvisited {
 public:
  ~AldousBroderGenerator();
  std::unique_ptr<Layout> Get(const CellSize& cell_size) final;

 private:
  AldousBroderGenerator();

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // ALDOUS_BRODER_GENERATOR_HPP_
