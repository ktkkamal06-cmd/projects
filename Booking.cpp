#include "Booking.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <iostream>

void Booking::bookVendor() {
    int eventId, vendorId;
    std::cout << "\n--- BOOK A VENDOR ---\n";
    std::cout << "Enter Event ID: "; std::cin >> eventId;
    std::cout << "Enter Vendor ID: "; std::cin >> vendorId;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO EventVendors (event_id, vendor_id) VALUES (?, ?)"
        ));
        pstmt->setInt(1, eventId);
        pstmt->setInt(2, vendorId);
        pstmt->execute();
        std::cout << "\nSuccess! Vendor ID " << vendorId << " booked for Event ID " << eventId << ".\n";
    } catch (sql::SQLException &e) {
        std::cout << "Error: " << e.what() << "\n(Hint: Check if those IDs actually exist!)\n";
    }
}

void Booking::bookEquipment() {
    int eventId, equipId, qty;
    std::cout << "\n--- BOOK EQUIPMENT ---\n";
    std::cout << "Enter Event ID: "; std::cin >> eventId;
    std::cout << "Enter Equipment ID: "; std::cin >> equipId;
    std::cout << "Enter Quantity to Book: "; std::cin >> qty;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();

        // --- PHASE 3: SMART ALGORITHM (INVENTORY VALIDATION) ---
        // 1. Ask the database how many we actually own
        std::unique_ptr<sql::PreparedStatement> checkStmt(conn->prepareStatement(
            "SELECT total_quantity FROM Equipment WHERE equipment_id = ?"
        ));
        checkStmt->setInt(1, equipId);
        std::unique_ptr<sql::ResultSet> res(checkStmt->executeQuery());

        // 2. Check the math
        if (res->next()) {
            int totalAvailable = res->getInt("total_quantity");
            if (qty > totalAvailable) {
                // The algorithm caught a mistake! Block the booking.
                std::cout << "\n[!] ERROR: Insufficient inventory! You requested " << qty 
                          << ", but only " << totalAvailable << " are available in the warehouse.\n";
                return; // This kicks them out of the function before the booking happens
            }
        } else {
            std::cout << "\n[!] ERROR: Equipment ID " << equipId << " does not exist!\n";
            return;
        }
        // -------------------------------------------------------

        // 3. If the code makes it here, the algorithm approved the booking!
        std::unique_ptr<sql::PreparedStatement> insertStmt(conn->prepareStatement(
            "INSERT INTO EventEquipment (event_id, equipment_id, quantity) VALUES (?, ?, ?)"
        ));
        insertStmt->setInt(1, eventId);
        insertStmt->setInt(2, equipId);
        insertStmt->setInt(3, qty);
        insertStmt->execute();
        
        std::cout << "\nSuccess! " << qty << " units of Equipment ID " << equipId 
                  << " booked for Event ID " << eventId << ".\n";
                  
    } catch (sql::SQLException &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Booking::assignStaff() {
    int eventId, staffId;
    std::cout << "\n--- ASSIGN STAFF ---\n";
    std::cout << "Enter Event ID: "; std::cin >> eventId;
    std::cout << "Enter Staff ID: "; std::cin >> staffId;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO EventStaff (event_id, staff_id) VALUES (?, ?)"
        ));
        pstmt->setInt(1, eventId);
        pstmt->setInt(2, staffId);
        pstmt->execute();
        std::cout << "\nSuccess! Staff ID " << staffId << " assigned to Event ID " << eventId << ".\n";
    } catch (sql::SQLException &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}