#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*A biblioteca <limits.h> � uma biblioteca padr�o do C que cont�m macros para fornecer limites
para v�rios tipos de dados. Ela define constantes como INT_MAX e INT_MIN que representam o valor
m�ximo e m�nimo que um int pode armazenar. Isso pode ser �til ao escrever c�digo que precisa
lidar com limites de tipos de dados.*/

/*Uma macro � uma sequ�ncia de comandos que � substitu�da por um identificador. Elas s�o usadas
para tornar o c�digo mais leg�vel e f�cil de manter. Em C, as macros s�o definidas usando a
diretiva de pr�-processador #define. Por exemplo, voc� pode definir uma macro para calcular o
quadrado de um n�mero da seguinte maneira:

/*As macros podem parecer fun��es � primeira vista, mas h� algumas diferen�as importantes entre
elas. Uma das principais diferen�as � que as macros s�o manipuladas pelo pr�-processador, enquanto
as fun��es s�o manipuladas pelo compilador. Isso significa que, quando voc� usa uma macro, o
pr�-processador substitui a chamada da macro pelo c�digo da macro antes da compila��o. Isso pode
levar a um c�digo mais r�pido, pois n�o h� sobrecarga de chamada de fun��o, mas tamb�m pode tornar
o c�digo mais dif�cil de ler e depurar.

Outra diferen�a importante � que as macros n�o verificam tipos de dados, enquanto as fun��es o fazem.
Isso significa que voc� pode passar qualquer tipo de dado para uma macro, enquanto uma fun��o s�
aceitar� argumentos do tipo especificado. Isso pode levar a erros sutis se voc� n�o for cuidadoso
ao usar macros. Em resumo, as macros podem ser �teis em algumas situa��es, mas � importante us�-las
com cuidado e entender suas limita��es.*/

#define MAX_NOS 100

struct No {
  int vertice;
  int peso;
  struct No *prox;
};

/*Estrutura de "No", que � utilizada na implementa��o de uma lista de adjac�ncia em grafos. Aqui est�
o que cada campo significa: vertice -  � um inteiro que representa o v�rtice. peso -  � um inteiro
que representa o peso ou custo associado a uma aresta que conecta o v�rtice ao pr�ximo v�rtice. prox:
� um ponteiro para o pr�ximo n� da lista de adjac�ncia.*/

struct Grafo {
  struct No *cabeca[MAX_NOS];
  int numVertices;
};

/*Define um Grafo que possui dois campos: cabeca -  um vetor de ponteiros para n�s (ou v�rtices) do grafo,
 que representa a lista de adjac�ncias do grafo; numVertices -  um inteiro que representa o n�mero de
 v�rtices no grafo. Basicamente, cabeca armazena uma lista encadeada de v�rtices adjacentes para cada
 v�rtice do grafo. O tamanho do vetor cabeca � determinado pelo n�mero m�ximo de n�s permitidos no grafo
  (definido por MAX_NOS).*/

struct No *criarNo(int v, int p) {
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));
  novoNo->vertice = v;
  novoNo->peso = p;
  novoNo->prox = NULL;
  return novoNo;
}

/*Fun��o criarNo, que recebe dois par�metros inteiros: v e p. A fun��o aloca dinamicamente mem�ria suficiente
 para armazenar um n� (estrutura No) e preenche os campos vertice e peso do n� com os valores passados como
 argumentos. Em seguida, define o campo prox como NULL, indicando que este � o �ltimo n� da lista encadeada.
 Por fim, retorna o ponteiro para o n� rec�m-criado.*/

struct Grafo *criarGrafo(int vertices) {
  struct Grafo *grafo = (struct Grafo *)malloc(sizeof(struct Grafo));
  grafo->numVertices = vertices;

  for (int i = 0; i < vertices; i++) {
    grafo->cabeca[i] = NULL;
  }

  return grafo;
}

/*Essa parte do c�digo cria um novo grafo com o n�mero especificado de v�rtices. Ele aloca dinamicamente a
mem�ria para a estrutura do grafo e inicializa o n�mero de v�rtices com o valor passado como par�metro. Em
seguida, ele usa um loop para inicializar a cabe�a de cada lista de adjac�ncias do grafo como NULL. Isso
significa que inicialmente n�o h� v�rtices adjacentes para cada v�rtice no grafo. Por fim, a fun��o retorna
o ponteiro para a estrutura do grafo rec�m-criada.*/

