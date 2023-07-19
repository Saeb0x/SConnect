#include "Server.h"

namespace SConnect {

    // Constructor implementation
    ChatServer::ChatServer(asio::io_context& io_context, const std::string& listen_port)
        : m_ioContext(io_context), m_acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), std::stoi(listen_port))) {
        log("Server started. Listening on port: " + listen_port);
        StartAccept();
    }

    void ChatServer::StartAccept() {
        std::shared_ptr<ChatClient> new_client = std::make_shared<ChatClient>(m_ioContext, "", "");
        m_acceptor.async_accept(new_client->GetSocket(), [this, new_client](const asio::error_code& ec) {
            if (!ec) {
                m_clients.push_back(new_client);
                log("New client is connected.Total clients : " + std::to_string(m_clients.size()));
                new_client->Receive(); // Start receiving messages from the client
            }
            StartAccept(); // Accept the next client connection
            });
    }


    void ChatServer::HandleAccept(std::shared_ptr<ChatClient> client, const asio::error_code& error) {
        // This function can be left empty for now, updates to the framework will take place later!
    }

    void ChatServer::HandleClientMessage(std::shared_ptr<ChatClient> client, const ChatMessage& message) {
        // Broadcast the message to all connected clients
        for (const auto& other_client : m_clients) {
            if (other_client != client) {
                other_client->Send(message);
            }
        }
    }
}