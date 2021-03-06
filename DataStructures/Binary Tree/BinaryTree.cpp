//
//  BinaryTree.cpp
//  DataStructures
//
//  Created by Jerome on 27/02/2013.
//  Copyright (c) 2013 Jerome. All rights reserved.
//

#include "BinaryTree.h"
#include <iostream.h>

BinarySearchTree::BinarySearchTree()
{
    root = NULL;
    size = 0;
}
BinarySearchTree::~BinarySearchTree()
{
    removeAll();
}
bool BinarySearchTree::add(char* key, char* value)
{
    if(key == NULL || value == NULL || strlen(key) > SIZE_KEY-1
       || strlen(value) > SIZE_VALUE-1)
    {
        return false;
    }
    METADATA* new_node = new METADATA(key, value);
    return addNode(&root, new_node);
}
bool BinarySearchTree::addNode(METADATA** current_node, METADATA* new_node)
{
    if(*current_node == NULL)
    {
        *current_node = new_node;
        size++;
        return true;
    }
    else
    {
        if(strcmp(new_node->key, (*current_node)->key) < 0)
        {
            return addNode(&((*current_node)->left), new_node);
        }
        else if(strcmp(new_node->key, (*current_node)->key) > 0)
        {
            return addNode(&((*current_node)->right), new_node);
        }
        else
        {
            delete new_node;
            return false;
        }
    }
}
bool BinarySearchTree::remove(char* key)
{
    return removeNode(&root, key);
}

bool BinarySearchTree::removeNode(METADATA** node, char* key)
{
    if(*node != NULL)
    {
        if (strcmp(key, (*node)->key) == 0)
        {
            removeRootNode(node);
            size--;
            return true;
        }
        else if(strcmp(key, (*node)->key) < 0)
        {
            return removeNode(&((*node)->left), key);
        }
        else
        {
            return removeNode(&((*node)->right), key);
        }
    }
    else
    {
        return false;
    }
}
void BinarySearchTree::removeRootNode(METADATA** root)
{
    METADATA* temp;
    if((*root)->left == NULL && (*root)->right == NULL)
    {
        delete(*root);
        *root = NULL;
    }
    else if((*root)->right == NULL)
    {
        temp = *root;
        *root = (*root)->left;
        delete(temp);
    }
    else if((*root)->left == NULL)
    {
        temp = *root;
        *root = (*root)->right;
        delete(temp);
    }
    else
    {
        moveLeftMostNode(&((*root)->right), *root);
    }
}
void BinarySearchTree::moveLeftMostNode(METADATA** node, METADATA* root)
{
    if(*node != NULL && (*node)->left == NULL)
    {
        METADATA* temp = *node;
        strcpy(root->key, (*node)->key);
        strcpy(root->value, (*node)->value);
        *node = (*node)->right;
        delete(temp);
    }
    else
    {
        moveLeftMostNode(&((*node)->left), root);
    }
}
void BinarySearchTree::removeAll()
{
    removeAllNodes(root);
    root = NULL;
    size = 0;
}
void BinarySearchTree::removeAllNodes(METADATA* node)
{
    if(node != NULL)
    {
        removeAllNodes(node->left);
        removeAllNodes(node->right);
        cout << "Removing node - key: " << node->key << "\t" << node->value
        << endl;
        delete node;
    }
}
bool BinarySearchTree::get(char* key, char* value)
{
    return getNode(root, key, value);
}
bool BinarySearchTree::getNode(METADATA* node, char* key, char* value)
{
    if(node == NULL)
    {
        value[0] = '\0';
        return false;
    }
    else
    {
        if(strcmp(key, node->key) == 0)
        {
            strcpy(value, node->value);
            return true;
        }
        else if(strcmp(key, node->key) < 0)
        {
            return getNode(node->left, key, value);
        }
        else
        {
            return getNode(node->right, key, value);
        }
    }
}
bool BinarySearchTree::contains(char* key)
{
    return containsNode(root, key);
}
bool BinarySearchTree::containsNode(METADATA* node, char* key)
{
    if(node == NULL)
    {
        return false;
    }
    else
    {
        if(strcmp(key, node->key) == 0)
        {
            return true;
        }
        else if(strcmp(key, node->key) < 0)
        {
            return containsNode(node->left, key);
        }
        else
        {
            return containsNode(node->right, key);
        }
    }
}
void BinarySearchTree::displayInOrder()
{
    processNodesInOrder(root);
}
void BinarySearchTree::processNodesInOrder(METADATA* node)
{
    if(node != NULL)
    {
        processNodesInOrder(node->left);
        cout << "key: " << node->key << "\tvalue: " << node->value << endl;
        processNodesInOrder(node->right);
    }
}
int BinarySearchTree::getSize()
{
    return size;
}
int BinarySearchTree::getDepth()
{
    return getTreeDepth(root);
}
int BinarySearchTree::getTreeDepth(METADATA* node)
{
    int depth_left;
    int depth_right;
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        depth_left = getTreeDepth(node->left);
        depth_right = getTreeDepth(node->right);
        if(depth_left > depth_right)
        {
            return depth_left + 1;
        }
        else
        {
            return depth_right + 1;
        }
    }
}