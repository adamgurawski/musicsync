#include "database.hpp"

#include "sqlite3.h"

#include <stdexcept>

namespace ms
{

void SqliteDb::Connect()
{
  if (DatabaseFilePath.empty())
    throw std::invalid_argument("Unable to connect to database: database file path not specified.");

  sqlite3_open(DatabaseFilePath.c_str(), &Connection);
}

void SqliteDb::Disconnect()
{
  sqlite3_close(Connection);
}

} // namespace ms
