#ifndef CONCURRENCY_ASYNCFILE_H
#define CONCURRENCY_ASYNCFILE_H

#include <mutex>
#include <fstream>
#include <string>

class JsonWriter {
private:
    std::ofstream _ofstream;
    std::mutex _mutex;

public:
    JsonWriter();
    ~JsonWriter();
    void sharedWrite(const std::string &json);
};

#endif //CONCURRENCY_ASYNCFILE_H
