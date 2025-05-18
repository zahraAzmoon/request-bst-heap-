#include <iostream>
#include <string>
using namespace std;

struct Node{
    int id;string name; Node* left; Node* right; Node* parent;

    Node(int id, string name){
        this->id = id;
        this->name = name;
        left=right=parent=nullptr;
    }

};

class Tree{
public:
    Node* root=nullptr;

    void tree_insert(Node* z){
        Node* y=nullptr;
        Node* x=root;
        while (x!=nullptr){
            y=x;
            if (z->id<x->id)
                x=x->left;
            else
                x=x->right;
        }
        z->parent=y;
        if (y==nullptr)
            root=z;
        else if (z->id < y->id)
            y->left=z;
        else
            y->right=z;
    }

    Node* tree_search(Node* x, int k){
        if (x==nullptr||k==x->id)
            return x;
        if (k < x->id)
            return tree_search(x->left,k);
        else
            return tree_search(x->right,k);
    }

    Node* tree_minimum(Node* x){
        while (x->left !=nullptr)
            x=x->left;
        return x;
    }

    void transplant(Node* u, Node* v){
        if (u->parent==nullptr)
            root=v;
        else if (u == u->parent->left)
            u->parent->left=v;
        else
            u->parent->right=v;
        if (v!=nullptr)
            v->parent = u->parent;
    }
};
