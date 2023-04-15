#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cassert>
using namespace std;


struct Pessoa {
        string nome;
        int cpf;

        bool operator<(const Pessoa &other) const { //para podermos ordenar com o algoritmo insertionSortPessoa, a classe pessoa deve ter uma função de comparação < (para que o insertion sort consiga fazer a comparacao)
            return nome < other.nome;
        }
};


void imprime(Pessoa pessoas[], int n) {
    for(int i=0;i<n;i++) cout << pessoas[i].nome << " " << pessoas[i].cpf << "\n";
}


/*
Abaixo, temos uma implementação do MergeSort
Adapte-a para que seja genérica (com templates no tipo a ser ordenado)
*/

/* Supondo que v[p...q-1] e 
v[q...r-1] estejam ordenados */
void merge(int *v, int p, int q, int r) {
    int tam = r-p;
    int *aux = new int[tam];
    int i = p; //cursor 1
    int j = q; //cursor 2
    int k = 0; //cursor para aux
    while(i < q && j < r) {
        if (v[i] < v[j])
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    }
    while(i < q)
        aux[k++] = v[i++];
    while(j < r)
        aux[k++] = v[j++];
    for(k = 0; k < tam; k++)
        v[p+k] = aux[k];    
    delete []aux;
}

/* Ordena o vetor v entre as posicoes p e r-1 */
void mergeSort(int *v, int p, int r) {
    // com um elemento, já está ordenado
    if (p < r-1) {
        int meio = (p+r) / 2;
        mergeSort(v, p, meio);
        mergeSort(v, meio, r);
        merge(v, p, meio, r); //intercala
    }
}


void mergeSort(int *v, int n) {
    //faca a alocacao aqui (apenas uma vez) e passe o array para que a versao recursiva do metodo possa utiliza-lo..
    mergeSort(v, 0, n);
}






int main(int argc, char**argv) {
    int v[] = {5,9,10,2,4};
    Pessoa pessoas[5];
    pessoas[0].nome = "Teste da Silva"; pessoas[0].cpf = 200;
    pessoas[1].nome = "Jacare da UFV"; pessoas[1].cpf = 100;
    pessoas[2].nome = "Capivaristo dos Lagos"; pessoas[2].cpf = 300;
    pessoas[3].nome = "Arthur Bernardes"; pessoas[3].cpf = 900;
    pessoas[4].nome = "Ubirajara Fernandes Vieira"; pessoas[4].cpf = 1000;

    cout << "ordenando inteiros" << "\n";
    mergeSort(v,5);
    for(int i=0;i<5;i++) cout << v[i] << "\n";

    cout << "ordenando pessoas" << "\n";
    mergeSort(pessoas,5);
    for(int i=0;i<5;i++) cout << pessoas[i].nome << " " << pessoas[i].cpf << "\n";


    return 0;
}