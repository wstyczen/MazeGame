#include "layout.hpp"

#include <cassert>
#include <iostream>

#include "utility.hpp"

namespace {

inline size_t GetExpandedSize(const size_t& original) {
  return 2 * original + 1;
}

inline Position GetExpandedPosition(const Position& position) {
  return Position(GetExpandedSize(position.y), GetExpandedSize(position.x));
}

}  // namespace

namespace maze {

Layout::Layout(const uint16_t& N, const uint16_t& M) {
  const uint16_t rows = GetExpandedSize(N), cols = GetExpandedSize(M);
  layout_.reserve(rows);
  for (size_t i = 0; i != rows; i += 1) {
    if (i % 2 == 0)
      layout_.push_back(std::vector<char>(cols, kBlocked));
    else {
      std::vector<char> row = std::vector<char>(cols, kBlocked);
      for (size_t j = 1; j <= cols; j += 2)
        row[j] = kEmpty;
      layout_.push_back(std::move(row));
    }
  }
}

void Layout::Unblock(const Edge& edge) {
  const std::optional<Position> to_unblock =
      Edge(GetExpandedPosition(edge.from_), edge.direction_).To();
  assert(to_unblock && "Invalid enum value passed.");
  layout_.at(to_unblock->y).at(to_unblock->x) = kUnblocked;
}

void Layout::Show() const {
  for (const std::vector<char>& row : layout_) {
    for (const char& c : row) {
      switch (c) {
        case kBlocked:
          std::cout << "\u2587";
          continue;
        case kUnblocked: {
          std::cout << " ";
          continue;
        }
        case kEmpty: {
          std::cout << " ";
          continue;
        }
      }
    }
    std::cout << "\n";
  }
}

}  // namespace maze
