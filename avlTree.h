#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#define NOPARENT -201
#define NOTIMES -202

#include <algorithm>
#include <sstream>
#include <string>

struct Tree {
  private:
    int times, data, height, numberOfChildren;
    Tree *parent;
    Tree *left, *right;

  public:
    Tree(Tree *firstChild = nullptr) :
      times(NOTIMES), data(0), height(0), numberOfChildren(firstChild ? 1 : 0),
      parent(nullptr), left(firstChild), right(nullptr) {}

    Tree(int n) :
      times(1), data(n), height(0), numberOfChildren(0),
      parent(new Tree(this)), left(nullptr), right(nullptr) {}

    friend int getNodeHeight(Tree *);

    int getData() { return data; }

    int getTimes() { return times; }

    bool hasParent() { return parent ? parent->times != NOTIMES : false; }

    int getHeight() { return getNodeHeight(this); }

    int getNumberOfChildren() { return numberOfChildren; }

    Tree *getParent() const { return parent; }

    Tree *getLeftChild() const { return left; }

    Tree *getRightChild() const { return right; }

    Tree *insert(int n) {
      if (n < data || times == NOTIMES) {
        if (left) { return left->insert(n); }
        return insert(left, n);
      }
      else if (n == data) {
        times++;
        return this;
      }
      else {
        if (right) { return right->insert(n); }
        return insert(right, n);
      }
      return nullptr;
    }

    Tree *insert(Tree *&tree, int n) {
      tree = new Tree(n);
      delete(tree->parent);
      tree->parent = this;
      if (tree->hasParent()) { tree->parent->updateHeight(); }
      tree->updateNumberOfChidren();
      tree->AVLcondition();
      return tree;
    }

    void updateNumberOfChidren() {
      if (hasParent()) {
        parent->numberOfChildren++;
        parent->updateNumberOfChidren();
      }
    }

    void AVLcondition() {
      Tree *ptr = this;

      while (ptr->hasParent()) {
        ptr = ptr->parent;

        if (!ptr->isAVLComplete()) {
          int rotation = 0;
          int leftHeight = ptr->left ? ptr->left->height : -1;
          int rightHeight = ptr->right ? ptr->right->height : -1;

          if (leftHeight > rightHeight) {
            leftHeight = ptr->left->left ? ptr->left->left->height : -1;
            rightHeight = ptr->left->right ? ptr->left->right->height : -1;
            if (leftHeight > rightHeight) { rotation = 1; }
            else if (rightHeight > leftHeight) { rotation = 2; }
          }
          else if (rightHeight > leftHeight) {
            leftHeight = ptr->right->left ? ptr->right->left->height : -1;
            rightHeight = ptr->right->right ? ptr->right->right->height : -1;
            if (leftHeight > rightHeight) { rotation = 3; }
            else if (rightHeight > leftHeight) { rotation = 4; }
          }

          switch (rotation) {
            case 2:
              if (ptr->left) { ptr->left->leftRotation(); }
            case 1:
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

    bool isAVLComplete() {
      return std::abs(getNodeHeight(left) - getNodeHeight(right)) <= 1;
    }

    void updateHeight() {
      height = std::max(getNodeHeight(left), getNodeHeight(right)) + 1;
      if (hasParent()) { parent->updateHeight(); }
    }

    Tree *rightRotation() {
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
      }

      updateHeight();
      return this;
    }

    Tree *leftRotation() {
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
      }

      updateHeight();
      return this;
    }

    Tree *find(int key) {
      if (key < data or times == NOTIMES) {
        if (left) { return left->find(key); }
        return nullptr;
      }

      if (key == data) { return this; }

      if (key > data) {
        if (right) { return right->find(key); }
        return nullptr;
      }

      return nullptr;
    }

    std::string pathToRoot() {
      std::stringstream ss("");
      ss << data;
      if (hasParent()) {
        ss << " <- ";
        ss << parent->pathToRoot();
      }
      return ss.str();
    }

    std::string printLongestHeight() {
      std::stringstream ss;
      if (times != NOTIMES) ss << data;
      int leftHeight = getNodeHeight(left);
      int rightHeight = getNodeHeight(right);

      if (leftHeight > rightHeight) {
        if (times != NOTIMES) ss << " -> ";
        ss << left->printLongestHeight();
      }
      else if (right) {
        if (times != NOTIMES) ss << " -> ";
        ss << right->printLongestHeight();
      }
      return ss.str();
    }

    std::string preOrder() {
      std::stringstream ss;
      if (times != NOTIMES) { ss << data << ' '; }
      if (left) { ss << left->preOrder(); }
      if (right) { ss << right->preOrder(); }
      return ss.str();
    }

    std::string inOrder() {
      std::stringstream ss;
      if (left) { ss << left->inOrder(); }
      if (times != NOTIMES) { ss << data << ' '; }
      if (right) { ss << right->inOrder(); }
      return ss.str();
    }

    std::string postOrder() {
      std::stringstream ss;
      if (left) { ss << left->postOrder(); }
      if (right) { ss << right->postOrder(); }
      if (times != NOTIMES) { ss << data << ' '; }
      return ss.str();
    }

    std::string parents() {
      std::stringstream ss;
      if (left) { ss << left->parents(); }
      if (times != NOTIMES) { ss << data << " Parent: " << (hasParent() ? parent->data : NOPARENT) << '\n'; }
      if (right) { ss << right->parents(); }
      return ss.str();
    }

    std::string specs() {
      if (times == NOTIMES) { return ""; }
      std::stringstream ss("");
      ss << "Data: " << data << '\n';
      ss << "Path to root: " << pathToRoot() << '\n';
      ss << "Times: " << times << '\n';
      ss << "Height: " << height << '\n';
      ss << "Children: " << numberOfChildren << '\n';
      ss << "Left child: " << (left ? left->data : NOTIMES) << '\n';
      ss << "Right child: " << (right ? right->data : NOTIMES) << '\n';
      return ss.str();
    }

};

int getNodeHeight(Tree *node) {
  if (node != nullptr) { return node->height; }
  return -1;
}

#endif
