# Multi-Threaded Graph Path Finder 🌐🔍

Welcome to the Multi-Threaded Graph Path Finder project! This repository contains a C++ application that implements a server-client architecture to handle multiple requests for finding the shortest path in an undirected graph.

## Features 🌟

- **Multi-threading**: Utilizes multi-threading to handle multiple client connections simultaneously.
- **Shortest Path Calculation**: Implements the Breadth-First Search (BFS) algorithm to determine the shortest path between two nodes in the graph.
- **Efficient Path Retrieval**: Caches up to 10 recent path requests to quickly serve repeated queries without recalculating.
- **Robust Server-Client Communication**: Uses TCP/IP sockets for reliable data transfer.

## Getting Started 🚀

Follow these instructions to get the project up and running on your local machine for development and testing purposes.

### Prerequisites

- GCC Compiler
- Linux Operating System

### Installing

1. **Clone the repository**

```bash
git clone https://your-repository-link-here.git
```
Compile the source code
Navigate to the project directory and run:

bash
Copy code
```
g++ -pthread server.cpp -o server
g++ client.cpp -o client
```
Usage
Run the server:

bash
Copy code
```
./server <graph_file_path> <port_number>
```
Run the client:

bash
```Copy code
./client <server_ip> <port_number> <start_vertex> <end_vertex>
```
Contributing 🤝
Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

Fork the Project
Create your Feature Branch (git checkout -b feature/AmazingFeature)
Commit your Changes (git commit -m 'Add some AmazingFeature')
Push to the Branch (git push origin feature/AmazingFeature)
Open a Pull Request

Contact 📧
Lidor Pahima - lidorpa@ac.sce.ac.il

