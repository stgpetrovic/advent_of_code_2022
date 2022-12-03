#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "day03/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day02, First) {
  std::string input = R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 157);
}

TEST(Day02, Second) {
  std::string input = R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 70);
}
