#include <iostream>
#include <fstream>
#include <string>
#include "matrix.h"
using namespace std;

void massofmult(Matrix mat){  // составление матрицы достижимости
    int nn = mat.getn();
    Matrix massive, edin(1.), qsum;

    massive.setparams(mat.getnenol(), mat.getvalue(0), mat.getcolumns(0), mat.getrows(0));
    massive.settrans(mat.getvalue(1), mat.getcolumns(1), mat.getrows(1));
    qsum.setparams(edin.getnenol(), edin.getvalue(0), edin.getcolumns(0), edin.getrows(0));

    for (int i = 1; i < nn - 1; i++){
        Matrix buf(massive, mat, 1);
        Matrix sum(qsum, buf);
        massive.setparams(buf.getnenol(), buf.getvalue(0), buf.getcolumns(0), buf.getrows(0));
        massive.settrans(buf.getvalue(1), buf.getcolumns(1), buf.getrows(1));
        if (i == nn -2)
            sum.write("C:\\Users\\79055\\Proga\\res.txt");
        else{
            qsum.setparams(sum.getnenol(), sum.getvalue(0), sum.getcolumns(0), sum.getrows(0));
        }
    }
}


int main() {
    Matrix ex1(1); //- ввод данных с клавиатуры
    Matrix ex2("C:\\Users\\79055\\Proga\\matrix.txt"); //- чтение из файла
    Matrix ex3(ex1, ex2);   // сумма     ex3 = ex1 + ex2
    ex3.write("C:\\Users\\79055\\Proga\\ex3.txt"); // - запись суммы в файл и вывод на экран

    Matrix ex4(ex1, ex2, 1);   // произведение    ex3 = ex1 * ex2
    ex4.write("C:\\Users\\79055\\Proga\\ex4.txt"); // - запись произведения в файл и вывод на экран

    massofmult(ex2); // - запись матрицы достижимости в файл и вывод на экран
}
