#pragma once
#include <QObject>
#include <vector>

namespace dsv {

template<typename V>
struct Node
{};

template<typename E>
struct Edge
{};

class Model : public QObject
{
    Q_OBJECT
public:
    Model();
signals:
    void notify();
private:
};

} // namespace dsv
