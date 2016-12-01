#ifndef CONCURRENCY_LAMBDAOBSERVER_H
#define CONCURRENCY_LAMBDAOBSERVER_H

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
//        std::cout << "callback registered, current _callbackIds.size()=" << _callbackIds.size() << '\n';

        return [wObserver = std::weak_ptr<Observer<Arg...>>{this->shared_from_this()}, callbackId](Arg ...arg){
            std::shared_ptr<Observer<Arg...>> sObserver = wObserver.lock();
            if (sObserver) {
                sObserver->_parameters.push_back(std::make_tuple(arg...));
                sObserver->notify(callbackId);

//                std::lock_guard<std::mutex> locker(Mutex);
                std::cout << "callback Dregistered " << callbackId << '\n';
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
//        std::lock_guard<std::mutex> locker(Mutex);
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


#endif //CONCURRENCY_LAMBDAOBSERVER_H
