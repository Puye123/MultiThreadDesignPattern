#include <iostream>
#include "Gate.h"

void Gate::Pass(std::string name, std::string address) {
    std::lock_guard<std::mutex> lock(mtx);
    this->counter++;
    this->name = name;
    this->address = address;
    Check();
}

std::string Gate::ToString() {
    std::lock_guard<std::mutex> lock(mtx);
    return "No." + std::to_string(this->counter) + ": " + this->name + ", " + this->address;
}

void Gate::Check() {
    if (this->name[0] != this->address[0]) {
        std::cout << "***** BROKEN *****" << ToString() << std::endl;
    }
}
