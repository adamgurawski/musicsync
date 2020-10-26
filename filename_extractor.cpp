#include "filename_extractor.hpp"

#include "filename_parser.hpp"
#include "utils.hpp"

#include <filesystem>

namespace 
{
namespace fs = std::filesystem;

template <typename Callable>
void PerformForEveryFile(fs::recursive_directory_iterator it, const std::string& extension, 
  Callable callable)
{
  for (const auto& item : it)
  {
    if (item.is_directory() == false)
    {
      fs::path itemsPath { item.path() };

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

namespace ms
{

std::vector<std::string> FilenameExtractor::ExtractFilenames(const std::string& path, 
  const std::string& extension)
{
  fs::path directoryPath{ path };
  fs::recursive_directory_iterator directoryIt{ directoryPath };

  std::vector<std::string> ctr;

  PerformForEveryFile(directoryIt, extension, [&](const fs::path& filePath)
    {
      // AG: TODO: temporarily print the path for debugging purposes.
      // AG: TODO: consider returning path as well.
      std::cout << "Path: " << filePath << std::endl;
      ctr.emplace_back(EraseFileExtension(filePath));
    });

  return ctr;
}

} // namespace ms
