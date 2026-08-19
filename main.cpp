#include "crow.h"
#include "Database.h"
#include <fstream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

int main() {
    // 1. Boot up the Crow Web App
    crow::SimpleApp app;

    // 2. Initialize your database just like before!
    Database* db = Database::getInstance();
    std::cout << "Database connection ready for web traffic!" << std::endl;
    // --- HOME PAGE (FRONTEND) ---
    CROW_ROUTE(app, "/")([](){
        std::ifstream file("index.html");
        std::string html((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        
        crow::response res(html);
        res.set_header("Content-Type", "text/html");
        return res;
    });
    // --- SERVE CSS FILE ---
    CROW_ROUTE(app, "/style.css")([](){
        std::ifstream file("style.css");
        std::string css((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        crow::response res(css);
        res.set_header("Content-Type", "text/css"); // Tell the browser this is CSS
        return res;
    });

    // --- SERVE JAVASCRIPT FILE ---
    CROW_ROUTE(app, "/script.js")([](){
        std::ifstream file("script.js");
        std::string js((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        crow::response res(js);
        res.set_header("Content-Type", "application/javascript"); // Tell the browser this is JS
        return res;
    });

    // --- YOUR FIRST WEB ROUTE (API ENDPOINT) ---
    // When the browser goes to /api/status, it runs this code!
    CROW_ROUTE(app, "/api/status")([](){
        // Create a JSON response to send to the browser
        crow::json::wvalue response;
        response["status"] = "success";
        response["message"] = "The Event Management API is online!";
        return response;
    });

    // --- GET ALL EVENTS (READ) ---
    CROW_ROUTE(app, "/api/events")([db](){
        crow::json::wvalue response;
        try {
            sql::Connection* conn = db->getConnection();
            std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
                "SELECT event_id, event_name, event_date FROM Events"
            ));
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            int i = 0;
            while (res->next()) {
                response[i]["id"] = res->getInt("event_id");
                response[i]["name"] = res->getString("event_name");
                response[i]["date"] = res->getString("event_date");
                i++;
            }
        } catch (sql::SQLException &e) {
            response["error"] = e.what();
        }
        return response;
    });

    // ==========================================
    // 2. VENUES API
    // ==========================================
    
    // GET: Read all Venues
    CROW_ROUTE(app, "/api/venues")([db](){
        crow::json::wvalue response;
        try {
            sql::Connection* conn = db->getConnection();
            // NOTE: Change these column names if your MySQL table uses different ones!
            std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
                "SELECT venue_id, venue_name, capacity FROM Venues"
            ));
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            int i = 0;
            while (res->next()) {
                response[i]["id"] = res->getInt("venue_id");
                response[i]["name"] = res->getString("venue_name");
                response[i]["capacity"] = res->getInt("capacity");
                i++;
            }
        } catch (sql::SQLException &e) {
            response["error"] = e.what();
        }
        return response;
    });

    // POST: Create a new Venue
    CROW_ROUTE(app, "/api/venues").methods("POST"_method)([db](const crow::request& req){
        try {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400, "Invalid JSON");
            
            std::string name = body["venueName"].s();
            int capacity = body["venueCapacity"].i(); // Use .i() for numbers!
            
            sql::Connection* conn = db->getConnection();
            std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
                "INSERT INTO Venues (venue_name, capacity) VALUES (?, ?)"
            ));
            pstmt->setString(1, name);
            pstmt->setInt(2, capacity);
            pstmt->executeUpdate();
            
            return crow::response(200, "Venue Created!");
        } catch (std::exception &e) {
            return crow::response(500, e.what());
        }
    });

    // 3. Start the server on port 8080!
    app.port(8080).multithreaded().run();

    return 0;
}