void adicionarAresta(struct Grafo *grafo, int orig, int dest, int peso) {
  struct No *novoNo = criarNo(dest, peso);
  novoNo->prox = grafo->cabeca[orig];
  grafo->cabeca[orig] = novoNo;
}
/*Fun��o que adiciona uma aresta ao grafo. A fun��o recebe como entrada um ponteiro para uma estrutura de
grafo, os v�rtices de origem e destino da aresta e o peso da aresta. A fun��o cria um novo n� com o v�rtice
de destino e o peso da aresta e o adiciona � lista de adjac�ncia do v�rtice de origem. O novo n� � adicionado
no in�cio da lista, apontando para o n� anteriormente no in�cio da lista. Isso � feito atualizando o ponteiro
para o in�cio da lista para apontar para o novo n�.*/

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

/*Esta fun��o imprime um grafo. A fun��o recebe como entrada um ponteiro para uma estrutura de grafo. A fun��o
percorre a lista de adjac�ncia de cada v�rtice do grafo e imprime os v�rtices adjacentes e o peso das arestas.
Para cada v�rtice, a fun��o percorre a lista de adjac�ncia e imprime o v�rtice adjacente e o peso da aresta entre
os dois v�rtices. Isso � repetido para cada v�rtice do grafo.*/

void dijkstra(struct Grafo *grafo, int iniciar) {
  int dist[MAX_NOS];
  int visitado[MAX_NOS];

  // Inicializa as dist�ncias e a array visitada
  for (int i = 0; i < grafo->numVertices; i++) {
    dist[i] = INT_MAX;
    visitado[i] = 0;
  }

  // Seta a dist�ncia para iniciar o n� como 0
  dist[iniciar] = 0;

  // Faz um Loop atrav�s de todos os n�s
  for (int i = 0; i < grafo->numVertices - 1; i++) {
    // Encontra o n� com a dist�ncia m�nima
    int minDist = INT_MAX;
    int minIndice = -1;
    for (int j = 0; j < grafo->numVertices; j++) {
      if (!visitado[j] && dist[j] < minDist) {
        minDist = dist[j];
        minIndice = j;
      }
    }

    // Marca o n� de dist�ncia m�nima como visitado
    visitado[minIndice] = 1;

    // Atualiza as dist�ncias dos n�s adjacentes
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

  // Imprime as dist�ncias mais curtas
  printf("\nDistancias mais curtas do No %d:\n", iniciar);
  for (int i = 0; i < grafo->numVertices; i++) {
    printf("No %d: %d\n", i, dist[i]);
  }
}

/*Implementa��o do algoritmo de Dijkstra. A fun��o dijkstra recebe um ponteiro para um grafo e um n� inicial. Ela
inicializa as dist�ncias e o array de visitados, define a dist�ncia para o n� inicial como 0 e, em seguida,
percorre todos os n�s do grafo. Para cada n�, a fun��o encontra o n� com a dist�ncia m�nima, marca-o como visitado
e atualiza as dist�ncias dos n�s adjacentes. Finalmente, a fun��o imprime as dist�ncias mais curtas a partir do n�
inicial.*/

/*O algoritmo de Dijkstra para encontrar o caminho mais curto em um grafo com pesos n�o negativos. O algoritmo
come�a inicializando as dist�ncias para todos os n�s como infinito e a dist�ncia para o n� inicial como 0. Em seguida,
ele percorre todos os n�s do grafo, encontrando o n� com a dist�ncia m�nima que ainda n�o foi visitado. O algoritmo
marca esse n� como visitado e atualiza as dist�ncias dos n�s adjacentes. Isso � repetido at� que todos os n�s tenham
sido visitados. Finalmente, o algoritmo imprime as dist�ncias mais curtas para todos os n�s a partir do n� inicial.*/

/*Defini��o - O algoritmo de Dijkstra � um algoritmo de caminho m�nimo que encontra o caminho mais curto entre um n�
inicial e todos os outros n�s em um grafo com pesos positivos nas arestas. Ele funciona mantendo um conjunto de n�s
para os quais o caminho mais curto j� foi determinado e, em cada itera��o, selecionando o n� com a menor dist�ncia do
conjunto de n�s n�o visitados. Em seguida, ele atualiza as dist�ncias dos n�s adjacentes ao n� selecionado e repete o
processo at� que todos os n�s tenham sido visitados ou a menor dist�ncia entre o n� inicial e o n� final tenha sido
encontrada.*/

/*O algoritmo de Dijkstra pode ser usado em diversas aplica��es que envolvem encontrar o caminho mais curto em um grafo
 com pesos positivos nas arestas. Algumas aplica��es comuns incluem encontrar o caminho mais curto entre dois pontos em
 um mapa, encontrar a rota mais r�pida em um sistema de transporte, encontrar o caminho mais barato em uma rede de
 telecomunica��es, entre outras.*/

/*Existem v�rias implementa��es do algoritmo de Dijkstra que podem ser usadas para otimizar o desempenho do algoritmo em
diferentes situa��es. Uma implementa��o comum � usar uma fila de prioridades para armazenar os n�s n�o visitados, o que
pode reduzir o tempo de execu��o do algoritmo. Outra implementa��o � usar uma estrutura de dados chamada heap de Fibonacci,
que pode reduzir ainda mais o tempo de execu��o do algoritmo. Al�m disso, existem v�rias varia��es do algoritmo de Dijkstra
que podem ser usadas para resolver problemas espec�ficos, como o algoritmo A* para encontrar o caminho mais curto em um
espa�o de busca com heur�stica.*/

/*Uma maneira de otimizar o desempenho do algoritmo de Dijkstra � usar uma fila de prioridades para armazenar os n�s n�o
visitados. A fila de prioridades � uma estrutura de dados que armazena elementos com uma chave associada e permite a remo��o
do elemento com a menor chave em tempo constante. No caso do algoritmo de Dijkstra, a chave de cada n� � a sua dist�ncia
atual do n� inicial.

Para implementar o algoritmo de Dijkstra usando uma fila de prioridades, voc� pode seguir os seguintes passos:

Inicialize a fila de prioridades com todos os n�s do grafo, com a dist�ncia do n� inicial definida como 0 e a dist�ncia
dos outros n�s definida como infinito. Enquanto a fila de prioridades n�o estiver vazia, remova o n� com a menor dist�ncia
da fila de prioridades. Para cada n� adjacente ao n� removido, atualize a sua dist�ncia se a dist�ncia atual for maior do
que a dist�ncia do n� removido mais o peso da aresta entre eles. Atualize a posi��o do n� adjacente na fila de prioridades
para refletir a sua nova dist�ncia. Repita os passos 2-4 at� que a fila de prioridades esteja vazia ou a menor dist�ncia
entre o n� inicial e o n� final tenha sido encontrada. Usando uma fila de prioridades, o tempo de execu��o do algoritmo de
Dijkstra pode ser reduzido, tornando-o mais eficiente para resolver problemas de caminho m�nimo em grafos grandes.*/

int main() {
    struct Grafo *grafo = criarGrafo(10);

  // Exemplo: Grafo - 10 N�s - 16 arestas

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
    adicionarAresta(grafo, 0, 1, 2);
    adicionarAresta(grafo, 9, 8, 7);

    printf("Grafo resultante:\n");
    imprimirGrafo(grafo);

    dijkstra(grafo, 1);

    return 0;

/*Mais uma defini��o: O Algoritmo de Dijkstra � um algoritmo de busca em grafos utilizado para encontrar o caminho
mais curto entre um n� de origem e todos os outros n�s em um grafo ponderado. Ele � um algoritmo guloso (greedy),
ou seja, a cada passo ele
escolhe a melhor op��o localmente na esperan�a de que essa escolha leve � melhor solu��o globalmente. O algoritmo come�a
marcando a dist�ncia da origem para todos os outros v�rtices como infinito e a dist�ncia da origem para ela mesma como
zero. Em seguida, � criado um conjunto S de n�s visitados e um conjunto Q de n�s n�o visitados. A cada passo, o algoritmo
escolhe o n� em Q com a menor dist�ncia da origem e adiciona a S. Em seguida, para cada vizinho desse n� que ainda est�
em Q, o algoritmo calcula a dist�ncia at� o n� visitado e atualiza a dist�ncia armazenada se essa dist�ncia for menor do
que a dist�ncia atual armazenada. O processo � repetido at� que todos os n�s tenham sido visitados ou a menor dist�ncia
para um n� ainda em Q seja infinita.

Ao final do algoritmo, a dist�ncia m�nima da origem para cada n� � conhecida e o caminho m�nimo pode ser reconstru�do
usando as informa��es armazenadas nas dist�ncias e nos n�s predecessores. O algoritmo de Dijkstra � eficiente para grafos
com muitos v�rtices e poucas arestas, e possui uma complexidade de tempo de O(E + VlogV), onde E � o n�mero de arestas e
V � o n�mero de v�rtices.*/

}
