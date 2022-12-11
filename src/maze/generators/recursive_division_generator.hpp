#ifndef MAZE_RECURSIVE_DIVISION_GENERATOR_HPP_
#define MAZE_RECURSIVE_DIVISION_GENERATOR_HPP_

#include "maze/generators/generator.hpp"

#include <iterator>

namespace maze {

class RecursiveDivisionGenerator : public Generator {
  enum class DivisionDirection {
    HORIZONTAL,
    VERTICAL,
  };
  struct Limits {
    uint16_t low, high;
    uint16_t PickRandom() const {
      if (high - low == kStep)
        return low + 1;
      return low + 1 +
             GetRandomNumber((high - low - kStep) / kStep - 1) * kStep;
    }
    std::vector<uint16_t> GetWall() const {
      std::vector<uint16_t> wall;
      wall.reserve(high - low + 1);
      for (uint16_t i = low; i <= high; i += kStep)
        wall.push_back(i);
      wall.erase(std::next(wall.begin(), GetRandomNumber(wall.size() - 1)));
      return wall;
    }
  };

 public:
  ~RecursiveDivisionGenerator();
  std::unique_ptr<Layout> Get(const CellSize& cell_size) final;

 private:
  RecursiveDivisionGenerator();

  DivisionDirection GetRandomDivisionDirection();
  void Divide(Layout* const layout,
              const DivisionDirection& division_direction,
              const Limits& horizontal_limits,
              const Limits& vertical_limits);

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_RECURSIVE_DIVISION_GENERATOR_HPP_
