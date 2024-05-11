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
                TreeNode* aux = createTreeNode(key, value);
                aux -> parent = tmp;
                tmp -> left = aux;
                tree -> current = aux;
                return;
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


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
