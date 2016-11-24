#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <deque>

std::mutex mu;
std::condition_variable condition;
std::deque<int> q;

// this function enqueues an integer into the dequeue
void function_thread1() {
    int count = 0;
    while (count < 10) {
        {
            std::unique_lock<std::mutex> locker(mu);
            q.push_front(++count);
        }
        condition.notify_all();     // Notify one waiting thread (if there is one)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// if there is at least one integer in the dequeue, this function pops from back.
void function_thread2() {
    int data = 0;
    while ( data != 10 ) {
        {
            std::unique_lock<std::mutex> locker(mu);
            condition.wait(locker, [](){ return !q.empty(); });
            data = q.back();
            q.pop_back();
        }
        std::cout << "::" << data << '\n';
    }
}

int main() {
    std::cout << "starting main\n";

    std::thread t1(function_thread1);
    std::thread t2(function_thread2);
    t1.join();
    t2.join();

    return 0;
}
