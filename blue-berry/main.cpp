#include "include/BlueBerry.hpp"
#include <iostream>

int main()
{
    struct sockaddr_in sk;
    BlueBerry *exchanger = new BlueBerry(sk, "blueberrys.ddns.net", "80", "/a", "");
    if (!exchanger->establishConnection())
    {
        std::cerr << "Failed to establish communication. Quitting..\n";
        return 1;
    }
    std::cout << exchanger->performGETReq() << '\n';
    
    return 0;
}