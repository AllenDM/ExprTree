#include <iostream>
#include <stdlib.h>
#include <stack>
#include <sstream>
#include "trees.h"

using namespace std;

// return the value of a node
int ExprTreeNode::eval() {
    if (flag==NUM)
        return datum.num;
    else if (datum.op=='+')
        return (leftChild->eval()) + (rightChild -> eval());
    else if (datum.op=='-')
        return (leftChild->eval()) - (rightChild->eval());
    else if (datum.op=='*')
        return (leftChild->eval()) * (rightChild->eval());
    else if (datum.op=='/')
        return (leftChild->eval()) / (rightChild->eval());
    else {
        cout << "STACK ERROR!!!";
        return 0;
    }
}

// display the vlue in the tree, indenting for depth
void ExprTreeNode::display(int depth) {
    for (int i=0; i<depth; i++) cout <<"  ";
    if (flag == OP) {
        cout << datum.op << endl;
        if (leftChild!=NULL) leftChild->display(depth+1);
        if (rightChild!=NULL) rightChild->display(depth+1);
    } else {
        cout << datum.num << endl;
    }
}

// print all details about a node
void ExprTreeNode::details() {
    cout << "@" << this << " : " ;
    if (flag==NUM)
        cout << datum.num;
    else
        cout << datum.op;
    cout << " left:" << leftChild << " right:" << rightChild << endl;
}

ExprTreeNode * assembleTree(int sz, string postFixExpr[]) {
    // use a stack to assemble tree from postfix
    stack<ExprTreeNode *> nodes;
    
    for (int i = 0; i<sz; i++) {
        // get a new node
        ExprTreeNode * nn = new ExprTreeNode;
        nn -> leftChild = NULL;
        nn -> rightChild = NULL;
        
        //cout << "   inserting: " << postFixExpr[i] << endl;
        
        // number or operator?
        if (postFixExpr[i][0]=='+' || postFixExpr[i][0]=='-'
            || postFixExpr[i][0]=='*'|| postFixExpr[i][0]=='/') {
            // if operator, set datum, link children & reduce stack
            nn -> flag = OP;
            nn -> datum.op = postFixExpr[i][0];
            nn -> rightChild = nodes.top();
            nodes.pop();
            nn -> leftChild = nodes.top();
            nodes.pop();
            nodes.push(nn);
        } else {
            // if string is number, convert & place number on the stack
            nn->flag = NUM;
            istringstream convert(postFixExpr[i]);
            convert >> nn->datum.num;
            nodes.push(nn);
        }
        //cout << nodes.size() << ": ";
        //nn ->details();
    }
    if (nodes.size()!= 1) {
        cerr << "improper post fix expression!!!" << endl;
        exit (1);
    } else {
        return nodes.top();
    }
}

int main() {
    string postFixExpr[] = {"2", "1", "-", "4", "5", "*", "+", "3", "/"};
    int sz = 9;
    
    ExprTreeNode * root = assembleTree(sz, postFixExpr);
    
    cout << "    Tree:" << endl;
    root->display(4);
    cout << endl;
    
    cout << "   Value: ";
    cout << root-> eval() << endl;
    cout << endl;
    
    cout << " prefix: " ;
    root->depthTraverse(prefix);
    cout << endl;
    
    cout << " infix: " ;
    root->depthTraverse(infix);
    cout << endl;
    
    cout << " postfix: " ;
    root->depthTraverse(postfix);
    cout << endl;
    
    cout << " breadth first order: " ;
    root->breadthTraverse();
    
    return 0;
}