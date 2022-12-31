#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::deque<int>> parse_crates(std::ifstream &stream) {
  std::vector<std::deque<int>> crates;
  std::string line;
  std::getline(stream, line);
  int content;
  bool crates_done = false;

  // Read initial crate distribution
  while (!crates_done) {
    // Loop through crates on this level
    for (int col = 0, i = 1; i < line.length(); col++, i += 4) {
      content = static_cast<int>(line[i]);

      // Break if crate setup is done
      crates_done = std::isdigit(content);

      // Add a new crate stack
      if (crates.size() < col + 1) {
        crates.emplace_back(std::deque<int>());
      }

      // Skip empty spaces between crate stacks
      if (content != ' ') {
        crates[col].push_back(content);
      }
    }

    std::getline(stream, line);
  }

  return crates;
}

// Rearrangement strategy according to Part I
void crate_mover_9000(std::vector<std::deque<int>> &crates, int count, int from,
                      int to) {
  for (int i = 0; i < count; ++i) {
    crates[to].push_front(crates[from].front());
    crates[from].pop_front();
  }
}

// Rearrangement strategy according to Part II
void crate_mover_9001(std::vector<std::deque<int>> &crates, int count, int from,
                      int to) {
  for (int i = count - 1; i >= 0; --i) {
    crates[to].push_front(crates[from][i]);
  }

  // Delete moved crates
  crates[from].erase(crates[from].begin(), crates[from].begin() + count);
}

int main() {
  std::ifstream crates_file("crates.txt");
  auto crates = parse_crates(crates_file);
  std::string word;
  int count, from, to;

  while (crates_file >> word) {
    crates_file >> std::skipws >> count >> word >> from >> word >> to;
    from -= 1;
    to -= 1;

    // Part I
    crate_mover_9000(crates, count, from, to);
    // Part II
    // crate_mover_9001(crates, count, from, to);
  }

  // Print crate at top of each stack
  for (auto &stack : crates) {
    std::cout << static_cast<char>(stack.front());
  }
  std::cout << std::endl;

  return 0;
}
