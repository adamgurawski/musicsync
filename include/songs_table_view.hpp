#pragma once

#include "song.hpp"

#include <vector>

namespace ms
{

/**
 * C++ representation of songs table allowing easier access to the data.
 * It's meant to be filled in sqlite C callbacks, so the interface of some functions
 * (e.g. AddRow) is prepared for this.
 */
class SongsTableView
{
public:
  struct Row
  {
    int         Id;
    std::string Author;
    std::string Title;
    bool        IsPresentInSpotify;
    bool        IsPresentInLocalFiles;

    Row(int id, const std::string& author, const std::string& title, bool isPresentInSpotify,
      bool isPresentInLocalFiles) : Id(id), Author(author), Title(title), 
      IsPresentInSpotify(isPresentInSpotify), IsPresentInLocalFiles(isPresentInLocalFiles)
    {}
  };

public:
  /**
   * This function is meant to be used inside of sqlite C callbacks for inserting row extracted
   * from the actual database. This is why bools are passed as ints here - the appropriate 
   * conversions will take place inside of this function.
   */
  void AddRow(int id, char* author, char* title, int isPresentInSpotify, int isPresentInLocalFiles);

  const std::vector<Row>& GetRows() const
  {
    return Rows;
  }

private:
  std::vector<Row> Rows;
};

} // namespace ms
