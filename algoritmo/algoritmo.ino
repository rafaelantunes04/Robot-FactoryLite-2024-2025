#include <Arduino.h>

// Direcao
enum Direcao {
  Norte,
  Sul,
  Este,
  Oeste
};

Direcao inverter(Direcao dir) {
  switch (dir) {
    case Norte: return Sul;
    case Sul: return Norte;
    case Este: return Oeste;
    case Oeste: return Este;
  }
}

// Ligacao
struct Ligacao {
  Direcao direcao;
  uint8_t distancia;
  uint8_t destino;
};

// Node
struct Node {
  Ligacao ligacoes[4];
  uint8_t ligacoes_usadas;

  Node() : ligacoes_usadas(0) {}

  void addLigacao(uint8_t destino, Direcao direcao, uint8_t distancia) {
    if (ligacoes_usadas < 4) {
      ligacoes[ligacoes_usadas].direcao = direcao;
      ligacoes[ligacoes_usadas].distancia = distancia;
      ligacoes[ligacoes_usadas].destino = destino;
      ligacoes_usadas++;
    }
  }
};

// Grafo
struct Grafo {
  Node nodes[35];

  void connect(uint8_t origem, uint8_t destino, Direcao direcao, uint8_t distancia) {
    nodes[origem].addLigacao(destino, direcao, distancia);
    nodes[destino].addLigacao(origem, inverter(direcao), distancia);
  }

  // Dijkstra's Algorithm
  void dijkstra(uint8_t start, uint8_t end, Direcao* path, uint8_t& pathLength) {
    const uint8_t numNodes = 35;
    uint16_t distances[numNodes]; // Stores the shortest distance to each node
    bool visited[numNodes];       // Tracks visited nodes
    uint8_t previous[numNodes];   // Stores the previous node in the shortest path

    // Initialize distances, visited, and previous arrays
    for (uint8_t i = 0; i < numNodes; i++) {
      distances[i] = UINT16_MAX; // Set initial distances to "infinity"
      visited[i] = false;
      previous[i] = 255; // Invalid value to indicate no previous node
    }

    distances[start] = 0; // Distance to the start node is 0

    // Main loop
    for (uint8_t count = 0; count < numNodes - 1; count++) {
      // Find the node with the smallest distance that hasn't been visited
      uint8_t currentNode = 255;
      uint16_t minDistance = UINT16_MAX;
      for (uint8_t i = 0; i < numNodes; i++) {
        if (!visited[i] && distances[i] < minDistance) {
          minDistance = distances[i];
          currentNode = i;
        }
      }

      if (currentNode == 255) {
        break; // No more nodes to process
      }

      visited[currentNode] = true;

      // Relaxation step: Update distances for neighboring nodes
      for (uint8_t i = 0; i < nodes[currentNode].ligacoes_usadas; i++) {
        uint8_t neighbor = nodes[currentNode].ligacoes[i].destino;
        uint16_t weight = nodes[currentNode].ligacoes[i].distancia;

        if (!visited[neighbor] && distances[currentNode] + weight < distances[neighbor]) {
          distances[neighbor] = distances[currentNode] + weight;
          previous[neighbor] = currentNode;
        }
      }
    }

    // Reconstruct the path
    pathLength = 0;
    uint8_t current = end;
    while (current != 255) {
      // Store the direction taken to reach the current node
      if (previous[current] != 255) {
        for (uint8_t i = 0; i < nodes[previous[current]].ligacoes_usadas; i++) {
          if (nodes[previous[current]].ligacoes[i].destino == current) {
            path[pathLength++] = nodes[previous[current]].ligacoes[i].direcao;
            break;
          }
        }
      }
      current = previous[current];
    }

    // Reverse the path to get the correct order (from start to end)
    for (uint8_t i = 0; i < pathLength / 2; i++) {
      Direcao temp = path[i];
      path[i] = path[pathLength - 1 - i];
      path[pathLength - 1 - i] = temp;
    }
  }
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  main();
}

int main() {
  Grafo grafo;

  // Add connections to the graph
  grafo.connect(31, 32, Este, 69);
  grafo.connect(31, 20, Norte, 21);
  grafo.connect(20, 16, Este, 26);
  grafo.connect(20, 21, Norte, 15);
  grafo.connect(21, 17, Este, 26);
  grafo.connect(21, 8, Norte, 36);
  grafo.connect(8, 12, Norte, 21);
  grafo.connect(8, 9, Este, 15);
  grafo.connect(9, 13, Norte, 21);
  grafo.connect(9, 10, Este, 15);
  grafo.connect(10, 14, Norte, 21);
  grafo.connect(10, 11, Este, 15);
  grafo.connect(11, 15, Norte, 21);
  grafo.connect(11, 33, Este, 26);
  grafo.connect(33, 27, Sul, 21);
  grafo.connect(33, 34, Este, 69);
  grafo.connect(27, 30, Sul, 15);
  grafo.connect(27, 24, Este, 26);
  grafo.connect(30, 22, Sul, 15);
  grafo.connect(30, 23, Este, 26);
  grafo.connect(30, 19, Oeste, 26);
  grafo.connect(22, 32, Sul, 21);
  grafo.connect(22, 18, Oeste, 26);
  grafo.connect(32, 0, Este, 26);
  grafo.connect(0, 4, Sul, 21);
  grafo.connect(0, 1, Este, 15);
  grafo.connect(1, 5, Sul, 21);
  grafo.connect(1, 2, Este, 15);
  grafo.connect(2, 6, Sul, 21);
  grafo.connect(2, 3, Este, 15);
  grafo.connect(3, 7, Sul, 21);
  grafo.connect(3, 28, Norte, 36);
  grafo.connect(28, 25, Oeste, 26);
  grafo.connect(28, 29, Norte, 15);
  grafo.connect(29, 26, Oeste, 26);
  grafo.connect(29, 34, Norte, 21);

  // Run Dijkstra's algorithm from node 31 to node 34
  Direcao path[35];
  uint8_t pathLength = 0;
  grafo.dijkstra(31, 34, path, pathLength);

  // Print the path
  Serial.println("\n");
  for (uint8_t i = 0; i < pathLength; i++) {
    switch (path[i]) {
      case Norte: Serial.println("Norte"); break;
      case Sul: Serial.println("Sul"); break;
      case Este: Serial.println("Este"); break;
      case Oeste: Serial.println("Oeste"); break;
    }
  }
  return 1;
}