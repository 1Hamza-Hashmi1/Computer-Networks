8 TCP packets generated when  packets are exchanged between the client and the server. They are as follows:
TCP Three-Way Handshake:
Packet 1 (SYN): The client sends a SYN (synchronize) packet to the server to initiate the connection.
Packet 2 (SYN-ACK): The server responds with a SYN-ACK (synchronize-acknowledgment) packet to acknowledge the client's request.
Packet 3 (ACK): The client sends an ACK packet to complete the handshake and establish the connection.

Data Transfer:
Packet 4: The client sends the application-level Echo request to the server.
Packet 5: The server responds with the Echo reply message back to the client.

TCP Connection Termination (Four-Way Termination):
Packet 6 (FIN): The client sends a FIN (finish) packet to signal the end of the connection.
Packet 7 (FIN-ACK): The server responds with an ACK packet and a FIN to acknowledge the termination.
Packet 8 (ACK): The client responds with a final ACK to complete the termination.


Extra: Packet goes through all the layers in this project except the Presentation layer.
