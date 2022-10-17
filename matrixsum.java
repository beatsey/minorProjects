/*
Реализовать консольное приложение, которое имеет примитивный текстовый интерфейс и меню,
состоящее как минимум из четырех пунктов:
* Ввод исходных данных, как вручную,  так и сгенерированных случайным образом
* Выполнение алгоритма по заданию
* Вывод результата
* Завершение работы программы

Входные данные: две квадратные матрицы одинакового размера, значение которого также вводит пользователь.
Результат работы алгоритма: сумма матриц и значение ее определителя.

Особые указания: В работе можно использовать только массивы! Результат не может быть выведен без обработки введённых данных.
Вывод результата не может быть осуществлен без выполнения алгоритма.
При вводе новых данных результаты выполнения алгоритма "сбрасываются".
Варианты заданий, где указан массив слов подразумевают, что разделителями для слов являются пробельные символы и знаки препинания.
* */

import java.util.Scanner;
import java.util.Random;

public class Main {
    static long det(long mat[][], int n)
    {
        int D = 0;
        if (n == 1)
            return mat[0][0];
        long temp[][] = new long[n][n];
        int sign = 1;
        for (int f = 0; f < n; f++) {
            getCofactor(mat, temp, 0, f, n);
            D += sign * mat[0][f] * det(temp, n - 1);
            sign = -sign;
        }

        return D;
    }
    static void getCofactor(long mat[][], long temp[][], int p, int q, int n)
    {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != p && col != q) {
                    temp[i][j++] = mat[row][col];
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }

    public static void main(String[] args) {


        /*
            Ввод исходных данных, как вручную,  так и сгенерированных случайным образом
            Выполнение алгоритма по заданию
            Вывод результата
            Завершение работы программы
        * */

        Scanner sc = new Scanner(System.in);
        long[][] A = {};
        long[][] B = {};
        long[][] C = {};
        int n = 1;
        int readystate = 0;

        while(true) {

            System.out.println("1) Ввод исходных данных");
            System.out.println("2) Выполнение алгоритма по заданию (сумма и определитель)");
            System.out.println("3) Вывод результата");
            System.out.println("4) Завершение работы программы");

            int res = sc.nextInt();
            if (res < 1 || res > 4){
                System.out.println("Некорректный ввод. Введите 1, 2, 3 или 4.");
                continue;
            }
            if (res == 1) {
                System.out.println("Размер матриц n=");
                n = sc.nextInt();
                A = new long[n][n];
                B = new long[n][n];

                while (true) {
                    System.out.println("1) Вручную");
                    System.out.println("2) Случайным образом");
                    System.out.println("3) Назад");
                    res = sc.nextInt();

                    if (res == 1) {
                        System.out.println("Введите элементы матрицы A=");
                        for (int i = 0; i < n; i++)
                            for (int j = 0; j < n; j++)
                                A[i][j] = sc.nextInt();

                        System.out.println("Введите элементы матрицы B=");
                        for (int i = 0; i < n; i++)
                            for (int j = 0; j < n; j++)
                                B[i][j] = sc.nextInt();
                    } else if (res == 2) {
                        Random rand = new Random();
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < n; j++) {
                                A[i][j] = rand.nextInt();
                                B[i][j] = rand.nextInt();
                            }
                        }
                    } else if (res != 3) {
                        System.out.println("Некорректный ввод. Введите 1, 2 или 3.");
                        continue;
                    }

                    System.out.println("Введены матрицы:");
                    System.out.println("A=");
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            System.out.print(A[i][j]);
                            System.out.print(" ");
                        }
                        System.out.println();
                    }
                    System.out.println("B=");
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            System.out.print(B[i][j]);
                            System.out.print(" ");
                        }
                        System.out.println();
                    }

                    readystate = 1;
                    break;
                }
            }
            else if(res == 2) {
                if (readystate < 1) {
                    System.out.println("Данные не были введены! Сначала введите матрицы.");
                    continue;
                }
                C = new long[n][n];
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        C[i][j] = A[i][j]+B[i][j];

                readystate = 2;
            }
            else if(res == 3) {
                if (readystate < 2) {
                    System.out.println("Сначала выполните пункт 2!");
                    continue;
                }
                System.out.println("Сумма матриц:");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        System.out.print(C[i][j]);
                        System.out.print(" ");
                    }
                    System.out.println();
                }
                System.out.println("Значение определителя:");
                System.out.println(det(C, n));
                readystate = 3;
            }
            else if(res == 4) {
                System.exit(0);
            }
        }
    }
}