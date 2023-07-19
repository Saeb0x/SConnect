#include "Client.h"

int main() {
    try {
        asio::io_context io_context;
        SConnect::ChatClient client(io_context, "localhost", "12345");
        client.Connect();

        // Send a message to the server
        std::string message_text;
        while (true) {
            std::cout << "Send a message (type exit to terminate): ";
            std::getline(std::cin, message_text); // Read user input from the console

            // Check if the user wants to exit
            if (message_text == "exit") {
                break;
            }

            // Send the message to the server
            SConnect::ChatMessage message;
            message.body = message_text;
            client.Send(message);
        }
        io_context.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Client exception: " << e.what() << std::endl;
    }
    return 0;
}