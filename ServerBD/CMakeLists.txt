cmake_minimum_required(VERSION 3.20)

# Устанавливаем имя проекта
project(ServerProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Добавляем исходные файлы
set(SOURCES
    DB.h
    BC_Errors.h
    ID.h
    DB.cpp
    sha256.h
    sha256.cpp
    Logs.cpp
    Logs.h
    BankOfUsers.cpp
    BankOfUsers.h
    ServerBD.cpp
)

# Включаем строгое соответствие стандарту C++ (для MSVC)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

# Добавляем исполняемый файл
add_executable(ServerBD ${SOURCES})

# Подключаем библиотеку Winsock2
target_link_libraries(ServerBD ws2_32)

# проект использует Windows API
target_compile_definitions(ServerBD PRIVATE _WIN32_WINNT=0x0601) # Для Windows 7 и выше


