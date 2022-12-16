#include <iostream>
#include <fstream>
#include <bitset>

// Compute correct priority according problem statement given offset ascii code
int compute_priority(const int& common_idx){
  if (common_idx > 31){ // lowercase letter
    return common_idx - 32 + 1;
  } else { // uppercase letter
    return common_idx + 26 + 1;
  }
}

int main(){
  std::string filename = "rucksacks.txt";

  std::string rucksack_line;
  std::ifstream rucksack_file(filename);
  if ( !rucksack_file.is_open() ){
    return -1;
  }

  // Shift offset so that capital letters start at '0'
  const int char_offset = 65;

  int total_priority = 0;
  int ascii_code;
  int offset_code;
  // To keep track of chars that appeared (26+6+26)
  // Extended to 64 due to performance reasons
  std::bitset<64> chars_taken;

  while (std::getline( rucksack_file, rucksack_line )){

    for(int item_idx = 0; item_idx < rucksack_line.size(); item_idx++){

      ascii_code = static_cast<int>(rucksack_line[item_idx]);
      offset_code = ascii_code - char_offset;
      bool is_first_compartment = item_idx < (rucksack_line.size()/2);
      bool char_occurred = chars_taken.test(offset_code);

      if (is_first_compartment && !char_occurred){
        chars_taken.set(offset_code);
      } else if (!is_first_compartment && char_occurred) {
        // Compute correct priority according problem statement
        total_priority += compute_priority(offset_code);

        // Reset
        chars_taken.reset();
        break;
      }
    }
  }

  std::cout << total_priority << std::endl;


  return 0;
}
