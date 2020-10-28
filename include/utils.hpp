#pragma once

#include <iostream>

namespace ms
{
namespace utils
{

inline void PrintNotImplementedYet(const char* what)
{
  std::cerr << what << " is not implemented yet." << std::endl;
};

} // namespace utils
} // namespace ms
