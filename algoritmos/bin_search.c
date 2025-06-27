bin_search(int flag, int *vector, int size){
    int inicio = 0, fim = size - 1, meio;
    meio = (inicio+fim)/2;

    while(inicio <= fim){
        meio = (inicio + fim) / 2;
        if(vector[meio] == flag){
            return meio; // Retorna o índice do elemento encontrado
        } else if(vector[meio] < flag){
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1; // Busca na metade esquerda
        }
    }
    return -1;
}