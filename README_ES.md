# AVL Tree
Implementación de Árbol Binario de Búsqueda (ABB) auto-balanceado.

## Inicio Rápido
  Puedes crear un nuevo árbol de dos formas:
  - Árbol vacío `Tree()`
  - Árbol con nodo inicial y valor `n` `Tree(int n)`

  Y después, puedes insertar nodos en tu árbol `tree.insert(int n)`

  Para imprimir los nodos ordenados, debes usar la función `tree.inOrder()`

### Constantes
  Ya he definido dos constantes: Cuando el nodo no tiene predecesor (NOPARENT) y cuando el nodo es raíz(NOTIMES).

  `#define NOPARENT -201`
  `#define NOTIMES -202`

  Propongo además, valores diferentes, para cuando necesites usar -201 o -202.

  `#define NOPARENT -45618540`
  `#define NOTIMES -45093591`

### Funciones
  Esta es la lista de todas las funciones incluidas en la biblioteca.
  Todas las funciones trabajan en el nodo actual, a menos que se indique lo contrario.

  `int getData()`: Devuelve el dato.

  `int getTimes()`: Devuelve cuantas veces introdujiste el mismo valor en el árbol. Por ejemplo, si introdujiste el
  número `3` dos veces, entonces el nodo con `data = 3` también tiene `times = 2`.

  `bool hasParent()`: Devuelve si el nodo tiene predecesor y si su predecesor tiene `times != 1`.

  `int getHeight()`: Devuelve la altura.

  `int getNumberOfChildren()`: Devuelve el número total de sucesores.

  `Tree *getParent() const`: Devuelve un apuntador al predecesor.

  `Tree *getLeftChild() const`: Devuelve un apuntador al sucesor izquierdo.

  `Tree *getRightChild() const`: Devuelve un apuntador al sucesor derecho.

  `Tree *insert(int n)`: Inserta un nuevo nodo con valor `n`.

  `void updateNumberOfChidren()`: Actualiza el número de sucesores en el subárbol y en sus predecesores.

  `void AVLcondition()`: Revisa si el subárbol cumple con la condición AVL y rota los nodos necesarios para conseguirlo.

  `bool isAVLComplete()`: Devuelve si el subárbol cumple con la condición AVL.

  `Tree *insertLeft(int n)`: Inserta un nuevo nodo a la izquierda con el valor `n`.

  `Tree *insertRight(int n)` Inserta un nuevo nodo a la derecha con el valor `n`.

  `void updateParentHeight()`: Actualiza las alturas de todos los predecesores.

  `int updateChildrenHeight()`: Actualiza las alturas de todos los sucesores.

  `void updateHeight()`: Actualiza las alturas de los predecesores y sucesores con la ayuda de `updateParentHeight()`
  y `updateChildrenHeight()`

  `Tree *rightRotation()`: Rota el nodo a la derecha.
  Ejemplo:
  ```
           x                   y
         /   \               /   \
        y     C      a      A     x
      /   \                     /   \
     A     B                   B     C
  ```

  `Tree *leftRotation()`: Rota el nodo a la izquierda.
  Ejemplo:
  ```
           x                      y
         /   \                  /   \
        A     y      a         x     C
            /   \            /   \
           B     C          A     B
  ```

  `Tree *find(int key)`: Devuelve el nodo con `data = key` o `nullptr` si no está presente.

  `void pathToRoot()`: Imprime el camino hacia la raíz.

  `void printLongestHeight()`: Imprime la altura más grande (camino hacia el sucesor más lejano).

  `void preOrder()`: Imprime el árbol en 'pre-order'.

  `void inOrder()`: Imprime el árbol en 'in-order'.

  `void postOrder()`: Imprime el árbol en 'post-order'.

  `void parents()`: Imprime todos los nodos con su predecesor inmediato.

  `void printSpecs()`: Imprime la siguiente información del nodo:
  - Data (Dato)
  - Path to root (Ruta hacia la raíz)
  - Times (Veces que aparece)
  - Height (Altura)
  - Children (Número de sucesores)
  - Left child (Valor de nodo izquierdo)
  - Right child (Valor de nodo derecho)
