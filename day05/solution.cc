#include "day05/solution.h"

#include <glog/logging.h>

#include <algorithm>
#include <cstdint>
#include <deque>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/types/span.h"

enum Crane { CrateMover9000, CrateMover9001 };

class Bauplatz {
 public:
  Bauplatz(const std::string& spec) : max_stacks_(0) {
    stacks_.resize(10);
    std::vector<std::string> lines = absl::StrSplit(spec, "\n");
    for (int i = lines.size() - 2; i >= 0; --i) {
      for (int j = 1; j < lines[i].length(); j += 4) {
        if (lines[i][j] == ' ') {
          continue;
        }
        stacks_[(j - 1) / 4].push(lines[i][j]);
        max_stacks_ = std::max(max_stacks_, (j - 1) / 4 + 1);
      }
    }
    stacks_.resize(max_stacks_);
  }

  void Run(const std::string& program, Crane crane = CrateMover9000) {
    for (const auto& instruction : absl::StrSplit(program, "\n")) {
      std::vector<std::string> parts = absl::StrSplit(instruction, ' ');
      int32_t count, from, to;
      if (!absl::SimpleAtoi(parts[1], &count) ||
          !absl::SimpleAtoi(parts[3], &from) ||
          !absl::SimpleAtoi(parts[5], &to)) {
        LOG(FATAL) << "Failed to parse instruction " << instruction;
      }

      if (crane == CrateMover9000) {
        PopPush(&stacks_[from - 1], &stacks_[to - 1], count);
      } else {
        std::stack<char> buffer;
        PopPush(&stacks_[from - 1], &buffer, count);
        PopPush(&buffer, &stacks_[to - 1], count);
      }
    }
  }

  std::string CollectTops() const {
    std::string tops;
    for (const auto& stack : stacks_) {
      tops += stack.empty() ? ' ' : stack.top();
    }
    return tops;
  }

 private:
  void PopPush(std::stack<char>* from, std::stack<char>* to, int32_t count) {
    for (int i = 0; i < count; ++i) {
      char t = from->top();
      from->pop();
      to->push(t);
    }
  }

  std::vector<std::stack<char>> stacks_;
  int32_t max_stacks_;
};

std::string SolveGeneric(const std::vector<std::string>& in, Crane crane) {
  std::vector<std::string> parts =
      absl::StrSplit(absl::StrJoin(in, "\n"), "\n\n");
  Bauplatz bp(parts[0]);
  bp.Run(parts[1], crane);
  return bp.CollectTops();
}

std::string Solve(const std::vector<std::string>& in) {
  return SolveGeneric(in, CrateMover9000);
}

std::string Solve2(const std::vector<std::string>& in) {
  return SolveGeneric(in, CrateMover9001);
}

