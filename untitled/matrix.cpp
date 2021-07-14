#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int in_array(int x, int * arr, int uzge, int kol){
    for (int i = 0; i < kol; i++){
        if (arr[uzge + i] == x)
            return 1;
    }
    return 0;
}

Matrix::Matrix(){
}

Matrix::Matrix(double a){    // единичная матрица
    a++;
    nenol = n;
    value = new int [n];
    columns = new int [n];
    rows = new int [n+1];
    for (int i = 0; i < n; i++){
        value[i] = 1;
        columns[i] = i;
        rows[i] = i;
    }
    rows[n] = n;
}

Matrix::Matrix(int x) // ввод матрицы с клавиатуры
{
    x++;
    mass = new int* [n];
    inputmass();
    for (int i=0; i<n; i++){
      for (int j=0; j<n; j++){
        cout<<mass[i][j]<<" ";
      }
      cout<<endl;
    }
    compress(mass);
}

Matrix::Matrix(string file){ // чтение матрицы из файла
    readfrom(file);
    compress(mass);
}

void Matrix::inputmass(){
  for (int i=0; i<n; i++){
    mass[i]= new int [n];
    for (int j=0; j<n; j++){
      cout<<"Is there an arc from the vertex "<<i<<" to the vertex "<<j<<"? (0/1) = ";
      cin>>mass[i][j];
      if (mass[i][j] != 0){
        nenol++;
      }
    }
  }
}

int * Matrix::getvalue(int x){
    if (x == 0)
        return value;
    else{
        return trvalue;
    }
}

int * Matrix::getcolumns(int x){
    if (x == 0)
        return columns;
    else{
        return trcolumns;
    }
}

int * Matrix::getrows(int x){
    if (x == 0)
        return rows;
    else{
        return trrows;
    }
}

int Matrix::getn(){
    return n;
}

int Matrix::getnenol(){
    return nenol;
}

void Matrix::setparams(int neno, int * va, int * col, int * ro){
    nenol = neno;
    value = new int [nenol];
    columns = new int [nenol];
    rows = new int [n+1];
    for (int i = 0; i < nenol; i ++){
        value[i] = va[i];
    }
    for (int i = 0; i < nenol; i ++){
        columns[i] = col[i];
    }
    for (int i = 0; i < n+1; i ++){
        rows[i] = ro[i];
    }
}

void Matrix::settrans(int * trva, int * trcol, int * trro){
    trvalue = new int [nenol];
    trcolumns = new int [nenol];
    trrows = new int [n+1];
    for (int i = 0; i < nenol; i ++){
        trvalue[i] = trva[i];
    }
    for (int i = 0; i < nenol; i ++){
        trcolumns[i] = trcol[i];
    }
    for (int i = 0; i < n+1; i ++){
        trrows[i] = trro[i];
    }
}

void Matrix::compress(int **matr){ // функция сжатия матрицы в формат crs
  value = new int [nenol];
  rows = new int [n+1];
  rows[0] = 0;
  columns = new int [nenol];
  int index = 0;
  int rownum = 0;
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      if (matr[i][j] != 0){
        value[index] = matr[i][j];
        columns[index] = j;
        rownum++;
        index++;
      }
    }
    rows[i+1] = rownum;
  }

  trvalue = new int [nenol];
  trrows = new int [n+1];
  trrows[0] = 0;
  trcolumns = new int [nenol];
  index = 0;
  rownum = 0;
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      if (matr[j][i] != 0){
        trvalue[index] = matr[j][i];
        trcolumns[index] = j;
        rownum++;
        index++;
      }
    }
    trrows[i+1] = rownum;
  }
}

void Matrix::readfrom(string file){
    ifstream in (file);
    if (in){
        mass = new int*[n];
        for (int i = 0; i<n; i++) mass[i] = new int[n];
        //Считаем матрицу из файла
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++){
                in >> mass[i][j];
                if (mass[i][j] != 0)
                    nenol++;
            }
        in.close();
    }
}

