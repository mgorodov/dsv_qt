#pragma once
#include <cstddef>

enum class EControlButton { Run, Stop, Backward, Forward };
enum class EAlgorithm { DFS, BFS, Prim, Dijkstra };

struct AlgorithmAction {
    EControlButton clickedButton;
    EAlgorithm selectedAlgorithm;
    size_t startVertex;
};
