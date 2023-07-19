#include "Server.h"

int main() {
    try {
        asio::io_context io_context;
        SConnect::ChatServer server(io_context, "12345"); 
        io_context.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Server exception: " << e.what() << std::endl;
    }
    return 0;
}