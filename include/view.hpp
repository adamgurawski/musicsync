/**
 * This file contains class responsible for communicating with the user.
 * Maybe some day I'd try to create a GUI so it'd much easier to introduce this change
 * by changing View's contents.
 */

#pragma once

#include "song.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace ms
{

class View
{
public:
  /// Redirect stream to std::cerr.
  static void PrintError(std::stringstream& ss)
    { std::cerr << ss.rdbuf() << std::endl; }

  /**
   * Print message to std::cerr. End with newline.
   * \exception std::invalid_argument empty message
   */
  static void PrintError(const char* message);
  
  /// Call PrintError(const char*).
  static void PrintError(const std::string& message)
    { PrintError(message.c_str()); }

  /// Print every song info.
  static void PrintSongs(const std::vector<Song>& songs);

  /// Redirect stream to std::cout.
  static void Print(std::stringstream& ss)
    { std::cout << ss.rdbuf() << std::flush; }

  /**
   * Print message to std::cout.
   * \exception std::invalid_argument empty message
   */
  static void Print(const char* message);
  
  /// /// Call Print(const char*).
  static void Print(const std::string& message)
    { Print(message.c_str()); }

   /// Call Println(const char*).
  static void Println(const std::string& message)
    { Print(message.c_str()); }

  /**
   * Print message with following newline.
   * \exception std::invalid_argument empty message
   */
  static void Println(const char* message);
};

} // namespace ms