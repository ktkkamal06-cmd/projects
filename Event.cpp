// Event.cpp
// Author: Kamal K. | Roll No: ce24btech11030
#include "Event.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

void Event::createEvent() {
    std::string name, date, time;
    int venueId, capacity;
    double budgetLimit;

    std::cout << "\n--- CREATE NEW EVENT ---\n";
    std::cout << "Enter Event Name (e.g., Tech Hackathon): ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Enter Event Date (YYYY-MM-DD): ";
    std::getline(std::cin >> std::ws, date);
    std::cout << "Enter Event Time (HH:MM): ";
    std::getline(std::cin >> std::ws, time);
    
    std::cout << "Enter Venue ID (Must exist in Venue Management!): ";
    std::cin >> venueId;
    std::cout << "Enter Expected Capacity: ";
    std::cin >> capacity;
    std::cout << "Enter Strict Budget Limit ($): ";
    std::cin >> budgetLimit;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO Events (event_name, event_date, event_time, venue_id, expected_capacity, budget_limit) "
            "VALUES (?, ?, ?, ?, ?, ?)"
        ));
        pstmt->setString(1, name);
        pstmt->setString(2, date);
        pstmt->setString(3, time);
        pstmt->setInt(4, venueId);
        pstmt->setInt(5, capacity);
        pstmt->setDouble(6, budgetLimit);
        pstmt->execute();

        std::cout << "\nSuccess! Event '" << name << "' created and linked to Venue ID " << venueId << ".\n";
    } catch (sql::SQLException &e) {
        // If you enter a Venue ID that doesn't exist, MySQL's foreign key will block it and throw an error here!
        std::cout << "\nERROR: Could not create event. " << e.what() << std::endl;
        std::cout << "(Hint: Did you enter a Venue ID that hasn't been created yet?)\n";
    }
}

void Event::viewAllEvents() {
    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        // We use a JOIN to automatically fetch the Venue's actual name using the linked ID!
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "SELECT e.event_id, e.event_name, e.event_date, v.venue_name, e.budget_limit "
            "FROM Events e JOIN Venues v ON e.venue_id = v.venue_id"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- MASTER EVENT SCHEDULE ---\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Event Name" 
                  << std::setw(15) << "Date" << std::setw(25) << "Venue Location" << "Budget Limit\n";
        std::cout << "--------------------------------------------------------------------------------\n";

        while (res->next()) {
            std::cout << std::left << std::setw(5) << res->getInt("event_id")
                      << std::setw(25) << res->getString("event_name")
                      << std::setw(15) << res->getString("event_date")
                      << std::setw(25) << res->getString("venue_name")
                      << "$" << std::fixed << std::setprecision(2) << res->getDouble("budget_limit") << "\n";
        }
    } catch (sql::SQLException &e) {
        std::cout << "Error fetching events: " << e.what() << std::endl;
    }
}