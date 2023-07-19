# SConnect
A portable, Asio-powered Framework for general purpose client/server applications with emphasis on chat applications, while also remaining open to future enhancements that may extend its capabilities to support other types of client/server applications.

## Architecture
At the heart of the framework lies a message-based communication model. All data transactions within the framework are encapsulated into messages, each comprising a header that includes an identifier (ID) and size (in bytes), along with a variable-sized body. The header ensures structured communication, allowing the framework to process messages efficiently. The framework consists of several key components that work together to facilitate efficient and structured communication between clients and the server. Below, I present the SConnect framework’s architecture.

1. #### ChatClient (Client-side):
  * ChatClient component represents the client-side of the application.
  * Handles interactions with the server and other clients.
  * Connects to the server and sends/receives chat messages.
  * Encapsulates and formats data into messages for communication.
2.  #### ChatServer (Server-side):
  * ChatServer component represents the server-side of the application.
  * Manages incoming client connections and maintains multiple client sessions concurrently.
  * Connects to the server and sends/receives chat messages.
  * Handles client messages and broadcasts them to all connected clients in real-time.

To achieve data transmission, the SConnect framework leverages the processes of serialization and deserialization. During serialization, the message’s header and body are converted into a linear stream of bytes, also known as a “byte stream.” This byte stream represents a compact and platform-independent representation of the message, making it suitable for transmission over a network or storage in a file. Upon receipt of the byte stream, deserialization comes into play. The deserialization process involves extracting the necessary information from the byte stream and reconstructing the original message on the receiving end. By properly interpreting the byte stream, the recipient can recreate the original message structure, including its header and body, in its entirety.

If you're interested in more details, check out my [blog](https://saebnaser.com/), where I provide a thorough breakdown of the framework's inner workings and its advantages.

## In Action
Chech the [video](https://saebnaser.com/post/nwcppthree/) at the end of the blog post.

![sConnectTest](https://github.com/Saeb0x/SConnect/assets/56490771/1b0520fd-5d31-4ab4-b3ee-8fcd366b9f3d)

