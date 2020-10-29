#include "view.hpp"

namespace ms
{

void View::PrintError(const char* message)
{
  if (message == nullptr)
    throw std::invalid_argument("Invalid usage of PrintError function: empty message passed.");

  std::cerr << message << std::endl;
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