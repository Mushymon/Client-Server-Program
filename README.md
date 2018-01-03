# Client-Server-Program
Includes a server program that waits for messages from the client and a client that sends user input to the server. Client can send messages through a network to another computer with the server open on the remote computer and client open on the local computer.

This command line program is written in C and the source code is included in the folders: Socket_multi_client, Socket_multi_server, User_Input_Client

How to use: Open 2 separate command prompts and navigate inside the Client-Server folder. In one CMD window run "Socket_multi_server.exe", then in the other CMD window run "User_Input_Client.exe XXXX", where XXXX is the IP address. (IP address can be found with entering "ipconfig" into CMD window; If you are running on the same computer, can type in "localhost" as the IP address).

When in use: You can send as many messages as you want to the server. If you send a message greater than 100 characters (the limit I set), it will separate that into multiple messages. Send "shutdown" and both the server and client will close.
