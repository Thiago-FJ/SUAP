#include "DatabaseManager.h"
#include <iostream>

using namespace std;

DatabaseManager::DatabaseManager() {
    int rc = sqlite3_open("DBSuap.db", &db);
    if (rc) {
        cerr << "\t\tErro ao abrir o banco de dados: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    }
    // Removida a chamada para criarTabelas()
}

DatabaseManager::~DatabaseManager() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3* DatabaseManager::getDB() {
    return db;
}

vector<map<string, string>> DatabaseManager::executarSelect(const string& sql) {
    vector<map<string, string>> resultados;
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "\t\tErro no SELECT: " << sqlite3_errmsg(db) << endl;
        return resultados;
    }

    int cols = sqlite3_column_count(stmt);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        map<string, string> linha;
        for (int i = 0; i < cols; ++i) {
            string colName = sqlite3_column_name(stmt, i);
            const unsigned char* val = sqlite3_column_text(stmt, i);
            linha[colName] = val ? string(reinterpret_cast<const char*>(val)) : "";
        }
        resultados.push_back(linha);
    }
    sqlite3_finalize(stmt);
    return resultados;
}

bool DatabaseManager::executarQuery(const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "\t\tErro na query: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

string DatabaseManager::getColuna(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? string(reinterpret_cast<const char*>(text)) : "";
}


