# Synchronization-Over-FTP
Networking Project

This is a project to synchronize the transfer of files between the client and server over the File Transfer Protocol using the SHA algorithm to create hashes of the present working directory and comparing them to find the files which are out of sync.

Steps-
 1. Create hash of the client directory using sha.c.
 2. Initialize the sockets and connect to the server using transferclient.c. Send the hashc.txt file created by sha.c to the server and wait for the server to respond.
 3. The server is already running and as soon as the client connects to it, the server which already has an updated version of  its hashs.txt (which is the hash of the server directory), compares the hash files of both client and the server and finds out the files of the server which are not present in the client or all the files which have been changed/modified/updated on the server but not on the client. The server then creates a sync.txt file which contains all files out of sync.
 4. The server then reads the sync.txt file and sends all the unsynced files to the client. Note that this is a one-way synchronization where the server is synchronized with the client and not the other way around. 
 5. The server and client then terminate the connection.
