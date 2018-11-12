# AVL Tree
Implementation of self-balanced Binary Search Tree (BST).

_Translations:_
[Español](https://github.com/halivert/avl-tree/blob/master/README_ES.md)

## Quick Start
  It uses templates.

  You can create a new Tree in two ways:
  - Empty tree `Tree<T>()`
  - Tree with initial node with value `n` `Tree<T>(T n)`

  And then, you can insert nodes in your tree `tree.insert(T n)`

  For get sorted nodes in string way, you must use the function
  `tree.inOrder()`

  If you are using a custom class or struct, you need to overload the
  binary operators (<, ==), and to have an empty constructor.

### Constants
  I've already defined two constants: When node hasn't parent (NOPARENT)
  and when node is root (NOTIMES).

  `#define NOPARENT -201`\ 
  `#define NOTIMES -202`

  I also propose different values, for when you need to use -201 or
  -202.

  `#define NOPARENT -45618540`\
  `#define NOTIMES -45093591`

### Functions
  This is the list of all the functions contained in the library. All
  functions work in the current node, unless otherwise stated.

  `friend int getNodeHeight(Tree<T> *node)`: Returns the height of node
  or `-1` if node is empty.

  `T const &getData()`: Returns the data.

  `int getTimes()`: Returns how many times you entered the same value in
  the tree. For example, if you insert the number `3` twice, then the
  node with `data = 3` also has `times = 2`.

  `bool hasParent()`: Returns true if the node isn't the root node.

  `int getHeight()`: Returns height.

  `int getNumberOfChildren()`: Returns the number of total children.

  `Tree<T> *getParent()`: Returns a pointer to the parent.

  `Tree<T> *getLeftChild()`: Returns a pointer to the left child.

  `Tree<T> *getRightChild()`: Returns a pointer to the right child.

  `Tree<T> *insert(T n)`: Inserts new node with value `n`.

  `Tree<T> *insert(Tree<T> *&node, T n)`: Inserts new node at `node`
  with value `n`;

  `Tree<T> *remove(T n)`: Removes node with value `n`.

  `Tree<T> *remove(Tree<T> *&node)`: Removes this `node`.

  `void updateNumberOfChidren()`: Updates the number of children in its
  ancestors.

  `void AVLcondition()`: Checks if the sub-tree is AVL complete and
  rotates necesary nodes to achieve that.

  `bool isAVLComplete()`: Returns true if the sub-tree is AVL complete.

  `void updateHeight()`: Updates its height and of its ancestors.

  `void rightRotation()`: Rotates the node to the right.
  Example:
  ```
           x                   y
         /   \               /   \
        y     C     to      A     x
      /   \                     /   \
     A     B                   B     C
  ```

  `void leftRotation()`: Rotates the node to the left.
  Example:
  ```
           x                      y
         /   \                  /   \
        A     y      to        x     C
            /   \            /   \
           B     C          A     B
  ```

  `Tree<T> *find(T key)`: Returns the node with `data = key` or
  `nullptr` if is not present.

  `std::string pathToRoot()`: Returns the path to the root.

  `std::string longestHeight()`: Returns the longest height (path to
  farthest descendant).

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

  `Tree<T> *findMinimum()`: Returns the minimum value in the tree.

  `Tree<T> *findMaximum()`: Returns the maximum value in the tree.

  `Tree<T> *findPredecessor()`: Returns the predecessor.

  `Tree<T> *findSuccessor()`: Returns the successor.

  `bool isLeaf()`: Returns true if the node is leaf (doesn't have
  children).

  `std::string levelOrder()`: Returns the level order tree traversal in
  a string way.

  `std::string givenLevel(int level)`: Returns the level of the tree in
  a string way.
