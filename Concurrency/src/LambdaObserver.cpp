#include "LambdaObserver.h"


void async(int x, const std::function<void(const std::string &)> &callback) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    callback(std::to_string(x));
}

int main() {

    auto observer = std::make_shared<Observer<int, std::string>>();

    std::vector<std::future<void>> futures;

    observer->setFinishHandler([](std::vector<std::tuple<int, std::string>> parameters){
        int numberOfCalls(0);
        std::string s;
        for(auto i : parameters) {
            numberOfCalls += std::get<0>(i);
            s += std::get<1>(i) + "+";
        }
        logDebug() << "finished::(" << parameters.size() << ")callbacks.\n" << "result:: " << s;
    });

    for (int i = 1; i <= 10; ++i) {
        std::function<void(int, std::string)> callme = *observer;

        auto f = std::async(std::launch::async, async, i, [callme, i](const std::string &str){ callme(i, str); });

        futures.push_back(std::move(f));
    }

    observer->start();


    return 0;
}