#include "Database.hpp"

#include "Logger.hpp"
#include <sqlite3.h>

int callback(UNUSED void *NotUsed, int numberOfRows, char **values, char **columnName) {
    logDebug() << "Callback with" << numberOfRows << "result(s)";
    int i;
    for (i=0; i<numberOfRows; i++) {
        logDebug() << columnName[i] << "=" << (values[i] ? values[i] : "NULL");
    }
    return 0;
}

int main() {
    Database database("exercise.db");

    database.execute("SELECT * FROM Students;", callback);

    return 0;
}
