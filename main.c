#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*A biblioteca <limits.h> é uma biblioteca padrão do C que contém macros para fornecer limites para vários tipos de dados. Ela define constantes como INT_MAX e INT_MIN que representam o valor máximo e mínimo que um int pode armazenar. Isso pode ser útil ao escrever código que precisa lidar com limites de tipos de dados.*/

/*As macros são manipuladas pelo pré-processador, enquanto
as funções são manipuladas pelo compilador. Isso significa que, quando você usa uma macro, o pré-processador substitui a chamada da macro pelo código da macro antes da compilação. Isso pode
levar a um código mais rápido, pois não há sobrecarga de chamada de função, mas também pode tornar o código mais difícil de ler e depurar.

Outra diferença importante é que as macros não verificam tipos de dados, enquanto as funções o fazem. Isso significa que você pode passar qualquer tipo de dado para uma macro, enquanto uma função só aceitará argumentos do tipo especificado. Isso pode levar a erros sutis se você não for cuidadoso ao usar macros. Em resumo, as macros podem ser úteis em algumas situações, mas é importante usá-las com cuidado e entender suas limitações.*/

#define MAX_NOS 100

struct No {
  int vertice;
  int peso;
  struct No *prox;
};

/*Estrutura de "No", que é utilizada na implementação de uma lista de adjacência em grafos. Aqui está
o que cada campo significa: vertice -  é um inteiro que representa o vértice. peso -  é um inteiro
que representa o peso ou custo associado a uma aresta que conecta o vértice ao próximo vértice. prox:
é um ponteiro para o próximo nó da lista de adjacência.*/

struct Grafo {
  struct No *cabeca[MAX_NOS];
  int numVertices;
};

/*Define um Grafo que possui dois campos: cabeca -  um vetor de ponteiros para nós (ou vértices) do grafo,
 que representa a lista de adjacências do grafo; numVertices -  um inteiro que representa o número de
 vértices no grafo. Basicamente, cabeca armazena uma lista encadeada de vértices adjacentes para cada
 vértice do grafo. O tamanho do vetor cabeca é determinado pelo número máximo de nós permitidos no grafo
  (definido por MAX_NOS).*/

struct No *criarNo(int v, int p) {
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));
  novoNo->vertice = v;
  novoNo->peso = p;
  novoNo->prox = NULL;
  return novoNo;
}

/*Função criarNo, que recebe dois parâmetros inteiros: v e p. A função aloca dinamicamente memória suficiente
 para armazenar um nó (estrutura No) e preenche os campos vertice e peso do nó com os valores passados como
 argumentos. Em seguida, define o campo prox como NULL, indicando que este é o último nó da lista encadeada.
 Por fim, retorna o ponteiro para o nó recém-criado.*/

struct Grafo *criarGrafo(int vertices) {
  struct Grafo *grafo = (struct Grafo *)malloc(sizeof(struct Grafo));
  grafo->numVertices = vertices;

  for (int i = 0; i < vertices; i++) {
    grafo->cabeca[i] = NULL;
  }

  return grafo;
}

/*Essa parte do código cria um novo grafo com o número especificado de vértices. Ele aloca dinamicamente a
memória para a estrutura do grafo e inicializa o número de vértices com o valor passado como parâmetro. Em
seguida, ele usa um loop para inicializar a cabeça de cada lista de adjacências do grafo como NULL. Isso
significa que inicialmente não há vértices adjacentes para cada vértice no grafo. Por fim, a função retorna
o ponteiro para a estrutura do grafo recém-criada.*/

void adicionarAresta(struct Grafo *grafo, int orig, int dest, int peso) {
  struct No *novoNo = criarNo(dest, peso);
  novoNo->prox = grafo->cabeca[orig];
  grafo->cabeca[orig] = novoNo;
}
/*Função que adiciona uma aresta ao grafo. A função recebe como entrada um ponteiro para uma estrutura de
grafo, os vértices de origem e destino da aresta e o peso da aresta. A função cria um novo nó com o vértice
de destino e o peso da aresta e o adiciona à lista de adjacência do vértice de origem. O novo nó é adicionado
no início da lista, apontando para o nó anteriormente no início da lista. Isso é feito atualizando o ponteiro
para o início da lista para apontar para o novo nó.*/

void imprimirGrafo(struct Grafo *grafo) {
  printf("\nGrafo:\n");
  for (int i = 0; i < grafo->numVertices; i++) {
    struct No *temp = grafo->cabeca[i];
    printf("Vertice %d: ", i);
    while (temp != NULL) {
      printf("(%d,%d) -> ", temp->vertice, temp->peso);
      temp = temp->prox;
    }
    printf("NULL\n");
  }
}

