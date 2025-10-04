#include <iostream>
#include "UserThread.h"
#include "Gate.h"

int main() {
    std::cout << "Testing Gate, hit CTRL+C to exit." << std::endl;
    
    Gate* gate = new Gate();
    UserThread thread1 = UserThread(gate, "Alice", "Alaska");
    UserThread thread2 = UserThread(gate, "Bobby", "Brazil");
    UserThread thread3 = UserThread(gate, "Chris", "Canada");

    thread1.Start();
    thread2.Start();
    thread3.Start();

    thread1.Join();
    thread2.Join();
    thread3.Join();

    delete gate;
    return 0;
}
