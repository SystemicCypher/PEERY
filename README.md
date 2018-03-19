# PeerCoin
### A peer-to-peer file sharing/cryptocurrency framework built on a blockchain
PeerCoin will be a secure way to share data with others. The more peercoins you have, the more you can send and recieve.
Every file sharing operation requires coins to change hands, that is, if Alice wants a file Bob has, Alice has to have enough coins to
fund the transfer of files. As confirmation of the file's arrival, Bob recieves some coins. If several people in the network have the file, 
coins will be distributed to all who send a piece to the requester.
### To run:
Download the project and then navigate to the src folder in a terminal.
From there, type "make all"
Then run "./peerclient"

### What this does right now :
Currently, this can send data between nodes and check if the users have enough coins to complete the transaction. It still does not update the blockchain at both ends, just the receiver's. 
