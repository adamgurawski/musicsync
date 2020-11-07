#include "songs_table_view.hpp"

namespace ms
{

void SongsTableView::AddRow(int id, char* author, char* title, int isPresentInSpotify,
  int isPresentInLocalFiles)
{
  Rows.emplace_back(
    id, 
    author ? author : "NULL", 
    title ? title : "NULL", 
    isPresentInSpotify != 0, 
    isPresentInLocalFiles != 0);
}

} // namespace ms