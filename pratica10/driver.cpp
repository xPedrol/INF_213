#include <iostream>
#include "MyStack.h"
#include "MyQueue.h"
#include <algorithm>
using namespace std;


// Insira aqui o codigo para a etapa 1....

//Voce pode adicionar includes como o abaixo...
//#include "MyStack.h"


void etapa1() {
    MyStack<int> pilha;
    MyQueue<int> fila;
    for (int i = 0; i < 6; i++) {
        int number;
        cin >> number;
        pilha.push(number);
        fila.push(number);
    }
    for (int i = 0; i < 6; i++) {
        cout << pilha.top() << " ";
        pilha.pop();
    }
    cout << endl;
    for (int i = 0; i < 6; i++) {
        cout << fila.front() << " ";
        fila.pop();
    }
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....


void etapa2() {
    MyQueue<char> *fila;
    char chars[6] = {'(', ')', '[', ']', '{', '}'};
    string entrada;
    MyStack<char> pilha;
    cin.ignore();
    getline(cin, entrada);
    //remove string white spaces
    entrada.erase(std::remove_if(entrada.begin(), entrada.end(), ::isspace), entrada.end());
    for (char c : entrada) {
        if (c == '(' || c == '[' || c == '{') {
            pilha.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pilha.empty()) {
                cout << "Inconsistente" << endl;
                return;
            } else if ((c == ')' && pilha.top() == '(') ||
                       (c == ']' && pilha.top() == '[') ||
                       (c == '}' && pilha.top() == '{')) {
                pilha.pop();
            } else {
                cout << "Inconsistente" << endl;
                return;
            }
        }
    }

   if(pilha.empty()){
       cout << "Consistente" << endl;
    } else {
         cout << "Inconsistente" << endl;
   }
}

//---------------------------------------

// Insira aqui o codigo para a etapa 3....


//#include "MedianaLenta.h" //use essa implementacao para fazer os primeiros testes (com o calculo lento da mediana...)
//#include "Mediana.h" //descomente esta linha para utilizar sua classe mais eficiente!
void etapa3() {
    //descomente o codigo abaixo ao fazer a etapa 3
    /*Mediana mediana;

    int n,elem;
    cin >> n;
    for(int i=0;i<n;i++) {
        cin >> elem;
        mediana.insere(elem);
        cout << mediana.getMediana() << " ";
    }
    cout << endl;*/
}

//---------------------------------------




int main() {
    int etapa;
    cin >> etapa;
    switch (etapa) {
        case 1:
            cout << "Etapa 1" << endl;
            etapa1();
            break;
        case 2:
            cout << "Etapa 2" << endl;
            etapa2();
            break;
        case 3:
            cout << "Etapa 3" << endl;
            etapa3();
            break;
    }
}