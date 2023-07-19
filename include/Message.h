#pragma once

#include <cstdint>
#include <string>

namespace SConnect {

    // Message structure for the chat application
    struct ChatMessage {
        // Message header
        struct Header {
            uint32_t message_id; // Identifier for the type of message
            uint32_t body_size; // Size of the message body in bytes
        };

        Header header;
        std::string body;
    };

}
