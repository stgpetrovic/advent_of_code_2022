#include "day04/solution.h"

#include <glog/logging.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/types/span.h"

struct Interval {
  int32_t l;
  int32_t r;

  std::string ToString() { return absl::StrCat(l, "-", r); }
  bool Contains(const Interval& other) { return l <= other.l && r >= other.r; }
  bool Overlaps(const Interval& other) {
    if (l == other.l || r == other.r) {
      return true;
    }
    if (l < other.l) {
      return other.l <= r;
    } else {
      return other.r >= l;
    }
  }
};

Interval ParseInterval(const std::string& spec) {
  std::vector<std::string> parts = absl::StrSplit(spec, "-");
  Interval i;
  if (!absl::SimpleAtoi(parts[0], &i.l) || !absl::SimpleAtoi(parts[1], &i.r)) {
    LOG(FATAL) << "Failed to parse spec " << spec;
  }
  return i;
}

std::pair<Interval, Interval> ParseSpec(const std::string& spec) {
  std::vector<std::string> parts = absl::StrSplit(spec, ",");
  return {ParseInterval(parts[0]), ParseInterval(parts[1])};
}

int32_t Solve(const std::vector<std::string>& in) {
  int32_t count = 0;
  for (const auto& row : in) {
    auto spec = ParseSpec(row);
    if (spec.first.Contains(spec.second) || spec.second.Contains(spec.first)) {
      ++count;
    }
  }
  return count;
}

int32_t Solve2(const std::vector<std::string>& in) {
  int32_t count = 0;
  for (const auto& row : in) {
    auto spec = ParseSpec(row);
    if (spec.first.Overlaps(spec.second)) {
      ++count;
    }
  }
  return count;
}
