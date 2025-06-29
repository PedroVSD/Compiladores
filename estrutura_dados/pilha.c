#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a estrutura do nó da pilha
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a estrutura da pilha
typedef struct Stack {
    Node* top;
    int size;
} Stack;

// Função para criar e inicializar uma nova pilha
Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) {
        perror("Falha ao alocar memória para a pilha");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    s->size = 0;
    return s;
}

// Função para verificar se a pilha está vazia
bool is_empty(Stack* s) {
    return s->size == 0;
}

// Função para obter o tamanho da pilha
int stack_size(Stack* s) {
    return s->size;
}

// Função para adicionar um elemento (push) no topo da pilha
void push(Stack* s, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Falha ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = s->top;
    s->top = new_node;
    s->size++;
}

// Função para remover e retornar o elemento (pop) do topo da pilha
int pop(Stack* s) {
    if (is_empty(s)) {
        fprintf(stderr, "Erro: Pilha vazia (underflow)\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = s->top;
    int data = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    return data;
}

// Função para liberar toda a memória alocada pela pilha
void destroy_stack(Stack* s) {
    while (!is_empty(s)) {
        pop(s);
    }
    free(s);
}

/*
// Exemplo de uso (função main)
int main() {
    Stack* minha_pilha = create_stack();

    printf("Pilha está vazia? %s\n", is_empty(minha_pilha) ? "Sim" : "Não");
    printf("Tamanho da pilha: %d\n", stack_size(minha_pilha));

    printf("\nEmpilhando 10, 20, 30...\n");
    push(minha_pilha, 10);
    push(minha_pilha, 20);
    push(minha_pilha, 30);

    printf("Pilha está vazia? %s\n", is_empty(minha_pilha) ? "Sim" : "Não");
    printf("Tamanho da pilha: %d\n", stack_size(minha_pilha));

    printf("\nDesempilhando...\n");
    printf("Elemento removido: %d\n", pop(minha_pilha));
    printf("Elemento removido: %d\n", pop(minha_pilha));

    printf("Tamanho da pilha agora: %d\n", stack_size(minha_pilha));

    printf("\nEmpilhando 40...\n");
    push(minha_pilha, 40);
    printf("Tamanho da pilha: %d\n", stack_size(minha_pilha));

    printf("Elemento removido: %d\n", pop(minha_pilha));
    printf("Elemento removido: %d\n", pop(minha_pilha));

    printf("\nLiberando a pilha...\n");
    destroy_stack(minha_pilha);

    return 0;
}
*/