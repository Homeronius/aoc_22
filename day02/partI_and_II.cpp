#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

enum class Outcome { Loss, Draw, Win };

// Compute outcome depending on the played moves
Outcome play_round(const int &opponent_move, const int &my_move) {
  if ((opponent_move + 1) % 3 == my_move) {
    return Outcome::Win;
  } else if (opponent_move == my_move) {
    return Outcome::Draw;
  } else {
    return Outcome::Loss;
  }
}

// Compute achieved score according to the game outcome
int compute_score(const Outcome &state, const int &my_move) {
  int score = my_move + 1;
  score += static_cast<int>(state) * 3;
  return score;
}

// Determine my move according to policy given in Problem I + II
std::tuple<Outcome, int> move_policy(const int &opponent_move,
                                     const int &second_column) {
  // Part I
  // int my_move = second_column;
  // Outcome state = play_round(opponent_move, my_move);

  // Part II
  int my_move = (opponent_move + second_column - 1 + 3) % 3;
  Outcome state = static_cast<Outcome>(second_column);

  return {state, my_move};
}

int main() {
  std::string filename = "strategy.txt";

  std::string strategy_line;
  std::ifstream strategy_file(filename);
  if (!strategy_file.is_open()) {
    return -1;
  }

  int score = 0;
  // Offset of capital letters in ASCII table
  const int char_offset = 65;
  int opponent_move;
  int my_move;
  int second_column;
  Outcome state;

  while (std::getline(strategy_file, strategy_line)) {
    if (strategy_line.empty())
      continue;

    opponent_move = static_cast<int>(strategy_line[0]) - char_offset;
    second_column = static_cast<int>(strategy_line[2] - 23) - char_offset;

    auto [state, my_move] = move_policy(opponent_move, second_column);

    score += compute_score(state, my_move);
  }

  std::cout << score << std::endl;

  return 0;
}
