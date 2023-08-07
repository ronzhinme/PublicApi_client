
qt_add_qml_module( category_model
    URI category
    VERSION 1.0
    SOURCES
        ../models/role_to_string.h
        ../models/tree/tree_node.h
        ../models/tree/tree_node.cpp
        ../models/tree/tree_model.h
        ../models/tree/tree_model.cpp
        category_node.h
        category_node.cpp
        category_tree.h
        category_tree.cpp
)
