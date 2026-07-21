#include "Database.h"
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <iostream>

Database* Database::instance = nullptr;

Database::Database() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        conn.reset(driver->connect("tcp://127.0.0.1:3306", "root", "password"));
        
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        stmt->execute("CREATE DATABASE IF NOT EXISTS EventLogistics");
        stmt->execute("USE EventLogistics");
        
    } catch (sql::SQLException &e) {
        std::cout << "DB Connection Error: " << e.what() << std::endl;
    }
}

Database* Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
    }
    return instance;
}

sql::Connection* Database::getConnection() {
    return conn.get();
}

void Database::initializeTables() {
    try {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        // Preserving your old table
        stmt->execute("CREATE TABLE IF NOT EXISTS CustomEvents (event_id INT AUTO_INCREMENT PRIMARY KEY, event_name VARCHAR(100), expected_capacity INT, estimated_budget DECIMAL(12,2))");
        // Creating the new Venues table
        stmt->execute("CREATE TABLE IF NOT EXISTS Venues (venue_id INT AUTO_INCREMENT PRIMARY KEY, venue_name VARCHAR(100), max_capacity INT, rental_cost DECIMAL(12,2), is_available BOOLEAN DEFAULT TRUE)");
    } catch (sql::SQLException &e) {
        std::cout << "Table Init Error: " << e.what() << std::endl;
    }
}