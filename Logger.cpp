#include "Logger.h"
#include <iostream>

void Logger::log(const std::string& event) {
    std::cout << "[LOG] " << event << std::endl;
}
