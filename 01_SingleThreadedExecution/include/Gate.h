#pragma once

#include <string>
#include <mutex>
#include <thread>

class Gate {
public:
    void Pass(std::string name, std::string address);
    std::string ToString();

private:
    int counter = 0;
    std::string name = "Nobody";
    std::string address = "Nowhere";
    void Check();
    std::mutex mtx;
};
