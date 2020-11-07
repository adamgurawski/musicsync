#include "view.hpp"

#include "songs_table_view.hpp"

#include <iomanip>

namespace ms
{

void View::PrintSongsTable(const SongsTableView& songsTable)
{
  // Hardcoded const chars would probably be more efficient, but this solution is
  // as simple as it gets in terms of maintenance - if I decide that the column is too narrow,
  // all I have to do is to add required spaces in "headers" and the width of all printed fiels 
  // will be automatically adjusted. Definitely worth it.
  char delimiter = '|';
  std::string idHeader = " Id  ";
  std::string authorHeader = "       Author       ";
  std::string titleHeader = "                Title                ";
  std::string spotifyHeader = " Spotify ";
  std::string localFilesHeader = " Local files";

  // Print header containing column names.
  std::cout << idHeader << delimiter << authorHeader << delimiter << titleHeader << delimiter
    << spotifyHeader << delimiter << localFilesHeader << "\n";

  // Print line separating column names and table contents.
  std::cout << std::setfill('-') << std::setw(idHeader.size() + 1) << delimiter
    << std::setw(authorHeader.size() + 1) << delimiter
    << std::setw(titleHeader.size() + 1) << delimiter
    << std::setw(spotifyHeader.size() + 1) << delimiter
    << std::setw(localFilesHeader.size() + 1) << "\n" << std::setfill(' ');

  // Align left & print bools as 'true' or 'false'.
  std::cout << std::left << std::boolalpha;

  const auto& rows = songsTable.GetRows();

  for (const auto& row : rows)
  {
    std::cout << ' ' << std::setw(idHeader.size() - 1) << row.Id << delimiter 
      << std::setw(authorHeader.size()) << row.Author << delimiter
      << std::setw(titleHeader.size()) << row.Title << delimiter 
      << std::setw(spotifyHeader.size()) << row.IsPresentInSpotify << delimiter 
      << std::setw(localFilesHeader.size()) << row.IsPresentInLocalFiles << "\n";
  }

  std::cout << std::flush;
  // Reset alignment & reset bool printing.
  std::cout << std::noboolalpha << std::right;
}


void View::PrintInfo(const char* message)
{
  if (message == nullptr)
    throw std::invalid_argument("Invalid usage of PrintInfo function: empty message passed.");

  std::cout << "[INFO] " << message << std::endl;
}

void View::PrintError(const char* message)
{
  if (message == nullptr)
    throw std::invalid_argument("Invalid usage of PrintError function: empty message passed.");

  std::cerr << "[ERROR] " << message << std::endl;
}

void View::PrintSongs(const std::vector<Song>& songs)
{
  Println("##### Songs #####");

  for (const auto& song : songs)
  {
    std::stringstream message;
    message << song << std::endl;
    Print(message);
  }
}

void View::Print(const char* message)
{
  if (message == nullptr)
    throw std::invalid_argument("Invalid usage of Print function: empty message passed.");

  std::cout << message << std::flush;
}

void View::Println(const char* message)
{
  if (message == nullptr)
    throw std::invalid_argument("Invalid usage of Println function: empty message passed.");

  std::cout << message << std::endl;
}

} // namespace ms