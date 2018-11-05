/* Implement AVL Tree with
 *
 * Insert & Delete
 * Min element
 * Successor & Predecessor
 */

#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

// #define NOPARENT -45618540
#define NOPARENT -201
// #define NOTIMES -45093591
#define NOTIMES -202
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

struct Tree {
  private:
    int times;
    int data;
    int height;
    int children;
    Tree *parent;
    Tree *left, *right;

  public:
    Tree(Tree *firstChild = nullptr) :
      times(NOTIMES), data(0), height(0), children(firstChild ? 1 : 0), parent(nullptr), left(firstChild), right(nullptr) {}

    Tree(int n) : times(1), data(n), height(0), children(0), parent(new Tree(this)), left(nullptr), right(nullptr) {}

    int getData() { return data; }

    int getTimes() { return times; }

    bool hasParent() { return parent ? parent->times != NOTIMES : false; }

    int getHeight() { return height; }

    int getNumberOfChildren() { return children; }

    Tree *getParent() const { return parent; }

    Tree *getLeftChild() const { return left; }

    Tree *getRightChild() const { return right; }

    Tree *insert(int n) {
      if (n < data || times == NOTIMES) {
        if (left) { return left->insert(n); }
        Tree *newNode = insertLeft(n);
        newNode->updateNumberOfChidren();
        newNode->AVLcondition();
        return newNode;
      }
      else if (n == data) {
        times++;
        return this;
      }
      else {
        if (right) { return right->insert(n); }
        Tree *newNode = insertRight(n);
        newNode->updateNumberOfChidren();
        newNode->AVLcondition();
        return newNode;
      }
      return nullptr;
    }

    void updateNumberOfChidren() {
      if (hasParent()) {
        parent->children++;
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
      int leftHeight = left ? left->height : -1;
      int rightHeight = right ? right->height : -1;
      return std::abs(leftHeight - rightHeight) <= 1;
    }

    Tree *insertLeft(int n) {
      left = new Tree(n);
      delete(left->parent);
      left->parent = this;
      if (left->hasParent()) { left->parent->updateHeight(); }
      return left;
    }

    Tree *insertRight(int n) {
      right = new Tree(n);
      delete(right->parent);
      right->parent = this;
      if (right->hasParent()) { right->parent->updateHeight(); }
      return right;
    }

    void updateParentHeight() {
      int leftHeight = left ? left->height : -1;
      int rightHeight = right ? right->height : -1;
      height = std::max(leftHeight, rightHeight) + 1;
      if (hasParent()) { parent->updateParentHeight(); }
    }

    int updateChildrenHeight() {
      int leftHeight = left ? left->updateChildrenHeight() : -1;
      int rightHeight = right ? right->updateChildrenHeight() : -1;
      return std::max(leftHeight, rightHeight) + 1;
    }

    void updateHeight() {
      updateChildrenHeight();
      updateParentHeight();
    }

    Tree *rightRotation() {
      if (left) {
        Tree *newLeft = left->right;

        left->children++;
        if (right) { left->children += right->children + 1; }
        children--;
        if (left->left) { children -= (left->left->children + 1); }

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

        right->children++;
        if (left) { right->children += left->children + 1; }
        children--;
        if (right->right) { children = children - (right->right->children + 1); }

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

    void pathToRoot() {
      printf("%d", data);
      if (hasParent()) {
        printf(" <- ");
        parent->pathToRoot();
      }
    }

    void printLongestHeight() {
      if (times != NOTIMES) printf("%d", data);
      int leftHeight = left ? left->height : -1;
      int rightHeight = right ? right->height : -1;

      if (leftHeight > rightHeight) {
        if (times != NOTIMES) printf(" -> ");
        left->printLongestHeight();
      }
      else if (right) {
        if (times != NOTIMES) printf(" -> ");
        right->printLongestHeight();
      }
    }

    void preOrder() {
      if (times != NOTIMES) { printf("%d ", data); }
      if (left) { left->preOrder(); }
      if (right) { right->preOrder(); }
    }

    void inOrder() {
      if (left) { left->inOrder(); }
      if (times != NOTIMES) { printf("%d ", data); }
      if (right) { right->inOrder(); }
    }

    void postOrder() {
      if (left) { left->postOrder(); }
      if (right) { right->postOrder(); }
      if (times != NOTIMES) { printf("%d ", data); }
    }

    void parents() {
      if (left) { left->parents(); }
      if (times != NOTIMES) { printf("%d Parent: %d\n", data, hasParent() ? parent->data : NOPARENT); }
      if (right) { right->parents(); }
    }

    void printSpecs() {
      printf("Data: %d\n", data);
      printf("Path to root: "); pathToRoot(); puts("");
      printf("Times: %d\n", times);
      printf("Height: %d\n", height);
      printf("Children: %d\n", children);
      printf("Left child: %d\n", left ? left->data : NOTIMES);
      printf("Right child: %d\n", right ? right->data : NOTIMES);
    }

};

#endif
