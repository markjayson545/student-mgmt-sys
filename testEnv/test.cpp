#include <sqlite3.h>
#include <iostream>
using namespace std;

int main() {
  sqlite3 *db; // Database handle
    int rc;

  // Open the database (create if it doesn't exist)
    rc = sqlite3_open("mydatabase.db", &db);
    if (rc != SQLITE_OK) {
    cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
    return 1;
    }

  // Create a table (if it doesn't exist)
  char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
    cerr << "Error creating table: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
    return 1;
    }

  // Insert data (example)
    string name = "Alice";
    sql = "INSERT INTO users (name) VALUES (?)";
    sqlite3_stmt *stmt; // Prepared statement handle
    rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
    return 1;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT); // Bind name
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
    cerr << "Error inserting data: " << sqlite3_errmsg(db) << endl;
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1;
    }

  sqlite3_finalize(stmt); // Clean up the prepared statement

  // Close the database connection
    sqlite3_close(db);

    cout << "Success!" << endl;
    return 0;
}
