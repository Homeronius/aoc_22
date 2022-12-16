#include <iostream>
#include <fstream>
#include <bitset>


int main(){
  std::string filename = "sections.txt";

  std::string elf1_begin, elf1_end, elf2_begin, elf2_end;
  std::ifstream ids_file(filename);
  if ( !ids_file.is_open() ){
    return -1;
  }

  int overlap_counter = 0;

  while (
    std::getline(ids_file, elf1_begin, '-'),
    std::getline(ids_file, elf1_end, ','),
    std::getline(ids_file, elf2_begin, '-'),
    std::getline(ids_file, elf2_end)
  )
    {
      // Section of elf1 is fully in elf2's section
      if (
        std::stoi(elf1_begin) >= std::stoi(elf2_begin) && 
        std::stoi(elf1_end) <= std::stoi(elf2_end)
      ) {
        overlap_counter++;
      // Section of elf2 is fully in elf1's section
      } else if (
        std::stoi(elf2_begin) >= std::stoi(elf1_begin) && 
        std::stoi(elf2_end) <= std::stoi(elf1_end)
      ) {
        overlap_counter++;
      }
    }

  std::cout << overlap_counter << std::endl;

  return 0;
}
