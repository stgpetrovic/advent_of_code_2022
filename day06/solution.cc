#include "day06/solution.h"

#include <glog/logging.h>

#include <string>
#include <unordered_map>
#include <vector>

int32_t SolveGeneric(const std::vector<std::string>& in,
                     int32_t distinct_length) {
  std::unordered_map<char, int32_t> buffer;
  for (int i = 0; i < in[0].size(); ++i) {
    char c = in[0][i];
    buffer[c]++;
    if (i > distinct_length - 1) {
      char out = in[0][i - distinct_length];
      if (buffer[out] == 1) {
        buffer.erase(out);
      } else {
        buffer[out]--;
      }
    }
    if (buffer.size() == distinct_length) {
      return i + 1;
    }
  }
  return -1;
}

int32_t Solve(const std::vector<std::string>& in) {
  return SolveGeneric(in, 4);
}

int32_t Solve2(const std::vector<std::string>& in) {
  return SolveGeneric(in, 14);
}

