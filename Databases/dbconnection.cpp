#include <iostream>
#include <sqlite3.h>
using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}


int main(){
    cout<<"here"<<endl;
    sqlite3* db;
    int rc = sqlite3_open("Bookshop.db", &db);

    if (rc != SQLITE_OK) {
        //error message if db doesn't open right
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }

    //test connection
    char* zErrMsg = 0;
    string query = "SELECT * FROM \"Order\";";

    cout << "STATE OF TABLE BEFORE INSERT" << endl;

    rc = sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }

    //close connection at end
    sqlite3_close(db);
    cout << "Press Enter to exit...";
    cin.get();
}