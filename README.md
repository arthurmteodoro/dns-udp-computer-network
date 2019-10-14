# dns-udp-computer-network
Simple DNS implementation using sockets UDP

## How to run

Follow this steps to execute code:

### Server
In server folder, execute:
`make clean`, to clear previous compilations.
Run `make` to compile server and execute using `./server.out

### Client

In client folder, execute:
`make clean`, to clear previous compilations.
Run `make` to compile client.

If you want to query the server to translate a name for an IP, use: `./client.out 1 <name_to_translate>`.
If you already want to save a name and IP pair on the server, use: `./client.out 2 <name> <IP>`.

For more details, run `./client.out -h` to show client help.
