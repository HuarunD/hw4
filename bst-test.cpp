#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('c',1));
    bt.insert(std::make_pair('d',2));
    bt.insert(std::make_pair('b',2));
    bt.insert(std::make_pair('e',2));
    bt.insert(std::make_pair('a',2));
 //   cout << "Binary Search Tree contents:" << endl;
    //int count =0;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    //     //count ++;
    // }
    //bt.print();
    // bt.remove('b');
    // bt.remove('c');
    // //bt.print();
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));
		at.insert(std::make_pair('c',2));
		at.insert(std::make_pair('d',2));
		//	at.print();
		at.insert(std::make_pair('d',3));
		at.insert(std::make_pair('f',2));
		//	at.print();
		at.insert(std::make_pair('e',2));
		//	at.print();
    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
		//at.print();
    //cout << "d" << endl;
		
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
		// cout << "Erasing b" << endl;

		AVLTree<int, double> bst;
		bst.insert(std::make_pair(2, 1.0));
		bst.insert(std::make_pair(1, 1.0));
		bst.insert(std::make_pair(3, 1.0));
		bst.remove(2);
		//cout << "t" << endl;
		bst.print();
    return 0;
}
