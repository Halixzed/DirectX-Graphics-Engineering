// SceneGraph.cpp

#include "SceneGraph.h"

bool SceneGraph::Initialise() {
    for (SceneNodePointer child : _children) {
        if (!child->Initialise()) {
            return false;
        }
    }
    return true;
}

void SceneGraph::Update(const Matrix& worldTransformation) {
    // Update the cumulative world transformation for itself
    SceneNode::Update(worldTransformation);

    // Call the Update method for each child node, passing the combined world transformation
    for (SceneNodePointer child : _children) {
        child->Update(_cumulativeWorldTransformation);
    }
}

void SceneGraph::Render() {
    // Call the Render method on each child node
    for (SceneNodePointer child : _children) {
        child->Render();
    }
}

void SceneGraph::Shutdown() {
    // Call the Shutdown method on each child node
    for (SceneNodePointer child : _children) {
        child->Shutdown();
    }
}

void SceneGraph::Add(SceneNodePointer node) {
    // Add the specified node to the collection of child nodes
    _children.push_back(node);
}

void SceneGraph::Remove(SceneNodePointer node) {
    // Call Remove on all child nodes
    for (auto it = _children.begin(); it != _children.end(); ++it) {
        (*it)->Remove(node);
    }

    // If the child node is the one to remove, remove it from the list of child nodes
    _children.erase(std::remove(_children.begin(), _children.end(), node), _children.end());
}

SceneNodePointer SceneGraph::Find(wstring name) {
    // If we are the node being searched for, return a pointer to ourselves
    if (_name == name) {
        return shared_from_this();
    }

    // If not, call Find on all child nodes
    for (SceneNodePointer child : _children) {
        SceneNodePointer foundNode = child->Find(name);
        if (foundNode != nullptr) {
            return foundNode;
        }
    }

    return nullptr; // Node not found
}
