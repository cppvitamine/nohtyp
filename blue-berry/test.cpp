#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    //Socket creation
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0)
    {
        std::cout << "failed to create socket" << std::endl;
        return 0;
    }

    //Query building
    struct sockaddr_in serv_addr;
    char buffer[4096];
    std::string host = "www.exampleweb.com";
    std::string port = "80";
    std::string resource = "/folder/file.php";
    std::string query = "?parameter=value&parameter2=value2";

    // Hostname resolving
    struct hostent *server = gethostbyname(host.c_str());
    if (!server)
    {
        std::cout << "could Not resolve hostname :(" << std::endl;
        close(socket_desc);
        return 0;
    }

    // Connection phase
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(std::stoi(port));
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    if (connect(socket_desc, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "connection failed :(" << std::endl;
        close(socket_desc);
        return 0;
    }

    //GET request
    std::string request = "GET " + resource + query + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";

    if (send(socket_desc, request.c_str(), request.size(), 0) < 0)
    {
        std::cout << "failed to send request..." << std::endl;
        close(socket_desc);
        return 0;
    }

    //Getting response
    int n;
    std::string raw_site;
    while ((n = recv(socket_desc, buffer, sizeof(buffer), 0)) > 0)
    {
        raw_site.append(buffer, n);
    }
    int a;
    std::cin >> a;
    //Closing 
    close(socket_desc);

    std::cout << raw_site << std::endl;
    return 0;
}