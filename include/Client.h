#pragma once

#include "SConnect.h"
#include "Message.h"
#include <memory>

namespace SConnect {

    class ChatClient {
    public:
        ChatClient(asio::io_context& io_context, const std::string& server_address, const std::string& server_port);

        // Connects to the server.
        void Connect();

        // Sends a chat message to the server.
        void Send(const ChatMessage& message);

        // Starts asynchronously receiving messages from the server.
        void Receive();

        // Handles an incoming message from the server.
        void HandleIncomingMessage(const ChatMessage& message);

        // Returns the socket associated with the ChatClient.
        asio::ip::tcp::socket& GetSocket() {
            return m_socket;
        }

    private:
        asio::io_context& m_ioContext;
        asio::ip::tcp::socket m_socket;
        asio::ip::tcp::resolver m_resolver;
        std::string m_serverAddress;
        std::string m_serverPort;
        std::vector<char> m_receiveBuffer;

        void log(const std::string& message) const {
            std::cout << "[ChatClient] " << message << std::endl;
        }
    };
}