#include "layout.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>

#include "utility.hpp"

namespace maze {

namespace {

uint16_t GetMazeDimensionFromCells(const uint16_t& cells) {
  return cells * kStep + kLayoutFirstCellIndex;
}

LayoutSize GetLayoutSizeFromCellSize(const CellSize& cell_size) {
  return {
      GetMazeDimensionFromCells(cell_size.rows),
      GetMazeDimensionFromCells(cell_size.cols)};
}
}  // namespace

Layout::Layout(const CellSize& cell_size)
    : size_(GetLayoutSizeFromCellSize(cell_size)) {
  assert(
      (cell_size.rows % kStep != 0 && cell_size.cols % kStep != 0) &&
      "Even Cell size provided - only odd accepted."
  );

  const auto& [rows, cols] = size_;

  layout_.reserve(rows);
  for (size_t i = 0; i != rows; i += 1) {
    if (i % kStep == 0)
      layout_.push_back(std::vector<char>(cols, kWall));
    else {
      auto row = std::vector<char>(cols, kWall);
      for (size_t j = kLayoutFirstCellIndex; j <= cols; j += kStep)
        row[j] = kCell;
      layout_.push_back(std::move(row));
    }
  }
}

LayoutSize Layout::size() const {
  return size_;
}

uint16_t Layout::middle_row() const {
  return size_.rows / kStep;
}
uint16_t Layout::bottom_row() const {
  return size_.rows - 2;
}
uint16_t Layout::middle_col() const {
  return size_.cols / kStep;
}
uint16_t Layout::rightmost_col() const {
  return size_.cols - 2;
}

bool Layout::IsWithin(const Position& position) const {
  return position.row > 0 && position.row < size_.rows && position.col > 0 &&
         position.col < size_.cols;
}

bool Layout::IsBlocked(const Position& position) const {
  assert(
      IsWithin(position) && "Trying to access a cell outside of the layout."
  );
  return layout_.at(position.row).at(position.col) == kWall;
}

bool Layout::IsACell(const Position& position) const {
  assert(
      IsWithin(position) && "Trying to access a cell outside of the layout."
  );
  return std::unordered_set<char>{kCell, kLocation, kPath}.contains(
      layout_.at(position.row).at(position.col)
  );
}

bool Layout::CanMove(const Edge& edge) const {
  return edge.To() && IsWithin(*edge.To()) && !IsBlocked(*edge.To(kHalfStep));
}

void Layout::Unblock(const Edge& edge) {
  const std::optional<Cell> to = edge.To();
  assert(to && "Invalid Direction enum passed to Edge instance.");
  const Cell to_unblock(
      (edge.from.row + to->row) / 2, (edge.from.col + to->col) / 2
  );
  layout_.at(to_unblock.row).at(to_unblock.col) = kDoor;
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
  for (const Cell& position : path)
    layout_.at(position.row).at(position.col) = kPath;
}

void Layout::SetLocation(const Cell& cell) {
  assert(IsACell(cell) && "Trying to set a location that is not a cell.");
  layout_.at(cell.row).at(cell.col) = kLocation;
}

void Layout::ClearCells() {
  for (size_t i = kLayoutFirstCellIndex; i < size_.rows; i += kStep)
    for (size_t j = kLayoutFirstCellIndex; j < size_.cols; j += kStep)
      layout_.at(i).at(j) = kCell;
}

}  // namespace maze
