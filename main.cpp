
#include "file_manager.hpp"

#include <iostream>

// AG: TODO: use command line args parser.

/**
 * First argument should be the directory path, e.g. "E:/vs_projects/musicsync".
 * Second argument should be the extension, e.g. ".mp3"
 */
int main(int argc, char** argv)
{
  constexpr int expectedArgs = 3;

  // This will do for now.
  if (argc != expectedArgs)
  {
    std::cerr << "Incorrect number of arguments passed: " << argc - 1 << "." << "\n" <<
      "Expected: " << expectedArgs - 1 << std::endl;
    return 1;
  }

  try
  {
    ms::FileManager::SongInfoCtr songInfo = ms::FileManager::ExtractSongInfo(argv[1], argv[2]);
    
    std::cout << "Printing song info container contents.." << std::endl;

    for (const auto& song : songInfo)
      std::cout << "song: " << song << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    return -1;
  }
  
  return 0;
}