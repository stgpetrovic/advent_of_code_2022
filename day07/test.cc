#include <string>
#include <vector>

#include "absl/strings/str_split.h"
#include "day07/solution.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

TEST(Day, First) {
  auto input = R"($ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k)";
  auto result = Solve(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 95437);
}

TEST(Day, Second) {
  auto input = R"($ cd /
$ ls
dir a
14848514 b.txt
8504156 c.dat
dir d
$ cd a
$ ls
dir e
29116 f
2557 g
62596 h.lst
$ cd e
$ ls
584 i
$ cd ..
$ cd ..
$ cd d
$ ls
4060174 j
8033020 d.log
5626152 d.ext
7214296 k)";
  auto result = Solve2(absl::StrSplit(input, "\n"));
  ASSERT_EQ(result, 24933642);
}

