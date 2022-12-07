#include "day07/solution.h"

#include <glog/logging.h>

#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

enum Type { IFILE, IDIR };

struct INode {
  Type type;
  std::string name;
  int64_t size;
  std::vector<std::unique_ptr<INode>> children;
  mutable int64_t total_size = 0;

  std::string ToString() const {
    std::string s = name;
    if (type == IFILE) {
      s += absl::StrCat(" file (", size, ")");
    } else {
      s += absl::StrCat(" dir (", children.size(), ")");
    }
    return s;
  }

  int64_t du() const {
    if (total_size > 0) {
      return total_size;
    }
    int64_t tt = type == IFILE ? size : 0;
    for (const auto& child : children) {
      if (child->type == IFILE) {
        tt += child->size;
      } else {
        tt += child->du();
      }
    }
    total_size = tt;
    return tt;
  }
};

INode* find(INode* inode, const std::filesystem::path& p) {
  if (p == "/" && inode->name == "/") {
    return inode;
  }
  INode* curr = inode;
  for (const auto& part : p) {
    if (p == "/") {
      continue;
    }
    for (const auto& c : curr->children) {
      if (c->name == part) {
        curr = c.get();
        continue;
      }
    }
  }
  return curr;
}

void InnerSumLessThan100k(INode* n, int64_t* sum) {
  if (n->type == IFILE) {
    return;
  }
  if (n->du() < 100000) {
    *sum += n->du();
  }
  for (const auto& child : n->children) {
    InnerSumLessThan100k(child.get(), sum);
  }
}

int64_t SumLessThan100k(INode* n) {
  int64_t sum = 0;
  InnerSumLessThan100k(n, &sum);
  return sum;
}

void InnerCollectSizes(INode* n, std::vector<int64_t>* sizes) {
  if (n->type == IFILE) {
    return;
  }
  sizes->push_back(n->du());
  for (const auto& child : n->children) {
    InnerCollectSizes(child.get(), sizes);
  }
}

std::vector<int64_t> CollectSizes(INode* n) {
  std::vector<int64_t> sizes;
  InnerCollectSizes(n, &sizes);
  return sizes;
}

INode ParseFs(const std::vector<std::string>& cmds) {
  INode fs_root{.type = IDIR, .name = "/"};
  std::filesystem::path cwd;
  for (const auto& cmd : cmds) {
    if (absl::StartsWith(cmd, "$ cd")) {
      cwd = std::filesystem::weakly_canonical(cwd / cmd.substr(5));
    } else if (!absl::StartsWith(cmd, "$ ls")) {
      std::vector<std::string> parts = absl::StrSplit(cmd, " ");
      auto f = std::make_unique<INode>();
      f->name = parts[1];
      if (parts[0] == "dir") {
        f->type = IDIR;
      } else {
        f->type = IFILE;
        if (!absl::SimpleAtoi(parts[0], &f->size)) {
          LOG(FATAL) << "failed to parse file size: " << parts[0];
        }
      }
      auto n = find(&fs_root, cwd);
      n->children.push_back(std::move(f));
    }
  }
  return fs_root;
}

int64_t Solve(const std::vector<std::string>& in) {
  auto fs = ParseFs(in);
  return SumLessThan100k(&fs);
}

int64_t Solve2(const std::vector<std::string>& in) {
  auto fs = ParseFs(in);
  int64_t total_disk_size = 70000000;
  int64_t free_disk_size = total_disk_size - fs.du();
  int64_t required_size = 30000000;
  int64_t must_delete_size = required_size - free_disk_size;

  int64_t min = total_disk_size;
  for (const auto& dir_size : CollectSizes(&fs)) {
    if (dir_size < must_delete_size) {
      continue;
    }
    min = std::min(min, dir_size);
  }
  return min;
}

