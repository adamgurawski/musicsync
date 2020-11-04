#include "database.hpp"
#include "local_files_utils.hpp"
#include "view.hpp"

#include <memory>

// TODO: AG: use command line args parser.
// TODO: AG: store song details in a database
// TODO: AG: get song list from spotify (use Spotify's web API)
// TODO: AG: improve path printing - sometimes slashes are printed doubled (//).

/**
 * First argument should be the path to the database file.
 * Second argument should be the directory path containing song files, e.g. "D:/my_music".
 * Third argument should be the song files' extension, e.g. ".mp3".
 */
int main(int argc, char** argv)
{
  constexpr int expectedArgs = 4;

  // This will do for now.
  if (argc != expectedArgs)
  {
    std::stringstream errorMessage;
    errorMessage << "Incorrect number of arguments passed: " << argc - 1 << "."
      << " Expected: " << expectedArgs - 1 << ".";
    ms::View::PrintError(errorMessage);
    return -1;
  }

  std::shared_ptr<ms::IDatabase> database;

  // Try to connect to the database for testing purposes.
  try
  {
    database = std::make_shared<ms::SqliteDb>(std::string(argv[1]));
    database->Connect();
    database->Init();
  }
  catch (const std::exception& e)
  {
    ms::View::PrintError("Exception thrown while connecting to the database: " 
      + std::string(e.what()));
    return 1;
  }

  /*
  try
  {
    // Get songs stored on the device from path specified by param.
    ms::Songs localSongs = ms::local_utils::ExtractSongs(argv[2], argv[3]);
    ms::View::PrintSongs(localSongs);
  }
  catch (const std::exception& e)
  {
    ms::View::PrintError("Exception thrown while extracting songs: " + std::string(e.what()));
    return 2;
  }
  */
  
  return 0;
}
