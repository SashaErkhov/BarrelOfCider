cmake_minimum_required(VERSION 3.20)

# Устанавливаем имя проекта
project(ServerProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Включаем строгое соответствие стандарту C++ (для MSVC)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

# Добавляем исходные файлы
set(SOURCES
    Client.cpp
    ID.h
    LexicalAnalysis.cpp
    LexicalAnalysis.h
)

# Добавляем исполняемый файл
add_executable(ClientBD ${SOURCES})


# Подключаем библиотеку Winsock2
target_link_libraries(ClientBD ws2_32)

# проект использует Windows API
target_compile_definitions(ClientBD PRIVATE _WIN32_WINNT=0x0601) # Для Windows 7 и выше

# использовать строгую проверку стандарта C++
set_property(TARGET ClientBD PROPERTY CXX_STANDARD 17)
set_property(TARGET ClientBD PROPERTY CXX_STANDARD_REQUIRED ON)
