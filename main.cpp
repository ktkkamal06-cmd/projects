// main.cpp
// Author: Kamal K. | Roll No: ce24btech11030
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <iostream>
#include <memory>

int main() {
    try {
        // 1. Initialize the driver
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

        // 2. Connect to the local Codespaces database
        std::unique_ptr<sql::Connection> conn(driver->connect("tcp://127.0.0.1:3306", "root", "password"));
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());

        // 3. Build and populate the schema
        stmt->execute("CREATE DATABASE IF NOT EXISTS EventLogistics");
        stmt->execute("USE EventLogistics");
        stmt->execute("CREATE TABLE IF NOT EXISTS Events (event_id INT AUTO_INCREMENT PRIMARY KEY, event_name VARCHAR(100), expected_capacity INT)");
        stmt->execute("INSERT INTO Events (event_name, expected_capacity) VALUES ('Prom Night', 2500)");

        std::cout << "Project is working! Event successfully logged in the database." << std::endl;
        
    } catch (sql::SQLException &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}