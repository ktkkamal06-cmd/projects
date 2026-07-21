#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <memory>

class Database {
private:
    static Database* instance;
    std::unique_ptr<sql::Connection> conn;
    Database(); // Private constructor for Singleton

public:
    static Database* getInstance();
    sql::Connection* getConnection();
    void initializeTables();
};

#endif