void Matrix::write(string file){ // запись crs в файл
    ofstream out;
    out.open(file);
    if (out.is_open())
    {
        for (int i = 0; i < nenol; i++){
            out << value[i] << ' ';
            cout << value[i] << ' ';
        }
        out << endl;
        cout << endl;
        for (int i = 0; i < nenol; i++){
            out << columns[i] << ' ';
            cout << columns[i] << ' ';
        }
        out << endl;
        cout << endl;
        for (int i = 0; i < n+1; i++){
            out << rows[i] << ' ';
            cout << rows[i] << ' ';
        }
    }
    out.close();
}

Matrix::Matrix(Matrix a, Matrix b){ // созданный экземпляр будет суммой двух других
    int nenol = (a.getnenol() + b.getnenol()) * 2;
    int *columns1, * columns2, *rows1, *rows2;
    columns = new int [nenol];
    value = new int [nenol];
    rows = new int [n + 1]; rows[0] = 0;
    columns1 = a.getcolumns(0);
    columns2 = b.getcolumns(0);
    rows1 = a.getrows(0);
    rows2 = b.getrows(0);
    int done = 0, done1 = 0, done2 = 0;
    int kol1;int kol2;

    for (int i = 1; i <= n; i++){
        kol1 = rows1[i] - rows1[i-1];
        kol2 = rows2[i] - rows2[i-1];
        int w = 0, q = 0;
        while (q < kol1 || w < kol2){
            if (w == kol2){
                value[done] = 1; columns[done] = columns1[done1+q]; q++; done++;
            }
            else if (q == kol1){
                value[done] = 1; columns[done] = columns2[done2+w]; w++; done++;
            }
            else{
                if (columns1[done1 + q] == columns2[done2 + w]){
                    value[done]=1; columns[done]=columns1[done1+q]; q++; w++; done++;
                }
                else if (columns1[done1 + q] > columns2[done2 + w]){
                    value[done] = 1; columns[done]=columns2[done2+w]; w++; done++;
                }
                else{
                    value[done] = 1; columns[done]=columns1[done1+q]; q++; done++;
                }
            }
        }
        done1 += kol1;
        done2 += kol2;
        rows[i] = done;
    }
    this->nenol = done;
}

Matrix::Matrix(Matrix a, Matrix b, int x){ // созданный экземпляр будет
    x++;                                   // произведением двух других
    int nenol = (a.getnenol() * b.getnenol());
    columns = new int [nenol] ,trcolumns = new int [nenol];
    value = new int [nenol], trvalue = new int [nenol];
    rows = new int [n + 1], trrows = new int [n + 1];
    rows[0] = 0, trrows[0] = 0;
    int *columns1, * columns2, *rows1, *rows2;
    columns1 = a.getcolumns(0);
    columns2 = b.getcolumns(1);
    rows1 = a.getrows(0);
    rows2 = b.getrows(1);
    int done1 = 0, done2 = 0, doneres = 0, doneres2 = 0;
    int kol1, kol2;

    for (int i = 1; i <= n; i++){
        kol1 = rows1[i] - rows1[i-1];
        for (int j = 1; j <= n; j++){
            kol2 = rows2[j] - rows2[j-1];
            int w = 0, q = 0;
            while (w < kol1 && q < kol2){
                if (columns1[done1 + w] == columns2[done2 + q]){
                    columns[doneres] = j-1;
                    value[doneres] = 1;
                    doneres++;
                    goto skip;
                }
                if (columns1[done1 + w] > columns2[done2 + q]) q++;
                else{
                    w++;
                }
            }
        skip:
            done2 += kol2;
        }
        done1 += kol1;
        done2 = 0;
        rows[i] = doneres;
    }
    done1 = done2 = doneres2 = 0;
    for (int i = 1; i <= n; i++){
        kol2 = rows2[i] - rows2[i-1];
        for (int j = 1; j <= n; j++){
            kol1 = rows1[j] - rows1[j-1];
            int w = 0, q = 0;
            while (q < kol1 && w < kol2){
                if (columns2[done2 + w] == columns1[done1 + q]){
                    trcolumns[doneres2] = j-1;
                    trvalue[doneres2] = 1;
                    doneres2++;
                    goto skip1;
                }
                if (columns2[done2 + w] > columns1[done1 + q]) q++;
                else{
                    w++;
                }
            }
        skip1:
            done1 += kol1;
        }
        done2 += kol2;
        done1 = 0;
        trrows[i] = doneres2;
    }
    this->nenol = doneres;
}
