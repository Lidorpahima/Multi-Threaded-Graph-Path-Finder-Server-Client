#include "std_lib_facilities.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
/**
 * Name:Lidor pahima
 * ID:206735961
 * This program is the server that storage the grpah and will find the shortest path using BFS algorithm
*/
typedef unordered_map<int, list<int>> Graph;//defining graph
//function to read the graph from the file
Graph ReadGraph(const string& filename) {
    Graph graph;//graph is a unordered map
    ifstream file(filename);//Name of the file
    string line;//line to read each line from the file

    while (getline(file, line)) {//reading the file line by line
        istringstream iss(line);//iss will used to read the line
        int vec1, vec2;//vec 1 is store the first value and vec2 is store the second value
        while (iss >> vec1 >> vec2) {//is reading the line first the vec1 than agnoring the space than reading the vec2
            graph[vec1].push_back(vec2);//pushing from vec1 to vec2
            graph[vec2].push_back(vec1); //pushing from vec2 to vec1 because its undirected graph
        }
    }

    return graph;
}
//using BFS algorithm to find the shortest path that asked from the user
vector<int> bfsShortPath(Graph& graph, int from, int to) {
    unordered_map<int, bool> visited;//checking the visited node
    unordered_map<int, int> prev;//checking the previous node
    queue<int> queue;//queue to store the node 
    vector<int> path;//vector to store the path from source to destination
   
    for (auto& node : graph) {//Set visited to false and prev to -1
        visited[node.first] = false;
        prev[node.first] = -1;
    }
    
    queue.push(from);//pushing the source node to the queue
    visited[from] = true;//setting the source node to visited

    while (!queue.empty()) {//loop until the queue is empty
        int node = queue.front();//taking the front node from the queue
        queue.pop();//poping the front noode

        if (node == to) { // if the node is equal to the destination so will for loop to rememeber the path
            for(int at = to; at != -1; at = prev[at]) {
                path.push_back(at);//pushing the path from destination to source backward because we know the destination found
                
            }
            reverse(path.begin(), path.end());//reversing the path to get the path from source to destination because the client want the path from source to destination
            return path;
        }
        for(int neighbor : graph[node]){//looping through the neighbors of the node
            if(!visited[neighbor]){//if the neighbor is not visited so will push it to the queue and set it to visited and set the previous node to the current node
                queue.push(neighbor);
                visited[neighbor] = true;
                prev[neighbor] = node;
            }
        }
        }
        
        return path;//returning the path null because the path is not found
}
deque<vector<int>> Searched;//will store the last 10 searched paths
vector<int> find(Graph& graph,int from,int to) {//function to find the path between the source and destination
    vector<int> path;
    for (auto& searched : Searched) {//looping through the searched paths
        if (searched.front() == from && searched.back() == to) {
            return searched;
        }
    }
    path = bfsShortPath(const_cast<Graph&>(graph), from, to);//not found so it mean we need to find the path
    if(Searched.size() >= 10) {//if the size of the searched paths is greater than 10 so will pop the first path and push the new path
        Searched.pop_front();
        Searched.push_back(path);
    }else{
    Searched.push_back(path);
    }return path;
}


void handleClient(int client_socket,const Graph& graph){//function to handle the client when it connect to the server
    char buffer[1024] ; //buffer will store the data from the client
    memset(buffer, 0, sizeof(buffer));//setting the buffer to 0
    ssize_t valread = read(client_socket, buffer, sizeof(buffer)) ;// reading the data from the client socket  
    if (valread < 0) {//if the data is not read so will print the error
        perror("fail socket reading");
    }else{
    }
    istringstream iss(buffer);//iss to read the buffer
    int from, to;
    iss >> from >> to;//reading the first value it mean it the from and the second value is the to
    
    vector<int> path = find(const_cast<Graph&>(graph), from, to);//finding the path between the source and destination
    string response;//will store the response to send it to the client
    if (path.empty()) {//if the path is empty so it mean the path no found so will set the response to "No path found"
        response = "No path found";
    } else {
        for (int node : path) {//looping through the path and adding the node to the response
            response += to_string(node) + " ";
        }
    }
    write(client_socket, response.c_str(), response.size());//sending the response to the client after calculate the response answer
    close(client_socket);//closing the client socket after sending the response
}
//Main

int main(int argc, char* argv[]) {
    if (argc < 3) {//checking if the user enter the file name and the port number
        cerr << "ERROR please enter only file name and port number" << endl;
        return 1;
    }
    string filename = argv[1];//ARGV 1 store the file name
    int port = atoi(argv[2]);//ARGV 2 store the port number

    Graph graph = ReadGraph(filename);//reading the graph from the file
    int server_fd, new_socket;//server_fd to store the server socket and new_socket to store the client socket
    struct sockaddr_in address;//address to store the address of the server
    int opt = 1;//opt to store the option
    int addrlen = sizeof(address);//

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {//creating the server socket
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {//will set the socket option to reuse the address and port
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;//setting the address family
    address.sin_addr.s_addr = INADDR_ANY;//setting the address to any address
    address.sin_port = htons(port);//setting the port number

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {//binding the server to the address
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
   
    if (listen(server_fd, 3) < 0) {//listening to the server socket with the maximum of 3 clients
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {//looping to accept the clients and handle them
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0) {//if the client is not accepted so will print the error and continue accepting other clients
            perror("accept");
            continue;  // Continue accepting other connections even if one accept fails
        }
        
        thread(handleClient, new_socket, ref(graph)).detach();  // Handle each client in a separate thread 
        
    }
    return 0;
}