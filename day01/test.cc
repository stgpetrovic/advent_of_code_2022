#include <vector>

#include <string>

#include "absl/strings/str_split.h"
#include "day01/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day01, First) {
  std::string input =R"(1000
2000
3000

4000

5000
6000

7000
8000
9000

10000)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 24000);
}

//TEST(Day01, Second) {
//  std::vector<int32_t> input = {199, 200, 208, 210, 200,
//                                207, 240, 269, 260, 263};
//  auto result = CountWindowIncreases(input);
//  ASSERT_EQ(result, 5);
//}
