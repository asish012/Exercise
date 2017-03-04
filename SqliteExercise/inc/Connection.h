#pragma once

#include "Logger.h"
#include <sqlite3.h>

namespace litedb {

class Connection {
public:
    explicit Connection(const std::string &fileName);
    ~Connection();

    bool createSchema(const std::string &schema);
    bool insert(const std::string &query);
    void execute(const std::string &query);
    void execute(const std::string &query, int (*callback)(void*,int,char**,char**));
    // void execute(const std::string &query, std::function<int (void*, int, char**, char**)> callback);

private:
    std::string fileName_;
    int result_  = 0;
    char *error_ = nullptr;
    sqlite3_stmt *stmt_ = nullptr;
    sqlite3      *db_   = nullptr;
};

} // litedb