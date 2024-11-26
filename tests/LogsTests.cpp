#include <gtest/gtest.h>
#include "../code/Logs.h"
#include "fstream"

TEST(LogsTests, Test) {
    std::fstream file;
    file.open("resources/logs.txt", std::ios::out);
    file.close();
    Logs::debug("Hello");
    Logs::info("Hello");
    Logs::error("Hello");
    Logs::warning("Hello");
}