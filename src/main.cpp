#include "generators/generator.hpp"
#include "generators/generator_factory.hpp"
#include "generators/kruskals_generator.hpp"
#include "generators/layout.hpp"

#include <ctime>
#include <iostream>
#include <memory>

int main() {
  std::srand(std::time(0));  // use current time as seed for random generator

  std::unique_ptr<maze::Generator> kruskals =
      maze::GeneratorFactory::GetInstance()->GetGenerator(
          maze::GeneratorType::KRUSKALS
      );
  const std::unique_ptr<maze::Layout> maze_layout = kruskals->Get(30, 80);
  maze_layout->Show();

  return 0;
}
