#include "Equipment.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

void Equipment::addEquipment() {
    std::string name;
    int quantity;
    double price;

    std::cout << "\nEnter Equipment Name (e.g., Acoustic Speaker): ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter Total Quantity Available: ";
    std::cin >> quantity;
    std::cout << "Enter Rental Price per item ($): ";
    std::cin >> price;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Equipment (equipment_name, total_quantity, rental_price) VALUES (?, ?, ?)"
        ));
        pstmt->setString(1, name);
        pstmt->setInt(2, quantity);
        pstmt->setDouble(3, price);
        pstmt->execute();

        std::cout << "\nSuccess! Equipment '" << name << "' added to inventory.\n";
    } catch (sql::SQLException &e) {
        std::cout << "Error adding equipment: " << e.what() << std::endl;
    }
}

void Equipment::viewAllEquipment() {
    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM Equipment"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- EQUIPMENT INVENTORY ---\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" 
                  << std::setw(15) << "Quantity" << "Price ($)\n";
        std::cout << "---------------------------------------------------------\n";

        while (res->next()) {
            std::cout << std::left << std::setw(5) << res->getInt("equipment_id")
                      << std::setw(25) << res->getString("equipment_name")
                      << std::setw(15) << res->getInt("total_quantity")
                      << std::fixed << std::setprecision(2) << res->getDouble("rental_price") << "\n";
        }
    } catch (sql::SQLException &e) {
        std::cout << "Error fetching equipment: " << e.what() << std::endl;
    }
}