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