/*Esta função imprime um grafo. A função recebe como entrada um ponteiro para uma estrutura de grafo. A função
percorre a lista de adjacência de cada vértice do grafo e imprime os vértices adjacentes e o peso das arestas.
Para cada vértice, a função percorre a lista de adjacência e imprime o vértice adjacente e o peso da aresta entre
os dois vértices. Isso é repetido para cada vértice do grafo.*/

void dijkstra(struct Grafo *grafo, int iniciar) {
  int dist[MAX_NOS];
  int visitado[MAX_NOS];

  // Inicializa as distâncias e a array visitada
  for (int i = 0; i < grafo->numVertices; i++) {
    dist[i] = INT_MAX;
    visitado[i] = 0;
  }

  // Seta a distância para iniciar o nó como 0
  dist[iniciar] = 0;

  // Faz um Loop através de todos os nós
  for (int i = 0; i < grafo->numVertices - 1; i++) {
    // Encontra o nó com a distância mínima
    int minDist = INT_MAX;
    int minIndice = -1;
    for (int j = 0; j < grafo->numVertices; j++) {
      if (!visitado[j] && dist[j] < minDist) {
        minDist = dist[j];
        minIndice = j;
      }
    }

    // Marca o nó de distância mínima como visitado
    visitado[minIndice] = 1;

    // Atualiza as distâncias dos nós adjacentes
    struct No *atualNo = grafo->cabeca[minIndice];
    while (atualNo != NULL) {
      int peso = atualNo->peso;
      int vizinho = atualNo->vertice;
      if (!visitado[vizinho] && dist[minIndice] != INT_MAX &&
          dist[minIndice] + peso < dist[vizinho]) {
        dist[vizinho] = dist[minIndice] + peso;
      }
      atualNo = atualNo->prox;
    }
  }

  // Imprime as distâncias mais curtas
  printf("\nDistancias mais curtas do No %d:\n", iniciar);
  for (int i = 0; i < grafo->numVertices; i++) {
    printf("No %d: %d\n", i, dist[i]);
  }
}

/*Implementação do algoritmo de Dijkstra. A função dijkstra recebe um ponteiro para um grafo e um nó inicial. Ela
inicializa as distâncias e o array de visitados, define a distância para o nó inicial como 0 e, em seguida,
percorre todos os nós do grafo. Para cada nó, a função encontra o nó com a distância mínima, marca-o como visitado
e atualiza as distâncias dos nós adjacentes. Finalmente, a função imprime as distâncias mais curtas a partir do nó
inicial.*/

/*O algoritmo de Dijkstra para encontrar o caminho mais curto em um grafo com pesos não negativos. O algoritmo
começa inicializando as distâncias para todos os nós como infinito e a distância para o nó inicial como 0. Em seguida,
ele percorre todos os nós do grafo, encontrando o nó com a distância mínima que ainda não foi visitado. O algoritmo
marca esse nó como visitado e atualiza as distâncias dos nós adjacentes. Isso é repetido até que todos os nós tenham
sido visitados. Finalmente, o algoritmo imprime as distâncias mais curtas para todos os nós a partir do nó inicial.*/

/*Definição - O algoritmo de Dijkstra é um algoritmo de caminho mínimo que encontra o caminho mais curto entre um nó
inicial e todos os outros nós em um grafo com pesos positivos nas arestas. Ele funciona mantendo um conjunto de nós
para os quais o caminho mais curto já foi determinado e, em cada iteração, selecionando o nó com a menor distância do
conjunto de nós não visitados. Em seguida, ele atualiza as distâncias dos nós adjacentes ao nó selecionado e repete o
processo até que todos os nós tenham sido visitados ou a menor distância entre o nó inicial e o nó final tenha sido
encontrada.*/

/*O algoritmo de Dijkstra pode ser usado em diversas aplicações que envolvem encontrar o caminho mais curto em um grafo
 com pesos positivos nas arestas. Algumas aplicações comuns incluem encontrar o caminho mais curto entre dois pontos em
 um mapa, encontrar a rota mais rápida em um sistema de transporte, encontrar o caminho mais barato em uma rede de
 telecomunicações, entre outras.*/

/*Existem várias implementações do algoritmo de Dijkstra que podem ser usadas para otimizar o desempenho do algoritmo em
diferentes situações. Uma implementação comum é usar uma fila de prioridades para armazenar os nós não visitados, o que
pode reduzir o tempo de execução do algoritmo. Outra implementação é usar uma estrutura de dados chamada heap de Fibonacci,
que pode reduzir ainda mais o tempo de execução do algoritmo. Além disso, existem várias variações do algoritmo de Dijkstra
que podem ser usadas para resolver problemas específicos, como o algoritmo A* para encontrar o caminho mais curto em um
espaço de busca com heurística.*/

