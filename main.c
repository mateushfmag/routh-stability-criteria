#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPolynomial(const char *polynomialStr){
    return 1;
}

void usageTerms()
{
    printf("usage: 1s3 + 3s2 + 6s1 + 30s0\n");
    exit(EXIT_FAILURE);
}

float char2float(char c){
    if(c == 's'){
        return 1;
    }
    return (float)(c - '0');
}

void fillPolynomial(char *polynomialStr, int *qtyTerms, float (**result)[2]){
    char *polynomialTerm = strtok(polynomialStr, " + ");
    *result = malloc(sizeof(float[*qtyTerms][2]));
    while (polynomialTerm != NULL) {
        printf("%c %c %c \n\n", polynomialTerm[0] , polynomialTerm[1], polynomialTerm[2]);
        (*result)[*qtyTerms][0] = char2float(polynomialTerm[0]);
        (*result)[*qtyTerms][1] = char2float(polynomialTerm[2]);
        ++(*qtyTerms);

        polynomialTerm = strtok(NULL, " + ");
    }
}

void routhMatrix(float (*polynomial)[2], int rowsQty){

    float **matrix = (float **) malloc(rowsQty * sizeof(float *));  // aloca qty linhas

    int columnsQty = (int)(rowsQty/2) + 1;
    for (int i = 0; i < rowsQty; i++) {
        matrix[i] = (float *) malloc(columnsQty * sizeof(float));  // aloca colunas para cada linha
    }

    matrix[0][0] = polynomial[0][1];
    matrix[1][0] = polynomial[1][1];

    for(int i=0;i<rowsQty;i++){
        if(i <= columnsQty){
            if(i%2 == 0){
                int index = i == 0 ? 1 : (i == 2 ? i : i-1);
                matrix[0][index] = polynomial[i][0];
                printf("matrix[0][index] = %.2f\n", matrix[0][index]);
            }else{
                int index = i == 1 ? 1 : (i == 3 ? i-1 : i-2);
                matrix[1][index] = polynomial[i][0];
                printf("matrix[1][index] = %.2f\n", matrix[1][index]);
            }
        }
    }

    for(int i=2;i<rowsQty;i++){
        matrix[i][0] = matrix[i-1][0] -1;
    }


    for(int i=0;i<rowsQty;i++){
        for(int j=0;j<columnsQty;j++){
            printf("%.2f   ", matrix[i][j]);
        }
        printf("\n");
    }


    for(int i=2;i<rowsQty;i++){
        for(int j=1;j<columnsQty;j++){
            printf("CONTA:\n");
            printf("%.2f*%.2f - %.2f*%.2f / %.2f\n",
                matrix[i-2][1] , matrix[i-1][j+1],
                matrix[i-2][j+1], matrix[i-1][1],
                matrix[i-1][1]);
            printf("\n");
            matrix[i][j] = (matrix[i-2][1]*matrix[i-1][j+1] - matrix[i-2][j+1]*matrix[i-1][1])/matrix[i-1][1];
        }
    }

    for(int i=0;i<rowsQty;i++){
        for(int j=0;j<columnsQty;j++){
            printf("%.2f   ", matrix[i][j]);
        }
        printf("\n");
    }

}

int main(int argc, char **argv)
{
    if(!isPolynomial(argv[0])){
        usageTerms();
    };
    char *polynomialStr = strdup("1s3 + 3s2 + 6s1 + 5s0");
    int qty = 0;
    float (*polynomial)[2] = NULL;
    fillPolynomial(polynomialStr, &qty, &polynomial);

    for(int i=0; i < qty; i++){
        printf("FIRST");
        printf("[%.2f , %.2f]\n",polynomial[i][0], polynomial[i][1]);
    }

    routhMatrix(polynomial, qty);

    free(polynomial);
    free(polynomialStr);
    return 0;
}
