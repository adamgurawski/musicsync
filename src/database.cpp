#include "database.hpp"
#include "view.hpp"

#include "sqlite3.h"

#include <stdexcept>

namespace ms
{

void SqliteDb::Connect()
{
  if (DatabaseFilePath.empty())
    throw std::invalid_argument("Unable to connect to database: database file path not specified.");

  int openResult = sqlite3_open(DatabaseFilePath.c_str(), &Connection);

  if (openResult == SQLITE_OK && Connection)
  {
    View::PrintInfo("Successfully connected to the database: " + DatabaseFilePath + '.');
    Connected = true;
  }
  else
  {
    throw std::runtime_error("Sqlite3_open failed: " + std::string(sqlite3_errmsg(Connection)));
  }
}

void SqliteDb::Disconnect()
{
  sqlite3_close(Connection);
  View::PrintInfo("Disconnected from the database.");
}

void SqliteDb::Init()
{
  AssertIsConnected();

  // TODO: AG: this query is meant to check if table 'songs' exists. 
  // Examine whether it actually does what it's supposed to.
  const char* query = 
    "SELECT name"
    "FROM sqlite_master"
    "WHERE type = 'table' AND name = 'songs'";

  // TODO: AG: create callback function.
  int result = sqlite3_exec(Connection, query, NULL, NULL, NULL);
  // TODO: AG: debug.
  View::PrintInfo("sqlite3_exec result: " + std::to_string(result));

  if (result == SQLITE_OK)
    Initialized = true;
}

void SqliteDb::AssertIsConnected() const
{
  if (!Connected)
    throw std::runtime_error("Unable to initialize the database if the connection "
      "has not been established.");
}

} // namespace ms
