// hash.h
#ifndef HASH_H
#define HASH_H

// Tipos de valor suportados
typedef enum { INT, FLOAT, STRING, CHAR } ValueType;

typedef struct {
    ValueType type;
    void *data;
} Value;

// Estrutura de item da tabela hash
typedef struct {
    char *chave;
    Value value;
    int ocupado;
} HashItem;

// Estrutura do Hash_map
typedef struct {
    int tamanho;
    int quantidade_elementos;
    HashItem *tabela;
} Hash_map;

/*typedef struct{
    HashItem* tabela;
    int tamanho;
    int quantidade_elementos;
}Hash_map;

// Estrutura da tabela hash
typedef struct {
    int chave;
    int valor;
    int ocupado;  // 0 = vazio, 1 = ocupado, 2 = removido
} HashItem;*/

// Funções principais
Hash_map *hash_create(int tamanho);
void hash_insert(Hash_map *table, const char *key, Value value);
Value *hash_search(Hash_map *table, const char *key);
void hash_delete_key(Hash_map *table, const char *key);
void hash_free(Hash_map *table);

// Criação de Value genérico
Value create_int_value(int x);
Value create_float_value(float x);
Value create_char_value(char x);
Value create_string_value(const char *str);

#endif
