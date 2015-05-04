#ifndef TREES_H_INCLUDED
#define TREES_H_INCLUDED
#include <iostream>
#include <queue>


// PROG 6 ExprTree Allen Moody
using namespace std;

const int OP = 0;
const int NUM = 1;

enum traverseType {prefix, infix, postfix};

union ExprNodeDatum {
    char op;
    int num;
};

class ExprTreeNode {
public:
    ExprNodeDatum datum;
    int flag;
    ExprTreeNode * leftChild;
    ExprTreeNode * rightChild;
    
    int eval();
    
    void display(int);
    
    void details();
    
    void depthTraverse(traverseType typ) {
        
        if(typ == prefix)
        {
            details();                                              // V
            if (leftChild != NULL) leftChild->depthTraverse(typ);   // L
            if (rightChild != NULL) rightChild->depthTraverse(typ); // R
            
        }
        
        if(typ == postfix)
        {
                if (leftChild != NULL) leftChild->depthTraverse(typ);   // L
                if (rightChild != NULL) rightChild->depthTraverse(typ); // R
                details();                                              // V
            }
        
        if (typ == infix) {
            if (leftChild != NULL) leftChild->depthTraverse(typ);   // L
            details();                                              // V
            if (rightChild != NULL) rightChild->depthTraverse(typ); // R
        }
        
        // your code here for a RECURSIVE DFS, printing where called for
        
    }
    
    void breadthTraverse () {
        queue<ExprTreeNode *> nodes;
        nodes.push(this);
        
        // iterate on queue, printing first and queuing children (if any)
        
        // your code here
        ExprTreeNode * traverse;
        
        
        
        while (!nodes.empty()) {
            traverse = nodes.front();
            nodes.pop();
            details();
            
            if (traverse->leftChild!= NULL) {
                
                nodes.push(traverse->leftChild);
               
            }
            
            if (traverse->rightChild!= NULL) {
                
                nodes.push(traverse->rightChild);
                
            }
            
        }
    }
};

#endif // TREES_H_INCLUDED