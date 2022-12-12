#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "day08/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day, First) {
  auto input = R"(30373
25512
65332
33549
35390)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 21);
}

TEST(Day, Second) {
  auto input = R"(30373
25512
65332
33549
35390)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 8);
}
