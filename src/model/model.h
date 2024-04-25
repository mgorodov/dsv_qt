#pragma once
#include <QObject>
#include <vector>

namespace dsv {

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
signals:
    void notify();

private:
};

}  // namespace dsv
