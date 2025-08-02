#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>

class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager();
    ~DatabaseManager();

    sqlite3* getDB();

    std::vector<std::map<std::string, std::string>> executarSelect(const std::string& sql);
    bool executarQuery(const std::string& sql);

    std::string getColuna(sqlite3_stmt* stmt, int col);

    // Removida a declaração de criarTabelas()
    // void criarTabelas();
};

#endif
