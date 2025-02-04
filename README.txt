Solutions to questions:
1. The reliability of the UDP dropped significantly to around 50% packet drop rate, since there's no ACK or verification that a message reached, justa  checksum.

2. The reliability of TCP was uncompromised, albeit packets were delayed. This is due to the TCP handshake ensuring packets get sent eventually.

3. Slowed down as while using TCP, a packet may have needed to be sent multiple times to surpass packet loss, hence resulting in delays. 
