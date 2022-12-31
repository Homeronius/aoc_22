#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

int safe_readline(std::string line) {
  // (skip if there are errors in converting the line into an integer)
  try {
    return std::stoi(line);
  } catch (std::invalid_argument const &ex) {
    std::cout << "std::invalid_argument::what(): " << ex.what() << "(\'" << line
              << "\')" << '\n';
  } catch (std::out_of_range const &ex) {
    std::cout << "std::out_of_range::what(): " << ex.what() << "(\'" << line
              << "\')" << '\n';
  }
  return 0;
}

int find_max_n_elfs(std::string filename, int N) {
  std::deque<int> elf_calories;

  std::string calorie_line;
  std::ifstream calorie_file(filename);

  int curr_calorie_sum = 0;
  int curr_meal_calorie = 0;
  int smallest_calorie_sum = 0;

  if (!calorie_file.is_open()) {
    return -1;
  }

  while (std::getline(calorie_file, calorie_line)) {
    if (calorie_line.empty()) {
      // Inventory of this elf is finished on this line
      // Find idx where to insert calories
      if (curr_calorie_sum <= smallest_calorie_sum) {
        // Reset counters
        curr_calorie_sum = 0;
        continue;
      }

      // Find where to insert the current calorie sum and insert
      auto it = std::upper_bound(elf_calories.begin(), elf_calories.end(),
                                 curr_calorie_sum);
      int insertion_idx = it - elf_calories.begin();
      elf_calories.insert(it, curr_calorie_sum);

      if (elf_calories.size() == N + 1) {
        elf_calories.pop_front();
      }

      // Reset counters
      curr_calorie_sum = 0;
      smallest_calorie_sum = elf_calories.front();
    } else {
      // Add calories of new meal
      curr_meal_calorie = safe_readline(calorie_line);
      curr_calorie_sum += curr_meal_calorie;
    }
  }

  calorie_file.close();

  return std::accumulate(elf_calories.begin(), elf_calories.end(), 0);
}

int main() {

  auto calorie_file = "calories.txt";

  std::cout << find_max_n_elfs(calorie_file, 3) << std::endl;

  return 0;
}
