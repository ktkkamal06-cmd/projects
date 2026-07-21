#include "BudgetCalculator.h"
#include <iostream>
#include <limits>
#include <iomanip>

// The crash-proof helper function
double BudgetCalculator::getSafeDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0) { // Also prevents negative prices!
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a positive number.\n";
        } else {
            return value;
        }
    }
}

void BudgetCalculator::runCalculator() {
    std::cout << "\n=== ADVANCED BUDGET CALCULATOR ===\n";
    
    double budgetLimit = getSafeDouble("Enter your strict Budget Limit ($): ");
    
    std::cout << "\nEnter estimated costs for the following categories:\n";
    double hall = getSafeDouble("1. Hall Rental: $");
    double food = getSafeDouble("2. Food & Catering: $");
    double decoration = getSafeDouble("3. Decoration: $");
    double photography = getSafeDouble("4. Photography: $");
    double security = getSafeDouble("5. Security: $");
    double transport = getSafeDouble("6. Transport: $");
    double equipment = getSafeDouble("7. Equipment Rental: $");
    double misc = getSafeDouble("8. Miscellaneous: $");

    double totalCost = hall + food + decoration + photography + security + transport + equipment + misc;
    double difference = budgetLimit - totalCost;

    // Print the professional receipt
    std::cout << "\n--- BUDGET ESTIMATE RECEIPT ---\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(25) << "Budget Limit:" << "$" << budgetLimit << "\n";
    std::cout << "----------------------------------\n";
    std::cout << std::left << std::setw(25) << "Hall:" << "$" << hall << "\n";
    std::cout << std::left << std::setw(25) << "Food:" << "$" << food << "\n";
    std::cout << std::left << std::setw(25) << "Decoration:" << "$" << decoration << "\n";
    std::cout << std::left << std::setw(25) << "Photography:" << "$" << photography << "\n";
    std::cout << std::left << std::setw(25) << "Security:" << "$" << security << "\n";
    std::cout << std::left << std::setw(25) << "Transport:" << "$" << transport << "\n";
    std::cout << std::left << std::setw(25) << "Equipment:" << "$" << equipment << "\n";
    std::cout << std::left << std::setw(25) << "Miscellaneous:" << "$" << misc << "\n";
    std::cout << "----------------------------------\n";
    std::cout << std::left << std::setw(25) << "TOTAL ESTIMATED COST:" << "$" << totalCost << "\n";
    
    if (difference < 0) {
        std::cout << "\n*** WARNING: BUDGET EXCEEDED BY $" << (difference * -1) << " ***\n";
    } else {
        std::cout << "\nSUCCESS: You are $" << difference << " under budget!\n";
    }
}