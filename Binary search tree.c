#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

using std::string;

template <typename T>
std::string my_to_string(const T& t) {
  return std::to_string(t);
}

template <>
std::string my_to_string(const std::string& t) {
  return "\"" + t + "\"";
}

template <typename T> struct Node {
  T element;
  int height;
  Node<T> *left;
  Node<T> *right;

  Node(T element)
      : element{element}, height{0}, left{nullptr}, right{nullptr} {}
  Node(T element, int height)
      : element{element}, height{height}, left{nullptr}, right{nullptr} {}
};

template <typename T> class Tree {
private:
  size_t m_size;
  Node<T> *m_root;

public:
  // Constructor
  Tree();

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.

  // Destructor
  ~Tree();

  // Returns a pointer to the root
  Node<T> *root();

  // Checks whether the tree is empty
  bool empty() const;

  // Returns the number of elements
  size_t size() const;

  // Returns the height of the tree
  int height() const;

  // Inserts the specified element
  void insert(T element);

  // Checks whether the container contains the specified element
  bool contains(T element) const;

  // Returns the maximum element
  T max() const;

  // Returns the minimum element
  T min() const;

  // Returns the successor of the specified element
  T successor(T element);

  // Convert each element in the tree to string in pre-order.
  string pre_order();

  // Convert each element in the tree to string in order.
  string in_order();

  // Convert each element in the tree to string in post-order.
  string post_order();

  // Returns a string equivalent of the tree
  string to_string(bool with_height = true) const {
    return m_to_string(with_height, m_root, 0);
  }

private:
  string m_to_string(bool with_height, Node<T> *node, int ident) const {
    string res;
    if (node == nullptr) {
      return res;
    }
    if (node->right != nullptr) {
      res += m_to_string(with_height, node->right, ident + 2);
    }
    for (int i = 0; i < ident; i++) {
      res += " ";
    }
    res += my_to_string(node->element);
    if (with_height) {
      res += "(h=" + my_to_string(node->height) + ")";
    }
    res += "\n";
    if (node->left != nullptr) {
      res += m_to_string(with_height, node->left, ident + 2);
    }
    return res;
  }

  // Feel free to declare helper functions here, if necessary
  void destroyTree(Node<T>* current);
  string _in_order(Node<T>* node);
  string _post_order(Node<T>* node);
  bool _insert(Node<T>*& root, const T& value);
  int balanceFactor(Node<T>* node);
  void rotateRight(Node<T>*& root);
  void rotateLeft(Node<T>*& root); 
  };

// Constructor
template <typename T> Tree<T>::Tree() : m_size(0), m_root(nullptr) {
  // TODO: Implement this method
}

// Destructor
template <typename T> Tree<T>::~Tree() {
  // TODO: Implement this method
  destroyTree(m_root);
}

// Returns a pointer to the root
template <typename T> Node<T> *Tree<T>::root() {
  // TODO: Implement this method
  if (m_root){
    return m_root;
  }
  return nullptr;
}

// Checks whether the tree is empty
template <typename T> bool Tree<T>::empty() const {
  // TODO: Implement this method
  if(m_size){
    return false;
  }
  return true;
}

// Returns the number of elements
template <typename T> size_t Tree<T>::size() const {
  // TODO: Implement this method
  return m_size;
}

// Returns the height of the tree
template <typename T> int Tree<T>::height() const {
  // TODO: Implement this method
  if(!m_root){
    return -1;
  }
  return m_root->height;
}

// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
  // TODO: Implement this method
  if (!m_root){
    m_root = new Node<T>(element);
    m_size = 1;
    m_root->height = 0;
    return;
  }

  _insert(m_root, element);

  m_size++;
  
}

// Checks whether the container contains the specified element
template <typename T> bool Tree<T>::contains(T element) const {
  // TODO: Implement this method
  if(m_size == 0){
    return false;
  }
  
  Node<T>* current = m_root;
  while(current && current->element != element ){
    if(element > current->element){
      current = current->right;
    }
    else{
      current = current->left;
    }

  }

  if(current == nullptr){
    return false;
  }

  return true;
}

// Returns the maximum element
template <typename T> T Tree<T>::max() const {
  // TODO: Implement this method
  if(!m_root){
    throw std::out_of_range("empty");
  }
  Node<T>* current = m_root;
  while(current->right){  
    current = current->right;
  }
  return current->element;
  //throw std::runtime_error("not implemented");
}

// Returns the minimum element
template <typename T> T Tree<T>::min() const {
  // TODO: Implement this method
    if(!m_root){
    throw std::out_of_range("empty");
  }
  Node<T>* current = m_root;
  while(current->left){  
    current = current->left;
  }
  return current->element;
  //throw std::runtime_error("not implemented");
}

