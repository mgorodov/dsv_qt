#pragma once

namespace dsv {

enum class EObjectType { Node, Edge };
enum class EActionType { Add, Delete };

struct EditAction {
    EObjectType object;
    EActionType action;
};

}  // namespace dsv
