#pragma once

#include "Logger.hpp"
#include <sqlite3.h>

class Database {
public:
    explicit Database(const std::string &fileName);
    ~Database();

    bool createSchema(const std::string &schema);
    bool insert(const std::string &query);
    void execute(const std::string &query);
    void execute(const std::string &query, int (*callback)(void*,int,char**,char**));

private:
    std::string fileName_;
    int result_  = 0;
    char *error_ = nullptr;
    sqlite3_stmt *stmt_ = nullptr;
    sqlite3      *db_   = nullptr;
};
