cmake_minimum_required(VERSION 3.10)
project(EventLogistics)

# Find system threads
find_package(Threads REQUIRED)

# Tell CMake where the Crow files live
include_directories(${CMAKE_SOURCE_DIR}/Crow/include)

add_executable(myapp main.cpp Database.cpp venue.cpp BudgetCalculator.cpp Vendor.cpp Equipment.cpp Staff.cpp Event.cpp Booking.cpp Analytics.cpp)

# Link MySQL and Threads to your app
target_link_libraries(myapp mysqlcppconn Threads::Threads)