#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cassert>
using namespace std;


struct Pessoa {    
    string nome;
    int cpf;
};


/*
Abaixo, temos diferentes versoes do insertion sort: para ordenar inteiros e para ordenar pessoas. 
Note que boa parte do código é repetido!
*/
template <class T>
void insertionSortNome(T *v, int n) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado
        T elemInserir = v[i];
        int j = i-1;
        while(j >= 0 && elemInserir.nome < v[j].nome) { //se Pessoa não tivesse o operador < implementado, teríamos que adaptar essa parte do código para não utilizar esse operador com o tipo Pessoa (ou seja, fazendo "elemInserir.nome < v[j].nome") 
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elemInserir;
    }
}

template <class T>
void insertionSortCpf(T *v, int n) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado
        T elemInserir = v[i];
        int j = i-1;
        while(j >= 0 && elemInserir.cpf < v[j].cpf) { //se Pessoa não tivesse o operador < implementado, teríamos que adaptar essa parte do código para não utilizar esse operador com o tipo Pessoa (ou seja, fazendo "elemInserir.nome < v[j].nome") 
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elemInserir;
    }
}

/*
Implementação genérica usando templates...
*/
template <class T, class C>
void insertionSort(T *v, int n, const C &antesDe) {
    for (int i = 1; i < n; i++) {
        // o arranjo entre as posicoes [0,i) já está ordenado

        //o tipo de elemInserir é o mesmo que o armazenado em v (tipo "T"). Se v for um array de Pessoa --> T será substituido por Pessoa pelo compilador
        T elemInserir = v[i]; //esse código "se transforma em "Pessoa elemInserir = v[i];" (antes da compilação), caso o tipo de "v" seja um array de Pessoa
        int j = i-1;
        while(j >= 0 && antesDe(elemInserir,v[j]) ) { 
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = elemInserir;
    }
}

class ComparadorNome {
public:
    bool operator()(const Pessoa &a, const Pessoa &b) const { //retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        return a.nome < b.nome;
    }
};

class ComparadorCpf {
public:
    bool operator()(const Pessoa &a, const Pessoa &b) const { //retorna true se o local correto do objeto "a" for antes do local correto do objeto "b"
        return a.cpf < b.cpf;
    }
};

//Crie, abaixo, um functor comparador que, se utilizado em um método de ordenação, ordena as pessoas por CPF em ordem decrescente. Caso haja empate de CPF, as pessoas devem estar ordenadas por nome (em ordem crescente) 



int main(int argc, char**argv) {    
    Pessoa pessoas[5];
    pessoas[0].nome = "Teste da Silva"; pessoas[0].cpf = 100; 
    pessoas[1].nome = "Jacare da UFV"; pessoas[1].cpf = 100;  
    pessoas[2].nome = "Capivaristo dos Lagos"; pessoas[2].cpf = 100;  
    pessoas[3].nome = "Arthur Bernardes"; pessoas[3].cpf = 900;  
    pessoas[4].nome = "Ubirajara Fernandes Vieira"; pessoas[4].cpf = 1000;    

    cout << "ordenando pessoas por nome" << "\n";
    insertionSort(pessoas,5, ComparadorNome() );  //comente isto
    //sort(pessoas,pessoas+5,ComparadorNome() );  //descomente isto
    for(int i=0;i<5;i++) cout << pessoas[i].nome << " " << pessoas[i].cpf << "\n";

    //No exemplo abaixo, primeiro declaramos o objeto comparador e depois o passamos para a funcao (ambas as formas funcionam!)
    cout << "\nordenando pessoas por cpf" << "\n";
    ComparadorCpf compCpf; //cria um objeto que compara Pessoa por cpf
    insertionSort(pessoas,5, compCpf ); //equivalente a insertionSort(pessoas,5, ComparadorCpf() ); 
    for(int i=0;i<5;i++) cout << pessoas[i].nome << " " << pessoas[i].cpf << "\n";

    cout << "\nordenando pessoas por cpf (decrescente) e, em caso de empate, por nome (crescente)\n";
    //chame aqui o sort() do C++ com seu functor, para fazer a ordenação

    for(int i=0;i<5;i++) cout << pessoas[i].nome << " " << pessoas[i].cpf << "\n";

    return 0;
}
