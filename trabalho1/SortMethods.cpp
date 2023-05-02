#include <algorithm>
#include "SortMethods.h"

// SortMethods::SortMethods()
// {
// }

// void SortMethods::insertionSort(int *v, int n)
// {
//     for (int i = 1; i < n; i++)
//     {
//         // o arranjo entre as posicoes [0,i) já está ordenado
//         int elemInserir = v[i];
//         int j = i - 1;
//         while (j >= 0 && v[j] > elemInserir)
//         {
//             v[j + 1] = v[j];
//             j--;
//         }
//         v[j + 1] = elemInserir;
//     }
// }

// // particiona o subvetor v[beg, ..., end - 1]
// // retorna a posição onde o pivo foi armazenado
// template <class FuncType, class T>
// int SortMethods::particiona(T *v, int beg, int end, int pivo, FuncType func)
// {
//     int valorPivo = v[pivo];
//     // colocamos o pivo temporariamente na ultima posição
//     swap(v[pivo], v[end - 1]);
//     // ao acharmos um elemento menor do que o pivo, vamos coloca-lo
//     // na posicao "pos"
//     int pos = beg;
//     for (int i = beg; i < end - 1; i++)
//     {
//         if (v[i] < valorPivo)
//         {
//             swap(v[pos], v[i]);
//             pos++;
//         }
//     }
//     // coloque o pivo depois do ultimo elemento menor que ele
//     swap(v[pos], v[end - 1]);
//     return pos;
// }
// template <class FuncType, class T>
// void SortMethods::quickSort2(T *v, int beg, int end, FuncType func)
// {
//     if (beg == end)
//         return;
//     if (end - beg <= 90)
//     {
//         insertionSort(v + beg, end - beg);
//     }
//     else
//     {
//         int pivoAleatorio = rand() % (end - beg) + beg; // escolhe um índice aleatório entre beg e end
//         int pos = particiona(v, beg, end, pivoAleatorio, func);
//         quickSort2(v, beg, pos, func);
//         quickSort2(v, pos + 1, end, func);
//     }
// }
// template <class FuncType, class T>
// int SortMethods::quickSort(T *v, int n, FuncType func)
// {
//     quickSort2(v, 0, n, func);
//     return 0;
// }
