/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>

// Excessao usada pela classe MyVec
class MyVecException
{
private:
    std::string msg;

public:
    MyVecException(const std::string &msg0) : msg(msg0) {}

    const std::string &what() const { return msg; }
};

template <class T>
class MyVec
{
public:
    template <class T2>
    friend std::ostream &operator<<(std::ostream &, const MyVec<T2> &);

    // construtores/destrutures/etc
    MyVec();

    MyVec(int n, const T &init = T());

    // destrutor
    ~MyVec() { destroy(); };

    // Construtor de copia
    MyVec(const MyVec &);

    MyVec &operator=(const MyVec &);

    // funcoes de acesso
    T &operator[](int pos) { return data[pos]; }

    const T &operator[](int pos) const { return data[pos]; }

    void push_back(const T &);

    void resize(int newSize);

    void insert(const T &, int pos);

    void clear();

    int eraseMatchingElements(const T &elem);
    void sortedInsert(const T &elem);

    void erase(int pos);

    void empty() const { return size() == 0; };

    int size() const { return dataSize; };

private:
    T *data;          // declare o membro de dados data, que devera armazenar os elementos da lista
    int dataSize;     // quantos elementos ha na lista?
    int dataCapacity; // quantos elementos atualmente cabem na lista?

    void create();

    void destroy();

    void resizeCapacity(int newCapacity);
};

template <class T>
void MyVec<T>::erase(int pos)
{
    if (pos < 0 || pos >= dataSize)
    {
        throw MyVecException("Erro na funcao erase: posicao invalida");
    }
    for (int i = pos; i < dataSize - 1; i++)
    {
        data[i] = data[i + 1];
    }
    dataSize--;
}

// O pior caso é quando todos os elementos são iguais ao elemento a ser apagado
// Dessa forma, a complexidade é O(n^2)
// Foi realizado uma busca sequencial para encontrar os elementos iguais ao elemento a ser apagado
// Para vetores maiores, é mais eficiente ordenar o vetor e realizar uma busca binária
template <class T>
int MyVec<T>::eraseMatchingElements(const T &elem)
{
    int count = 0;
    int i = 0;
    while (i < dataSize)
    {
        if (data[i] == elem)
        {
            erase(i);
            count++;
        }
        else
        {
            i++;
        }
    }
    return count;
}

template <class T>
void MyVec<T>::sortedInsert(const T &elem)
{
    if (dataSize == dataCapacity)
    {
        resizeCapacity(dataCapacity == 0 ? dataCapacity + 1 : dataCapacity * 2);
    }
    if (dataSize == 0)
    {
        data[0] = elem;
        dataSize++;
        return;
    }
    int i;
    for (i = dataSize - 1; (i >= 0 && data[i] > elem); i--)
    {
        data[i + 1] = data[i];
    }
    data[i + 1] = elem;
    dataSize++;
}

template <class T>
void MyVec<T>::push_back(const T &elem)
{
    // Implemente esta funcao! (nao reutilize a funcao "insere")
    if (dataSize == dataCapacity)
    {
        resizeCapacity(dataCapacity == 0 ? dataCapacity + 1 : dataCapacity * 2);
    }
    data[dataSize] = elem;
    dataSize++;
}

template <class T>
void MyVec<T>::resize(int newSize)
{
    if (newSize >= dataCapacity)
    {                            // primeiro temos que realocar o vector...
        resizeCapacity(newSize); // para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
    }
    for (int i = dataSize; i < newSize; i++)
    { // preencha a parte "extra" do vector com valores "em branco"
        data[i] = T();
    }
    dataSize = newSize;
}

// insere o elemento na posicao pos e move os elementos ja presentes no vetor
//  pos pode ser:
//    uma posicao apos o final do vetor (para inserir na ultima posicao)
//    ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template <class T>
void MyVec<T>::insert(const T &elem, int pos)
{
    if (pos > dataSize || pos < 0)
    {
        throw MyVecException("Erro na funcao insert: posicao invalida");
    }

    if (dataSize == dataCapacity)
    {                          // preciso redimensionar?
        if (dataCapacity == 0) // Exercicio: Por que e' preciso testar isso?
            resizeCapacity(1);
        else
            resizeCapacity(dataCapacity * 2);
    }

    for (int i = dataSize; i > pos; i--)
        data[i] = data[i - 1];
    data[pos] = elem;
    dataSize++;
}

template <class T>
void MyVec<T>::clear()
{
    destroy();
    create();
}

template <class T>
void MyVec<T>::resizeCapacity(int newCapacity)
{
    // implemente esta funcao
    // Ela deve redimensionar o vetor de modo que ele tenha capacidade newCapacity
    // Se newCapacity for menor do que a capacidade atual voce devera ignorar a chamada a esta funcao (i.e., nunca reduziremos a capacidade do vetor)
    // Nao se esqueca de liberar (deletar) a memoria que nao for mais necessaria (para evitar vazamentos de memoria)
    // Exemplo de execucao:
    // data=[1,2,3,,], dataSize=3, dataCapacity=5 (vetor de capacidade 5, com 3 elementos ocupados)
    // se chamarmos resizeCapacity(10), os membros de dados deverao ter os seguintes valores:
    // data=[1,2,3,,,,,,,], dataSize=3, dataCapacity=10
    if (newCapacity < dataCapacity)
    {
        throw MyVecException("Erro na funcao resizeCapacity: nova capacidade menor que a atual");
    }
    T *newData = new T[newCapacity];
    for (int i = 0; i < dataSize; i++)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    dataCapacity = newCapacity;
}

template <class T>
void MyVec<T>::destroy()
{
    delete[] data;
    dataSize = dataCapacity = 0;
}

template <class T>
void MyVec<T>::create()
{
    data = NULL;
    dataSize = dataCapacity = 0;
}

template <class T>
MyVec<T>::MyVec()
{
    create();
}

template <class T>
MyVec<T>::MyVec(int n, const T &init)
{
    // Implemente esta funcao:
    // Cria um vetor de tamanho e capacidade n, onde todos os n elementos valem "init"
    create();
    data = new T[n];
    dataSize = dataCapacity = n;
    for (int i = 0; i < n; i++)
    {
        data[i] = init;
    }
}

// Construtor de copia
template <class T>
MyVec<T>::MyVec(const MyVec &other)
{
    // Implemente esta funcao
    // Dica: nao duplique codigo! (esta funcao deve ser escrita utilizando apenas 2 linhas de codigo!)
    create();
    try
    {
        *this = other;
    }
    catch (const std::exception &e)
    {
        throw MyVecException("Erro na funcao construtora de copia");
    }
}

template <class T>
MyVec<T> &MyVec<T>::operator=(const MyVec &other)
{
    if (this == &other)
        return *this;
    destroy(); // Exercicio: por que precisamos disso? Para preparar o vetor para receber os valores de other e evitar vazamento de memória
    dataCapacity = other.dataCapacity;
    dataSize = other.dataSize;
    // data = other.data; //por que nao podemos fazer isso? Como data é um ponteiro, ele aponta para o mesmo endereço de memória que other.data. Dessa forma, se alterarmos o valor de data, estaremos alterando o valor de other.data
    data = new T[dataCapacity];
    for (int i = 0; i < dataSize; i++)
        data[i] = other.data[i];
    return *this;
}

template <class T2>
std::ostream &operator<<(std::ostream &out, const MyVec<T2> &v)
{
    out << "Size: " << v.size() << "\n";
    out << "Capacity: " << v.dataCapacity << "\n";
    for (int i = 0; i < v.size(); i++)
        out << v.data[i] << " ";
    out << "\n";
    return out;
}

#endif