#include "local_files_utils.hpp"
#include "view.hpp"

// TODO: AG: extern possibly not required, but I'll leave it here for now.
extern "C" {
#include "sqlite3.h"
}

// TODO: AG: use command line args parser.
// TODO: AG: store song details in a database
// TODO: AG: get song list from spotify (use Spotify's web API)

/**
 * First argument should be the directory path, e.g. "D:/my_music".
 * Second argument should be the file's extension, e.g. ".mp3"
 */
int main(int argc, char** argv)
{
  sqlite3 db;
  constexpr int expectedArgs = 3;

  // This will do for now.
  if (argc != expectedArgs)
  {
    std::stringstream errorMessage;
    errorMessage << "Incorrect number of arguments passed: " << argc - 1 << "." << "\n" <<
      "Expected: " << expectedArgs - 1 << ".";
    ms::View::PrintError(errorMessage);
    return 1;
  }

  try
  {
    // Get songs stored on the device from path specified by argv[1].
    ms::Songs localSongs = ms::local_utils::ExtractSongs(argv[1], argv[2]);

    ms::View::PrintSongs(localSongs);
  }
  catch (const std::exception& e)
  {
    std::string message = "Exception caught in main function: ";
    message += e.what();
    ms::View::PrintError(message);
    return -1;
  }
  
  return 0;
}