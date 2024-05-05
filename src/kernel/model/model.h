#pragma once
#include <QObject>
#include <vector>

namespace dsv::Kernel {

enum class ENodeState { INTACT, SELECTED, USED };

enum class EEdgeState { INTACT, SELECTED, USED };

template <typename V>
struct Node {
    V val;
    size_t index;
    ENodeState state;
};

template <typename E>
struct Edge {
    E weight;
    size_t from;
    size_t to;
    EEdgeState state;
};

class Model : public QObject {
    Q_OBJECT
public:
    Model();
    void addNode(size_t index, int value);
    void removeNode(size_t index);
    void addEdge(size_t from, size_t to, int weight);
    void removeEdge(size_t from, size_t to);

    std::vector<size_t> DFS(size_t start);
    std::vector<size_t> BFS(size_t start);
    std::unordered_map<size_t, int> Dijkstra(size_t start);
    std::vector<std::vector<int>> FloydWarshall();
    std::unordered_map<size_t, size_t> Prim();

    std::vector<size_t> reconstructPath(size_t start, size_t end, const std::unordered_map<size_t, size_t>& prev);
signals:
    void notify();

private:
    std::unordered_map<size_t, Node<int>> nodes;
    std::unordered_map<size_t, std::unordered_map<size_t, Edge<int>>> edges;

    void DFSUtil(size_t nodeIndex, std::unordered_map<size_t, bool>& visited, std::vector<size_t>& result);
    size_t MinKey(std::unordered_map<size_t, int>& key, std::unordered_map<size_t, bool>& inMST);
};

}  // namespace dsv::Kernel
