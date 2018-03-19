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

### Testing:
System - the system class, make a system object to start a node of the blockchain. Client.cpp does this automatically

request(string from, string flag) - from is who you are requesting the file from, flag only has one flag ("file") for network transfer, if testing coin transfer within the chain, 

join(string usr) - usr is your node's username. if a config file exists with a username established, you cannot re-join.

getInfo() - returns your username and how many coins you have

share(string file) - opens a file up for sharing, if it's not in the directory that client or gen is in, the value needs to be a filepath

unshare(string file) - removes a file from sharing

For a node testing example, look at coins.cpp.

### Usage:
Editing coins.cpp can be used as a basic simulation of multiple nodes having access to the same blockchain and updating its state, with valid transactions passing coins around.

client.cpp is the blockchain client, server.py needs to be running on a sharing system before files can be requested by the client from the server. This doesn't transfer the chain data between nodes, but does limit a requester based on the number of coins they have, as well as allows them to share more files to gain more coins. The server.py on the side of the sharer will allow for those files to be requested as they are opened up for sharing.

### What this does right now :
Currently, this can send coins between nodes (all created within the same directory) and check if the users have enough coins to complete the transaction. Over the network, files can be exchanged, and the coins will determine whether a user can keep requesting. However, over the network, if there are two separate chains, the transaction will only be written on the requester's and not the sender's. 
