#pragma once

#include <iostream>
#include <thread>
#include "Gate.h"

class UserThread {
public:
    UserThread(Gate* gate, const std::string myname, const std::string myaddress)
    : gate_(gate), myname_(myname), myaddress_(myaddress) {}

    void Start();
    void Join();

private:
    std::thread t_;
    void Run();
    Gate* gate_;
    const std::string myname_;
    const std::string myaddress_;
};
