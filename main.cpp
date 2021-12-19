#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

void set_color(int text_color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Console descriptor
    SetConsoleTextAttribute(hStdOut, (WORD) (text_color));
}

static void input(int min, int max, int &k) {
    k = max + 1;
    do {
        set_color(6);
        printf("> ");
        set_color(7);
        scanf("%d", &k);
    } while (k > max || k < min);
}

void print_matrix(double **matrix, int m, int n) {

    set_color(11);
    printf("%7d", 1);
    for (int i = 2; i <= n; i++) {
        printf("%9d", i);
    }
    printf("\n");

    for (int i = 0; i < m; i++) {
        set_color(11);
        printf("%2d |", i + 1);
        set_color(7);
        for (int j = 0; j < n; j++)
            printf("%8.3f ", matrix[i][j]);
        printf("\n");
    }
}

void random_matrix(double **matrix, int m, int n) {
    srand(time(nullptr));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = static_cast <double> (rand() % 100);
}

void input_matrix(double **matrix, int m, int n) {
    srand(time(nullptr));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%f", &matrix[i][j]);
}

double determinant(double **matrix, int n) {
    double temp;
    double determinant = 1;

    auto **tempMatrix = new double *[n];
    for (int i = 0; i < n; i++) {
        tempMatrix[i] = new double[n];
        for (int j = 0; j < n; j++)
            tempMatrix[i][j] = matrix[i][j];
    }

    // Приводим матрицу к верхне-треугольному виду
    for (int k = 0; k < n; k++)
        for (int i = k + 1; i < n; i++) {
            temp = tempMatrix[i][k] / tempMatrix[k][k];
            for (int j = 0; j < n; j++)
                tempMatrix[i][j] -= tempMatrix[k][j] * temp;
        }

    for (int i = 0; i < n; i++) {
        determinant *= tempMatrix[i][i];
        delete[] tempMatrix[i];
    }

    delete[] tempMatrix;
    return determinant;
}

double **inverse_matrix(double **matrix, int n) {
    double temp;

    auto **tempMatrix = new double *[n];
    auto **resultMatrix = new double *[n];

    for (int i = 0; i < n; i++) {
        tempMatrix[i] = new double[n];
        resultMatrix[i] = new double[n];

        for (int j = 0; j < n; j++) {
            tempMatrix[i][j] = matrix[i][j];
            resultMatrix[i][j] = i == j;
        }
    }

    // Приводим исходную матрицу к верхне-треугольному виду
    for (int k = 0; k < n; k++)
        for (int i = k + 1; i < n; i++) {
            temp = tempMatrix[i][k] / tempMatrix[k][k];
            for (int j = 0; j < n; j++) {
                tempMatrix[i][j] -= tempMatrix[k][j] * temp;
                resultMatrix[i][j] -= resultMatrix[k][j] * temp;
            }
        }

    // Приводим исходную матрицу к виду диагональной матрицы
    for (int k = n - 1; k >= 0; k--)
        for (int i = k - 1; i >= 0; i--) {
            temp = tempMatrix[i][k] / tempMatrix[k][k];
            for (int j = n - 1; j >= 0; j--) {
                tempMatrix[i][j] -= tempMatrix[k][j] * temp;
                resultMatrix[i][j] -= resultMatrix[k][j] * temp;
            }
        }

    // Приводим исходную матрицу к единичной
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++)
            resultMatrix[i][k] /= tempMatrix[i][i];
        tempMatrix[i][i] /= tempMatrix[i][i];
    }

    for (int i = 0; i < n; i++)
        delete[] tempMatrix[i];

    delete[] tempMatrix;

    return resultMatrix;
}

double **matrix_multiplication(double **a, double **b, int an, int am, int bn, int bm) {
    auto resultMatrix = new double *[an];
    for (int i = 0; i < an; i++)
        resultMatrix[i] = new double[bm];

    if (am != bn)
        throw exception();

    for (int i = 0; i < an; i++) {
        for (int j = 0; j < bm; j++) {
            resultMatrix[i][j] = 0;
            for (int h = 0; h < am; h++)
                resultMatrix[i][j] += a[i][h] * b[h][j];
        }
    }

    return resultMatrix;
}

