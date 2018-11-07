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
  I've already defined two constants: When node hasn't parent (NOPARENT) and when node is root (NOTIMES).

  `#define NOPARENT -201`\
  `#define NOTIMES -202`

  I also propose different values, for when you need to use -201 or -202.

  `#define NOPARENT -45618540`\
  `#define NOTIMES -45093591`

### Functions
  This is the list of all the functions contained in the library.
  All functions work in the current node, unless otherwise stated.

  `friend int getNodeHeight(Tree *)`: Returns the height of node or `-1` if `node == nullptr`.

  `int const &getData()`: Returns the data.

  `int getTimes()`: Returns how many times you entered the same value in the tree. For example, if you insert the
  number `3` twice, then the node with `data = 3` also has `times = 2`.

  `bool hasParent()`: Returns if this node has parent and if parent has `times != 1`.

  `int getHeight()`: Returns height.

  `int getNumberOfChildren()`: Returns the number of total children.

  `Tree *getParent()`: Returns a pointer to the parent.

  `Tree *getLeftChild()`: Returns a pointer to the left child.

  `Tree *getRightChild()`: Returns a pointer to the right child.

  `Tree *insert(int n)`: Inserts new node with value `n`.

  `Tree *insert(Tree *&node, int n)`: Inserts new node at `node` with value `n`;

  `void updateNumberOfChidren()`: Updates the number of children in its ancestors.

  `void AVLcondition()`: Checks if sub-tree is AVL complete and rotates necesary nodes to achieve that.

  `bool isAVLComplete()`: Returns if sub-tree is AVL complete.

  `void updateHeight()`: Updates the height of its ancestors.

  `void rightRotation()`: Rotates node to the right.
  Example:
  ```
           x                   y
         /   \               /   \
        y     C     to      A     x
      /   \                     /   \
     A     B                   B     C
  ```

  `void leftRotation()`: Rotates node to the left.
  Example:
  ```
           x                      y
         /   \                  /   \
        A     y     to         x     C
            /   \            /   \
           B     C          A     B
  ```

  `Tree *find(int key)`: Returns the node with `data = key` or `nullptr` if is not present.

  `std::string pathToRoot()`: Returns the path to the root.

  `std::string longestHeight()`: Returns the longest height (path to farthest descendant).

  `std::string preOrder()`: Returns the tree in pre-order way.

  `std::string inOrder()`: Returns the tree in in-order way.

  `std::string postOrder()`: Returns the tree in post-order way.

  `std::string parents()`: Returns all nodes with it's inmediate parent.

  `std::string specs()`: Returns the following information of node:
  - Data
  - Path to root
  - Times
  - Height
  - Children
  - Left child
  - Right child
