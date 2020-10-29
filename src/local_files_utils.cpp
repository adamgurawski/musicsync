#include "local_files_utils.hpp"

#include "view.hpp"

#include <filesystem>
#include <sstream>

namespace
{
namespace fs = std::filesystem;

std::string GetFilenameWithoutExtension(const ms::local_utils::Path& path)
{
  return path.filename().replace_extension().string();
}

/**
 * Extract song details from file path. Split the filename using a delimiter, which
 * allows to determine an author and a title.
 * \return details of a song
 * \exception std::invalid_argument filename does not contain specified substring, so we're
 * unable to determine the author and the title.
 */
ms::Song ExtractSongDetails(const ms::local_utils::Path& filePath)
{
  // Get filename.
  std::string filename = GetFilenameWithoutExtension(filePath);
  // Get delimiter's positon - for now delimiter is set as " - ". It may change in the future.
  std::string delimiter = " - ";
  size_t delimiterPos = filename.find(delimiter);

  if (delimiterPos == std::string::npos)
  { // Delimiter not found.
    std::stringstream message;
    message << "Filename '" << filename << "' does not contain delimiter '" << delimiter <<
      "' so we're unable to extract song details from it.";
    throw std::invalid_argument(message.str());
  }

  ms::Song result;
  result.Author = filename.substr(0, delimiterPos);
  result.Title = filename.substr(delimiterPos + delimiter.length());
  result.AbsolutePath = fs::absolute(filePath);
  return result;
}

/**
 * Call the callable on every path that is not a directory.
 */
template <typename Callable>
void PerformOnEveryNonDirectoryFile(fs::recursive_directory_iterator directoryIt, 
  const std::string& extension, Callable callable)
{
  for (const auto& directoryEntry : directoryIt)
  {
    if (directoryEntry.is_directory() == false)
    {
      fs::path path = directoryEntry.path();

      if (path.extension() == extension)
        callable(path);
    }
  }
}

} // anonymous namespace

namespace ms::local_utils
{

/**
 * TODO: AG: comment me.
 * Scan all files with given extension in specified path (and subdirectories if any exists).
 * \return
 */
Songs ExtractSongs(const std::string& path, const std::string& fileExtension)
{
  Paths songPaths = ExtractFilePaths(path, fileExtension);

  Songs result;

  for (const auto& path : songPaths)
  {
    try
    {
      result.emplace_back(ExtractSongDetails(path));
    }
    catch (const std::exception& e)
    {
      std::stringstream message;
      message << "Unable to extract song details from path '" << path.string() <<
        "': " << e.what() << ".";
      View::PrintError(message);
    }
  }

  return result;
}

Paths ExtractFilePaths(const std::string& path, const std::string& extension)
{
  Path directoryPath { path };
  fs::recursive_directory_iterator directoryIt { directoryPath };

  Paths result;

  PerformOnEveryNonDirectoryFile(directoryIt, extension, [&](const Path& filePath) mutable
    {
      result.emplace_back(filePath);
    });

  return result;
}

} // namespace ms::local_files
