#pragma once
#include <stddef.h>

namespace dsv {

enum class EObjectType { Node, Edge };
enum class EActionType { Add, Delete };

struct EditAction {
    EObjectType object;
    EActionType action;
    size_t index;
};

}  // namespace dsv
