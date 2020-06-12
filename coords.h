#pragma once

#include <map>
#include <tuple>

using Direction = ushort;
using Coord = short;
using CoordDirection = std::tuple<Coord, Coord, Direction>;

const Direction N = 0b0001;
const Direction S = 0b0010;
const Direction E = 0b0100;
const Direction W = 0b1000;

const Direction IN = 0x10; // 0b10000

const std::map<Direction, short> DX = {
  {E, 1},
  {W, -1},
  {N, 0},
  {S, 0},
};

const std::map<Direction, short> DY = {
  {E, 0},
  {W, 0},
  {N, -1},
  {S, 1},
};

const std::map<Direction, Direction> OPPOSITE = {
  {E, W},
  {W, E},
  {N, S},
  {S, N},
};

