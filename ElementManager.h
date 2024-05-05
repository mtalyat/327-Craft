#ifndef __ELEMENTMANAGER_H__
#define __ELEMENTMANAGER_H__

#include "Element.h"

// A manager for Elements. This will ensure only one of the elements is focused at any given time.
// It also will allow the user to navigate between different Elements by using the D-PAD/ARROW KEYS.
class ElementManager
    : public Element
{
public:
    // A node within the Element Manager.
    // Any null nodes will not allow the user to navigate in that direction.
    struct Node
    {
        // The element this node pertains to.
        Element *element;
        // The above node that can be navigated to.
        Node *above;
        // The below node that can be navigated to.
        Node *below;
        // The right side node that can be navigated to.
        Node *right;
        // The left side node that can be navigated to.
        Node *left;
    };

private:
    // A list of all nodes within this ElementManager.
    std::vector<Node *> nodes;
    // The current/focused node.
    Node *currentNode;

private:
    // Moves the current Node to the given node, if it is not null.
    void move(Node *node);

protected:
    bool onInput(EngineData &data) override;

public:
    ElementManager();
    ~ElementManager();

    // Adds a Node to this ElementManager. If no current Node is set, it will automatically be set to the given Node.
    void addNode(Node *node);
    // Sets the current Node to the given Node (even if null).
    void setCurrent(Node *node);
    // Sets the current Node to the node at the given index.
    void setCurrent(int const index);
};

#endif // __ELEMENTMANAGER_H__