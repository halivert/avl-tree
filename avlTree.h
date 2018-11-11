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

    ~Tree() {}

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
    Tree<T> *remove(T n);
    Tree<T> *remove(Tree<T> *&node);

    void updateNumberOfChidren(bool inserted = true);

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

    Tree<T> *findMinimum();
    Tree<T> *findMaximum();
    Tree<T> *findPredecessor();
    Tree<T> *findSuccessor();

    bool isLeaf();
    std::string levelOrder();
    std::string givenLevel(int level);

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
Tree<T> *Tree<T>::remove(T n) {
  Tree<T> **ptr, **ptrParent;
  if (times == NOTIMES) {
    if (left) { ptr = &left; }
    else { return insert(left, n); }
  }
  else ptr = &parent;

  for (ptrParent = ptr; (*ptr)->hasParent(); ptr = &(*ptr)->parent);

  while (*ptr) {
    ptrParent = ptr;
    if (n < (*ptr)->data) {
      ptr = &(*ptr)->left;
    }
    else if (n == (*ptr)->data) {
      if ((*ptr)->times > 1) {
        (*ptr)->times--;
        return *ptr;
      }
      ptrParent = &(*ptr)->parent;
      return (*ptrParent)->remove(*ptr);
    }
    else {
      ptr = &(*ptr)->right;
    }
  }

  return nullptr;
}

template <typename T>
Tree<T> *Tree<T>::remove(Tree<T> *&node) {
  Tree<T> *successor, *predecessor;
  if (left != node and right != node) return nullptr;
  bool leftChild = left and left == node;

  if (node->isLeaf()) {
    if (leftChild) {
      delete(left);
      left = nullptr;
    }
    else {
      delete(right);
      right = nullptr;
    }
    updateHeight();
    updateNumberOfChidren(false);
    AVLcondition();
    return this;
  }

  successor = node->findSuccessor();
  predecessor = node->findPredecessor();

  /*
  if (successor) {
    Tree<T> *successorParent;
    successor->left = node->left;
    if (node->right != successor) {
      successor->right = node->right;
      successorParent = successor->parent;
    }
    successor->parent = this;

    if (leftChild) left = successor;
    else right = successor;

    if (successorParent) {
      if (successorParent->left == successor) successorParent->left = nullptr;
      if (successorParent->right == successor) successorParent->right = nullptr;

      successorParent->updateHeight();
      successorParent->updateNumberOfChidren(false);
      successorParent->AVLcondition();
    }
  }
  else if (predecessor) {
    Tree<T> *predecessorParent;
    if (node->left != predecessor) {
      predecessor->left = node->left;
      predecessorParent = predecessor->parent;
    }
    predecessor->right = node->right;
    predecessor->parent = this;

    if (leftChild) left = predecessor;
    else right = predecessor;

    if (predecessorParent) {
      if (predecessorParent->left == predecessor) predecessorParent->left = nullptr;
      if (predecessorParent->right == predecessor) predecessorParent->right = nullptr;

      predecessorParent->updateHeight();
      predecessorParent->updateNumberOfChidren(false);
      predecessorParent->AVLcondition();
    }
  }

  delete(node);
  */
  return this;
}

template <typename T>
void Tree<T>::updateNumberOfChidren(bool inserted) {
  Tree<T> *ptr = this;
  if (!inserted) { ptr->numberOfChildren--; }
  while (ptr->hasParent()) {
    ptr = ptr->parent;
    ptr->numberOfChildren += inserted ? 1 : -1;
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
        else { rotation = 2; }
      }
      else if (rightHeight > leftHeight) {
        leftHeight = getNodeHeight(ptr->right->left);
        rightHeight = getNodeHeight(ptr->right->right);
        if (leftHeight > rightHeight) { rotation = 3; }
        else { rotation = 4; }
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
  std::stringstream ss;
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
  std::stringstream ss;
  ss << "Data: " << data << '\n';
  ss << "Path to root: " << pathToRoot() << '\n';
  ss << "Times: " << times << '\n';
  ss << "Height: " << height << '\n';
  ss << "Children: " << numberOfChildren << '\n';
  if (left) { ss << "Left child: " << left->data << '\n'; }
  if (right) { ss << "Right child: " << right->data << '\n'; }
  Tree<T> *pred = findPredecessor();
  Tree<T> *succ = findSuccessor();
  if (pred) { ss << "Predecessor: " << pred->data << '\n'; }
  if (succ) { ss << "Successor: " << succ->data << '\n'; }
  return ss.str();
}

template <typename T>
Tree<T> *Tree<T>::findMinimum() {
  Tree<T> *ptr = times == NOTIMES ? left : this;
  while (ptr->left) { ptr = ptr->left; }
  return ptr;
}

template <typename T>
Tree<T> *Tree<T>::findMaximum() {
  Tree<T> *ptr = times == NOTIMES ? left : this;
  while (ptr->right) { ptr = ptr->right; }
  return ptr;
}

template <typename T>
Tree<T> *Tree<T>::findPredecessor() {
  Tree<T> *ptr = times == NOTIMES ? left : this;
  if (ptr->left) { return ptr->left->findMaximum(); }

  Tree<T> *ptrParent = ptr->parent;
  while (ptrParent and (ptrParent->left == ptr)) {
    ptr = ptrParent;
    ptrParent = ptr->parent;
  }

  if (!ptrParent) return nullptr;
  return ptrParent->times != NOTIMES ? ptrParent : nullptr;
}

template <typename T>
Tree<T> *Tree<T>::findSuccessor() {
  Tree<T> *ptr = times == NOTIMES ? left : this;
  if (ptr->right) { return ptr->right->findMinimum(); }

  Tree<T> *ptrParent = ptr->parent;
  while (ptrParent and (ptrParent->right == ptr)) {
    ptr = ptrParent;
    ptrParent = ptr->parent;
  }

  if (!ptrParent) return nullptr;
  return ptrParent->times != NOTIMES ? ptrParent : nullptr;
}

template <typename T>
bool Tree<T>::isLeaf() {
  return !left and !right;
}

template <typename T>
std::string Tree<T>::levelOrder() {
  Tree<T> *ptr = times == NOTIMES ? left : this;
  std::stringstream ss;
  for (int i = 0; i <= ptr->height; i++) {
    ss << ptr->givenLevel(i + 1) << '\n';
  }
  return ss.str();
}

template <typename T>
std::string Tree<T>::givenLevel(int level) {
  std::stringstream ss;
  if (level == 1) {
    ss << data << ' ';
  }
  else {
    if (left) ss << left->givenLevel(level - 1);
    if (right) ss << right->givenLevel(level - 1);
  }
  return ss.str();
}

#endif
