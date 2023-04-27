using namespace std;

class SortMethods
{
public:
    template <class FuncType, class T>
    static int quickSort(T *v, int n, FuncType func);
    static void insertionSort(int *v, int n);
    template <class FuncType, class T>
    static int particiona(T *v, int beg, int end, int pivo, FuncType func);
    template <class FuncType, class T>
    static void quickSort2(T *v, int beg, int end, FuncType func);
};