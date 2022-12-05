#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "day05/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day02, First) {
  std::string input = R"(    [D]
[N] [C]
[Z] [M] [P]
1   2   3

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, "CMZ");
}

TEST(Day02, Second) {
  std::string input = R"(    [D]
[N] [C]
[Z] [M] [P]
1   2   3

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, "MCD");
}
