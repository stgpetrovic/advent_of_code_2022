
#include "day08/solution.h"

#include <glog/logging.h>

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

enum Direction { L, R, U, D };

int64_t Solve(const std::vector<std::string>& in) {
  int x = in.size(), y = in[0].size();

  char max_x[99][99];
  char max_y[99][99];
  char max_rx[99][99];
  char max_ry[99][99];
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      max_x[i][j] = std::max((j == 0 ? '0' : max_x[i][j - 1]), in[i][j]);
      max_y[i][j] = std::max((i == 0 ? '0' : max_y[i - 1][j]), in[i][j]);

      max_rx[i][y - j - 1] =
          std::max((j == 0 ? '0' : max_rx[i][y - j]), in[i][y - j - 1]);
      max_ry[x - i - 1][j] =
          std::max((i == 0 ? '0' : max_ry[x - i][j]), in[x - i - 1][j]);
    }
  }
  int32_t total_visible = 0;
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      if (i == 0 || j == 0 || i == x - 1 || j == y - 1 ||
          in[i][j] > max_x[i][j - 1] || in[i][j] > max_rx[i][j + 1] ||
          in[i][j] > max_y[i - 1][j] || in[i][j] > max_ry[i + 1][j]) {
        ++total_visible;
      }
    }
  }

  return total_visible;
}

int32_t Visible(const std::vector<std::string>& in, int i, int j, Direction d) {
  int32_t di = 0, dj = 0;
  switch (d) {
    case L:
      dj = -1;
      break;
    case R:
      dj = +1;
      break;
    case U:
      di = -1;
      break;
    case D:
      di = +1;
      break;
    default:
      LOG(FATAL) << "deces bre";
  }

  int32_t dist = 1;
  auto fits = [&in](int i, int j) {
    return i >= 0 && i < in.size() && j >= 0 && j < in[i].size();
  };
  int32_t ti = i + di;
  int32_t tj = j + dj;
  while (fits(ti, tj) && in[ti][tj] < in[i][j]) {
    ti += di;
    tj += dj;
    ++dist;
  }
  if (!fits(ti, tj)) {
    --dist;
  }
  return dist;
}

int64_t Solve2(const std::vector<std::string>& in) {
  int x = in.size(), y = in[0].size();
  int32_t max_score = 0;
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      max_score =
          std::max(max_score, Visible(in, i, j, L) * Visible(in, i, j, R) *
                                  Visible(in, i, j, U) * Visible(in, i, j, D));
    }
  }
  return max_score;
}

