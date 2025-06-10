//include "hash.h"
//Criação da lib de hash para o compilador
#define TAM 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


Hash_map *criarHashMap(int tamanho);
unsigned int hash(const char *str, int tamanho);
Value *createIntValue(int x);
Value *createFloatValue(float x);
Value *createStringValue(char *str);
Value *createCharValue(char x);
void insereHashMap(Hash_map *hash_map, const char *chave, Value value);
int buscaTabela(Hash_map *hash_map, const char *chave);
void removeHashMap(Hash_map *hash_map, const char *chave);
void liberaHashMap(Hash_map *hash_map);

int main(){


    return 0;
}


// Nao precisa passar o TAM como parâmetro é constante global
//Hash de tamanho dinamico, tentei fazer como o C++
Hash_map *criarHashMap(int tamanho) {
    Hash_map *hash_map = (Hash_map *)malloc(sizeof(Hash_map));
    hash_map->tamanho = tamanho;
    hash_map->quantidade_elementos = 0;
    hash_map->tabela = (HashItem *)malloc(tamanho * sizeof(HashItem));

    for (int i = 0; i < tamanho; i++) {
        hash_map->tabela[i].ocupado = 0; // Marca como vazio
    }

    return hash_map;
}

/*int hash(int chave){
    return chave % TAM; // Função de hash simples
}*/
//A função abaixo é uma função de hash simples que usa o algoritmo djb2, pesquisei sobre e vi que era uma boa função de hash e evita colisões
unsigned int hash(const char *str, int tamanho) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c usando shift
    }

    return hash % tamanho; // Retorna o índice dentro do tamanho da tabela
    
}

//Criando hashs de tipos direfentes
//Int
Value *createIntValue(int x){
    Value *value = (Value *)malloc(sizeof(Value));
    value->type = INT;
    value->data = malloc(sizeof(int));
    *(int *)(value->data) = x;
    return value;
}
//Float
Value *createFloatValue(float x){
    Value *value = (Value *)malloc(sizeof(Value));
    value->type = FLOAT;
    value->data = malloc(sizeof(float));
    *(float *)(value->data) = x;
    return value;
}
//String
Value *createStringValue(char *str){
    Value *value = (Value *)malloc(sizeof(Value));
    value->type = STRING;
    value->data = malloc(strlen(str) + 1); // +1 para o terminador nulo
    strcpy((char *)(value->data), str);
    return value;
}
//Char
Value *createCharValue(char x){
    Value *value = (Value *)malloc(sizeof(Value));
    value->type = CHAR;
    value->data = malloc(sizeof(char));
    *(char *)(value->data) = x;
    return value;
}

//Funções da API da HASH

//Inserção de valores
void insereHashMap(Hash_map *hash_map, const char *chave, Value value) {
    unsigned int index = hash(chave, hash_map->tamanho);
    while (hash_map->tabela[index].ocupado == 1) { // Enquanto a posição estiver ocupada
        if (strcmp(hash_map->tabela[index].chave, chave) == 0) {
            // Se a chave já existe, atualiza o valor
            hash_map->tabela[index].value = value;
            return;
        }
        index = (index + 1) % hash_map->tamanho; // Proximo índice
    }
    // Insere o novo item
    hash_map->tabela[index].chave = strdup(chave); // Duplica a string da chave
    hash_map->tabela[index].value = value;
    hash_map->tabela[index].ocupado = 1; // Marca como ocupado
    hash_map->quantidade_elementos++;
}

/*A função abaio é uma busca mais simples usando vetor
void insereTabela(int valor, int tabela[]){
    int id = hash(valor);
    while(tabela[id] != -1){ // Encontra uma posição livre
        id = (id + 1) % TAM; // Passa para a próxima posição
    }
    tabela[id] = valor; // Insere o valor na tabela
}*/

int buscaTabela(Hash_map *hash_map, const char *chave) {
    unsigned int index = hash(chave, hash_map->tamanho);
    unsigned int start_index = index;
    while (hash_map->tabela[index].ocupado) {
        if (strcmp(hash_map->tabela[index].chave, chave) == 0) {
            // Retorna o valor se encontrado (ajuste o tipo de retorno conforme necessário)
            return 1; // Encontrado
        }
        index = (index + 1) % hash_map->tamanho;
        if (index == start_index) {
            break; // Evita loop infinito
        }
    }
    return 0; // Não encontrado
}

void removeHashMap(Hash_map *hash_map, const char *chave) {
    unsigned int index = hash(chave, hash_map->tamanho);
    while (hash_map->tabela[index].ocupado) {
        if (strcmp(hash_map->tabela[index].chave, chave) == 0) {
            // Marca como removido
            hash_map->tabela[index].ocupado = 2; // Marca como removido
            hash_map->quantidade_elementos--;
            return;
        }
        index = (index + 1) % hash_map->tamanho;
    }
}

void liberaHashMap(Hash_map *hash_map) {
    for (int i = 0; i < hash_map->tamanho; i++) {
        if (hash_map->tabela[i].ocupado == 1) {
            free(hash_map->tabela[i].chave); // Libera a chave
            free(hash_map->tabela[i].value.data); // Libera o valor
        }
    }
    free(hash_map->tabela);
    free(hash_map);
}