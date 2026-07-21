#include "Vendor.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

void Vendor::addVendor() {
    std::string name, type;
    double price;

    std::cout << "\nEnter Vendor Name (e.g., Royal Catering): ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter Vendor Type (e.g., Catering, Photography, Sound): ";
    std::getline(std::cin >> std::ws, type);
    std::cout << "Enter Price ($): ";
    std::cin >> price;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Vendors (vendor_name, vendor_type, price) VALUES (?, ?, ?)"
        ));
        pstmt->setString(1, name);
        pstmt->setString(2, type);
        pstmt->setDouble(3, price);
        pstmt->execute();

        std::cout << "\nSuccess! Vendor '" << name << "' added.\n";
    } catch (sql::SQLException &e) {
        std::cout << "Error adding vendor: " << e.what() << std::endl;
    }
}

void Vendor::viewAllVendors() {
    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM Vendors"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- REGISTERED VENDORS ---\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" 
                  << std::setw(20) << "Type" << "Price ($)\n";
        std::cout << "------------------------------------------------------------\n";

        while (res->next()) {
            std::cout << std::left << std::setw(5) << res->getInt("vendor_id")
                      << std::setw(25) << res->getString("vendor_name")
                      << std::setw(20) << res->getString("vendor_type")
                      << std::fixed << std::setprecision(2) << res->getDouble("price") << "\n";
        }
    } catch (sql::SQLException &e) {
        std::cout << "Error fetching vendors: " << e.what() << std::endl;
    }
}