#include <iostream>
#include <sqlite3.h>
using namespace std;

int main(){
        sqlite3 *db; // Database handle
        int rc;

        rc = sqlite3_open("mydatabase.db", &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1; // Or handle the error appropriately
        }
    return 0;
}