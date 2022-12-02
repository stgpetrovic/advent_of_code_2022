#include "day02/solution.h"

#include <glog/logging.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include "absl/strings/numbers.h"

enum Move {
  ROCK, PAPER, SCISSORS
};

Move ParseMove(char c) {
  switch (c) {
    case 'A':
    case 'X':
      return ROCK;
    case 'B':
    case 'Y':
      return PAPER;
    case 'C':
    case 'Z':
      return SCISSORS;
  }
  LOG(INFO) << "Unknown move " << c;
  exit(1);
}

int32_t PointForMove(Move m) {
  switch (m) {
    case ROCK:
      return 1;
    case PAPER:
      return 2;
    case SCISSORS:
      return 3;
  }
  LOG(INFO) << "Unknown move " << m;
  exit(1);
}

bool Beats(Move first, Move second) {
  if (first == ROCK && second == SCISSORS) {
    return true;
  }
  else if (first == SCISSORS && second == PAPER) {
    return true;
  }
  else if (first == PAPER && second == ROCK) {
    return true;
  }
  return false;
}

int32_t Points(Move you, Move other) {
  if (you == other) {
    return 3;
  }
  if (Beats(you, other)) {
    return 6;
  }
  return 0;
}

int32_t Solve(const std::vector<std::string>& in) {
  int32_t points = 0;
  for (const auto& line : in) {
    Move they = ParseMove(line[0]);
    Move you = ParseMove(line[2]);
    points += PointForMove(you) + Points(you, they);
  }
  return points;
}

enum Action {
  LOSE, DRAW, WIN
};

Action ParseAction(char c) {
  switch (c) {
    case 'X':
      return LOSE;
    case 'Y':
      return DRAW;
    case 'Z':
      return WIN;
  }
  LOG(INFO) << "Unknown action: " << c;
  exit(1);
}

Move MoveForAction(Move they, Action a) {
  if (a == DRAW) {
    return they;
  }
  if (a == LOSE) {
    switch (they) {
      case ROCK:
        return SCISSORS;
      case PAPER:
        return ROCK;
      case SCISSORS:
        return PAPER;
    }
  } else if (a == WIN) {
    switch (they) {
      case ROCK:
        return PAPER;
      case PAPER:
        return SCISSORS;
      case SCISSORS:
        return ROCK;
    }
  }
  LOG(INFO) << "Unexpected inputs move = " << they << " action = " << a;
  exit(1);
}

int32_t Solve2(const std::vector<std::string>& in) {
  int32_t points = 0;
  for (const auto& line : in) {
    Move they = ParseMove(line[0]);
    Action action = ParseAction(line[2]);
    Move you = MoveForAction(they, action);
    points += PointForMove(you) + Points(you, they);
  }
  return points;
}
