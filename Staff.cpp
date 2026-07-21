#include "Staff.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

void Staff::addStaff() {
    std::string name, role, phone;

    std::cout << "\nEnter Staff Name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter Role (e.g., Security, Registration, Hospitality): ";
    std::getline(std::cin >> std::ws, role);
    std::cout << "Enter Contact Number: ";
    std::getline(std::cin >> std::ws, phone);

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Staff (name, role, contact_number) VALUES (?, ?, ?)"
        ));
        pstmt->setString(1, name);
        pstmt->setString(2, role);
        pstmt->setString(3, phone);
        pstmt->execute();

        std::cout << "\nSuccess! Staff member '" << name << "' added to the roster.\n";
    } catch (sql::SQLException &e) {
        std::cout << "Error adding staff: " << e.what() << std::endl;
    }
}

void Staff::viewAllStaff() {
    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM Staff"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- STAFF ROSTER ---\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" 
                  << std::setw(20) << "Role" << "Contact\n";
        std::cout << "--------------------------------------------------------------\n";

        while (res->next()) {
            std::cout << std::left << std::setw(5) << res->getInt("staff_id")
                      << std::setw(25) << res->getString("name")
                      << std::setw(20) << res->getString("role")
                      << res->getString("contact_number") << "\n";
        }
    } catch (sql::SQLException &e) {
        std::cout << "Error fetching staff: " << e.what() << std::endl;
    }
}