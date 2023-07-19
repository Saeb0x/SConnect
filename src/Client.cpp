#include "Client.h"

namespace SConnect {

    // Constructor implementation
    ChatClient::ChatClient(asio::io_context& io_context, const std::string& server_address, const std::string& server_port)
        : m_ioContext(io_context), m_socket(io_context), m_resolver(io_context), m_serverAddress(server_address), m_serverPort(server_port) {
    }

    void ChatClient::Connect() {
        asio::ip::tcp::resolver::results_type endpoints = m_resolver.resolve(m_serverAddress, m_serverPort);
        asio::connect(m_socket, endpoints);
    }

    void ChatClient::Send(const ChatMessage& message) {
        // Prepare the serialized message
        std::vector<char> serialized_message;
        serialized_message.resize(sizeof(ChatMessage::Header) + message.body.size());

        // Copy the header into the serialized message
        ChatMessage::Header header;
        header.message_id = message.header.message_id;
        header.body_size = static_cast<uint32_t>(message.body.size());
        std::memcpy(serialized_message.data(), &header, sizeof(ChatMessage::Header));

        // Copy the body into the serialized message
        std::memcpy(serialized_message.data() + sizeof(ChatMessage::Header), message.body.data(), message.body.size());

        // Send the serialized message over the socket
        asio::write(m_socket, asio::buffer(serialized_message));
    }

    void ChatClient::Receive() {
        m_receiveBuffer.resize(sizeof(ChatMessage::Header)); // Reserve space for the message header
        asio::async_read(m_socket, asio::buffer(m_receiveBuffer),
            [this](const asio::error_code& ec, std::size_t bytes_received) {
                if (!ec) {
                    // Extract the header from the receive buffer
                    ChatMessage::Header header;
                    std::memcpy(&header, m_receiveBuffer.data(), sizeof(ChatMessage::Header));

                    // Resize the buffer to fit the entire message
                    m_receiveBuffer.resize(sizeof(ChatMessage::Header) + header.body_size);

                    // Asynchronously read the rest of the message (body)
                    asio::async_read(m_socket, asio::buffer(m_receiveBuffer.data() + sizeof(ChatMessage::Header), header.body_size),
                        [this, header](const asio::error_code& inner_ec, std::size_t bytes_received) {
                            if (!inner_ec) {
                                // Create a ChatMessage object from the received data
                                ChatMessage received_message;
                                received_message.header = header;
                                received_message.body.assign(m_receiveBuffer.begin() + sizeof(ChatMessage::Header), m_receiveBuffer.end());

                                // Handle the incoming message
                                HandleIncomingMessage(received_message);

                                // Continue receiving more messages
                                Receive();
                            }
                        });
                }
            });
    }

    void ChatClient::HandleIncomingMessage(const ChatMessage& message) {
        std::cout << "Received: " << message.body << std::endl;
    }

}