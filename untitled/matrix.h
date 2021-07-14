#ifndef MATRIX_H
#define MATRIX_H
#include <string>
using namespace std;

class Matrix
{
private:
    const int n = 4;  // здесь должна быть записана размерность матрицы
    int nenol;
    int * value, * columns, * rows, ** mass;
    int * trvalue, * trcolumns, * trrows; // tr - transposed
public:
    Matrix();
    Matrix(int x);
    Matrix(string file);
    Matrix(Matrix a, Matrix b);
    Matrix(Matrix a, Matrix b, int x);
    Matrix(double a);
    void inputmass();
    void compress(int **matr);
    void readfrom(string file);
    int * getvalue(int x);
    int * getcolumns(int x);
    int * getrows(int x);
    void setparams(int neno, int * va, int * col, int * ro);
    void settrans(int * trva, int * trcol, int * trro);
    int getn();
    int getnenol();
    void write(string file);
};

int in_array(int x, int * arr, int uzge, int kol);

#endif // MATRIX_H
