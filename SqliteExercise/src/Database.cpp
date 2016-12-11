#include "Database.hpp"

const static std::string studentsSchema = " CREATE TABLE IF NOT EXISTS Students("
                                          " id text NOT NULL PRIMARY KEY,"
                                          " first_name text NOT NULL,"
                                          " last_name text NOT NULL,"
                                          " email text NOT NULL UNIQUE,"
                                          " phone text NOT NULL UNIQUE"
                                          ");";
const static std::string insertStudent = " INSERT INTO Students(id, first_name, last_name, email, phone)"
                                         " VALUES('123', 'David', 'Beckham', 'beckham@gmail.com', '12345');";

Database::Database(const std::string &fileName) : _fileName(fileName)
{
    _success = sqlite3_open_v2(_fileName.c_str(),
                               &_database,
                               SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
                               NULL);

    if (_success != SQLITE_OK) {
        logError() << "couldn't open database (" << _fileName << ')' << sqlite3_errmsg(_database);
        sqlite3_close(_database);
    }

    // TODO: Schema creation should be operated with configuration file
    createSchema(studentsSchema);
    // TODO: Data insertion should be re engineered
    insert(insertStudent);
}

Database::~Database()
{
    _success = sqlite3_close(_database);
    if (_success != SQLITE_OK) {
        logError() << "couldn't close database (" << _fileName << ") properly:" << sqlite3_errmsg(_database);
    }
}

bool Database::createSchema(const std::string &schema)
{
    _success = sqlite3_exec(_database, schema.c_str(), nullptr, nullptr, &_error);
    if (_success != SQLITE_OK) {
        logError() << "Couldn't create schema:" << sqlite3_errmsg(_database);
        return false;
    }
    return true;
}

bool Database::insert(const std::string &query)
{
    _success = sqlite3_exec(_database, query.c_str(), nullptr, nullptr, &_error);
    if (_success != SQLITE_OK) {
        logError() << "Couldn't execute insert query:" << _error;
        return false;
    }
    return true;
}

void Database::execute(const std::string &query, int (*callback)(void*,int,char**,char**))
{
    _success = sqlite3_exec(_database, query.c_str(), callback, nullptr, &_error);
    if (_success != SQLITE_OK) {
        logError() << "Couldn't execute query:" << _error;
    }
}