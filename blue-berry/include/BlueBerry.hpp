#ifndef BB_H
#define BB_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


class BlueBerry
{
    private:
        int socketDescriptor;
        struct sockaddr_in servAddr;
        struct hostent *server;
        std::string host;
        std::string port;
        std::string resource;
        std::string queryParams;
        unsigned short int bufferSize;

    public: 
        // CONSTRUCTOR & DISTRUCTOR
        BlueBerry(struct sockaddr_in, std::string = "",  std::string = "", std::string = "", std::string = "");
        ~BlueBerry();
        
        // CONN UTILITIES
        bool establishConnection();
        std::string performGETReq();
        void closeSocket();
        
        // SETTERS
        void setSocket();
        void setServerAddress(struct sockaddr_in);
        void setHost(std::string = "");
        void setPort(std::string = "");
        void setResource(std::string = "");
        void setQueryParams(std::string = "");
        void setBufferSize(unsigned short int);

        // GETTERS
        int getSocketDescriptor();
        struct sockaddr_in getServerAddress();
        std::string getHost();
        std::string getPort();
        std::string getResource();
        std::string getQueryParams();
        unsigned short int getBufferSize();

};

#endif // BB_H include guard