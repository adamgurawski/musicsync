#include "database.hpp"
#include "view.hpp"

#include "sqlite3.h"

#include <stdexcept>

namespace
{

/**
 * Throw std::runtime_error with message consisting of concatenated description 
 * and sqliteErrorMessage. Meant to be used after sqlite3_exec returns something other than
 * SQLITE_OK. The message is copied before sqlite3_free is called on message pointer.
 * \param description e.g. "Unable to connect to database", it's advised NOT to end description
 *  with colon, space, commas etc. as ": " will be appended after the description.
 * \param sqliteErrorMessage error message returned from sqlite3_exec, will be freed before the throw
 * \throw std::runtime_error will be thrown as a result with what() consisting of concatenated 
 *  description and sqliteErrorMessage
 * \throw std::invalid_argument description not specified (nullptr)
 */
void ThrowRuntimeError(const char* description, char* sqliteErrorMessage)
{
  if (!description)
  {
    sqlite3_free(sqliteErrorMessage);
    throw std::invalid_argument("Incorrect use of ThrowRuntimeError function: "
      "empty description parameter.");
  }

  std::string message = description;
  message += ": ";

  if (sqliteErrorMessage)
  { // Append sqlite error message and free it.
    message += sqliteErrorMessage;
    sqlite3_free(sqliteErrorMessage);
  }

  message += '.';
  throw std::runtime_error(message);
}

} // anonymous namespace

namespace ms
{

void SqliteDb::Connect()
{
  if (DatabaseFilePath.empty())
    throw std::invalid_argument("Unable to connect to database: database file path not specified.");

  int openResult = sqlite3_open(DatabaseFilePath.c_str(), &Connection);

  if (openResult == SQLITE_OK && Connection)
  {
    View::PrintInfo("Successfully connected to the database: '" + DatabaseFilePath + "'.");
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

  bool songsTableExists = SongsTableExists();

  if (songsTableExists == false)
  {
    View::PrintInfo("Table 'songs' does not exist yet. Proceeding to create it..");
    CreateSongsTable();
  }
  else
  {
    View::PrintInfo("Table 'songs' already exists in the database. Skip creating.");
  }
}

void SqliteDb::AssertIsConnected() const
{
  if (!Connected)
    throw std::runtime_error("Unable to initialize the database if the connection "
      "has not been established.");
}

void SqliteDb::AddSong(const std::string& author, const std::string& title,
  bool presentInSpotify)
{
  AssertIsConnected();
  throw std::runtime_error("SqliteDb::AddSong is not implemented yet.");
}

void SqliteDb::CreateSongsTable()
{
  AssertIsConnected();

  const char* query =
    "CREATE TABLE IF NOT EXISTS songs ("
    "id INT PRIMARY KEY,"
    "author TEXT,"
    "title TEXT,"
    "is_present_in_spotify INTEGER DEFAULT 0,"
    "is_present_in_local_files INTEGER DEFAULT 0"
    ");";

  char* errorMsg;

  int result = sqlite3_exec(Connection, query, NULL, NULL, &errorMsg);

  if (result != SQLITE_OK)
    ThrowRuntimeError("Unable to create 'songs' table", errorMsg);
  
  View::PrintInfo("Table 'songs' successfully created.");
}

bool SqliteDb::SongsTableExists()
{
  // Count tables having name 'songs'.
  const char* query =
    "SELECT COUNT(name) AS song_table_count "
    "FROM sqlite_master "
    "WHERE type = 'table' AND name = 'songs';";

  int tableExists = 0;
  char* errorMsg;

  int result = sqlite3_exec(Connection, query,
    // Callback function.
    [](void* exists, int rowElementsCount, char** rowElements, char** columnNames) -> int
    {
      // Abort the execution of callback if returned different number of columns than 1
      // or if first element is NULL (instead of SELECT COUNT(..) result).
      if (rowElementsCount != 1 || !rowElements[0])
        return 1; 

      int selectResult = std::stoi(rowElements[0]);
      int* tableExists = static_cast<int*>(exists);
      
      *tableExists = selectResult == 0 ? 0 : 1;
      return 0;
    },
    &tableExists, &errorMsg);

  if (result != SQLITE_OK)
    ThrowRuntimeError("Unable to determine whether 'songs' table exists in the database", errorMsg);

  return tableExists != 0;
}

} // namespace ms
