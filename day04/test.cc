#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "day04/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day02, First) {
  std::string input = R"(2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 2);
}

TEST(Day02, Second) {
  std::string input = R"(2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 4);
}
