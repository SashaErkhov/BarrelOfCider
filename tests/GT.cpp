#include <string>
#include <iostream>
#include "Logs.h"

int main()
{
    Logs::debug("Hello");
    Logs::info("Hello");
    Logs::error("Hello");
    Logs::warning("Hello");
    return 0;
}