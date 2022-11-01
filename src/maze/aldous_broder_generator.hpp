#ifndef ALDOUS_BRODER_GENERATOR_HPP_
#define ALDOUS_BRODER_GENERATOR_HPP_

#include <memory>

#include "generator.hpp"
#include "unvisited.hpp"

namespace maze {

class Layout;

class AldousBroderGenerator : public Generator, public Unvisited {
 public:
  ~AldousBroderGenerator();
  std::unique_ptr<Layout>
  Get(const uint16_t& cells_vertical, const uint16_t& cells_horizontal) final;

 private:
  AldousBroderGenerator();

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // ALDOUS_BRODER_GENERATOR_HPP_
