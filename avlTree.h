#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#define NOPARENT -201
#define NOTIMES -202

#include <algorithm>
#include <sstream>
#include <string>

template <typename T>
class Tree {
  private:
    int times, height, numberOfChildren;
    T data;
    Tree *parent;
    Tree *left, *right;

  public:
    Tree(Tree *firstChild = nullptr) :
      times(NOTIMES), height(0), numberOfChildren(firstChild ? 1 : 0), data(T()),
      parent(nullptr), left(firstChild), right(nullptr) {}

    Tree(T n) :
      times(1), height(0), numberOfChildren(0), data(n),
      parent(new Tree(this)), left(nullptr), right(nullptr) {}

    template <typename S>
    friend int getNodeHeight(Tree<S> *node);

    T const &getData();
    int getTimes();
    bool hasParent();
    int getHeight();
    int getNumberOfChildren();

    Tree<T> *getParent();
    Tree<T> *getLeftChild();
    Tree<T> *getRightChild();
    Tree<T> *insert(T n);
    Tree<T> *insert(Tree<T> *&node, T n);

    void updateNumberOfChidren();

    void AVLcondition();
    bool isAVLComplete();
    void updateHeight();
    void rightRotation();
    void leftRotation();

    Tree<T> *find(T key);

    std::string pathToRoot();
    std::string longestHeight();
    std::string preOrder();
    std::string inOrder();
    std::string postOrder();
    std::string parents();
    std::string specs();

};

template <typename S>
int getNodeHeight(Tree<S> *node) {
  if (node) { return node->height; }
  return -1;
}

template <typename T>
T const &Tree<T>::getData() { return data; }

template <typename T>
int Tree<T>::getTimes() { return times; }

template <typename T>
bool Tree<T>::hasParent() { return parent ? parent->times != NOTIMES : false; }

template <typename T>
int Tree<T>::getHeight() { return getNodeHeight(this); }

template <typename T>
int Tree<T>::getNumberOfChildren() { return numberOfChildren; }

template <typename T>
Tree<T> *Tree<T>::getParent() { return parent; }

template <typename T>
Tree<T> *Tree<T>::getLeftChild() { return left; }

template <typename T>
Tree<T> *Tree<T>::getRightChild() { return right; }

template <typename T>
Tree<T> *Tree<T>::insert(T n) {
  Tree<T> **ptr, *ptrParent;
  if (times == NOTIMES) {
    if (left) { ptr = &left; }
    else { return insert(left, n); }
  }
  else ptr = &parent;

  for (ptrParent = *ptr; (*ptr)->hasParent(); ptr = &(*ptr)->parent);

  while (*ptr) {
    ptrParent = *ptr;
    if (n < (*ptr)->data) {
      ptr = &(*ptr)->left;
    }
    else if (n == (*ptr)->data) {
      (*ptr)->times++;
      return *ptr;
    }
    else {
      ptr = &(*ptr)->right;
    }
  }

  return ptrParent->insert(*ptr, n);
}

template <typename T>
Tree<T> *Tree<T>::insert(Tree<T> *&node, T n) {
  node = new Tree<T>(n);
  delete(node->parent);
  node->parent = this;
  if (node->hasParent()) { node->parent->updateHeight(); }
  node->updateNumberOfChidren();
  node->AVLcondition();
  return node;
}

template <typename T>
void Tree<T>::updateNumberOfChidren() {
  if (hasParent()) {
    parent->numberOfChildren++;
    parent->updateNumberOfChidren();
  }
}

template <typename T>
void Tree<T>::AVLcondition() {
  Tree *ptr = this;

  while (ptr->hasParent()) {
    ptr = ptr->parent;

    if (!ptr->isAVLComplete()) {
      int rotation = 0;
      int leftHeight = getNodeHeight(ptr->left);
      int rightHeight = getNodeHeight(ptr->right);

      if (leftHeight > rightHeight) {
        leftHeight = getNodeHeight(ptr->left->left);
        rightHeight = getNodeHeight(ptr->left->right);
        if (rightHeight > leftHeight) { rotation = 1; }
        else if (leftHeight > rightHeight) { rotation = 2; }
      }
      else if (rightHeight > leftHeight) {
        leftHeight = getNodeHeight(ptr->right->left);
        rightHeight = getNodeHeight(ptr->right->right);
        if (leftHeight > rightHeight) { rotation = 3; }
        else if (rightHeight > leftHeight) { rotation = 4; }
      }

      switch (rotation) {
        case 1:
          if (ptr->left) { ptr->left->leftRotation(); }
        case 2:
          ptr->rightRotation();
          break;
        case 3:
          if (ptr->right) { ptr->right->rightRotation(); }
        case 4:
          ptr->leftRotation();
          break;
      }
    }
  }
}

