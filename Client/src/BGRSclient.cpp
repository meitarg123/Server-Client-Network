#include <stdlib.h>
#include "../include/readAndWrite.h"
//#include "../include/connectionHandler.h"

#include <iostream>


/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    //std::this_thread::sleep_until()
    std::string host = argv[1];
    short port = atoi(argv[2]);
    bool terminate = false;

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect " << endl;
    }

    readAndWrite readKey(connectionHandler, terminate);
    std::thread th1(&readAndWrite::run, &readKey);

    while (!terminate) {

        char bytes[2];//for the opCODE - BYTESTOSHORT
        connectionHandler.getBytes(bytes, 2);
        short opCode = connectionHandler.bytesToShort(bytes);
        char bytesOp[2];

        connectionHandler.getBytes(bytesOp, 2);
        short msgOp = connectionHandler.bytesToShort(bytesOp);
        if (opCode == 12) {
            string str = "";
            if (msgOp == 6 || msgOp == 7 || msgOp == 8 || msgOp == 9 || msgOp == 11) {
                connectionHandler.getFrameAscii(str, '\0');

            }

            if (str == "") {
                cout << "ACK " << msgOp << endl;
            } else {
                cout << "ACK " << msgOp << '\n' << str << endl;
            }

        } else if (opCode == 13) {
            cout << "ERR " << msgOp << endl;
        }

        if (msgOp == 4 & opCode == 12) {
            terminate = true;
        }
    }

        exit(0);
    //th1.join();
    //return 0;
}
