#pragma once

#include <string>
#include <vector>

struct NovaLocker
{
    int id {};
    std::string type {};
    bool locked {};
    int pinNumber {};
    // ...
};
