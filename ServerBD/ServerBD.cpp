// ServerBD.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <time.h>
#include <sstream>
#include "BankOfUsers.h"
#include "BC_Errors.h"
#include "DB.h"
#include "ID.h"
#include "ID.h"
#include "sha256.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
const int PORT = 2024;

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

int main(int argc, char const* argv[]) {


    std::ofstream LogFile("log.txt"); 
    if (!LogFile) {
        std::cout << "Cannot open the file" << std::endl;
        return -1;
    }

    // иницализируем винсок
    logTime(LogFile);
    LogFile << "Initialising Winsock...\n";
    WSADATA wsa;
    int res = WSAStartup(MAKEWORD(2, 2), &wsa);
    handleError(res != 0, "Failed. Error Code: ", LogFile);

    int valread;
    int opt = 1;
    const char* hello = "hello";
    char buffer[1080] = { 0 };
    SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
    handleError(server_sock == SOCKET_ERROR, "Could not create socket: ", LogFile);

    LogFile << "Server socket created.\n";

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    res = bind(server_sock, (struct sockaddr*)&address, sizeof(address));
    handleError(res == SOCKET_ERROR, "Bind failed with error code: ", LogFile);
    LogFile << "Bind done\n";

    res = listen(server_sock, 3);
    //handleError(res <0, "listen failed with error code: ", LogFile);

    SOCKET new_socket;
    new_socket = accept(server_sock, (struct sockaddr*)&address, &addrlen);
    logTime(LogFile);
    LogFile << "User connected.\n";
    handleError(new_socket == SOCKET_ERROR, "Accept failed with error code: ", LogFile);
    bool correct_pass = true;

    IDer start;
    DataBank DB(start);

    BankOfUsers::addUser("admin", "qwerty");//создаем пользователя - админа

    recv(new_socket, buffer, 1080, 0); // сначала принимаем Имя и пароль от первого пользователя
    std::istringstream inf1(buffer); // Создаем поток из строки
    std::string name;
    std::string password;
    std::string output = "1";


    // Считываем значения из потока
    inf1 >> name >> password;
    if (!BankOfUsers::checkUser(name,password)) {
        logTime(LogFile);
        LogFile << "Check user password and name" << std::endl;
        output = "0"; // Если неверно , то отправляем единичку. Иначе - ноль
    }
    send(new_socket, output.c_str(), output.size(), 0);
    logTime(LogFile);
    LogFile << "send to user information about correctness his name and pass" << std::endl;
    memset(buffer, 0, sizeof(buffer));
    bool isEnd = 0;
    while (!isEnd) {
        
        std::string first = "";
        std::string second = "";
        std::string third = "";
        std::string res = "success!";
        memset(buffer, 0, sizeof(buffer));
        recv(new_socket, buffer, 1080, 0);
        logTime(LogFile);
        LogFile << "get command from user" << std::endl;
        std::istringstream command(buffer+1);
        switch (buffer[0]) {
        case 'r': {
            logTime(LogFile);
            LogFile << "add User" << std::endl;
            std::string nameFromMessage = "";
            std::string passwordFromMessage = "";
            command >> nameFromMessage >> passwordFromMessage;
            BankOfUsers::addUser(nameFromMessage, passwordFromMessage);
            break;
        }
        case 'a': {
            logTime(LogFile);
            LogFile << "add note" << std::endl;
            std::string nameFromMessage = "";
            std::string valueFromMessage = "";
            command >> nameFromMessage >> valueFromMessage;;
            DB.add(nameFromMessage, valueFromMessage);
            break; }
        case 'd': {
            logTime(LogFile);
            LogFile << "delete data" << std::endl;
            std::string IDFromMessage;
            command >> IDFromMessage;
            DB.del(stoul(IDFromMessage));
            break;
        }

        case 'u': {
            logTime(LogFile);
            LogFile << "update data" << std::endl;
            std::string IDFromMessage;
            std::string NewNameFromMessage;
            std::string NewValueFromMessage;
            command >> IDFromMessage >> NewNameFromMessage >> NewValueFromMessage;
            DB.update(stoul(IDFromMessage), NewNameFromMessage, NewValueFromMessage);
            break;
        }

        case 'l':
            logTime(LogFile);
            LogFile << "print all data" << std::endl;
            res = DB.getAll();
            break;
        case 'n': {
            logTime(LogFile);
            LogFile << "print data with specific name" << std::endl;
            std::string NameFromMessage;
            command >> NameFromMessage;
            res = DB.getAllWhereName(NameFromMessage);
            break; 
        }
        case 'v': {
            logTime(LogFile);
            LogFile << "print data with specific value" << std::endl;
            std::string ValueFromMessage;
            command >> ValueFromMessage;
            res = DB.getAllWhereValue(ValueFromMessage);
            break;
        }
        case 'q': {
            logTime(LogFile);
            LogFile << "quit session" << std::endl;
            isEnd = true;
            break;
        }
        }


        send(new_socket, res.c_str(), res.length(), 0);
        logTime(LogFile);
        LogFile << "send result to user" << std::endl;
        
        if (res.length() == 0) {
            res = "Nothing found!";
            send(new_socket, res.c_str(), res.length(), 0);
        }
        
        


    }
    logTime(LogFile);
    LogFile << "session is closed" << std::endl;
    closesocket(new_socket);
    closesocket(server_sock);
    WSACleanup();
    return 0;
    


}
