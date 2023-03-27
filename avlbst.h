#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void rotateRight(AVLNode<Key,Value>*n);
    virtual void rotateLeft(AVLNode<Key,Value>*n);
    virtual void Insertfix(AVLNode<Key,Value>*p, AVLNode<Key,Value>*n);
    virtual void RemoveFix(AVLNode<Key,Value>*n, size_t diff);


};
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>*n){
	AVLNode<Key,Value>* temp = n->getRight();
	n->setRight(temp->getLeft());
	if(n->getRight()!=nullptr) n->getRight()->setParent(n);
	temp->setParent(n->getParent());
	n->setParent(temp);
	temp->setLeft(n);
	if(temp->getParent()!=nullptr){
		if(temp->getKey()<temp->getParent()->getKey()){
			temp->getParent()->setLeft(temp);
		}
		else{
			temp->getParent()->setRight(temp);	
		}
	}
	else{
		this->root_ = static_cast<Node<Key, Value>*>(temp); 
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>*n){
	AVLNode<Key,Value>* temp = n->getLeft();
	n->setLeft(temp->getRight());
	if(n->getLeft()!=nullptr) n->getLeft()->setParent(n);
	temp->setParent(n->getParent());
	n->setParent(temp);
	temp->setRight(n);
	if(temp->getParent()!=nullptr){
		if(temp->getKey()<temp->getParent()->getKey()){
			temp->getParent()->setLeft(temp);
		}
		else{
			temp->getParent()->setRight(temp);	
		}
	}
	else{
		this->root_ = static_cast<Node<Key, Value>*>(temp); 
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::Insertfix(AVLNode<Key,Value>*p, AVLNode<Key,Value>*n){
	AVLNode<Key,Value>* gp = p->getParent();
	if(gp==nullptr) return;
	if(gp->getKey()>p->getKey()){
		gp->updateBalance(-1);
		if(gp->getBalance()==0) return;
		else if(gp->getBalance()==-1){
			Insertfix(gp,p);
		}
		else if(gp->getBalance()==-2){
			if(p->getBalance()==-1){
				rotateRight(gp);
				p->setBalance(0);
				gp->setBalance(0);
			}
			else{
				rotateLeft(p);
				rotateRight(gp);
				if(n->getBalance()==-1){
					p->setBalance(0);
					gp->setBalance(1);
					n->setBalance(0);
				}
				else if(n->getBalance()==0){
					p->setBalance(0);
					gp->setBalance(0);
					n->setBalance(0);
				
				}
				else if(n->getBalance()==1){
					p->setBalance(-1);
					gp->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
	else{
		gp->updateBalance(1);
		if(gp->getBalance()==0) return;
		else if(gp->getBalance()==1){
			Insertfix(gp,p);
		}
		else if(gp->getBalance()==2){
			if(p->getBalance()==1){
				rotateLeft(gp);
				p->setBalance(0);
				gp->setBalance(0);
			}
			else{
				rotateRight(p);
				rotateLeft(gp);
				if(n->getBalance()==1){
					p->setBalance(0);
					gp->setBalance(-1);
					n->setBalance(0);
				}
				else if(n->getBalance()==0){
					p->setBalance(0);
					gp->setBalance(0);
					n->setBalance(0);
				}
				else if(n->getBalance()==-1){
					p->setBalance(1);
					gp->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
}


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first,new_item.second,NULL);
    if(this->root_==nullptr){
			//std::cout << "till " << std::endl;
			this->root_ = static_cast<Node<Key, Value>*>(temp);  
			//std::cout << "till " << std::endl;
		}
    else{
				//std::cout << "till " << std::endl;
			AVLNode<Key, Value>* curr_ = static_cast<AVLNode<Key, Value>*>(this->root_);
				//std::cout << "till " << std::endl;
    	while(curr_!=nullptr){
				if(curr_->getKey()>temp->getKey()){

					if(curr_->getLeft()==nullptr){
						//std::cout << "till " << std::endl;
						curr_->setLeft(temp);
						temp->setParent(curr_);
						//std::cout << "till " << std::endl;
						curr_->updateBalance(-1);
						if(curr_->getBalance()!=0){
							//std::cout << "till " << std::endl;
							Insertfix(curr_,temp);
						}
						break;
					}
					curr_ = curr_->getLeft();

				}
				else if(curr_->getKey()==temp->getKey()){
					curr_->setValue(temp->getValue());
					delete temp;
					break;
				}
				else {
					if(curr_->getRight()==nullptr){
						curr_->setRight(temp);
						//std::cout << "till " << std::endl;
						temp->setParent(curr_);
						//std::cout << "till " << std::endl;
						curr_->updateBalance(1);
						if(curr_->getBalance()!=0){
							//std::cout << "till " << std::endl;
							Insertfix(curr_,temp);
						}
						break;
					}
					curr_ = curr_->getRight();
				}
			}
		}

}


template<class Key, class Value>
void AVLTree<Key, Value>::RemoveFix(AVLNode<Key,Value>* n, size_t diff){
	if(n == nullptr) return;
	AVLNode<Key, Value>* p = n->getParent();
	int ndiff = 0;
	//this->print();
	if(p!=nullptr){
		if(n->getKey()<p->getKey()){
			ndiff = 1;
		}
		else{
			ndiff = -1;
		}
	}
	if((signed)diff==-1){
		if((unsigned)n->getBalance()+diff==-2){
			AVLNode<Key, Value>* c = n->getLeft();
			if((signed)c->getBalance()==-1){
				rotateRight(n);
				n->setBalance(0);
				c->setBalance(0);
				RemoveFix(p, ndiff);
			}
			else if((signed)c->getBalance()==0){
				rotateRight(n);
				n->setBalance(-1);
				c->setBalance(1);
			}
			else{
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(c);
				rotateRight(n);
				if((signed)g->getBalance()==1){
					n->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0);
				}
				else if((signed)(g->getBalance())==0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else{
					n->setBalance(1);
					c->setBalance(0);
					g->setBalance(0);
				}
				RemoveFix(p, ndiff);
			}

		}
		else if((signed)(n->getBalance() + diff )== -1){
			n->setBalance(-1);
		}
		else{
			n->setBalance(0);
			RemoveFix(p,ndiff);
		}
	}
	else{
		if((signed)(n->getBalance()+diff)==2){
			AVLNode<Key, Value>* c = n->getRight();
			if(c->getBalance()==1){
				rotateLeft(n);
				n->setBalance(0);
				c->setBalance(0);
				RemoveFix(p, ndiff);
			}
			else if(c->getBalance()==0){
				rotateLeft(n);
				n->setBalance(1);
				c->setBalance(-1);
			}
			else{
				AVLNode<Key, Value>* g = c->getLeft();
				rotateRight(c);
				rotateLeft(n);
				if(g->getBalance()==-1){
					n->setBalance(0);
					c->setBalance(1);
					g->setBalance(0);
				}
				else if(g->getBalance()==0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else{
					n->setBalance(-1);
					c->setBalance(0);
					g->setBalance(0);
				}
				RemoveFix(p, ndiff);
			}

		}
		else if(n->getBalance() + diff == 1){
			n->setBalance(1);
		}
		else{
			n->setBalance(0);
			RemoveFix(p,ndiff);
		}
	}
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    //if()
    //AVLNode<Key, Value>* current_ = root_;
    //while
		int diff_ = 0;
		if(this->root_==nullptr){
		}
    else{
			AVLNode<Key, Value>* curr_ = static_cast<AVLNode<Key, Value>*>(this->root_);
    	while(curr_!=nullptr){
				if(curr_->getKey()>key){
					curr_ = curr_->getLeft();

				}
				else if(curr_->getKey()==key){
						AVLNode<Key, Value>* p;
						if(curr_->getLeft()!=nullptr && curr_->getRight()!=nullptr){
							AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(curr_));
							nodeSwap(pred,curr_);
							//std:: cout << pred->getKey() <<std::endl;
							p = curr_->getParent();
							if(p != nullptr){
								if(pred->getKey()<=p->getKey()){
									diff_ = 1;
								}
								else{
									diff_ = -1;
								}
							}
							// pointer adjust
							if(curr_->getBalance()==0){
								if(pred->getKey()<=p->getKey()){
									p->setLeft(NULL);
									delete curr_;
								}
								else{
									p->setRight(NULL);;
									delete curr_;
								}							
							}
							else if(curr_->getBalance()==1){
								if(pred->getKey()<=p->getKey()){
									p->setLeft(curr_->getRight());
									curr_->getRight()->setParent(p);
									delete curr_;
								}
								else{
									p->setRight(curr_->getRight());
									curr_->getRight()->setParent(p);
									delete curr_;
								}
							}
							else{
								if(pred->getKey()<=p->getKey()){
									p->setLeft(curr_->getLeft());
									curr_->getLeft()->setParent(p);
									delete curr_;
								}
								else{
									p->setRight(curr_->getLeft());
									curr_->getLeft()->setParent(p);
									delete curr_;
								}
							}
						}
						else{
							p = curr_->getParent();
							if(p != nullptr){
								if(curr_->getKey()<p->getKey()){
									diff_ = 1;
								}
								else{
									diff_ = -1;
								}
							}
							// pointer adjust
							if(curr_->getBalance()==0){
								if(p==nullptr){
									delete curr_;
									this->root_ = nullptr;
									break;
								}
								if(curr_->getKey()<p->getKey()){
									p->setLeft(NULL);
									delete curr_;
								}
								else{
									p->setRight(NULL);;
									//std::cout << "till" << std::endl;
									delete curr_;
								}							
							}
							else if(curr_->getBalance()==1){
								if(p==nullptr){
									this->root_ = static_cast<Node<Key, Value>*>(curr_->getRight());
									this->root_ ->setParent(NULL);
									delete curr_;	
									break;
								}
								if(curr_->getKey()<p->getKey()){
									p->setLeft(curr_->getRight());
									curr_->getRight()->setParent(p);
									delete curr_;
								}
								else{
									p->setRight(curr_->getRight());
									curr_->getRight()->setParent(p);
									delete curr_;
								}
							}
							else{
								if(p==nullptr){
									this->root_ = static_cast<Node<Key, Value>*>(curr_->getLeft());
									this->root_ ->setParent(NULL);
									delete curr_;		
									break;							
								}
								if(curr_->getKey()<p->getKey()){
									p->setLeft(curr_->getLeft());
									curr_->getLeft()->setParent(p);
									delete curr_;
								}
								else{
									p->setRight(curr_->getLeft());
									curr_->getLeft()->setParent(p);
									delete curr_;
								}
							}
						}
					//std:: cout << "till" <<std::endl;
					RemoveFix(p,diff_);
					break;
				}
				else {
					curr_ = curr_->getRight();
				}
			}
		}
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
