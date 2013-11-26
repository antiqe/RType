
#include <iostream>
#include "ASocket.hpp"

bool ASocket::bind(int socket, struct sockaddr_in *s_in)
{
  if (::bind(socket, (const struct sockaddr *)s_in, sizeof(*s_in)) == -1)
    {
      std::cerr << "Bind has failed." << std::endl;
      return false;
    }
  return true;
}

bool ASocket::listen(int socket, int nbClient)
{
	if (::listen(socket, nbClient) == -1)
	 {
	   std::cerr << "Listen has failed." << std::endl;
	   return false;
	 }
  return true;
}
