#include "layout.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>

#include "utility.hpp"

namespace maze {

namespace {

uint16_t GetLayoutSizeFromCells(const uint16_t& cell_count) {
  return cell_count * kStep + kFirstCellIndex;
}

}  // namespace

Layout::Layout(const uint16_t& vertical_cells, const uint16_t& horizontal_cells)
    : rows_(GetLayoutSizeFromCells(vertical_cells)),
      cols_(GetLayoutSizeFromCells(horizontal_cells)) {
  assert(
      (vertical_cells % kStep != 0 && horizontal_cells % kStep != 0) &&
      "Even Cell size provided."
  );
  layout_.reserve(rows_);
  for (size_t i = 0; i != rows_; i += 1) {
    if (i % kStep == 0)
      layout_.push_back(std::vector<char>(cols_, kWall));
    else {
      std::vector<char> row = std::vector<char>(cols_, kWall);
      for (size_t j = kFirstCellIndex; j <= cols_; j += kStep)
        row[j] = kCell;
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
  assert(
      IsWithin(position) && "Trying to access a cell outside of the layout."
  );
  return layout_.at(position.y).at(position.x) == kWall;
}

bool Layout::IsACell(const Position& position) const {
  assert(
      IsWithin(position) && "Trying to access a cell outside of the layout."
  );
  return std::set<char>{kCell, kLocation, kPath}.contains(
      layout_.at(position.y).at(position.x)
  );
}

bool Layout::CanMove(const Edge& edge) const {
  return IsWithin(*edge.To()) && !IsBlocked(*edge.To(kHalfStep));
}

void Layout::Unblock(const Edge& edge) {
  const std::optional<Position> to = edge.To();
  assert(to && "Invalid Direction enum passed to Edge instance.");
  const Position to_unblock = {
      (edge.from.y + to->y) / uint16_t{2}, (edge.from.x + to->x) / uint16_t{2}};
  layout_.at(to_unblock.y).at(to_unblock.x) = kDoor;
}

void Layout::Show() const {
  for (const std::vector<char>& row : layout_) {
    for (const char& c : row) {
      switch (c) {
        case kWall:
          std::cout << "\u2588";
          continue;
        case kCell:
        case kDoor: {
          std::cout << " ";
          continue;
        }
        case kPath: {
          std::cout << "\u26CC";
          continue;
        }
        case kLocation: {
          std::cout << "\u24E7";
          continue;
        }
      }
    }
    std::cout << "\n";
  }
}

void Layout::AddPath(const Path& path) {
  for (const Position& position : path)
    layout_.at(position.y).at(position.x) = kPath;
}

void Layout::SetLocation(const Position& position) {
  assert(IsACell(position) && "Trying to set a location that is not a cell.");
  layout_.at(position.y).at(position.x) = kLocation;
}

void Layout::ClearCells() {
  for (size_t i = kFirstCellIndex; i < rows_; i += kStep)
    for (size_t j = kFirstCellIndex; j < cols_; j += kStep)
      layout_.at(i).at(j) = kCell;
}

}  // namespace maze
