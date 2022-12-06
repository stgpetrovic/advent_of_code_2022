#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "day06/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day02, First) {
  auto input = R"(mjqjpqmgbljsphdztnvjfqwrcgsmlb)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 7);
}

TEST(Day02, Second) {
  auto input = R"(mjqjpqmgbljsphdztnvjfqwrcgsmlb)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 19);
}

