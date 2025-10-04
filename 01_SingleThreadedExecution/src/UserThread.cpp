#include "UserThread.h"

void UserThread::Start() {
    t_ = std::thread(&UserThread::Run, this);
}

void UserThread::Join() {
    if (t_.joinable()) {
        t_.join();
    }
}

void UserThread::Run() {
    std::cout << this->myname_ << " BEGIN" << std::endl;
    while (true) {
        this->gate_->Pass(this->myname_, this->myaddress_);
    }
}