#include<stdio.h>
#include<stdlib.h>

typedef struct Lista{
    int info;
    struct Lista* prox;
}listas_encadeadas;

// função de criação da lista
listas_encadeadas* criar_lista();

// função que insere elementos no início da lista
listas_encadeadas* inserir_lista(listas_encadeadas* l, int i);

//função para imprimir os itens da lista
void imprimir_lista(listas_encadeadas* l);

//função que verifica se a lista está vazia
int verifica_lista(listas_encadeadas* l);

//função que busca elementos
listas_encadeadas* busca(listas_encadeadas* l, int v);

//remoção de elementos da lista
listas_encadeadas* remover(listas_encadeadas* l, int v);

//libera a lista
void liberar(listas_encadeadas* l);


listas_encadeadas* criar_lista(){
    return NULL;
}

listas_encadeadas* inserir_lista(listas_encadeadas* l, int i){
    listas_encadeadas* novo = (listas_encadeadas*)malloc(sizeof(listas_encadeadas));
    novo->info = i;
    novo->prox = l;
    return novo;
}

void imprimir_lista(listas_encadeadas* l){
    listas_encadeadas* p;
    
    for(p = l; p != NULL; p=p->prox){
        printf("%d\n", p->info);
    }
}

int verifica_lista(listas_encadeadas *l){
    if(l == NULL){
        return 1;
    }return 0;
}

listas_encadeadas* busca(listas_encadeadas* l, int v){
    listas_encadeadas* p;

    for(p = l; p!=NULL; p=p->prox){
        if(p->info == v){
            return p;
        }
    }
    return NULL;
}

listas_encadeadas* remover(listas_encadeadas* l, int v){
    listas_encadeadas* ant = NULL; //ponteiro para o elemento anterior
    listas_encadeadas* p = l;

    while(p != NULL && p->info != v){
        ant = p;
        p = p->prox;
    }

    if(p==NULL){
        return l;
    }

    if(ant == NULL){
        //remove do início da lista
        l = p->prox;
    }else{
        //remove do meio da lista
        ant->prox = p->prox;
    }
    free(p);
    return l;
}

void liberar(listas_encadeadas* l){
    listas_encadeadas* p = l;
    while (p != NULL){
        listas_encadeadas* t = p->prox;
        free(p);
        p = t;
    }
}
