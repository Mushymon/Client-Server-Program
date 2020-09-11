# Client-Server
Client Server is a Windows command line program written in C++ that has a client server pair that can send and receive messages through a network. It is required that the remote computer and the local computer be connected on the same network if run on multiple computers.

# How to use
1. Open a CMD window in the executables folder on the remote computer and run "server.exe".
2. Open a CMD window in the executables folder on the local computer and type in "client.exe XXXX" where XXXX is the IP address of the remote computer (IP address can be found by entering "ipconfig" into CMD window).
3. In the case these are run on the same computer, you can type in "client.exe localhost" in Step 2 instead.

# When in use
You may send as many messages as desired to the server. If you send a message greater than 200 characters (the limit I set), it will separate that into multiple messages. Send "shutdown" as a message and both the server and client will close.
