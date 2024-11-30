#include <iostream>
#include <stdexcept>

using namespace std;

struct Matrix {
    int** data_ = nullptr;
    size_t n_ = 0u; // Количество столбцов
    size_t m_ = 0u; // Количество строк
};

// Создает заполненную нулями матрицу n x m.
void Construct(Matrix& out, size_t n, size_t m) {
    out.n_ = n;
    out.m_ = m;
    out.data_ = new int*[m];
    for (size_t i = 0; i < m; ++i) {
        out.data_[i] = new int[n](); // Инициализируем нулями
    }
}

// Освобождает выделенную память.
void Destruct(Matrix& in) {
    if (in.data_ != nullptr) {
        for (size_t i = 0; i < in.m_; ++i) {
            delete[] in.data_[i];
        }
        delete[] in.data_;
        in.data_ = nullptr;
    }
    in.n_ = 0;
    in.m_ = 0;
}

// Создает копию матрицы |matrix|.
Matrix Copy(const Matrix& matrix) {
    Matrix copy;
    Construct(copy, matrix.n_, matrix.m_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            copy.data_[i][j] = matrix.data_[i][j];
        }
    }
    return copy;
}

// Возвращает сумму двух матриц.
// Если операция невозможна - вернуть пустую матрицу.
Matrix Add(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return Matrix{}; // Возвращаем пустую матрицу
    }
    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return result;
}

// Возвращает разницу двух матриц.
// Если операция невозможна - вернуть пустую матрицу.
Matrix Sub(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return Matrix{};
    }
    Matrix result;
    Construct(result, a.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return result;
}

// Возвращает произведение двух матриц.
// Если операция невозможна - вернуть пустую матрицу.
Matrix Mult(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.m_) {
        return Matrix{};
    }
    Matrix result;
    Construct(result, b.n_, a.m_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < b.n_; ++j) {
            result.data_[i][j] = 0;
            for (size_t k = 0; k < a.n_; ++k) {
                result.data_[i][j] += a.data_[i][k] * b.data_[k][j];
            }
        }
    }
    return result;
}

// Транспонирование матрицы.
void Transposition(Matrix& matrix) {
    Matrix transposed;
    Construct(transposed, matrix.m_, matrix.n_);
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            transposed.data_[j][i] = matrix.data_[i][j];
        }
    }
    Destruct(matrix);
    matrix = transposed;
}

// Сравнение двух матриц.
bool operator==(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return false;
    }

    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            if (a.data_[i][j] != b.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Вывод матрицы на экран.
void PrintMatrix(const Matrix& matrix) {
    for (size_t i = 0; i < matrix.m_; ++i) {
        for (size_t j = 0; j < matrix.n_; ++j) {
            cout << matrix.data_[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << endl;
}

int main() {
    Matrix matrixA, matrixB, matrixC;
    Construct(matrixA, 3, 3);
    Construct(matrixB, 3, 3);

    // Инициализируем матрицы A и B
    for (size_t i = 0; i < matrixA.m_; ++i) {
        for (size_t j = 0; j < matrixA.n_; ++j) {
            matrixA.data_[i][j] = i + j;
            matrixB.data_[i][j] = (i + j) * i;
        }
    }

    cout << "Выберите операцию:\n";
    cout << "1: Копировать матрицу A\n";
    cout << "2: Сложить матрицы A и B\n";
    cout << "3: Вычесть матрицу B из A\n";
    cout << "4: Умножить матрицу A на B\n";
    cout << "5: Сравнить матрицы A и B\n";
    cout << "0: Выход\n";

    int x;
    cin >> x;

    switch (x) {
        case 1:
            matrixC = Copy(matrixA);
            cout << "Матрица A:\n";
            PrintMatrix(matrixA);
            cout << "Матрица B:\n";
            PrintMatrix(matrixB);
            cout << "Копия матрицы A (матрица C):\n";
            PrintMatrix(matrixC);
            Destruct(matrixA);
            Destruct(matrixB);
            Destruct(matrixC);
            break;
        case 2:
            matrixC = Add(matrixA, matrixB);
            if (matrixC.data_ != nullptr) {
                cout << "Матрица A:\n";
                PrintMatrix(matrixA);
                cout << "Матрица B:\n";
                PrintMatrix(matrixB);
                cout << "Сумма матриц A и B (матрица C):\n";
                PrintMatrix(matrixC);
                Destruct(matrixA);
                Destruct(matrixB);
                Destruct(matrixC);
            } else {
                cout << "Невозможно сложить матрицы: размеры не совпадают.\n";
                Destruct(matrixA);
                Destruct(matrixB);
            }
            break;
        case 3:
            matrixC = Sub(matrixA, matrixB);
            if (matrixC.data_ != nullptr) {
                cout << "Матрица A:\n";
                PrintMatrix(matrixA);
                cout << "Матрица B:\n";
                PrintMatrix(matrixB);
                cout << "Разность матриц A и B (матрица C):\n";
                PrintMatrix(matrixC);
                Destruct(matrixA);
                Destruct(matrixB);
                Destruct(matrixC);
            } else {
                cout << "Невозможно вычесть матрицы: размеры не совпадают.\n";
                Destruct(matrixA);
                Destruct(matrixB);
            }
            break;
        case 4:
            matrixC = Mult(matrixA, matrixB);
            if (matrixC.data_ != nullptr) {
                cout << "Матрица A:\n";
                PrintMatrix(matrixA);
                cout << "Матрица B:\n";
                PrintMatrix(matrixB);
                cout << "Произведение матриц A и B (матрица C):\n";
                PrintMatrix(matrixC);
                Destruct(matrixA);
                Destruct(matrixB);
                Destruct(matrixC);
            } else {
                cout << "Невозможно умножить матрицы: несогласованные размеры.\n";
                Destruct(matrixA);
                Destruct(matrixB);
            }
            break;
        case 5:
            if (matrixA == matrixB) {
                cout << "Матрицы A и B равны.\n";
            } else {
                cout << "Матрицы A и B не равны.\n";
            }
            Destruct(matrixA);
            Destruct(matrixB);
            break;
        case 0:
            Destruct(matrixA);
            Destruct(matrixB);
            return 0;
        default:
            cout << "Неверный вариант.\n";
            Destruct(matrixA);
            Destruct(matrixB);
            break;
    }
    return 0;
}