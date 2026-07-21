// main.cpp
// Author: Kamal K. | Roll No: ce24btech11030
#include "Database.h"
#include "Venue.h"
#include "Vendor.h"
#include "Equipment.h"
#include "Staff.h"
#include "BudgetCalculator.h"
#include "Event.h"
#include <iostream>
#include <limits>

int main() {
    std::cout << "Booting Event Management System...\n";
    Database::getInstance()->initializeTables();

    int choice = 0;
    while (choice != 13) {
        std::cout << "\n=== MASTER MENU ===\n";
        std::cout << "1. Create Event\n";
        std::cout << "2. View Events\n";
        std::cout << "6. Venue Management\n";
        std::cout << "7. Vendor Management\n";
        std::cout << "8. Equipment Management\n";
        std::cout << "9. Staff Management\n";
        std::cout << "11. Legacy Budget Calculator\n";
        std::cout << "13. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: 
                Event::createEvent();
                break;
            case 2:
                Event::viewAllEvents();
                break;
            case 6: {
                int sub = 0; std::cout << "\n1. Add Venue\n2. View Venues\nSelect: "; std::cin >> sub;
                if (sub == 1) Venue::addVenue(); else if (sub == 2) Venue::viewAllVenues();
                break;
            }
            case 7: {
                int sub = 0; std::cout << "\n1. Add Vendor\n2. View Vendors\nSelect: "; std::cin >> sub;
                if (sub == 1) Vendor::addVendor(); else if (sub == 2) Vendor::viewAllVendors();
                break;
            }
            case 8: {
                int sub = 0; std::cout << "\n1. Add Equipment\n2. View Equipment\nSelect: "; std::cin >> sub;
                if (sub == 1) Equipment::addEquipment(); else if (sub == 2) Equipment::viewAllEquipment();
                break;
            }
            case 9: {
                int sub = 0; std::cout << "\n1. Add Staff\n2. View Staff\nSelect: "; std::cin >> sub;
                if (sub == 1) Staff::addStaff(); else if (sub == 2) Staff::viewAllStaff();
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