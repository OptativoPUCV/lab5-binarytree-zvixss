#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* new = (TreeMap *)malloc(sizeof(TreeMap));
    new->lower_than = lower_than;

    if (new->lower_than == NULL) return NULL;

    new->root = NULL;
    return new;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL) return;

    if (tree->root == NULL)
    {
        tree->root = createTreeNode(key, value);
        return;
    }

    TreeNode* tmp = tree->root;

    while (tmp != NULL)
        {
            if (is_equal(tree, key, tmp -> pair -> key))return;

            if (tree -> lower_than(key, tmp -> pair -> key))
            {
                if (tmp -> right == NULL)
                {
                    TreeNode* aux = createTreeNode(key, value);
                    aux -> parent = tmp;
                    tmp -> left = aux;
                    tree -> current = aux;
                    return;
                }
            }
            
            if (tmp -> left != NULL)
            {
                tmp = tmp-> left;
            }
        }
    
    if (tree -> lower_than(key, tmp -> pair -> key))
    {
        if (tmp -> right == NULL)
        {
            TreeNode* aux = createTreeNode(key, value);
            aux -> parent = tmp;
            tmp -> left = aux;
            tree -> current = aux;
            return;
        }
        
        if (tmp -> right != NULL)
        {
            tmp = tmp -> right;
        }
    }
}

TreeNode * minimum(TreeNode * x)
{
    while (x -> left != NULL)
        {
            if(x -> left == NULL) break;

            x = x -> left;
        }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if (node -> left == NULL && node -> right == NULL)
    {
        if (node -> parent -> left  == node) 
        {
            node -> parent -> left = NULL;
        }

        if (node -> parent -> right == node)
        {
            node -> parent -> right = NULL;
        }
    }

    else if (node -> left == NULL || node -> right == NULL)
    {
        if (node -> left != NULL)
        {
            if (node -> parent -> left == node)
            {
                node -> parent -> left = node -> left;
                node -> left -> parent = node -> parent;
            }

            if (node -> parent -> right == node)
            {
                node -> parent -> right = node -> left;
                node -> left -> parent = node -> parent;
            }
        }

        else if (node -> right != NULL)
        {
            if (node -> parent -> left == node)
            {
                node -> parent -> left = node -> left;
                node -> left -> parent = node -> parent;
            }
            if (node -> parent -> right == node)
            {
                node -> parent -> right = node -> left;
                node -> left -> parent = node -> parent;
            }
        }
    }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);
}

Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree == NULL || tree -> root == NULL) return NULL;

    TreeNode *node = tree -> root;

    while (node != NULL)
        {
            if (is_equal(tree, node -> pair -> key, key))
            {
                tree -> current = node;
                return node -> pair;
            }

            if (tree -> lower_than( node -> pair -> key, key))
                node = node -> right;
            else
                node = node -> left;
        }
    return NULL;
}

Pair * upperBound(TreeMap * tree, void* key) 
{
    if (tree == NULL || tree -> root == NULL) return NULL;

    TreeNode *nodeID = NULL;
    TreeNode *node = tree -> root;

    while (node != NULL)
        {
            if (is_equal(tree, node -> pair -> key, key))
            {
                tree -> current = node;
                return node -> pair;
            }
            else if (tree -> lower_than(node -> pair -> key, key))
            {
                node = node -> right;
            }
            else
            {
                nodeID = node;
                node = node -> left;
            }
        }

    if (nodeID != NULL)
    {
        tree -> current = nodeID;
        return nodeID -> pair;
    }
    
    else return NULL;
}

Pair * firstTreeMap(TreeMap * tree) 
{
    if (tree == NULL || tree -> root == NULL) return NULL;

    TreeNode *node = tree -> root;

    while (node -> left != NULL)
        {
            node = node -> left;
        }

    tree -> current = node;
    return node -> pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
    if (tree == NULL || tree -> current == NULL) return NULL;

    TreeNode *node = tree -> current;

    if (node -> right != NULL)
    {
        node = node -> right;

        while (node -> left != NULL)
            {
                node = node -> left;
            }
        tree -> current = node;
        return node -> pair;
    }
    else
    {
        TreeNode *aux = node -> parent;

        while (aux != NULL && node == aux -> right)
            {
                node = aux;
                aux = aux -> parent;
            }

        tree -> current = aux;

        if (aux != NULL) return aux -> pair;

        else return NULL;
    }
}
