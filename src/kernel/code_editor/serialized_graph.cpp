#include "serialized_graph.h"

#include <QDebug>
#include <QList>
#include <unordered_set>

namespace dsv::Kernel {

bool SerializedGraph::Row::operator==(const SerializedGraph::Row& rhs) const {
    return from == rhs.from && to == rhs.to && weight == rhs.weight;
}

SerializedGraph SerializedGraph::fromGraph(const Graph& graph) {
    SerializedGraph serializedGraph;

    std::unordered_set<size_t> usedNodes;
    for (const auto& [from, toEdges] : graph.getEdges()) {
        for (const auto& [to, edge] : toEdges) {
            SerializedGraph::Row row{
                .from = QString::number(from), .to = QString::number(to), .weight = QString::number(edge.weight)
            };
            serializedGraph.rows.push_back(std::move(row));
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

        if (!row.from.isEmpty() && !row.from.isEmpty() && !row.weight.isEmpty()) {
            auto from = row.from.toInt();
            auto to = row.to.toInt();
            bool ok;
            auto weight = row.weight.toInt(&ok);
            assert(ok);
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
