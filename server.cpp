#include <cpprest/http_listener.h>
#include <cpprest/json.h>
// #include <mysql/mysql.h>
#include <mysql.h>
#include <iostream>
#include <string>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "food_db"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

json::value queryDatabase() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Kapcsolódás az adatbázishoz
    conn = mysql_init(NULL);
    if (!conn) {
        return json::value::string("MySQL initialization failed");
    }
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        return json::value::string("Database connection failed");
    }

    // SQL lekérdezés futtatása
    std::string query = "SELECT * FROM food";
    if (mysql_query(conn, query.c_str())) {
        mysql_close(conn);
        return json::value::string("Query execution failed");
    }

    res = mysql_store_result(conn);
    if (!res) {
        mysql_close(conn);
        return json::value::string("Failed to retrieve result");
    }

    json::value result;
    int index = 0;
    while ((row = mysql_fetch_row(res))) {
        result[index]["id"] = std::stoi(row[0]);
        // result[index]["name"] = row[1] ? row[1] : "";
        result[index]["calories"] = row[2] ? std::stoi(row[2]) : 0;
        result[index]["protein"] = row[3] ? std::stof(row[3]) : 0.0f;
        index++;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

// GET request handler
void handle_get(http_request request) {
    json::value response = queryDatabase();
    request.reply(status_codes::OK, response);
}

int main() {
    // HTTP listener beállítása
    http_listener listener("http://localhost:8080/api/foods");
    listener.support(methods::GET, handle_get);

    // Szerver indítása
    try {
        listener
            .open()
            .then([]() { std::wcout << L"Server is running...\n"; })
            .wait();
    } catch (const std::exception& e) {
        std::wcout << L"An error occurred: " << e.what() << std::endl;
    }

    // Várakozás a szerver leállításáig
    std::string line;
    std::getline(std::cin, line);
}