// Returns the successor of the specified element
template <typename T> T Tree<T>::successor(T element) {
  // TODO: Implement this method
  if (empty()) {
      throw std::out_of_range("Tree is empty");
  }

  // Find the node containing the specified element
  Node<T> *current = m_root;
  while (current && current->element != element) {
    if (element < current->element) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  // If the element is not in the tree, find the smallest element greater than it
  if (!current) {
    // Initialize the successor to be null
    Node<T> *successor = nullptr;
    // Start from the root and traverse the tree
    Node<T> *currentnode = m_root;

    while (currentnode) {
      if (element < currentnode->element) {
        // If the current node's element is greater than the specified element,
        // update the successor and move to the left subtree
        successor = currentnode;
        currentnode = currentnode->left;
      } else {
        // If the current node's element is less than or equal to the specified element,
        // move to the right subtree
        currentnode = currentnode->right;
      }
    }
    // If successor is still null, throw an exception
    if (!successor) {
      throw std::out_of_range("No successor found for the given element");
    }
    // Return the element of the successor node
    return successor->element;
  }

  // If the node has a right subtree, find the leftmost node in that subtree
  if (current->right != nullptr) {
    current = current->right;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current->element;
  }

  // If the node doesn't have a right subtree, find the lowest ancestor whose left child is also an ancestor
  Node<T> *successor = nullptr;
  Node<T> *ancestor = m_root;
  while (ancestor != current) {
    if (current->element < ancestor->element) {
      successor = ancestor;
      ancestor = ancestor->left;
    } else {
      ancestor = ancestor->right;
    }
  }

  if (!successor) {
    throw std::out_of_range("No successor found for the given element");
  }

  return successor->element;
}

template <typename T>
string _pre_order(Node<T> *node) {
  return my_to_string(node->element)
    + (node->left == nullptr ? "" : " " + _pre_order(node->left))
    + (node->right == nullptr ? "" : " " + _pre_order(node->right));
}

template <typename T>
string Tree<T>::pre_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _pre_order(m_root);
}

template <typename T>
string Tree<T>::in_order() {
  // TODO: Implement this method
  if (m_root == nullptr) {
    return "";
  }
  return _in_order(m_root);
}

template <typename T>
string Tree<T>::_in_order(Node<T>* node) {
  // TODO: Implement this method

  return (node->left == nullptr ? "" : _in_order(node->left)+ " ") 
     + my_to_string(node->element)
    + (node->right == nullptr ? "" : " " + _in_order(node->right));
}

template <typename T>
string Tree<T>::post_order() {
  // TODO: Implement this method
  if (m_root == nullptr) {
    return "";
  }
  return _post_order(m_root);
}

template <typename T>
string Tree<T>::_post_order(Node<T>* node) {
  // TODO: Implement this method
  return (node->left == nullptr ? "" : _post_order(node->left)+ " ")  
    + (node->right == nullptr ? "" : _post_order(node->right) + " ")
      + my_to_string(node->element);
}

template <typename T>
void Tree<T>::destroyTree(Node<T>* current) {
  if (current) {
    destroyTree(current->left);
    destroyTree(current->right);
    delete current;
  }
}
template <typename T>
bool Tree<T>::_insert(Node<T>*& root, const T& value) {
    if (root == nullptr) {
        root = new Node<T>(value);
        return true; // Height has changed
    } else if (value < root->element) {
        if (_insert(root->left, value)) {
            root->height = 1 + std::max((root->left ? root->left->height : -1), (root->right ? root->right->height : -1));
            int balance = balanceFactor(root);
            if (balance > 1) {
                if (value < root->left->element) {
                    // Left-Left Case
                    rotateRight(root);
                } else {
                    // Left-Right Case
                    rotateLeft(root->left);
                    rotateRight(root);
                }
            }
            return true; // Height has changed
        }
    } else {
        if (_insert(root->right, value)) {
            root->height = 1 + std::max((root->left ? root->left->height : -1), (root->right ? root->right->height : -1));
            int balance = balanceFactor(root);
            if (balance < -1) {
                if (value > root->right->element) {
                    // Right-Right Case
                    rotateLeft(root);
                } else {
                    // Right-Left Case
                    rotateRight(root->right);
                    rotateLeft(root);
                }
            }
            return true; // Height has changed
        }
    }
    return false; // Height has not changed
}


template <typename T>
int Tree<T>::balanceFactor(Node<T>* node){
    int leftHeight = (node->left == nullptr) ? -1 : node->left->height;
    int rightHeight = (node->right == nullptr) ? -1 : node->right->height;
    return leftHeight - rightHeight;
}

template <typename T>
void Tree<T>::rotateLeft(Node<T>*& root) {
    Node<T>* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root->height = 1 + std::max((root->left ? root->left->height : -1), (root->right ? root->right->height : -1));
    newRoot->height = 1 + std::max((newRoot->left ? newRoot->left->height : -1), (newRoot->right ? newRoot->right->height : -1));
    root = newRoot;
}

template <typename T>
void Tree<T>::rotateRight(Node<T>*& root) {
    Node<T>* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root->height = 1 + std::max((root->left ? root->left->height : -1), (root->right ? root->right->height : -1));
    newRoot->height = 1 + std::max((newRoot->left ? newRoot->left->height : -1), (newRoot->right ? newRoot->right->height : -1));
    root = newRoot;
}

#endif
