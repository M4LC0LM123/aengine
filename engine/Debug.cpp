#include "headers/Debug.h"
#include "iostream"

#define nextln "\n"

struct Debug
{
    
    static void mode(bool debugMode)
    {
        EntityManager::renderCollidersBool = debugMode;
        EntityManager::debugBool = debugMode;
    }

    static void println(std::string str)
    {
        std::cout << str << nextln;
    }

    static void println(char* str)
    {
        std::cout << str << nextln;
    }

    static void print(std::string str)
    {
        std::cout << str;
    }

    static void print(char* str)
    {
        std::cout << str;
    }

    static void printCurrentDir()
    {
        std::cout << "current dir: " << getCurrentDir() << nextln;
    }

    static void readln(std::string str)
    {
        std::cin >> str;
    }

    static void readln(char* str)
    {
        std::cin >> str;
    }

};
