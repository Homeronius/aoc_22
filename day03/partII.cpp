#include <iostream>
#include <fstream>
#include <vector>
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

  const int char_offset = 65;
  const int group_size = 3;
  int total_priority = 0;
  int ascii_code;
  int offset_code;

  // To keep track of chars that appeared (26+6+26)
  // Extended to 64 due to performance reasons
  // std::bitset<64> chars_taken;
  std::vector< std::bitset<64> > chars_taken(group_size);
  std::bitset<64> and_result;

  int member_idx = 0;
  while (std::getline( rucksack_file, rucksack_line )){

    for(int item_idx = 0; item_idx < rucksack_line.size(); item_idx++){

      ascii_code = static_cast<int>(rucksack_line[item_idx]);
      offset_code = ascii_code - char_offset;
      bool char_occurred = chars_taken[member_idx].test(offset_code);

      if (!char_occurred){
        chars_taken[member_idx].set(offset_code);
      }
    }

    // Check if info about all group members has been collected
    if (member_idx == 2){
      // Do a bitwise AND
      and_result.set();
      for(const auto& member_bitset : chars_taken){
        and_result = and_result & member_bitset;
      }

      int common_idx = and_result._Find_first();
  
      // Compute correct priority according problem statement
      total_priority += compute_priority(common_idx);
      
      // Reset char_taken for next group
      chars_taken = std::vector< std::bitset<64> >(group_size);
    }

    member_idx = ( ++member_idx + group_size ) % group_size;
  }

  std::cout << total_priority << std::endl;


  return 0;
}
