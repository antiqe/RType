
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <md5.h>
#include <hex.h>

#include "MD5encode.hpp"

MD5encode::MD5encode()
{
}

MD5encode::~MD5encode()
{
}

std::string	MD5encode::encode(std::string const &message)
{
  CryptoPP::Weak1::MD5	hash;
  byte digest[ CryptoPP::Weak1::MD5::DIGESTSIZE ];

  hash.CalculateDigest( digest, (byte*) message.c_str(), message.length() );

  CryptoPP::HexEncoder encoder;
  std::string output;
  encoder.Attach( new CryptoPP::StringSink( output ) );
  encoder.Put( digest, sizeof(digest) );
  encoder.MessageEnd();
  std::transform(output.begin(), output.end(), output.begin(), ::tolower);
  return (output);
}
