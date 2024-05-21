# Server-Client Network

In this project, we implemented a "Course Registration System" with a server and client architecture. The communication between the server and the clients was performed using a binary communication protocol.

## Communication Protocol

The messages in this protocol are binary numbers, composed of an opcode (a short number of two bytes) indicating the command and the data needed for this command (of various lengths). Messages are identified by a predefined message length.

## Client-Server Connection

### Client Side

The client side was implemented in C++ and involved the following steps:
- Establishing a connection with the server.
- Registering a new user with a username and password, or logging in as an existing user.
- Sending commands to the server, which were encoded and sent via a connection handler.
- Waiting for responses from the server, which could be acknowledgment messages or error messages.

The client utilized two threads:
1. One thread for reading commands from the user.
2. Another thread for reading responses from the server.

### Server Side

The server side was implemented in Java and supported two models:
1. **Thread-Per-Client (TPC)**: Each client connection is handled by a dedicated thread.
2. **Reactor**: A fixed-size thread pool handles client connections using a selector for non-blocking I/O operations.

The server could run in either TCP or Reactor mode. On startup, the server initializes the database, creates an encoder/decoder, and starts the main thread.

#### Server Implementation Details:

- **TPC Mode**:
  - Defines a server socket.
  - Opens a new socket for each client request, creating a new connection handler.
  - The connection handler runs as a thread, decoding messages received on the socket, processing them, and returning responses to the client.
  - The protocol interacts with the database to execute commands.

- **Reactor Mode**:
  - Creates a fixed-size thread pool.
  - Opens a selector socket.
  - Queues client requests and processes them when a thread becomes available.

## Database

The system includes a thread-safe singleton database containing:
- Regular users and administrators.
- Courses, each with prerequisite courses.
- Student records.

## User Classes

- **Abstract User Class**: Contains fields for the name, password, and login status.
- **Student**: Inherits from the User class.
- **Admin**: Inherits from the User class.

## Purpose

The purpose of this project was to practice implementing network communication and concurrency using Java and C++. This project required a strong understanding of threading, synchronization, and network protocols.

