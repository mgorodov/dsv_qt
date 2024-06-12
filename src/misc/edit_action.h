#pragma once
#include <stddef.h>

#include <QString>

namespace dsv {

enum class EObjectType { Node, Edge };
enum class EActionType { Add, Delete, Change };

struct EditAction {
    EObjectType object;
    EActionType action;
    size_t index;
    std::optional<size_t> indexEnd;
    std::optional<QString> text;
};

}  // namespace dsv
