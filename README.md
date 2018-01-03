# Client-Server-Program
Includes a server program that waits for messages from the client and a client that sends user input to the server.

This program is written in C and the source code is included in the folders: Socket_multi_client, Socket_multi_server, User_Input_Client

How to use: Navigate inside the Client-Server folder. Run Socket_multi_server.exe then run User_Input_Client.exe.

When in use: You can send as many messages as you want to the server. If you send a message greater than 100 characters (the limit I set), it will separate that into multiple messages. Send "shutdown" and both the server and client will close.
