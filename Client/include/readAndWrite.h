//
// Created by spl211 on 02/01/2021.
//

#ifndef ASS32_READANDWRITE_H
#define ASS32_READANDWRITE_H
#include <string>
#include <boost/asio.hpp>
#include "../include/connectionHandler.h"

using boost::asio::ip::tcp;

#include <thread>
using namespace std;


class readAndWrite{
private:
    //const string host;//ip
    //const short port;
    ConnectionHandler &connectionHandler;
    bool &terminate;

public:
    readAndWrite(ConnectionHandler &connectionHandler, bool &terminate);
    void run();

};

#endif //ASS32_READANDWRITE_H