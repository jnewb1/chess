# chess

A simple chess engine and chess-ai built in C++ and including a web interface.
Features:
- Possible move generation given a board input
- Web Interface for viewing AI games or playing against an AI
- Object Oriented programming for flexibility of new player types or updates to the engine
Specifics:
- Web Interface is built around Mongoose, a C library for network communications.
- A custom C++ interface for Mongoose was developed for specific applications,
like the HTTP Server and the WebSocket Server
- View live games and control their state (play, pause, step one move...)