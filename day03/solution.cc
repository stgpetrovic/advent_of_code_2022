#include "day03/solution.h"

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
#include "absl/types/span.h"

int32_t Priority(char c) {
  if (c >= 'a') {
    return c - 'a' + 1;
  }
  return c - 'A' + 1 + 26;
}

int32_t Solve(const std::vector<std::string>& in) {
  int32_t psum = 0;
  for (std::string r : in) {
    std::vector<char> i;
    std::sort(r.begin(), r.begin() + r.size() / 2);
    std::sort(r.begin() + r.size() / 2, r.end());
    std::set_intersection(r.begin(), r.begin() + r.size() / 2,
                          r.begin() + r.size() / 2, r.end(),
                          std::back_inserter(i));
    psum += Priority(i[0]);
  }

  return psum;
}

int32_t Solve2(const std::vector<std::string>& in) {
  int32_t psum = 0;
  int i = 0;
  std::string seen;
  for (std::string r : in) {
    absl::c_sort(r);
    ++i;
    if (seen.empty()) {
      seen = r;
      continue;
    }

    std::string updated_seen;
    absl::c_set_intersection(seen, r, std::back_inserter(updated_seen));
    seen = updated_seen;

    if (i == 3) {
      psum += Priority(seen[0]);
      seen.clear();
      i = 0;
    }
  }
  return psum;
}
