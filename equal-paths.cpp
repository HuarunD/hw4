#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here


bool equalPaths(Node * root)
{
    // Add your code below
    int heights_ =-1;
    return fdepth(root,0, &heights_);
}
bool fdepth(Node * root, int heights , int* t_h)
{
    if(root == nullptr){
        return true;
    }
    if(root->left == nullptr && root->right == nullptr){
        if(*t_h == -1){
            *t_h = heights;
        }
        else{
            return *t_h == heights;
        }
        return true;
    }
    return fdepth(root->left, heights+1, t_h)&& fdepth(root->right, heights+1, t_h);
}

