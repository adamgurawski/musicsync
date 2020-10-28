#include "local_files_utils.hpp"

#include <filesystem>

namespace
{
namespace fs = std::filesystem;

ms::Song Parse(const std::string& filename)
{
  std::string delimiter = " - ";
  size_t delimiterPos = filename.find(delimiter);

  ms::Song result;
  result.Author = filename.substr(0, delimiterPos);
  result.Title = filename.substr(delimiterPos + delimiter.length());
  return result;
}

template <typename Callable>
void PerformForEveryFile(fs::recursive_directory_iterator it, const std::string& extension,
  Callable callable)
{
  for (const auto& item : it)
  {
    if (item.is_directory() == false)
    {
      fs::path itemsPath{ item.path() };

      if (itemsPath.extension() == extension)
        callable(itemsPath);
    }
  }
}

std::string EraseFileExtension(fs::path path)
{
  return path.filename().replace_extension().string();
}

} // anonymous namespace

namespace ms::local_utils
{

std::vector<std::string> ExtractFilenames(const std::string& path,
  const std::string& extension)
{
  fs::path directoryPath{ path };
  fs::recursive_directory_iterator directoryIt{ directoryPath };

  std::vector<std::string> ctr;

  PerformForEveryFile(directoryIt, extension, [&](const fs::path& filePath)
    {
      // TODO: AG: temporarily print the path for debugging purposes.
      // TODO: AG: consider returning path as well.
      std::cout << "Path: " << filePath << std::endl;
      ctr.emplace_back(EraseFileExtension(filePath));
    });

  return ctr;
}

Songs ExtractSongs(const std::string& path, const std::string& fileExtension)
{
  std::vector<std::string> filenames = ExtractFilenames(path, fileExtension);

  Songs songs;

  for (const auto& filename : filenames)
    songs.emplace_back(Parse(filename));

  return songs;
}

} // namespace ms::local_files
