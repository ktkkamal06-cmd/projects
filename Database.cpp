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
        // Old Tables
        stmt->execute("CREATE TABLE IF NOT EXISTS CustomEvents (event_id INT AUTO_INCREMENT PRIMARY KEY, event_name VARCHAR(100), expected_capacity INT, estimated_budget DECIMAL(12,2))");
        stmt->execute("CREATE TABLE IF NOT EXISTS Venues (venue_id INT AUTO_INCREMENT PRIMARY KEY, venue_name VARCHAR(100), max_capacity INT, rental_cost DECIMAL(12,2), is_available BOOLEAN DEFAULT TRUE)");
        
        // --- NEW TABLES ---
        stmt->execute("CREATE TABLE IF NOT EXISTS Vendors (vendor_id INT AUTO_INCREMENT PRIMARY KEY, vendor_name VARCHAR(100), vendor_type VARCHAR(50), price DECIMAL(12,2))");
        stmt->execute("CREATE TABLE IF NOT EXISTS Equipment (equipment_id INT AUTO_INCREMENT PRIMARY KEY, equipment_name VARCHAR(100), total_quantity INT, rental_price DECIMAL(12,2))");
        stmt->execute("CREATE TABLE IF NOT EXISTS Staff (staff_id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(100), role VARCHAR(50), contact_number VARCHAR(20))");
        // --- PHASE 2: THE CORE ENGINE ---
        stmt->execute("CREATE TABLE IF NOT EXISTS Events ("
                      "event_id INT AUTO_INCREMENT PRIMARY KEY, "
                      "event_name VARCHAR(100), "
                      "event_date VARCHAR(20), "
                      "event_time VARCHAR(20), "
                      "venue_id INT, "
                      "expected_capacity INT, "
                      "budget_limit DECIMAL(12,2), "
                      "estimated_budget DECIMAL(12,2) DEFAULT 0, "
                      "revenue DECIMAL(12,2) DEFAULT 0, "
                      "profit DECIMAL(12,2) DEFAULT 0, "
                      "FOREIGN KEY(venue_id) REFERENCES Venues(venue_id))");
    } catch (sql::SQLException &e) {
        std::cout << "Table Init Error: " << e.what() << std::endl;
    }
}