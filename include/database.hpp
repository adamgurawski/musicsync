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

  /**
   * Insert a new song into the database or update the existing one.
   * \param presentInSpotify set to true if inserting spotify song, false if inserting
   * song from local disk.
   */
  virtual void AddSong(const std::string& author, const std::string& title, 
    bool presentInSpotify) = 0;

protected:
  IDatabase() = default;
};

class SqliteDb : public IDatabase
{
public:
  explicit SqliteDb(const std::string& dbFilePath) : DatabaseFilePath(dbFilePath), 
    Connection(NULL), Connected(false)
    {}

  ~SqliteDb()
  {
    Disconnect();
  }

  virtual void Connect() override;

  virtual void Disconnect() override;

  virtual void Init() override;

  virtual void AddSong(const std::string& author, const std::string& title,
    bool presentInSpotify) override;

private:
  /**
   * Throw if the connection has not been established. This function is meant to be called
   * before every call to the database.
   * \throw std::runtime_error connection to the database has not been established
   */
  void AssertIsConnected() const;

  /**
   * Create table 'songs'.
   * \throw std::runtime_error unable to create the table (sqlite3_exec returned something 
   *   other than 0)
   */
  void CreateSongsTable();

  /**
   * Check whether 'songs' table exists in the database.
   * \return true 'songs' table already exists in the database, false otherwise
   * \throw std::runtime_error unable to determine whether table exists in the database 
   *   (sqlite3_exec returned something other than 0)
   */
  bool SongsTableExists();

private:
  /// Path to database file.
  // TODO: AG: consider changing into std::filesystem::path.
  std::string DatabaseFilePath;
  /// Connection to the database through sqlite.
  sqlite3*    Connection;
  /// Flag set after successful Connect() - indicates that we have an active connection.
  bool        Connected;
};

} // namespace ms
