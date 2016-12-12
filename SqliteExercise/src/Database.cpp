#include "Database.hpp"

const static std::string studentsSchema = " CREATE TABLE IF NOT EXISTS Students("
                                          " id text NOT NULL PRIMARY KEY,"
                                          " first_name text NOT NULL,"
                                          " last_name text NOT NULL,"
                                          " email text NOT NULL UNIQUE,"
                                          " phone text NOT NULL UNIQUE"
                                          ");";
const static std::string insertStudent1 = " INSERT INTO Students(id, first_name, last_name, email, phone)"
                                         " VALUES('123', 'David', 'Beckham', 'beckham@gmail.com', '12345');";
const static std::string insertStudent2 = " INSERT INTO Students(id, first_name, last_name, email, phone)"
                                         " VALUES('124', 'Victor', 'Hugo', 'vhugo@gmail.com', '54321');";

Database::Database(const std::string &fileName) : _fileName(fileName)
{
    _result = sqlite3_open_v2(_fileName.c_str(),
                               &_database,
                               SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
                               NULL);

    if (_result != SQLITE_OK) {
        logError() << "couldn't open database (" << _fileName << ')' << sqlite3_errmsg(_database);
        sqlite3_close(_database);
    }

    // TODO: Schema creation should be operated with configuration file
    createSchema(studentsSchema);
    // TODO: Data insertion should be re engineered
    insert(insertStudent1);
    insert(insertStudent2);
}

Database::~Database()
{
    _result = sqlite3_close(_database);
    if (_result != SQLITE_OK) {
        logError() << "couldn't close database (" << _fileName << ") properly:" << sqlite3_errmsg(_database);
    }
}

bool Database::createSchema(const std::string &schema)
{
//    _result = sqlite3_exec(_database, schema.c_str(), nullptr, nullptr, &_error);
//    if (_result != SQLITE_OK) {
//        logError() << "Couldn't create schema:" << sqlite3_errmsg(_database);
//        return false;
//    }

    _result = sqlite3_prepare_v2(_database, schema.c_str(), -1, &_stmt, nullptr);
    if (_result != SQLITE_OK) {
        logError() << "Couldn't prepare create schema:" << sqlite3_errmsg(_database);
        return false;
    }

    _result = sqlite3_step(_stmt);
    if (_result != SQLITE_DONE) {
        logError() << "Couldn't execute create schema:" << sqlite3_errmsg(_database);
        return false;
    }
    sqlite3_finalize(_stmt);

    return true;
}

bool Database::insert(const std::string &query)
{
    _result = sqlite3_exec(_database, query.c_str(), nullptr, nullptr, &_error);
    if (_result != SQLITE_OK) {
        logError() << "Couldn't execute insert query:" << _error;
        return false;
    }
    return true;
}

void Database::execute(const std::string &query, UNUSED int (*callback)(void*,int,char**,char**))
{
//    _result = sqlite3_exec(_database, query.c_str(), callback, nullptr, &_error);
//    if (_result != SQLITE_OK) {
//        logError() << "Couldn't execute query:" << _error;
//    }

    _result = sqlite3_prepare_v2(_database, query.c_str(), -1, &_stmt, nullptr);
    if (_result != SQLITE_OK) {
        logError() << "Couldn't prepare query:" << sqlite3_errmsg(_database);
    }

    while ((_result = sqlite3_step(_stmt)) == SQLITE_ROW) {
        for (int i = sqlite3_column_count(_stmt); i > 0; --i) {
            logDebug() << "value:" << sqlite3_column_text(_stmt, i);
        }
    }
    sqlite3_finalize(_stmt);
}