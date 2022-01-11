/*
Структура struct tree (int x; struct tree *left, *right, *parent;); описывает двоичное дерево поиска. Напишите функцию void ins (struct tree *t, int x), вставляющую в дерево поиска t, заведомо содержащее ключ x, элемент с ключом, на единицу меньшим следующего по размеру за x ключа в дереве, либо с ключом x+1, если x - максимальный элемент дерева. Гарантируется, что ключ, который нужно вставлять, не содержится в дереве.
*/

#include <stdio.h>
#include <stdlib.h>

struct tree {
    int x;
    struct tree* left, * right, * parent;
};

void insert(struct tree* t, int x) {
    if (x > t->x) {
        if(t->right != NULL)
            insert(t->right, x);
        else {
            t->right = malloc(sizeof(struct tree));
            t->right->x = x;
            t->right->left = NULL;
            t->right->right = NULL;
        }
    }
    else if (x <= t->x) {
        if (t->left != NULL)
            insert(t->left, x);
        else {
            t->left = malloc(sizeof(struct tree));
            t->left->x = x;
            t->left->left = NULL;
            t->left->right = NULL;
        }
    }
}

void printTree(struct tree* t) {
    if (t != NULL) {
        printTree(t->left);
        printf("%d ", t->x);
        printTree(t->right);
    }
}

void clearTree(struct tree* t) {
    if (t != NULL) {
        clearTree(t->left);
        clearTree(t->right);
        free(t);
    }
}

void ins(struct tree* t, int x) {
    if (t->x == x) {
        // идём в правого ребёнка
        if(t->right != NULL){
            t = t->right;
            while (t->left != NULL) {
                t = t->left;
            }

            // нужно вставить элемент t->x - 1
            insert(t, t->x - 1);
        }
        else {
            
            while ((t->parent!=NULL) && (t->x <= x)) {
                t = t->parent;
            }

            if (t->x > x) {
                // t->x - следующий за x элемент.

                // нужно вставить элемент t->x - 1
                insert(t, t->x - 1);
            }
            else {
                // нужно вставить элемент t->x + 1
                insert(t, x + 1);
            }

        }
        // ищем следующий в родителях

    }
    else if (x > t->x) {
        ins(t->right, x);
    }
    else {
        ins(t->left, x);
    }
}

int main()
{
    struct tree* t = malloc(sizeof(struct tree));
    t->parent = NULL;

    t->left = malloc(sizeof(struct tree));
    t->left->parent = t;

    t->left->left = malloc(sizeof(struct tree));
    t->left->left->parent = t->left;

    t->left->right = malloc(sizeof(struct tree));
    t->left->right->parent = t->left;

    t->left->left->left = NULL;
    t->left->left->right = NULL;

    t->left->right->left = NULL;
    t->left->right->right = NULL;


    t->right = malloc(sizeof(struct tree));
    t->right->parent = t;

    t->right->left = malloc(sizeof(struct tree));
    t->right->left->parent = t->right;

    t->right->right = malloc(sizeof(struct tree));
    t->right->right->parent = t->right;

    t->right->left->left = NULL;
    t->right->left->right = NULL;

    t->right->right->left = NULL;
    t->right->right->right = NULL;


    t->x = 40;
    t->left->x = 20;
    t->left->left->x = 10;
    t->left->right->x = 30;

    t->right->x = 60;
    t->right->left->x = 50;
    t->right->right->x = 70;

    printTree(t);

    ins(t, 40);
    ins(t, 70);
    ins(t, 30);

    printf("\n");

    printTree(t);
    clearTree(t);

}