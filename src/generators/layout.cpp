#include "layout.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "utility.hpp"

namespace maze {

namespace {

uint16_t GetLayoutSizeFromTiles(const uint16_t& tiles) {
  return tiles * kStep + kFirstTileIndex;
}

}  // namespace

Layout::Layout(const uint16_t& vertical_tiles, const uint16_t& horizontal_tiles)
    : rows_(GetLayoutSizeFromTiles(vertical_tiles)),
      cols_(GetLayoutSizeFromTiles(horizontal_tiles)) {
  assert(
      (vertical_tiles % kStep != 0 && horizontal_tiles % kStep != 0) &&
      "Even tile size provided."
  );
  layout_.reserve(rows_);
  for (size_t i = 0; i != rows_; i += 1) {
    if (i % kStep == 0)
      layout_.push_back(std::vector<char>(cols_, kBlocked));
    else {
      std::vector<char> row = std::vector<char>(cols_, kBlocked);
      for (size_t j = kFirstTileIndex; j <= cols_; j += kStep)
        row[j] = kEmpty;
      layout_.push_back(std::move(row));
    }
  }
}

uint16_t Layout::rows() const {
  return rows_;
}
uint16_t Layout::cols() const {
  return cols_;
}
uint16_t Layout::middle_row() const {
  return rows_ / kStep;
}
uint16_t Layout::bottom_row() const {
  return rows_ - 2;
}
uint16_t Layout::middle_col() const {
  return cols_ / kStep;
}
uint16_t Layout::rightmost_col() const {
  return cols_ - 2;
}

bool Layout::IsWithin(const Position& position) const {
  return position.y > 0 && position.y < rows_ && position.x > 0 &&
         position.x < cols_;
}

bool Layout::IsBlocked(const Position& position) const {
  assert(IsWithin(position) && "Trying to access a tile out of range.");
  return layout_.at(position.y).at(position.x) == kBlocked;
}

bool Layout::CanMove(const Edge& edge) const {
  std::optional<Position> at_half_step = edge.To(kHalfStep);
  return (IsWithin(*at_half_step) && !IsBlocked(*at_half_step));
}

void Layout::Unblock(const Edge& edge) {
  const std::optional<Position> to = edge.To();
  assert(to && "Invalid Direction enum passed to Edge instance.");
  const Position to_unblock = {
      (edge.from.y + to->y) / uint16_t{2}, (edge.from.x + to->x) / uint16_t{2}};
  layout_.at(to_unblock.y).at(to_unblock.x) = kUnblocked;
}

void Layout::AddPath(const Path& path) {
  for (const Position& position : path)
    layout_.at(position.y).at(position.x) = kPath;
}

void Layout::Show() const {
  for (const std::vector<char>& row : layout_) {
    for (const char& c : row) {
      switch (c) {
        case kBlocked:
          std::cout << "\u2588";
          continue;
        case kUnblocked:
        case kEmpty: {
          std::cout << " ";
          continue;
        }
        case kPath: {
          std::cout << "\u26CC";
          continue;
        }
      }
    }
    std::cout << "\n";
  }
}

}  // namespace maze
