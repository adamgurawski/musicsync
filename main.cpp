
#include "file_manager.hpp"

#include <iostream>

// AG: TODO: file name parser.

int main()
{
  try
  {
    // AG: TODO: values hardcoded for testing purposes, to be passed as command line arguments.
    // Maybe some day inserted in GUI.
    ms::FileManager::ExtractSongInfo("E:/vs_projects/musicsync", ".txt");
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    return -1;
  }
  
  return 0;
}