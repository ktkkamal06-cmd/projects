// main.cpp
// Author: G. Akhil | Roll No: ce24btech11026
#include "Database.h"
#include "Venue.h"
#include "BudgetCalculator.h"
#include <iostream>
#include <limits>



int main() {
    std::cout << "Booting Event Management System...\n";
    Database::getInstance()->initializeTables();

    int choice = 0;
    while (choice != 13) {
        std::cout << "\n=== MASTER MENU ===\n";
        std::cout << "6. Venue Management\n";
        std::cout << "11. Legacy Budget Calculator\n";
        std::cout << "13. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 6: {
                int venueChoice = 0;
                std::cout << "\n-- Venue Management --\n1. Add Venue\n2. View Venues\nSelect: ";
                std::cin >> venueChoice;
                if (venueChoice == 1) Venue::addVenue();
                else if (venueChoice == 2) Venue::viewAllVenues();
                break;
            }
            case 11:
                BudgetCalculator::runCalculator();
                break;
            case 13:
                std::cout << "Shutting down system...\n";
                break;
            default:
                std::cout << "Feature in development. Please select a valid option.\n";
        }
    }
    return 0;
}