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
Abaixo, temos diferentes versoes do insertion sort: para ordenar inteiros e para ordenar pessoas. 
Note que boa parte do código é repetido!
*/
void insertionSortInteiros(int *v, int n) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado
        int elemInserir = v[i];
        int j = i-1;
        while(j >= 0 && elemInserir < v[j]) { //Estamos utilizando o operador < (em vez do >), pois assim é mais fácil de pensar na solução destes exercícios
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elemInserir;
    }
}

void insertionSortPessoa(Pessoa *v, int n) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado
        Pessoa elemInserir = v[i];
        int j = i-1;
        while(j >= 0 && elemInserir < v[j]) { //se Pessoa não tivesse o operador < implementado, teríamos que adaptar essa parte do código para não utilizar esse operador com o tipo Pessoa (ou seja, fazendo "elemInserir.nome < v[j].nome") 
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elemInserir;
    }
}




/*
Implementação genérica usando templates...
*/
template <class T>
void insertionSort(T *v, int n) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado

        //o tipo de elemInserir é o mesmo que o armazenado em v (tipo "T"). Se v for um array de Pessoa --> T será substituido por Pessoa pelo compilador
        T elemInserir = v[i]; //esse código "se transforma em "Pessoa elemInserir = v[i];" (antes da compilação), caso o tipo de "v" seja um array de Pessoa
        int j = i-1;
        while(j >= 0 && elemInserir < v[j] ) { 
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elemInserir;
    }
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
    insertionSort(v,5);
    for(int i=0;i<5;i++) cout << v[i] << "\n";

    cout << "ordenando pessoas" << "\n";
    insertionSort(pessoas,5);
    for(int i=0;i<5;i++) cout << pessoas[i].nome << " " << pessoas[i].cpf << "\n";


    return 0;
}