#include "Database.hpp"

const static std::string studentsSchema = " DROP TABLE IF EXISTS Students;"
                                          " CREATE TABLE IF NOT EXISTS Students("
                                          " id INT NOT NULL PRIMARY KEY,"
                                          " first_name text NOT NULL,"
                                          " last_name text NOT NULL,"
                                          " email text NOT NULL UNIQUE,"
                                          " phone text NOT NULL UNIQUE"
                                          ");";
const static std::string insertStudent1 = " INSERT INTO Students(id, first_name, last_name, email, phone)"
                                         " VALUES(123, 'David', 'Beckham', 'beckham@gmail.com', '12345');";
const static std::string insertStudent2 = " INSERT INTO Students(id, first_name, last_name, email, phone)"
                                         " VALUES(124, 'Victor', 'Hugo', 'vhugo@gmail.com', '54321');";

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
    _result = sqlite3_exec(_database, schema.c_str(), nullptr, nullptr, &_error);
    if (_result != SQLITE_OK) {
        logError() << "Couldn't create schema:" << sqlite3_errmsg(_database);
        return false;
    }

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

void Database::execute(const std::string &query)
{
    logInfo() << "Query with prepare->step->finalize";
    _result = sqlite3_prepare_v2(_database, query.c_str(), -1, &_stmt, nullptr);
    if (_result != SQLITE_OK) {
        logError() << "Couldn't prepare query:" << sqlite3_errmsg(_database);
    }

    while ((_result = sqlite3_step(_stmt)) == SQLITE_ROW) {
        int columns = sqlite3_column_count(_stmt);
        for (int i = 0; i < columns; ++i) {
            switch (sqlite3_column_type(_stmt, i)) {
                case SQLITE_INTEGER:
                    logInfo() << sqlite3_column_name(_stmt, i) << ":" << sqlite3_column_int(_stmt, i);
                    break;
                case SQLITE_FLOAT:
                    logInfo() << sqlite3_column_name(_stmt, i) << ":" << sqlite3_column_double(_stmt, i);
                    break;
                case SQLITE_BLOB:
                    logInfo() << sqlite3_column_name(_stmt, i) << ":" << sqlite3_column_blob(_stmt, i);
                    break;
                case SQLITE_TEXT:
                    logInfo() << sqlite3_column_name(_stmt, i) << ":" << sqlite3_column_text(_stmt, i);
                    break;
                case SQLITE_NULL:
                    logWarn() << "Column Type NULL";
                    logInfo() << sqlite3_column_name(_stmt, i) << ":" << sqlite3_column_text(_stmt, i);
                    break;
            }

        }
    }
    sqlite3_finalize(_stmt);
}

void Database::execute(const std::string &query, UNUSED int (*callback)(void*,int,char**,char**))
{
    logDebug() << "Query with exec";
    _result = sqlite3_exec(_database, query.c_str(), callback, nullptr, &_error);
    if (_result != SQLITE_OK) {
        logError() << "Couldn't execute query:" << _error;
    }
}
