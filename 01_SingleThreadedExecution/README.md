# 01_SingleThreadedExecution

## 概要
**Single Threaded Executionパターン** のサンプルコードです。
複数のスレッドが共通のインスタンスを共有する場合に、それぞれのスレッドがインスタンスを変更したらインスタンスの安全性が損なわれる。

**Single Threaded Executionパターン** はクリティカルセクションの実行は１つのスレッドのみが実行するようにガードする。

### コード例

以下のコードのうち、Pass関数及びToString関数がクリティカルセッションである。C++ではstd::mutexとstd::lock_guardでクリティカルセッションのガードを実現する。
```c++
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

```

```c++
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
```

この実行結果は以下の通り。
```
Testing Gate, hit CTRL+C to exit.
Alice BEGIN
Bobby BEGIN
Chris BEGIN
```


もし、std::mutexとstd::lock_guardが無い場合は以下のような出力となる。複数のスレッドが共通のインスタンスへの書き込みを行うことでインスタンスが破壊されていることがわかる。

実験をする場合は ``std::lock_guard<std::mutex> lock(mtx);`` をコメントアウトすればよい。

```c++
Testing Gate, hit CTRL+C to exit.
Alice BEGIN
Bobby BEGIN
Chris BEGIN
(省略)
***** BROKEN *****No.53500038: Bobby, Brazil
***** BROKEN *****No.53500082: Bobby, Brazil
***** BROKEN *****No.53500123: Chris, Canada
***** BROKEN *****No.53500165: Bobby, Brazil
***** BROKEN *****No.53500216: Bobby, Brazil
***** BROKEN *****No.53500257: Chris, Canada
***** BROKEN *****No.53500303: Chris, Canada
***** BROKEN *****No.53500347: Chris, Canada
***** BROKEN *****No.53500388: Bobby, Brazil
***** BROKEN *****No.53500442: Bobby, Brazil
***** BROKEN *****No.53500484: Chris, Canada
***** BROKEN *****No.53500525: Bobby, Brazil
***** BROKEN *****No.53500568: Bobby, Brazil
***** BROKEN *****No.53500621: Chris, Canada
***** BROKEN *****No.53500663: Bobby, Brazil
***** BROKEN *****No.53520065: Chris, Canada
***** BROKEN *****No.53521436: Alice, Alaska
***** BROKEN *****No.53521617: Alice, Alaska
***** BROKEN *****No.53521662: Alice, Alaska
(省略)
```