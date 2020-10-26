#include "song_extractor.hpp"

#include "filename_extractor.hpp"
#include "filename_parser.hpp"

namespace ms
{

Songs SongExtractor::ExtractSongs(const std::string& path, const std::string& fileExtension)
{
  std::vector<std::string> filenames = FilenameExtractor::ExtractFilenames(path, fileExtension);

  Songs songs;

  for (const auto& filename : filenames)
    songs.emplace_back(FilenameParser::Parse(filename));
  
  return songs;
}

} // namespace ms