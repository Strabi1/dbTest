#include <cpprest/http_listener.h>
#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void handle_request(http_request request) {
    request.reply(status_codes::OK, "Csaaa");
}

int main() {
    http_listener listener("http://0.0.0.0:8080/api");
    listener.support(methods::GET, handle_request);

    try {
        listener.open().then([]() { std::wcout << L"Server is running...\n"; }).wait();
    } catch (const std::exception &e) {
        std::wcout << L"An error occurred: " << e.what() << std::endl;
    }

    std::string line;
    std::getline(std::cin, line);
}