# ft_irc

A non-blocking IRC server developed in C++ as a team project, focused on networking, event-driven I/O, and protocol handling.

> **Team project:** This repository is a personal case study documenting my contributions and engineering work.
> **Original repository:** [ft_irc](https://github.com/messkely/ft_irc)

## Build & Run

Clone the original project:

```bash
git clone <original-repository-url>
cd ft_irc
```

Build and start the server:

```bash
make
./ircserv <port> <password>
```

## Demo

The demo shows the server running with clients connected through **HexChat** and **netcat (`nc`)**.

[▶️ Watch the demo](./assets/demo.webm)

## Features

* Multiple simultaneous clients
* IRC authentication and registration
* Channel management and messaging
* Operator privileges and channel modes: `i`, `t`, `k`, `o`, `l`
* Core IRC commands: `PASS`, `NICK`, `USER`, `JOIN`, `PRIVMSG`, `KICK`, `INVITE`, `TOPIC`, `MODE`

## Architecture

Built around an event-driven architecture using `poll()` for non-blocking I/O.

The server manages client connections, command handling, channel state, and outgoing data through separate responsibilities.

## My Contribution

* Server socket and event loop
* Core class and responsibility design
* Authentication and IRC commands
* Resource ownership and lifecycle
* Testing and debugging

## Engineering Highlight

Initially, all client sockets were monitored for `POLLOUT`, causing unnecessary CPU activity because sockets are normally writable.

I changed the event loop to monitor `POLLOUT` only when a client has pending outgoing data.

## What I Learned

Developed a deeper understanding of TCP networking, event-driven I/O, protocol handling, and resource management beneath the socket API.

## Technologies

C++ · POSIX Sockets · `poll()` · TCP/IP
