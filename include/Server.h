#pragma once

#include "Client.h"

namespace SConnect {

    class ChatServer {
    public:
        ChatServer(asio::io_context& io_context, const std::string& listen_port);

        // Starts accepting client connections asynchronously.
        void StartAccept();

        // Handles a newly accepted client connection.
        void HandleAccept(std::shared_ptr<ChatClient> client, const asio::error_code& error);

        // Handles an incoming message from a client.
        void HandleClientMessage(std::shared_ptr<ChatClient> client, const ChatMessage& message);

    private:
        asio::io_context& m_ioContext;
        asio::ip::tcp::acceptor m_acceptor;
        std::vector<std::shared_ptr<ChatClient>> m_clients;

        void log(const std::string& message) const {
            std::cout << "[ChatServer] " << message << std::endl;
        }
    };

}