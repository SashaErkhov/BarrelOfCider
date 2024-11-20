#include <gtest/gtest.h>
#include "../code/Logs.h"

TEST(LogsTests, Test) {
    Logs::debug("Hello");
    Logs::info("Hello");
    Logs::error("Hello");
    Logs::warning("Hello");
}