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


class Functor1 {
public:
    void operator()() const { 
        cout << "Ola" << endl;
    }
};

class Functor2 {
public:
    void operator()(int x) const { 
        cout << x << endl;
    }
};


class ComparadorNome {
public:
    bool operator()(const Pessoa &a, const Pessoa &b) const { //retorna true se o local correto do objeto "a" em um array ordenado for antes do local correto do objeto "b"
        return a.nome < b.nome;
    }
};

class ComparadorCpf {
public:
    bool operator()(const Pessoa &a, const Pessoa &b) const { //retorna true se o local correto do objeto "a" em um array ordenado for antes do local correto do objeto "b"
        return a.cpf < b.cpf;
    }
};


int main(int argc, char**argv) {    
    Pessoa pessoas[5];
    pessoas[0].nome = "Teste da Silva"; pessoas[0].cpf = 200; 
    pessoas[1].nome = "Jacare da UFV"; pessoas[1].cpf = 100;  
    pessoas[2].nome = "Capivaristo dos Lagos"; pessoas[2].cpf = 300;  
    pessoas[3].nome = "Arthur Bernardes"; pessoas[3].cpf = 900;  
    pessoas[4].nome = "Ubirajara Fernandes Vieira"; pessoas[4].cpf = 1000;    

    Functor1 f1; //Functors sao classes que implementam o operador () . Um objeto dessa classe pode chamar a funcao () de forma similar a uma chamada de funcao!
    Functor2 f2;
    f1(); //chama a funcao () de f1 (classe Functor1)
    f2(5); //chama a funcao () de f2 (classe Functor2). Como esssa funcao tem um parametro (x), devemos passar um inteiro na chamada!

    ComparadorNome compNome; //cria um functor da classe ComparadorNome. Note que chamadas do operador () nesse functor terao que passar dois objetos do tipo Pessoa!
    cout << compNome(pessoas[0],pessoas[1]) << endl; //imprime false, ja que "Teste da Silva" não é < "Jacare da UFV"
    cout << compNome(pessoas[1],pessoas[0]) << endl; //imprime true

    //ou seja, compNome(a,b) é equivalente a "a.nome < b.nome"

    ComparadorCpf compCpf; 
    cout << compCpf(pessoas[0],pessoas[1]) << endl; //imprime false, ja que 200 não é < 100
    cout << compCpf(pessoas[1],pessoas[0]) << endl; //imprime true

    //ou seja, compCpf(a,b) é equivalente a "a.cpf < b.cpf"

    return 0;
}