#include "Analytics.h"
#include "Database.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include <iomanip>

void Analytics::recordRevenue() {
    int eventId;
    double revenue;

    std::cout << "\n--- RECORD EVENT REVENUE ---\n";
    std::cout << "Enter Event ID: "; 
    std::cin >> eventId;
    std::cout << "Enter Total Revenue Earned (Ticket Sales, etc) ($): "; 
    std::cin >> revenue;

    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        
        // We calculate Profit directly inside the SQL command! (Profit = Revenue - Budget Limit)
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "UPDATE Events SET revenue = ?, profit = (? - budget_limit) WHERE event_id = ?"
        ));
        pstmt->setDouble(1, revenue);
        pstmt->setDouble(2, revenue);
        pstmt->setInt(3, eventId);
        
        // executeUpdate() returns the number of rows changed. If it's 0, the ID didn't exist!
        int rowsUpdated = pstmt->executeUpdate();
        
        if (rowsUpdated > 0) {
            std::cout << "\nSuccess! Revenue and Profit metrics updated for Event ID " << eventId << ".\n";
        } else {
            std::cout << "\n[!] ERROR: Could not find Event ID " << eventId << ".\n";
        }

    } catch (sql::SQLException &e) {
        std::cout << "Error updating revenue: " << e.what() << std::endl;
    }
}

void Analytics::generateFinancialReport() {
    try {
        sql::Connection* conn = Database::getInstance()->getConnection();
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "SELECT event_id, event_name, budget_limit, revenue, profit FROM Events"
        ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n======================== FINANCIAL DASHBOARD ========================\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(25) << "Event Name" 
                  << std::setw(15) << "Budget" << std::setw(15) << "Revenue" << "Net Profit\n";
        std::cout << "---------------------------------------------------------------------\n";

        double totalSystemProfit = 0;

        while (res->next()) {
            double profit = res->getDouble("profit");
            totalSystemProfit += profit;

            std::cout << std::left << std::setw(5) << res->getInt("event_id")
                      << std::setw(25) << res->getString("event_name")
                      << "$" << std::setw(14) << std::fixed << std::setprecision(2) << res->getDouble("budget_limit")
                      << "$" << std::setw(14) << res->getDouble("revenue")
                      << "$" << profit << "\n";
        }
        
        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "TOTAL SYSTEM NET PROFIT: $" << totalSystemProfit << "\n";
        std::cout << "=====================================================================\n";

    } catch (sql::SQLException &e) {
        std::cout << "Error fetching report: " << e.what() << std::endl;
    }
}