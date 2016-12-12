#ifndef DATABASE_H
#define DATABASE_H

#include "Logger.hpp"
#include <sqlite3.h>

class Database {
public:
    explicit Database(const std::string &fileName);
    ~Database();

    bool createSchema(const std::string &schema);
    bool insert(const std::string &query);
    void execute(const std::string &query, int (*callback)(void*,int,char**,char**));

private:
    std::string _fileName;
    int _result = 0;
    char *_error = nullptr;
    sqlite3_stmt *_stmt     = nullptr;
    sqlite3      *_database = nullptr;
};

#endif //DATABASE_H