template <typename T>
bool Tree<T>::isAVLComplete() {
  return std::abs(getNodeHeight(left) - getNodeHeight(right)) <= 1;
}

template <typename T>
void Tree<T>::updateHeight() {
  Tree<T> *ptr = this;

  ptr->height = std::max(getNodeHeight(ptr->left), getNodeHeight(ptr->right)) + 1;
  while (ptr->hasParent()) {
    ptr = ptr->parent;
    ptr->height = std::max(getNodeHeight(ptr->left), getNodeHeight(ptr->right)) + 1;
  }
}

template <typename T>
void Tree<T>::rightRotation() {
  if (left) {
    Tree *newLeft = left->right;

    left->numberOfChildren++;
    if (right) { left->numberOfChildren += right->numberOfChildren + 1; }
    numberOfChildren--;
    if (left->left) { numberOfChildren -= (left->left->numberOfChildren + 1); }

    if (parent) {
      if (parent->left == this) { parent->left = left; }
      if (parent->right == this) { parent->right = left; }
    }

    left->parent = parent;
    left->right = this;
    parent = left;

    left = newLeft;
    if (left) left->parent = this;

    updateHeight();
  }
}

template <typename T>
void Tree<T>::leftRotation() {
  if (right) {
    Tree *newRight = right->left;

    right->numberOfChildren++;
    if (left) { right->numberOfChildren += left->numberOfChildren + 1; }
    numberOfChildren--;
    if (right->right) { numberOfChildren = numberOfChildren - (right->right->numberOfChildren + 1); }

    if (parent) {
      if (parent->right == this) { parent->right = right; }
      if (parent->left == this) { parent->left = right; }
    }

    right->parent = parent;
    right->left = this;
    parent = right;

    right = newRight;
    if (right) right->parent = this;

    updateHeight();
  }
}

template <typename T>
Tree<T> *Tree<T>::find(T key) {
  Tree<T> *ptr = times == NOTIMES ? left : this;

  while (ptr) {
    if (key < ptr->data) { ptr = ptr->left; }
    else if (key == ptr->data) { break; }
    else { ptr = ptr->right; }
  }

  return ptr;
}

template <typename T>
std::string Tree<T>::pathToRoot() {
  std::stringstream ss("");
  for (Tree<T> *ptr = this; ptr; ) {
    ss << ptr->data;
    if (ptr->hasParent()) {
      ss << " -> ";
      ptr = ptr->getParent();
    }
    else break;
  }
  return ss.str();
}

template <typename T>
std::string Tree<T>::longestHeight() {
  std::stringstream ss;
  if (times != NOTIMES) ss << data;
  int leftHeight = getNodeHeight(left);
  int rightHeight = getNodeHeight(right);

  if (leftHeight > rightHeight) {
    if (times != NOTIMES) ss << " -> ";
    ss << left->longestHeight();
  }
  else if (right) {
    if (times != NOTIMES) ss << " -> ";
    ss << right->longestHeight();
  }
  return ss.str();
}

template <typename T>
std::string Tree<T>::preOrder() {
  std::stringstream ss;
  if (times != NOTIMES) { ss << data << ' '; }
  if (left) { ss << left->preOrder(); }
  if (right) { ss << right->preOrder(); }
  return ss.str();
}

template <typename T>
std::string Tree<T>::inOrder() {
  std::stringstream ss;
  if (left) { ss << left->inOrder(); }
  for (int i = 0; i < times; i++) { ss << data << ' '; }
  if (right) { ss << right->inOrder(); }
  return ss.str();
}

template <typename T>
std::string Tree<T>::postOrder() {
  std::stringstream ss;
  if (left) { ss << left->postOrder(); }
  if (right) { ss << right->postOrder(); }
  if (times != NOTIMES) { ss << data << ' '; }
  return ss.str();
}

template <typename T>
std::string Tree<T>::parents() {
  std::stringstream ss;
  if (left) { ss << left->parents(); }
  if (times != NOTIMES) {
    ss << data;
    if (hasParent()) ss << " parent: " << parent->getData() << '\n';
    else ss << " is root\n";
  }
  if (right) { ss << right->parents(); }
  return ss.str();
}

template <typename T>
std::string Tree<T>::specs() {
  if (times == NOTIMES) { return ""; }
  std::stringstream ss("");
  ss << "Data: " << data << '\n';
  ss << "Path to root: " << pathToRoot() << '\n';
  ss << "Times: " << times << '\n';
  ss << "Height: " << height << '\n';
  ss << "Children: " << numberOfChildren << '\n';
  if (left) { ss << "Left child: " << left->data << '\n'; }
  if (right) { ss << "Right child: " << right->data << '\n'; }
  return ss.str();
}

#endif
