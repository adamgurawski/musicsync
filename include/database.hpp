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

  /// Create appropriate table if does not exist yet.
  virtual void Init() = 0;

protected:
  IDatabase() = default;
};

class SqliteDb : public IDatabase
{
public:
  explicit SqliteDb(const std::string& dbFilePath) : DatabaseFilePath(dbFilePath), 
    Connection(NULL), Initialized(false), Connected(false)
    {}

  ~SqliteDb()
  {
    Disconnect();
  }

  virtual void Connect() override;

  virtual void Disconnect() override;

  virtual void Init() override;

private:
  /**
   * Throw if the connection has not been established. This function is meant to be called
   * before every call to the database.
   * \throw std::runtime_error connection to the database has not been established
   */
  void AssertIsConnected() const;

private:
  // TODO: AG: comment members.
  std::string DatabaseFilePath;
  sqlite3*    Connection;
  bool        Connected;
  bool        Initialized;
};

} // namespace ms
