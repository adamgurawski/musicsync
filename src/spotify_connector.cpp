#include "spotify_connector.hpp"

#include <cpr/cpr.h>

#include <iostream>

void SpotifyConnector::CprDemo()
{
  // Get the OAuth token.
  cpr::Response response = cpr::Post(
    cpr::Url{ "https://accounts.spotify.com/api/token" },
    cpr::Payload{
      {"grant_type", "client_credentials"},
      {"client_id", "TODO: AG: get me from a config file"},
      {"client_secret", "TODO: AG: get me from a config file"}
    }
  );

  const std::string accessToken = ExtractAccessToken(response.text);
  cpr::Bearer token = { accessToken };

  response = cpr::Get(
    cpr::Url{ "https://api.spotify.com/v1/tracks/2TpxZ7JUBn3uw46aR7qd6V" },
    token
  );

  std::cout << "Access token: " << accessToken << std::endl;
  std::cout << "Url: " << response.url << std::endl;
  std::cout << "Status code: " << response.status_code << std::endl;
  std::cout << "Header: " << response.header["content-type"] << std::endl;
  std::cout << "Text: " << response.text << std::endl;
}

std::string SpotifyConnector::ExtractAccessToken(const std::string& textResponse)
{
  // TODO: AG: find a better way to extract the token.
  std::string accessTokenStr = "access_token\"";
  auto quoteBeforeTokenPos = textResponse.find(accessTokenStr) + 2 + accessTokenStr.size();
  auto quoteAfterTokenPos = textResponse.find_first_of('"', quoteBeforeTokenPos);
  size_t accessTokenLength = quoteAfterTokenPos - quoteBeforeTokenPos;
  return textResponse.substr(quoteBeforeTokenPos, accessTokenLength);
}