double **matrix_sum(double **a, double **b, int n, int m) {
    auto resultMatrix = new double *[n];
    for (int i = 0; i < n; i++)
        resultMatrix[i] = new double[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            resultMatrix[i][j] = a[i][j] + b[i][j];

    return resultMatrix;
}

double **matrix_difference(double **a, double **b, int n, int m) {
    auto resultMatrix = new double *[n];
    for (int i = 0; i < n; i++)
        resultMatrix[i] = new double[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            resultMatrix[i][j] = a[i][j] - b[i][j];

    return resultMatrix;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n = 0, m = 0, temp = 0;
    set_color(12);
    printf("Введите размерность матрицы A (Диапазон значений [1, 15]):\n");
    set_color(7);
    input(1, 15, n);

    auto matrixA = new double *[n];
    for (int i = 0; i < n; i++)
        matrixA[i] = new double[n];

    set_color(12);
    printf("\nЗначения элементов матрицы A:\n");
    set_color(7);
    printf("1. Случайным образом.\n");
    printf("2. Вручную с клавиатуры.\n");
    input(1, 2, temp);

    if (temp == 1)
        random_matrix(matrixA, n, n);
    else
        input_matrix(matrixA, n, n);

    set_color(12);
    printf("\nВведите количество столбцов матрицы B (Диапазон значений [1, 15]):\n");
    set_color(7);
    input(1, 15, m);

    auto matrixB = new double *[n];
    for (int i = 0; i < n; i++)
        matrixB[i] = new double[m];

    set_color(12);
    printf("\nЗначения элементов матрицы B:\n");
    set_color(7);
    printf("1. Случайным образом.\n");
    printf("2. Вручную с клавиатуры.\n");
    input(1, 2, temp);

    if (temp == 1)
        random_matrix(matrixB, n, m);
    else
        input_matrix(matrixB, n, m);

    set_color(12);
    printf("\nМатрица A:\n");
    set_color(7);
    print_matrix(matrixA, n, n);

    set_color(12);
    printf("\nМатрица B:\n");
    set_color(7);
    print_matrix(matrixB, n, m);

    set_color(12);
    printf("\ndet(A) =");
    set_color(7);
    printf(" %0.3lf\n", determinant(matrixA, n));

    set_color(12);
    printf("\nМатрица, обратная матрице A:\n");
    set_color(7);
    double **inversedA = inverse_matrix(matrixA, n);
    print_matrix(inversedA, n, n);

    set_color(12);
    printf("\nМатрица X, соответствующая условию X = A^-1 * B:\n");
    set_color(7);
    double **matrixX = matrix_multiplication(inversedA, matrixB, n, n, n, m);
    print_matrix(matrixX, n, m);

    set_color(11);
    printf("\n---={ Проверки }=---\n");

    set_color(12);
    printf("\nA*X:\n");
    set_color(7);
    double** a_multiplied_by_x = matrix_multiplication(matrixA, matrixX, n, n, n, m);
    print_matrix(a_multiplied_by_x, n, m);

    set_color(12);
    printf("\nA*X-B:\n");
    set_color(7);
    print_matrix(matrix_difference(a_multiplied_by_x, matrixB, n, m), n, m);

    set_color(12);
    printf("\nA*A^-1:\n");
    set_color(7);
    print_matrix(matrix_multiplication(matrixA, inversedA, n, n, n, n), n, m);

    set_color(12);
    printf("\nA^-1*A:\n");
    set_color(7);
    print_matrix(matrix_multiplication(inversedA, matrixA, n, n, n, n), n, m);

    set_color(14);
    printf("\nС наступающим");
    set_color(10);
    printf(" новым");
    set_color(13);
    printf(" 2022");
    set_color(11);
    printf(" годом!!!");

    for (int i = 0; i < n; i++) {
        delete[] matrixA[i];
        delete[] matrixB[i];
        delete[] matrixX[i];
        delete[] inversedA[i];
        delete[] a_multiplied_by_x[i];
    }

    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixX;
    delete[] inversedA;
    delete[] a_multiplied_by_x;
    return 0;
}
