#include "day01/solution.h"

#include <glog/logging.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include "absl/strings/numbers.h"

std::priority_queue<int32_t> Parse(const std::vector<std::string>& in) {
  std::priority_queue<int32_t> cals;

  int32_t acc = 0;
  for (const auto& c : in) {
    if (c.empty()) {
      cals.push(acc);
      acc = 0;
      continue;
    }
    int32_t num;
    if (!absl::SimpleAtoi(c, &num)) {
      LOG(FATAL) << "Failed to parse as int: " << c;
    }
    acc += num;
  }
  return cals;
}

int32_t Solve(const std::vector<std::string>& in) {
  return Parse(in).top();
}

int32_t Solve2(const std::vector<std::string>& in) {
  int32_t acc = 0;
  auto cals = Parse(in);
  for (int i = 0; i < 3; ++i) {
    acc += cals.top();
    cals.pop();
  }
  return acc;
}
