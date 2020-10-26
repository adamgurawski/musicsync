#include "filename_parser.hpp"

namespace ms
{

Song FilenameParser::Parse(const std::string& filename)
{
  std::string delimiter = " - ";
  size_t delimiterPos = filename.find(delimiter);

  Song result;
  result.Author = filename.substr(0, delimiterPos);
  result.Title = filename.substr(delimiterPos + delimiter.length());
  return result;
}

} // namespace ms