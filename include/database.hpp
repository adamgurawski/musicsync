#pragma once

#include <string>

struct sqlite3;

namespace ms
{

class IDatabase
{
public:
  virtual ~IDatabase() = default;

  /// Open database connection.
  virtual void Connect() = 0;

  /// Close database connection.
  virtual void Disconnect() = 0;

protected:
  IDatabase() = default;
};

class SqliteDb : public IDatabase
{
public:
  explicit SqliteDb(const std::string& dbFilePath) : DatabaseFilePath(dbFilePath), 
    Connection(nullptr)
    {}

  ~SqliteDb()
  {
    Disconnect();
  }

  virtual void Connect() override;

  virtual void Disconnect() override;

private:
  std::string DatabaseFilePath;
  sqlite3*    Connection;
};

} // namespace ms
