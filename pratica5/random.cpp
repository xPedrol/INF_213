#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
int random_number(int x, int y) {

    int rand_num = rand(); // número aleatório gerado pela função rand()

    // transformação linear para o intervalo [x,y]
    rand_num = x + (rand_num % (y - x + 1));

    return rand_num;
}
int main(){
    srand(time(NULL));
    cout << random_number(1, 10) << endl;
    return 0;
}