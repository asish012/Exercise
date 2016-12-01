#include "AsyncFile.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <numeric>

JsonWriter::JsonWriter() {
    std::lock_guard<std::mutex> locker(_mutex);
    if(not _ofstream.is_open()) { _ofstream.open("db.json"); }
}

JsonWriter::~JsonWriter() {
    std::lock_guard<std::mutex> locker(_mutex);
    if (_ofstream.is_open()) { _ofstream.close(); }
}

void JsonWriter::sharedWrite(const std::string &json) {
    std::lock_guard<std::mutex> locker(_mutex);
    if(not _ofstream.is_open()) {
        std::cout << "File not open. Couldn't write json string.\n";
        return;
    }

    _ofstream << json;
}

void write() {
    JsonWriter jsonWriter;
    std::string json = R"({
    "student": {
        "name": "Alien",
        "age" : 15,
        "dept": "CSE",
        "semester": 4
    }
})";

    std::thread t(&JsonWriter::sharedWrite, &jsonWriter, json);
    t.join();
}

int main() {
    write();

    return 0;
}
