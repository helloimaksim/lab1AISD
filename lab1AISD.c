#include <stdio.h>
#include <malloc.h>


typedef struct Line{
    int n;
    int *a;
} Line;

typedef struct Matrix{
    int lines;
    Line *matr;
} Matrix;

int getInt(int *a){
    
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        if (n == 0){
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

int input(Matrix *rm){
    
    const char *pr = "";
    int m;
    int i, j;
    int *p;
    do{
        printf("%s\n", pr);
        printf("Enter number of lines: ");
        pr = "Wrong input. Repeat!";
        if(getInt(&m) == 0)
        return 0;
    } while( m < 1);
    rm->lines = m;
    rm->matr = (Line *)calloc(m, sizeof(Line));
    for(i = 0; i < rm->lines; i++){
        pr = "";
        do{
            printf("%s\n", pr);
            printf("Enter number of items in lines %d: ", i + 1);
            pr = "Wront input. Repeat!";
            if (getInt(&m) == 0){
                return 0;
            }
        } while (m < 1);
        rm->matr[i].n = m;
        p = (int *)malloc(sizeof(int)*m);
        rm->matr[i].a = p;
        printf("Enter items for matrix line #%d:\n", i+1);
        for (j = 0; j < m; j++, p++)
        if (getInt(p) == 0){
            return 0;
        }
    }
    return 1;
}

void output(const char *msg, Matrix a){
    
    int i, j;
    int *p;
    printf("%s:\n", msg);
    for (i = 0; i < a.lines; ++i){
        p = a.matr[i].a;
        for (j = 0; j < a.matr[i].n; ++j, ++p){
            printf(" %d ", *p);
        }
        printf("\n");
    }
}


void erase(Matrix *a){
    
    int i;
    for (i = 0; i < a->lines; ++i)
    free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}

void resmat(Matrix a, Matrix *b){
    
    int j, i, n, lines;
    int *p;
    lines = a.lines;
    b->lines = lines;
    b->matr = (Line *)calloc(lines, sizeof(Line));
    for(i = 0; i < lines; i++){
        n = a.matr[i].n;
        b->matr[i].n = n;
        p = (int *)malloc(sizeof(int)*n);
        b->matr[i].a = p;
        for(j = 0; j < n; j++){
            p[j] = 0;
        }
    }
}

void min(Matrix *a, Matrix *b){
    
    int i, j;
    int min;
    int nmin;
    for ( i = 0; i < a->lines; ++i){
        min = a->matr[i].a[0];
        nmin = 0;
        for ( j = 0; j < a->matr[i].n; j++){
            if(min > a->matr[i].a[j]){
                min = a->matr[i].a[j];
                nmin = j;
            }
        }
        b->matr[i].a[0] = min;
        b->matr[i].a[nmin] = a->matr[i].a[0];
        for ( j = 1; j < a->matr[i].n; j++){
            if(j != nmin){
                b->matr[i].a[j] = a->matr[i].a[j];
            }
        }
    }
}

int main(){
    
    Matrix matr = {0, NULL};
    Matrix res = {0, NULL};
    if (input(&matr) == 0){
        printf("%s\n", "This is the end of the file");
        return 1;
    }
    resmat(matr, &res);
    min(&matr, &res);
    output("Source matrix", matr);
    output("Result matrix", res);
    erase(&matr);
    erase(&res);
    return 0;
}
