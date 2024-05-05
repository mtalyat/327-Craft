#include "ElementManager.h"

ElementManager::ElementManager()
    : nodes(), currentNode(nullptr)
{
}

ElementManager::~ElementManager()
{
    // delete all nodes (GameObject deletes the Element children)
    for (size_t i = nodes.size() - 1; i >= 0; i--)
    {
        delete nodes.at(i);
    }
    nodes.clear();
    currentNode = nullptr;
}

void ElementManager::addNode(Node *node)
{
    nodes.push_back(node);

    node->element->unfocus();

    if (!currentNode)
    {
        setCurrent(node);
    }
}

void ElementManager::setCurrent(Node *node)
{
    if (currentNode)
    {
        currentNode->element->unfocus();
    }

    currentNode = node;

    if (currentNode)
    {
        currentNode->element->focus();
    }
}

void ElementManager::setCurrent(int const index)
{
    setCurrent(nodes[index]);
}

bool ElementManager::onInput(EngineData &data)
{
    if (!currentNode)
    {
        return false;
    }

    // move around with D-pad
    switch (data.getInput())
    {
    case KEY_UP:
    case '8': // up
        move(currentNode->above);
        break;
    case KEY_LEFT:
    case '4': // left
        move(currentNode->left);
        break;
    case KEY_RIGHT:
    case '6': // right
        move(currentNode->right);
        break;
    case KEY_DOWN:
    case '2': // down
        move(currentNode->below);
        break;
    default:
        return false;
    }

    return true;
}

void ElementManager::move(Node *node)
{
    // only move if not null
    if (node)
    {
        setCurrent(node);
    }
}
