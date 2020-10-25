
#include <iostream>

namespace ms
{
namespace utils
{

inline void PrintNotSupportedYet(const char* what)
{
  std::cerr << what << " is not supported yet." << std::endl;
};

} // namespace utils
} // namespace ms