/*Uma maneira de otimizar o desempenho do algoritmo de Dijkstra é usar uma fila de prioridades para armazenar os nós não
visitados. A fila de prioridades é uma estrutura de dados que armazena elementos com uma chave associada e permite a remoção
do elemento com a menor chave em tempo constante. No caso do algoritmo de Dijkstra, a chave de cada nó é a sua distância
atual do nó inicial.

Para implementar o algoritmo de Dijkstra usando uma fila de prioridades, você pode seguir os seguintes passos:

Inicialize a fila de prioridades com todos os nós do grafo, com a distância do nó inicial definida como 0 e a distância
dos outros nós definida como infinito. Enquanto a fila de prioridades não estiver vazia, remova o nó com a menor distância
da fila de prioridades. Para cada nó adjacente ao nó removido, atualize a sua distância se a distância atual for maior do
que a distância do nó removido mais o peso da aresta entre eles. Atualize a posição do nó adjacente na fila de prioridades
para refletir a sua nova distância. Repita os passos 2-4 até que a fila de prioridades esteja vazia ou a menor distância
entre o nó inicial e o nó final tenha sido encontrada. Usando uma fila de prioridades, o tempo de execução do algoritmo de
Dijkstra pode ser reduzido, tornando-o mais eficiente para resolver problemas de caminho mínimo em grafos grandes.*/

/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_VERTICES 10
#define MIN_PESO 1
#define MAX_PESO 20

int main() {
    srand(time(NULL)); // inicializa o gerador de números aleatórios

    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = i + 1; j < NUM_VERTICES; j++) {
            int peso = (rand() % (MAX_PESO - MIN_PESO + 1)) + MIN_PESO; // gera um peso aleatório entre MIN_PESO e MAX_PESO
            printf("adicionarAresta(grafo, %d, %d, %d);\n", i, j, peso);
        }
    }

    return 0;
}*/

int main() {
    struct Grafo *grafo = criarGrafo(10);

  // Exemplo: Grafo - 10 Nós - 16 arestas

    adicionarAresta(grafo, 0, 1, 3);
    adicionarAresta(grafo, 1, 2, 2);
    adicionarAresta(grafo, 1, 6, 4);
    adicionarAresta(grafo, 2, 3, 1);
    adicionarAresta(grafo, 3, 4, 10);
    adicionarAresta(grafo, 3, 5, 2);
    adicionarAresta(grafo, 4, 9, 5);
    adicionarAresta(grafo, 5, 2, 2);
    adicionarAresta(grafo, 5, 4, 1);
    adicionarAresta(grafo, 5, 9, 1);
    adicionarAresta(grafo, 6, 5, 1);
    adicionarAresta(grafo, 6, 7, 4);
    adicionarAresta(grafo, 7, 0, 5);
    adicionarAresta(grafo, 7, 8, 2);
    adicionarAresta(grafo, 8, 6, 3);
    adicionarAresta(grafo, 9, 8, 7);

    printf("Grafo resultante:\n");
    imprimirGrafo(grafo);

    dijkstra(grafo, 1);

    return 0;

/*Mais uma definição: O Algoritmo de Dijkstra é um algoritmo de busca em grafos utilizado para encontrar o caminho
mais curto entre um nó de origem e todos os outros nós em um grafo ponderado. Ele é um algoritmo guloso (greedy),
ou seja, a cada passo ele
escolhe a melhor opção localmente na esperança de que essa escolha leve à melhor solução globalmente. O algoritmo começa
marcando a distância da origem para todos os outros vértices como infinito e a distância da origem para ela mesma como
zero. Em seguida, é criado um conjunto S de nós visitados e um conjunto Q de nós não visitados. A cada passo, o algoritmo
escolhe o nó em Q com a menor distância da origem e adiciona a S. Em seguida, para cada vizinho desse nó que ainda está
em Q, o algoritmo calcula a distância até o nó visitado e atualiza a distância armazenada se essa distância for menor do
que a distância atual armazenada. O processo é repetido até que todos os nós tenham sido visitados ou a menor distância
para um nó ainda em Q seja infinita.

Ao final do algoritmo, a distância mínima da origem para cada nó é conhecida e o caminho mínimo pode ser reconstruído
usando as informações armazenadas nas distâncias e nos nós predecessores. O algoritmo de Dijkstra é eficiente para grafos
com muitos vértices e poucas arestas, e possui uma complexidade de tempo de O(E + VlogV), onde E é o número de arestas e
V é o número de vértices.*/

}
