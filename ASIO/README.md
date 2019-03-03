# ASIO example

## General info
This project contains a boost ASIO example of client and server communicating with each other.
Inspired by the chat boost example:
	https://www.boost.org/doc/libs/1_69_0/doc/html/boost_asio/examples/cpp11_examples.html#boost_asio.examples.cpp11_examples.chat

Client(s) send text messages to the Server and the Server replies with some status messages.	
To see how it works, run server first, then client(s) from /bin directory.
Two bat files are there for a sample server and client run.
You can run several clients in the same time.
Server replies with OK on the "Hello world" request and with "Not OK" on any other request.
The messages sent by the client are read from the std input.

## Build
Both projects /client/asio_client.pro and /server/asio_server.pro are Qt windows based. To compile it, install and build BOOST.
The locations are "C:\boost\boost_1_69_0" for include and "C:\boost\boost_1_69_0\stage\lib" for libs.
Change the common/common.pri file if you have different instalation.
Ensure -lws2_32 -lwsock32 are accesible on your system.
The code was tested with MinGW only

## Code
The project is separated in 3 parts: common, server and client
	
### Common	
Common subproject contains Message and Session classes that are used both by the client and server subprojects.

The Message class represents messages used in the communication. It consists of the "header" and the "body". The header holds the length of the body string and the body is the message content itself.
To incorporate in the code more advanced messages/protocols, use the "body" part of the message to implement it.
	
The Session class uses the asio facilities to write and read messages. It is an abstract class intended to be
extended to implement custom behavior. In this project two sample Sessions are implemented: ClientSession and ServerSession.
Custom session behavior is possible by extending and implementing the listed in the class handling functions.
	
### Server
Server subprojects contains the ServerSession class with the custom server session implementation, Server class, that handles multiple sessions and accepts the connections from remote parties, and the main() entry point for the server.
	
### Client 
Client subprojects contains the ClientSession class with the custom client session implementation, Client class, that handles the underlying session and connects to the remote server, and the main() entry point for the client with read the messages from the console.
