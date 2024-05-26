//
// Created by spl211 on 02/01/2021.
//

#include "../include/readAndWrite.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <iostream>
#include "boost//lexical_cast.hpp"


using namespace std;

using std::cin;

    ConnectionHandler *connectionHandler;
    bool *terminate;

    readAndWrite::readAndWrite(ConnectionHandler &connectionHandler, bool &terminate) : connectionHandler(connectionHandler), terminate(terminate){}

    void readAndWrite::run() {
        while (!terminate) {
            string input = "";
            string word = "";
            short opCode;
            string withoutOpCode = "";

            getline(cin, input);
            int i = 0;
            int size = input.size();
            while (i < size && (input.at(i) != ' ')) {
                i++;
            }

            word = input.substr(0, i);

            if (word == "ADMINREG")
                opCode = 1;
            else if (word == "STUDENTREG")
                opCode = 2;
            else if (word == "LOGIN")
                opCode = 3;
            else if (word == "LOGOUT")
                opCode = 4;
            else if (word == "COURSEREG")
                opCode = 5;
            else if (word == "KDAMCHECK")
                opCode = 6;
            else if (word == "COURSESTAT")
                opCode = 7;
            else if (word == "STUDENTSTAT")
                opCode = 8;
            else if (word == "ISREGISTERED")
                opCode = 9;
            else if (word == "UNREGISTER")
                opCode = 10;
            else if (word == "MYCOURSES")
                opCode = 11;


            if (opCode != 4 && opCode != 11) {
                withoutOpCode = input.substr(i + 1, input.size());
            }

            //read the opCode from keyBoard
           /* if (withoutOpCode.length() == 1) {
                withoutOpCode = '0' + withoutOpCode;
            }
*/
            int len;
            if (opCode == 1 || opCode == 2 || opCode == 3) {
                i = 0;
                int size = withoutOpCode.size();
                while (i < size) {
                    if (withoutOpCode.at(i) == ' ') {
                        withoutOpCode.at(i) = '\0';
                    }
                    i++;
                }
                len = 3 + withoutOpCode.length();
            }

            short courseNumber;

            if (opCode == 8) {
                len = 3 + withoutOpCode.length();
            }

            if ((opCode == 4) | (opCode == 11)) {
                len = 2;
            }

            char opCodeByte[len];

            connectionHandler.shortToBytes(opCode, opCodeByte);

            if (opCode == 5 || opCode == 6 || opCode == 7 || opCode == 9 || opCode == 10) {
                //len = 2 + withoutOpCode.length();
                courseNumber= boost::lexical_cast<short>(withoutOpCode);
                char sendCourseNum[2];
                connectionHandler.shortToBytes(courseNumber,sendCourseNum);
                int i1=0;
                int j = 2;
                int size1 = withoutOpCode.length();
                while (i1 < size1) {
                    opCodeByte[j] = sendCourseNum[i1];
                    i1++;
                    j++;
                }
                len = 4;

            }
            else {
                int i1 = 0;
                int j = 2;
                int size1 = withoutOpCode.length();
                while (i1 < size1) {
                    opCodeByte[j] = withoutOpCode.at(i1);
                    i1++;
                    j++;
                }

                if (opCode != 4 && opCode != 11) {
                    opCodeByte[j] = '\0';
                }
            }



            connectionHandler.sendBytes(opCodeByte, len);
        }
    }





