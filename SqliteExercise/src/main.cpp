#include "Database.hpp"

#include "Logger.hpp"
#include <sqlite3.h>

int callback(UNUSED void *NotUsed, int numberOfColumns, char **values, char **columnName) {
    logDebug() << "Callback with" << numberOfColumns << "columns(s)";
    int i;
    for (i=0; i<numberOfColumns; i++) {
        logDebug() << columnName[i] << "=" << (values[i] ? values[i] : "NULL");
    }
    return 0;
}

int main() {
    Database database("exercise.db");

    database.execute("SELECT * FROM Students;");
    // database.execute("SELECT * FROM Students;", callback);

    return 0;
}
