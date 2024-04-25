#include "model.h"

#include <queue>

namespace dsv {

Model::Model() {}

void Model::addNode(size_t index, int value) {
    nodes[index] = {value, index, ENodeState::INTACT};
}

void Model::removeNode(size_t index) {
    nodes.erase(index);
    edges.erase(index);
    for (auto& pair : edges) {
        pair.second.erase(index);
    }
}

void Model::addEdge(size_t from, size_t to, int weight) {
    edges[from][to] = {weight, from, to, EEdgeState::INTACT};
}

void Model::removeEdge(size_t from, size_t to) {
    edges[from].erase(to);
}

void Model::DFSUtil(size_t nodeIndex, std::unordered_map<size_t, bool>& visited, std::vector<size_t>& result) {
    visited[nodeIndex] = true;
    result.push_back(nodeIndex);

    for (const auto& adj : edges[nodeIndex]) {
        if (!visited[adj.first]) {
            DFSUtil(adj.first, visited, result);
        }
    }
}

std::vector<size_t> Model::DFS(size_t start) {
    std::vector<size_t> result;
    std::unordered_map<size_t, bool> visited;

    DFSUtil(start, visited, result);
    return result;
}

std::vector<size_t> Model::BFS(size_t start) {
    std::vector<size_t> result;
    std::queue<size_t> q;
    std::unordered_map<size_t, bool> visited;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        size_t nodeIndex = q.front();
        q.pop();
        result.push_back(nodeIndex);

        for (const auto& edge : edges[nodeIndex]) {
            if (!visited[edge.first]) {
                q.push(edge.first);
                visited[edge.first] = true;
            }
        }
    }
    return result;
}

std::unordered_map<size_t, int> Model::Dijkstra(size_t start) {
    const int INF = std::numeric_limits<int>::max();
    std::unordered_map<size_t, int> dist;
    for (auto& node : nodes) {
        dist[node.first] = INF;
    }
    dist[start] = 0;

    auto comp = [&](size_t left, size_t right) { return dist[left] > dist[right]; };
    std::priority_queue<size_t, std::vector<size_t>, decltype(comp)> pq(comp);

    pq.push(start);

    while (!pq.empty()) {
        size_t u = pq.top();
        pq.pop();

        for (auto& edge : edges[u]) {
            size_t v = edge.first;
            int w = edge.second.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(v);
            }
        }
    }
    return dist;
}

std::unordered_map<size_t, size_t> Model::Prim() {
    std::unordered_map<size_t, size_t> parent;

    std::unordered_map<size_t, int> key;

    std::unordered_map<size_t, bool> inMST;

    for (auto& node : nodes) {
        key[node.first] = std::numeric_limits<int>::max();
        inMST[node.first] = false;
    }

    if (!nodes.empty())
        key[nodes.begin()->first] = 0;

    for (size_t count = 0; count < nodes.size(); ++count) {
        size_t u = MinKey(key, inMST);

        inMST[u] = true;

        for (auto& adj : edges[u]) {
            size_t v = adj.first;
            int weight = adj.second.weight;

            if (!inMST[v] && key[v] > weight) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }
    return parent;
}

size_t Model::MinKey(std::unordered_map<size_t, int>& key, std::unordered_map<size_t, bool>& inMST) {
    int min = std::numeric_limits<int>::max();
    size_t min_index = 0;

    for (auto& kv : key) {
        if (!inMST[kv.first] && kv.second < min) {
            min = kv.second, min_index = kv.first;
        }
    }
    return min_index;
}

std::vector<std::vector<int>> Model::FloydWarshall() {
    const int INF = std::numeric_limits<int>::max();
    size_t V = nodes.size();

    std::vector<std::vector<int>> dist(V, std::vector<int>(V, INF));

    for (const auto& edgeMap : edges) {
        size_t u = edgeMap.first;
        for (const auto& edge : edgeMap.second) {
            size_t v = edge.first;
            int w = edge.second.weight;
            dist[u][v] = w;
        }
    }

    for (size_t i = 0; i < V; ++i) {
        dist[i][i] = 0;
    }

    for (size_t k = 0; k < V; ++k) {
        for (size_t i = 0; i < V; ++i) {
            for (size_t j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

}  // namespace dsv
