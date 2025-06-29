#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura do nó da fila
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Estrutura da fila
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

// Protótipos das funções
Queue* create_queue();
void enqueue(Queue* q, void* data);
void* dequeue(Queue* q);
int queue_size(Queue* q);
bool is_queue_empty(Queue* q);
void destroy_queue(Queue* q);

/**
 * @brief Cria e inicializa uma nova fila.
 * @return Ponteiro para a nova fila criada.
 */
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (!q) {
        perror("Falha ao alocar memória para a fila");
        exit(EXIT_FAILURE);
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Adiciona um elemento ao final da fila (enfileirar).
 * @param q Ponteiro para a fila.
 * @param data Ponteiro para o dado a ser adicionado.
 */
void enqueue(Queue* q, void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Falha ao alocar memória para o novo nó");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (is_queue_empty(q)) {
        q->front = new_node;
        q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

/**
 * @brief Remove e retorna o elemento do início da fila (desenfileirar).
 * @param q Ponteiro para a fila.
 * @return Ponteiro para o dado removido, ou NULL se a fila estiver vazia.
 */
void* dequeue(Queue* q) {
    if (is_queue_empty(q)) {
        return NULL;
    }

    Node* temp = q->front;
    void* data = temp->data;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return data;
}

/**
 * @brief Retorna o número de elementos na fila.
 * @param q Ponteiro para a fila.
 * @return O tamanho da fila.
 */
int queue_size(Queue* q) {
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

/**
 * @brief Verifica se a fila está vazia.
 * @param q Ponteiro para a fila.
 * @return true se a fila estiver vazia, false caso contrário.
 */
bool is_queue_empty(Queue* q) {
    return (q == NULL || q->size == 0);
}

/**
 * @brief Libera toda a memória alocada para a fila e seus nós.
 * @param q Ponteiro para a fila a ser destruída.
 * @note Esta função não libera a memória dos dados armazenados na fila.
 */
void destroy_queue(Queue* q) {
    if (q == NULL) {
        return;
    }
    while (!is_queue_empty(q)) {
        // A função dequeue já libera o nó (Node)
        dequeue(q);
    }
    free(q);
}