
#include "song_extractor.hpp"

#include <iostream>

// AG: TODO: use command line args parser.

/**
 * First argument should be the directory path, e.g. "D:/my_music".
 * Second argument should be the files extension, e.g. ".mp3"
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
    ms::Songs localSongs = ms::SongExtractor::ExtractSongs(argv[1], argv[2]);
    
    std::cout << "Printing song info container contents.." << std::endl;

    for (const auto& song : localSongs)
      std::cout << "song: " << song << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    return -1;
  }
  
  return 0;
}