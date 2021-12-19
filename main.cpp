#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

// Функции для упрощения ввода и вывода в консоль

/**
 * Устанавливает цвет текста в консоли. Фон по умолчанию чёрный.
 * @param text_color ID цвета.
 * 6 - жёлтый
 * 7 - белый
 * 11 - светло-голубой
 */
void set_color(int text_color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Console descriptor
    SetConsoleTextAttribute(hStdOut, (WORD) (text_color));
}

void print_matrix(float **matrix, int m, int n) {

    printf("%16d", 1);
    for (int i = 2; i <= n; i++) {
        printf("%9d", i);
    }
    printf("\n");

    for (int i = 0; i < m; i++) {
        printf("%10d |", i + 1);
        for (int j = 0; j < n; j++)
            printf("%8.3f ", matrix[i][j]);
        printf("\n");
    }
}

void random_matrix(float **matrix, int m, int n) {
    srand(time(nullptr));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = static_cast <float> (rand() % 100);
}

void input_matrix(float **matrix, int m, int n) {
    srand(time(nullptr));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 10;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n = 0, m = 0;
    printf("Введите размерность матрицы A:\n");
    scanf("%d", &n);

    auto matrixA = new float*[n];
    for (int i = 0; i < n; i++)
        matrixA[i] = new float[n];

    random_matrix(matrixA, n, n);
    print_matrix(matrixA, n, n);

    printf("Введите количество столбцов матрицы B:\n");
    scanf("%d", &m);

    auto matrixB = new float*[n];
    for (int i = 0; i < n; i++)
        matrixB[i] = new float[m];

    random_matrix(matrixB, n, m);
    print_matrix(matrixB, n, m);
    return 0;
}
