#pragma once

namespace litedb {

class Exception : public std::runtime_error {
public:
    explicit Exception(const std::string &message) : errorMessage_(message) {}
    ~Exception() {}

    virtual const char* what() const { return errorMessage_.c_str(); }

private:
    std::string errorMessage_;
};

} // litedb
