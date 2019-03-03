# ASIO

## General info
This project contains a boost asio example of client and server communicating with each other.
Inspired by the chat boost example:
	https://www.boost.org/doc/libs/1_69_0/doc/html/boost_asio/examples/cpp11_examples.html#boost_asio.examples.cpp11_examples.chat

Client(s) send text messages to the Server and the Server replies with some status messages.	
To see how it works, run server first, then client(s) from /bin directory.
Two bat files are there for a sample server and client run.
You can run several clients in the same time.
Server replies with OK on the "Hello world" request and with "Not OK" on any other request.
The messages sent by the client are read from the std input.

##Build
Both projects /client/asio_client.pro and /server/asio_server.pro are Qt windows based. To compile it, install and build BOOST.
The locations are "C:\boost\boost_1_69_0" for include and "C:\boost\boost_1_69_0\stage\lib" for libs.
Change the common/common.pri file if you have different instalation.
Ensure -lws2_32 -lwsock32 are accesible on your system.
The code was tested with MinGW only

##Code
The project is separated in 3 parts:
	- common
	- server
	- client
	
	Common subproject contains the Message and Session classes used and implemented both by the client and server paries.
	
	The Message class represent the communication message consisting of the header and body.
	To implement custom messages, use the body as the place for a custom protocol. I.e. extend by "has-a".
	
	The Session class uses the asio facilities to write and read messages. It is an abstract class intended to be
	extended to implement custom behavior. In this project two sample Sessions are implemented: ClientSession and ServerSession
	
	Server subprojects contains the ServerSession class with the custom server session implementation, Server class, that handles multiple sessions
	and accepts the connections from remote parties, and the main() entry point for the server.
	
	Client subprojects contains the ClientSession class with the custom client session implementation, Client class, that handles the underlying session
	and connects to the remote server, and the main() entry point for the client with read the messages from the console.
	
	See more comments in the classes.