#include <iostream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <future>

std::mutex Mutex;

template <typename ...Arg>
class Observer : public std::enable_shared_from_this<Observer<Arg...>> {

public:
    // conversion operator
    operator std::function<void(Arg...)>() {
        int callbackId = raiseCounter();
        _callbackIds.emplace(callbackId);

        return [wObserver = std::weak_ptr<Observer<Arg...>>{this->shared_from_this()}, callbackId](Arg ...arg){
            std::cout << "callback Dregister: " << callbackId << '\n';
            std::shared_ptr<Observer<Arg...>> sObserver = wObserver.lock();
            if (sObserver) {
                    std::lock_guard<std::mutex> locker(Mutex);
                    sObserver->_parameters.push_back(std::make_tuple(arg...));
                    sObserver->notify(callbackId);
            }
            else {
                std::cout << "Observer is not alive anymore\n";
            }
        };
    }

    void setFinishHandler(std::function<void(std::vector<std::tuple<Arg...>>)> function) {
        _finishHandler = std::move(function);
    }

    void callFinishHandler() {
        std::cout << "callback remains: " << _callbackIds.size() << '\n';
        if (_callbackIds.empty() and _started and _finishHandler) {
            _finishHandler(_parameters);
        }
    }

    void start() {
        _started = true;
    }

    int raiseCounter() {
        return ++_id;
    }

    void notify(int id) {
        _callbackIds.erase(id);
        callFinishHandler();
    }

    std::function<void(std::vector<std::tuple<Arg...>>)> _finishHandler;
    std::vector<std::tuple<Arg...>> _parameters;
    std::unordered_set<int> _callbackIds;
    int _id{0};
    bool _started{false};
};

/* ------------------------------------------------------------------ */

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
        std::cout << "finished::(" << parameters.size() << ")callbacks.\n" << "result:: " << s << '\n';
    });

    for (int i = 1; i <= 10; ++i) {
        std::function<void(int, std::string)> callme = *observer;

        auto f = std::async(std::launch::async, async, i, [callme, i](const std::string &str){ callme(i, str); });

        futures.push_back(std::move(f));
    }

    observer->start();


    return 0;
}