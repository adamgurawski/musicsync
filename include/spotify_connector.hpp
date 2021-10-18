#pragma once

#include <string>

/**
 * TODO: AG: comment me.
 * 
 * This class should be responsible for connecting and retrieving data from Spotify.
 */
class SpotifyConnector
{
public:
  /// TODO: AG: comment me.
  /// For now, this function is a temporary cpr library testing ground.
  void CprDemo();

private:
  /// TODO: AG: comment me.
  std::string ExtractAccessToken(const std::string& textResponse);

  // TODO: AG: consider storing access token in a member variable.
}; // class SpotifyConnector
