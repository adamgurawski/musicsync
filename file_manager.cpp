#include "file_manager.hpp"

#include "filename_parser.hpp"
#include "utils.hpp"

#include <filesystem>

namespace 
{
namespace fs = std::filesystem;

// AG: TODO: take a look at "std::filesystem::recursive_directory_iterator"

template <typename Callable>
void PerformForEveryFile(fs::directory_iterator it, const std::string& extension, Callable callable)
{
  for (const auto& item : it)
  {
    if (item.is_directory())
    {
      fs::directory_iterator it2 { item.path() };
      PerformForEveryFile(it2, extension, callable);
    }
    else 
    {
      // A file, not a directory. Print its path.
      fs::path itemsPath { item.path() };

      if (itemsPath.extension() == extension)
        callable(itemsPath);
    }
  }
}

std::string GetFileNameWithoutExtension(fs::path path)
{
  return path.filename().replace_extension().string();
}

/**
 * Return vector of file names with specified extensions in specified path (and in 
 * subdirectories if exist).
 */
std::vector<std::string> GetFileNames(const std::string& path, const std::string& extension)
{
  fs::path directoryPath{ path };
  fs::directory_iterator directoryIt{ directoryPath };

  std::vector<std::string> ctr;

  PerformForEveryFile(directoryIt, extension, [&](const fs::path& filePath)
    {
      // AG: TODO: temporarily print the path for debugging purposes.
      std::cout << "Path: " << filePath << std::endl;
      ctr.emplace_back(GetFileNameWithoutExtension(filePath));
    });

  return ctr;
}

} // anonymous namespace

namespace ms
{

FileManager::SongInfoCtr FileManager::ExtractSongInfo(const std::string& path, 
  const std::string& extension)
{
  auto filenames = GetFileNames(path, extension);

  SongInfoCtr ctr;

  for (const auto& elem : filenames)
    ctr.emplace_back(FilenameParser::Parse(elem));

  return ctr;
}

} // namespace ms