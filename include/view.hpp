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
  /**
   * Append [INFO] before the message and print it to std::cout. End with newline.
   * \exception std::invalid_argument empty message
   */
  static void PrintInfo(const char* message);
  
  /// Redirect stream to std::cout and append [INFO] before the message.
  static void PrintInfo(std::stringstream& ss)
    { std::cout << "[INFO] " << ss.rdbuf() << std::endl; }

  /// Call PrintInfo(const char*)
  static void PrintInfo(const std::string& message)
    { PrintInfo(message.c_str()); }

  /**
   * Append [ERROR] before the message and print it to std::cerr. End with newline.
   * \exception std::invalid_argument empty message
   */
  static void PrintError(const char* message);

  /// Redirect stream to std::cerr and append [ERROR] before the message.
  static void PrintError(std::stringstream& ss)
    { std::cerr << "[ERROR] " << ss.rdbuf() << std::endl; }
  
  /// Call PrintError(const char*).
  static void PrintError(const std::string& message)
    { PrintError(message.c_str()); }

  /// Print every song info.
  static void PrintSongs(const std::vector<Song>& songs);

  /**
   * Print message to std::cout.
   * \exception std::invalid_argument empty message
   */
  static void Print(const char* message);
  
  /// Redirect stream to std::cout.
  static void Print(std::stringstream& ss)
    { std::cout << ss.rdbuf() << std::flush; }
  
  /// Call Print(const char*).
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