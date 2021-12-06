/*
��������� �����������

����������� ��������� ��� ������ � ���������� ��������. ��������� ������ ���������:
1. ���������, ����������� �������.
2. ������� ��� ���������� ���������� ������� ������������ n*n ������������ ������������������� �� 1 �� n*n ����� ����� �� �������� �����. �� ������� n=4:
4 3 2 1
5 10 11 12
6 9 14 13
7 8 15 16

n=5:
5 4 3 2 1
6 13 14 15 16
7 12 19 18 17
8 11 20 23 24
9 10 21 22 25

3. ������� ��� ���������� ���������� ������� ������������ n*n ����� �����.
4. ������� ������ ������� � ���� (� ���� �������).
5. ������� ���������� �������� �������.
6. ������� ��������� ������.

*/

#include <fstream>

typedef double elem;

struct Matrix {

    // �������� ������ � ������, ���� �� ������� ������ �������������
    explicit Matrix(int n) :arr(nullptr), n(n) {
        arr = new elem * [n];
        for (int i = 0; i < n; i++) {
            arr[i] = new elem[n];
            for (int j = 0; j < n; j++)
                arr[i][j] = 0;
        }
    }

    Matrix(const elem** initial_array, int n):arr(nullptr),n(n) {
        setMatrix(initial_array, n);
    }

    Matrix(const elem* initial_array, int n):arr(nullptr),n(n) {
        setMatrix(initial_array, n);
    }

    void initSpiral() {
        int k = 1;

        for (int i = 0; i < n - 1; i += 2) { // ����� ������� �������������� ������
            
            for (int j = n - 1; j >= i; j--) { // ��� �� ������� �����
                arr[i][j] = k++;
            }
            
            for (int j = i + 1; j < n; j++) { // ��� �� ������� ����
                arr[j][i] = k++;
            }
            
            // ��� ����� ���� ������
            for (int j = n-1; j > i; j--) { // ��� �� ������� ����
                arr[j][i+1] = k++;
            }
            
            // ��� ������
            for (int j = i+2; j < n; j++) {
                arr[i+1][j] = k++;
            }

        }
        if (n % 2 != 0) { // ����� ������� ��������, ����� ���������� ��������� �����
            arr[n - 1][n - 1] = k;
        }
    }

    void setMatrix(const elem** initial_array, int m) {
        if (m > 16 || m < 4) throw "Matrix dimensions should be in range 4<=n<=16!";
        n = m;

        if (arr != nullptr)
            delete[] arr;

        arr = new elem* [n];
        for (int i = 0; i < n; i++) {
            arr[i] = new elem[n];
            for (int j = 0; j < n; j++)
                arr[i][j] = initial_array[i][j];
        }
    }

    void setMatrix(const elem* initial_array, int m) {
        if (m > 16 || m < 4) throw "Matrix dimensions should be in range 4<=n<=16!";
        n = m;

        if (arr != nullptr)
            delete[] arr;

        arr = new elem * [n];
        for (int i = 0; i < n; i++) {
            arr[i] = new elem[n];
            for (int j = 0; j < n; j++)
                arr[i][j] = initial_array[i * n + j];
        }
    }

    // ������� ��������� ������
    Matrix operator*(const Matrix& mat2) {

        if (n != mat2.n) {
            throw "dimensions are unequal!";
        }

        Matrix sum(n);

        for(int i=0;i<n;i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) 
                    sum.arr[i][j] += arr[i][k] * mat2.arr[k][j];
    
        return sum;
    }

    // �������������� ����� � �������� A[p][q]
    Matrix getCofactor(int p, int q)
    {
        Matrix temp(n-1);

        int i = 0, j = 0;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                if (row != p && col != q)
                {
                    temp.arr[i][j++] = arr[row][col];

                    if (j == n - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }

        return temp;
    }

    // ������� ������������
    double determinant()
    {

        if (n == 1)
            return arr[0][0];

        int sign = 1;

        double D = 0;
        for (int f = 0; f < n; f++)
        {
            Matrix temp = getCofactor(0, f);
            D += sign * arr[0][f] * temp.determinant();

            // terms are to be added with alternate sign
            sign = -sign;
        }

        return D;
    }

    // �������� ����������������� ������� �������������� ����������
    Matrix adjoint()
    {
        Matrix adj(n);
        if (n == 1)
        {
            adj.arr[0][0] = 1;
            return adj;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                // �������� ������� ��������������� ���������� ��� �������� A[i][j]
                Matrix temp = getCofactor(i, j);

                if ((i + j) % 2 == 0) {
                    adj.arr[j][i] = temp.determinant();
                }
                else {
                    adj.arr[j][i] = -temp.determinant();
                }
            }

        return adj;
    }

    // �������� �������� �������
    Matrix Inverse()
    {

        double det = determinant();
        if (det == 0)
        {
            throw "Singular matrix, can't find its inverse";
        }

        Matrix adj = adjoint();

        Matrix inverse(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                inverse.arr[i][j] = adj.arr[i][j] / det;

        return inverse;
    }

private:
    elem** arr;
    int n;

    friend std::fstream& operator << (std::fstream& out, const Matrix& mat);
    friend std::ostream& operator << (std::ostream& out, const Matrix& mat);
};

std::ostream& operator << (std::ostream& out, const Matrix& mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            out << mat.arr[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

std::fstream& operator << (std::fstream& out, const Matrix& mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            out << mat.arr[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

int main()
{
    elem identity[] = {
        1,0,0,0,0,
        0,1,0,0,0,
        0,0,1,0,0,
        0,0,0,1,1,
        0,0,0,0,1
    };

    elem random[] = {
        1,2,3,4,0,
        0,1,2,3,0,
        9,10,29,30,0,
        -5,-6,-7,1,1,
        0,0,0,0,1
    };

    Matrix Iden(identity, 5);
    Matrix Rand(random, 5);

    // ��������� ���� out.txt ��� ������ ����������
    std::fstream file("out.txt", std::ios::out | std::ios::trunc);

    file << "Identity:\n" << Iden;
    file << "Random:\n" << Rand;

    file << "Identity*Random:\n" << (Iden*Rand);
    file << "Random*Identity:\n" << (Rand*Iden);
    file << "Identity*Identity:\n" << (Iden * Iden);
    file << "Random*Random:\n" << (Rand * Rand);

    Rand.initSpiral();
    file << "Spiral:\n" << Rand;

    file << "Inverse for identity:\n" << Iden.Inverse();
    file << "Inverse for Spiral:\n" << Rand.Inverse();

    file << "(Inverse for Spiral)*Spiral:\n" << Rand.Inverse() * Rand;
    file << "Spiral*(Inverse for Spiral):\n" << Rand * Rand.Inverse();

    return 0;
}