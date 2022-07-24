exec:				main.o	BlueBerry.o
					g++ -o exec BlueBerry.o main.o

main.o:				main.cpp include/BlueBerry.hpp
					g++ -c main.cpp

BlueBerry.o:		src/BlueBerry.cpp include/BlueBerry.hpp
					g++ -c -Wall src/BlueBerry.cpp
