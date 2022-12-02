#include <vector>

#include <string>

#include "absl/strings/str_split.h"
#include "day02/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"


TEST(Day02, First) {
  std::string input =R"(A Y
B X
C Z)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 15);
}

TEST(Day02, Second) {
  std::string input =R"(A Y
B X
C Z)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 12);
}
