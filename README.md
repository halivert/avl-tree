# AVL Tree
Implementation of self-balanced Binary Search Tree (BST).

_Translations:_ [Español](https://github.com/halivert/avl-tree/blob/master/README_ES.md)

## Quick Start
  You can create a new Tree in two ways:
  - Empty tree `Tree()`
  - Tree with initial node with value `n` `Tree(int n)`

  And then, you can insert nodes in your tree `tree.insert(int n)`

  For print sorted nodes, you must use the function `tree.inOrder()`

### Constants
  I've already defined two constants: When node hasn't predecessor (NOPARENT) and when node is root (NOTIMES).

  `#define NOPARENT -201`
  `#define NOTIMES -202`

  I also propose different values, for when you need to use -201 or -202.

  `#define NOPARENT -45618540`
  `#define NOTIMES -45093591`

### Functions
  This is the list of all the functions contained in the library.
  All functions work in the current node, unless otherwise stated.

  `int getData()`: Returns the data.

  `int getTimes()`: Returns how many times you entered the same value in the tree. For example, if you insert the
  number `3` twice, then the node with `data = 3` also has `times = 2`.

  `bool hasParent()`: Returns if this node has predecessor and if predecessor has `times != 1`.

  `int getHeight()`: Returns height.

  `int getNumberOfChildren()`: Returns the number of total successors.

  `Tree *getParent() const`: Returns a pointer to the predecessor.

  `Tree *getLeftChild() const`: Returns a pointer to the left successor.

  `Tree *getRightChild() const`: Returns a pointer to the right successor.

  `Tree *insert(int n)`: Inserts new node with value `n`.

  `void updateNumberOfChidren()`: Updates the number of successors in the subtree and in predecessors.

  `void AVLcondition()`: Checks if subtree is AVL complete and rotates necesary nodes to achieve that.

  `bool isAVLComplete()`: Returns if subtree is AVL complete.

  `Tree *insertLeft(int n)`: Inserts new node at left with value `n`.

  `Tree *insertRight(int n)` Inserts new node at right with value `n`.

  `void updateParentHeight()`: Updates heights for all predecessors.

  `int updateChildrenHeight()`: Updates heights for all successors.

  `void updateHeight()`: Updates heights for predecessors and successors with help of `updateParentHeight()` and
  `updateChildrenHeight()`

  `Tree *rightRotation()`: Rotates node to the right.
  Example:
  ```
           x                   y
         /   \               /   \
        y     C     to      A     x
      /   \                     /   \
     A     B                   B     C
  ```

  `Tree *leftRotation()`: Rotates node to the left.
  Example:
  ```
           x                      y
         /   \                  /   \
        A     y     to         x     C
            /   \            /   \
           B     C          A     B
  ```

  `Tree *find(int key)`: Returns the node with `data = key` or `nullptr` if is not present.

  `void pathToRoot()`: Print the path to the root.

  `void printLongestHeight()`: Print the longest height (path to farthest successor).

  `void preOrder()`: Prints the tree in pre-order way.

  `void inOrder()`: Prints the tree in in-order way.

  `void postOrder()`: Prints the tree in post-order way.

  `void parents()`: Prints all nodes with it's inmediate predecessor.

  `void printSpecs()`: Prints the following information of node:
  - Data
  - Path to root
  - Times
  - Height
  - Children
  - Left child
  - Right child
