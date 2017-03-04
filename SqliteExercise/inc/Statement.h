#pragma once

namespace litedb {

class Statement {


private:
    sqlite3_stmt *stmt_ = nullptr;
}

} // litedb
