#include "Database.h"

#include "Logger.h"
#include <sqlite3.h>

typedef int (*ResultRowCallback)(UNUSED void *NotUsed, int numberOfColumns, char **values, char **columnName);

int main() {
    litedb::Database database("exercise.db");

    // database.execute("SELECT * FROM Students;");

    ResultRowCallback rowCallback = [](UNUSED void *NotUsed, int numberOfColumns, char **values, char **columnName) ->int {
        logDebug() << "Callback with" << numberOfColumns << "columns(s)";
        int i;
        for (i=0; i<numberOfColumns; i++) {
            logDebug() << columnName[i] << "=" << (values[i] ? values[i] : "NULL");
        }
        return 0;
    };

    database.execute("SELECT * FROM Students;", rowCallback);

    return 0;
}

