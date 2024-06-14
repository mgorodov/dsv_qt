#pragma once
#include <stddef.h>

#include <QString>

namespace dsv {

enum class EObjectType { Node, Edge, Algorithm };
enum class EActionType { Add, Delete, Change, DFS, Finish };

struct EditAction {
    EObjectType object;
    EActionType action;
    size_t index;
    std::optional<size_t> indexEnd;
    std::optional<QString> text;
};

}  // namespace dsv
