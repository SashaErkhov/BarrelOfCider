// sstrings.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "LexicalAnalysis.h"

const int PORT = 2024;

#pragma comment(lib, "ws2_32.lib")

void logTime(std::ofstream& LogFile) {
    std::time_t now = std::time(0);
    std::tm localTime;
    localtime_s(&localTime, &now); // Используем localtime_s для получения локального времени
    LogFile << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << " - ";
}

void handleError(bool err, const char* msg, std::ofstream& LogFile) {
    if (!err)
        return;
    logTime(LogFile);
    LogFile << msg << std::endl;
    std::cout << msg;
    exit(EXIT_FAILURE);
}


int main(int argc, char const* argv[])
{


    std::ofstream LogFile("log.txt"); // Открываем файл в режиме добавления
    if (!LogFile) {
        std::cout << "Cannot open the file" << std::endl;
        return -1;
    }

    if (argc < 2) {
        handleError(true, "Cannot open the configuration file", LogFile);
        return -1;
    }

    std::ifstream configFile;
    configFile.open(argv[1]);
    if (!configFile) {
        handleError(true, "Cannot open the configuration file", LogFile);
        return -1;
    }

    std::string line;
    std::string PASSWORD;
    std::string IPConf;
    std::string nameConf;

    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string key, equal_sign;

        // Разделяем строку на ключ и значение
        if (iss >> key >> equal_sign) {
            if (equal_sign == "=") {
                if (key == "IP") {
                    iss >> IPConf; // Считываем пароль
                }
                else if (key == "name") {
                    iss >> nameConf; //Считываем имя
                }
                else {
                    handleError(true, "Something wrong with configuration file", LogFile);
                }
            }
            else {
                handleError(true, "Something wrong with configuration file", LogFile);
            }
        }
        else {
            handleError(true, "Something wrong with configuration file", LogFile);
        }
    }


    WSADATA wsa;
    int startup = WSAStartup(MAKEWORD(2, 2), &wsa);
    handleError(startup != 0, "Failed. Error Code : ", LogFile);

    LPCSTR IP = IPConf.c_str();
    
    SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
    handleError(client_sock == SOCKET_ERROR, "Could not create socket : ", LogFile);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    InetPtonA(AF_INET, (IP), &servaddr.sin_addr.s_addr);

    int status = connect(client_sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    handleError(status == SOCKET_ERROR, "Could not connect to server : ", LogFile);

    char buffer[1080] = { 0 };

    std::string UserInfo;
    std::cout << "Please, enter the password for your account" << std::endl;
    std::getline(std::cin, UserInfo);
    UserInfo = nameConf + " " + UserInfo;
    send(client_sock, UserInfo.c_str(), UserInfo.length(), 0);
    logTime(LogFile);
    LogFile << "password was send" << std::endl;
    int valread = recv(client_sock, buffer, 1024, 0);
    handleError(valread <= 0, "Connection closed by server.\n", LogFile);
    logTime(LogFile);
    LogFile << "client input:"<<buffer << std::endl;

    if (buffer[0] != '1') {
        WSACleanup();
        handleError(true, "The password by client is wrong. Session is closed!", LogFile);
    }

    std::cout << ">";
    std::string command;
    std::string log="";
    std::string str_res="";
    std::getline(std::cin, command);
    LexicalAnalysis result;
    int state = result.checkBasic(command, log, str_res);
    std::string output;
    while (state != LexResult::quit) {
        if (state == LexResult::error) {
            std::cout << log;
        }
        else {
            send(client_sock, str_res.c_str(), str_res.size(), 0);
            logTime(LogFile);
            LogFile << "user send command" << std::endl;
            recv(client_sock, buffer, 1080, 0);
            logTime(LogFile);
            LogFile << "user get outcome from server" << std::endl;
            std::cout << buffer;
            memset(buffer, 0, sizeof(buffer));
        }
        log = "";
        str_res = "";
        std::cout <<std::endl<< ">";
        std::getline(std::cin, command);
        state = result.checkBasic(command, log, str_res);
    }
    str_res = "q";
    send(client_sock, str_res.c_str(), str_res.size(), 0);
    logTime(LogFile);
    LogFile << "user send exit command" << std::endl;
    logTime(LogFile);
    LogFile << "connection to server is closed." << std::endl;
    closesocket(client_sock);
    WSACleanup();
}

