#include "Connection.h"

namespace {

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
} // namespace

namespace litedb {

Connection::Connection(const std::string &fileName) : fileName_(fileName)
{
    result_ = sqlite3_open_v2(fileName_.c_str(),
                               &db_,
                               SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX,
                               NULL);

    if (result_ != SQLITE_OK) {
        logError() << "couldn't open database (" << fileName_ << ')' << sqlite3_errmsg(db_);
        sqlite3_close(db_);
    }

    // TODO: Schema creation should be operated with configuration file
    createSchema(studentsSchema);
    // TODO: Data insertion should be re engineered
    insert(insertStudent1);
    insert(insertStudent2);
}

Connection::~Connection()
{
    result_ = sqlite3_close(db_);
    if (result_ != SQLITE_OK) {
        logError() << "couldn't close database (" << fileName_ << ") properly:" << sqlite3_errmsg(db_);
    }
}

bool Connection::createSchema(const std::string &schema)
{
    result_ = sqlite3_exec(db_, schema.c_str(), nullptr, nullptr, &error_);
    if (result_ != SQLITE_OK) {
        logError() << "Couldn't create schema:" << sqlite3_errmsg(db_);
        return false;
    }

    return true;
}

bool Connection::insert(const std::string &query)
{
    result_ = sqlite3_exec(db_, query.c_str(), nullptr, nullptr, &error_);
    if (result_ != SQLITE_OK) {
        logError() << "Couldn't execute insert query:" << error_;
        return false;
    }
    return true;
}

void Connection::execute(const std::string &query)
{
    logInfo() << "Query with prepare->step->finalize";
    result_ = sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt_, nullptr);
    if (result_ != SQLITE_OK) {
        logError() << "Couldn't prepare query:" << sqlite3_errmsg(db_);
    }

    while ((result_ = sqlite3_step(stmt_)) == SQLITE_ROW) {
        int columns = sqlite3_column_count(stmt_);
        for (int i = 0; i < columns; ++i) {
            switch (sqlite3_column_type(stmt_, i)) {
                case SQLITE_INTEGER:
                    logInfo() << sqlite3_column_name(stmt_, i) << ":" << sqlite3_column_int(stmt_, i);
                    break;
                case SQLITE_FLOAT:
                    logInfo() << sqlite3_column_name(stmt_, i) << ":" << sqlite3_column_double(stmt_, i);
                    break;
                case SQLITE_BLOB:
                    logInfo() << sqlite3_column_name(stmt_, i) << ":" << sqlite3_column_blob(stmt_, i);
                    break;
                case SQLITE_TEXT:
                    logInfo() << sqlite3_column_name(stmt_, i) << ":" << sqlite3_column_text(stmt_, i);
                    break;
                case SQLITE_NULL:
                    logWarn() << "Column Type NULL";
                    logInfo() << sqlite3_column_name(stmt_, i) << ":" << sqlite3_column_text(stmt_, i);
                    break;
            }
        }
    }
    sqlite3_finalize(stmt_);
}

void Connection::execute(const std::string &query, UNUSED int (*callback)(void*,int,char**,char**))
{
    logDebug() << "Query with exec";
    result_ = sqlite3_exec(db_, query.c_str(), callback, nullptr, &error_);
    if (result_ != SQLITE_OK) {
        logError() << "Couldn't execute query:" << error_;
    }
}

} // litedb