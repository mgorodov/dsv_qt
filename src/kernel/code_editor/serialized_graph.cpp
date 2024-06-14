#include "serialized_graph.h"

#include <QDebug>
#include <QHash>
#include <QList>

namespace dsv::Kernel {

bool SerializedGraph::Row::operator==(const SerializedGraph::Row& rhs) const {
    return from == rhs.from && to == rhs.to && weight == rhs.weight;
}

size_t SerializedGraph::RowHash::operator()(const SerializedGraph::Row& row) const {
    return qHash(row.from) ^ qHash(row.to) ^ qHash(row.weight);
}

bool SerializedGraph::operator==(const SerializedGraph& rhs) const {
    const auto curGraph = toGraph();
    const auto rhsGraph = rhs.toGraph();
    return curGraph.getEdges() == rhsGraph.getEdges() && curGraph.getNodes() == rhsGraph.getNodes();
}

bool SerializedGraph::operator!=(const SerializedGraph& rhs) const {
    return !(*this == rhs);
}

SerializedGraph SerializedGraph::fromGraph(const Graph& graph) {
    SerializedGraph serializedGraph;

    std::unordered_set<size_t> usedNodes;
    for (const auto& [from, toEdges] : graph.getEdges()) {
        for (const auto& [to, edge] : toEdges) {
            if (edge.weight != 0) {
                SerializedGraph::Row row{
                    .from = QString::number(from), .to = QString::number(to), .weight = QString::number(edge.weight)
                };
                serializedGraph.rows.push_back(std::move(row));
            } else {
                SerializedGraph::Row row{.from = QString::number(from), .to = QString::number(to)};
                serializedGraph.rows.push_back(std::move(row));
            }
            usedNodes.insert(from);
            usedNodes.insert(to);
        }
    }

    for (const auto& [index, node] : graph.getNodes()) {
        if (usedNodes.count(index))
            continue;
        SerializedGraph::Row row{.from = QString::number(index)};
        serializedGraph.rows.push_back(std::move(row));
    }

    return serializedGraph;
}

SerializedGraph SerializedGraph::fromString(const QString& str) {
    SerializedGraph serializedGraph;

    for (const auto& row : str.split("\n")) {
        const auto splittedRow = row.split(" ");
        if (splittedRow.size() == 1) {
            SerializedGraph::Row row{.from = splittedRow[0]};
            serializedGraph.rows.push_back(std::move(row));
        } else if (splittedRow.size() == 2) {
            SerializedGraph::Row row{.from = splittedRow[0], .to = splittedRow[1]};
            serializedGraph.rows.push_back(std::move(row));
        } else if (splittedRow.size() == 3) {
            SerializedGraph::Row row{.from = splittedRow[0], .to = splittedRow[1], .weight = splittedRow[2]};
            serializedGraph.rows.push_back(std::move(row));
        } else {
            qDebug() << "ShitShitShitShitShit happened";
        }
    }

    return serializedGraph;
}

Graph SerializedGraph::toGraph() const {
    Graph graph;
    for (const auto& row : rows) {
        if (!row.from.isEmpty()) {
            bool ok;
            auto from = row.from.toInt(&ok);
            assert(ok);
            graph.addNode(from, Node{row.from.toStdString()});
        }

        if (!row.to.isEmpty()) {
            bool ok;
            auto to = row.to.toInt(&ok);
            assert(ok);
            graph.addNode(to, Node{row.to.toStdString()});
        }

        if (!row.from.isEmpty() && !row.to.isEmpty()) {
            auto from = row.from.toInt();
            auto to = row.to.toInt();
            int weight = 0;
            if (!row.weight.isEmpty()) {
                bool ok;
                weight = row.weight.toInt(&ok);
                assert(ok);
            }
            graph.addEdge(from, to, Edge{weight});
        }
    }
    return graph;
}

QString SerializedGraph::toString() const {
    QString text;
    for (const auto& row : rows) {
        text += row.from;
        if (!row.to.isEmpty()) {
            text += " " + row.to;
        }
        if (!row.weight.isEmpty()) {
            text += " " + row.weight;
        }
        text += '\n';
    }
    return text;
}

}  // namespace dsv::Kernel
