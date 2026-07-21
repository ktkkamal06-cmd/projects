#include "Venue.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <limits>
#include <iomanip>

void Venue::addVenue() {
    std::string name;
    int capacity;
    double cost;

    std::cout << "\nEnter Venue Name (e.g., Main Auditorium): ";
    std::getline(std::cin >> std::ws, name);
    
    std::cout << "Enter Maximum Capacity: ";
    std::cin >> capacity;
    
    std::cout << "Enter Rental Cost ($): ";
    std::cin >> cost;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Venues (venue_name, max_capacity, rental_cost) VALUES (?, ?, ?)"
        ));
        pstmt->setString(1, name);
        pstmt->setInt(2, capacity);
        pstmt->setDouble(3, cost);
        pstmt->execute();

        std::cout << "\nSuccess! Venue '" << name << "' added to the system.\n";
    } catch (sql::SQLException &e) {
        std::cout << "Error adding venue: " << e.what() << std::endl;
    }
}

void Venue::viewAllVenues() {
    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM Venues"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- REGISTERED VENUES ---\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Name" 
                  << std::setw(15) << "Capacity" << std::setw(15) << "Cost ($)" << "Status\n";
        std::cout << "------------------------------------------------------------------\n";

        while (res->next()) {
            std::cout << std::left << std::setw(5) << res->getInt("venue_id")
                      << std::setw(25) << res->getString("venue_name")
                      << std::setw(15) << res->getInt("max_capacity")
                      << std::setw(15) << std::fixed << std::setprecision(2) << res->getDouble("rental_cost")
                      << (res->getBoolean("is_available") ? "Available" : "Booked") << "\n";
        }
    } catch (sql::SQLException &e) {
        std::cout << "Error fetching venues: " << e.what() << std::endl;
    }
}