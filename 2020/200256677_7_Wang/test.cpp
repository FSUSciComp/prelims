#include "BST.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    // initialize integer binary search tree
    BST<int> bst;
    int array[] = {1,6,8,3,67,0,2,-13,7,3,43,43,43,43,43,100,-999};
    for(int a : array) {
        bst.insert(a);
    }

    // testing sorted output function
    // NOTE: I chose to have the .output() function return a sorted array instead of just printing, since that's more useful
    // to that end, I have also included a public BST<T>::getSize() function, demonstrated here
    int* sorted = bst.output();
    for(int i = 0; i < bst.getSize(); i++) {
        cout << sorted[i] << endl;
    }

    // testing search function
    int queries[] = {67, 42}; // 67=true, 42=false
    for(int i : queries) {

        if(bst.search(i)) {
            cout << "Search tree contains " << i << endl;
        } 
        else{
            cout << "Search tree does NOT contain " << i << endl;
        }

    }

}