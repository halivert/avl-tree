# AVL Tree
Implementación de Árbol Binario de Búsqueda (ABB) auto-balanceado.

## Inicio Rápido
  Puedes crear un nuevo árbol de dos formas:
  - Árbol vacío `Tree()`
  - Árbol con nodo inicial y valor `n` `Tree(int n)`

  Y después, puedes insertar nodos en tu árbol `tree.insert(int n)`

  Para imprimir los nodos ordenados, debes usar la función `tree.inOrder()`

### Constantes
  Ya he definido dos constantes: Cuando el nodo no tiene padre (NOPARENT) y cuando el nodo es raíz(NOTIMES).

  `#define NOPARENT -201`\
  `#define NOTIMES -202`

  Propongo además, valores diferentes, para cuando necesites usar -201 o -202.

  `#define NOPARENT -45618540`\
  `#define NOTIMES -45093591`

### Funciones
  Esta es la lista de todas las funciones incluidas en la biblioteca.
  Todas las funciones trabajan en el nodo actual, a menos que se indique lo contrario.

  `friend int getNodeHeight(Tree *)`: Devuelve la altura del nodo o `-1` si `node == nullptr`.

  `int const &getData()`: Devuelve el dato.

  `int getTimes()`: Devuelve cuantas veces introdujiste el mismo valor en el árbol. Por ejemplo, si introdujiste el
  número `3` dos veces, entonces el nodo con `data = 3` también tiene `times = 2`.

  `bool hasParent()`: Devuelve si el nodo tiene padre y si su padre tiene `times != 1`.

  `int getHeight()`: Devuelve la altura.

  `int getNumberOfChildren()`: Devuelve el número total de hijos.

  `Tree *getParent()`: Devuelve un apuntador al padre.

  `Tree *getLeftChild()`: Devuelve un apuntador al hijo izquierdo.

  `Tree *getRightChild()`: Devuelve un apuntador al hijo derecho.

  `Tree *insert(int n)`: Inserta un nuevo nodo con valor `n`.

  `Tree *insert(Tree *&node, int n)`: Inserta un nuevo nodo en `nodo` con valor `n`;

  `void updateNumberOfChidren()`: Actualiza el número de hijos en sus ancestros.

  `void AVLcondition()`: Revisa si el subárbol cumple con la condición AVL y rota los nodos necesarios para conseguirlo.

  `bool isAVLComplete()`: Devuelve si el subárbol cumple con la condición AVL.

  `void updateHeight()`: Actualiza la altura de sus ancestros.

  `void rightRotation()`: Rota el nodo a la derecha.
  Ejemplo:
  ```
           x                   y
         /   \               /   \
        y     C      a      A     x
      /   \                     /   \
     A     B                   B     C
  ```

  `void leftRotation()`: Rota el nodo a la izquierda.
  Ejemplo:
  ```
           x                      y
         /   \                  /   \
        A     y      a         x     C
            /   \            /   \
           B     C          A     B
  ```

  `Tree *find(int key)`: Devuelve el nodo con `data = key` o `nullptr` si no está presente.

  `std::string pathToRoot()`: Devuelve el camino hacia la raíz.

  `std::string longestHeight()`: Devuelve la altura más grande (camino hacia el descendiente más lejano).

  `std::string preOrder()`: Devuelve el árbol en 'pre-order'.

  `std::string inOrder()`: Devuelve el árbol en 'in-order'.

  `std::string postOrder()`: Devuelve el árbol en 'post-order'.

  `std::string parents()`: Devuelve todos los nodos con su padre inmediato.

  `std::string specs()`: Devuelve la siguiente información del nodo:
  - Data (Dato)
  - Path to root (Ruta hacia la raíz)
  - Times (Veces que aparece)
  - Height (Altura)
  - Children (Número de hijos)
  - Left child (Valor de nodo izquierdo)
  - Right child (Valor de nodo derecho)
