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

int char2int(char c){
    if(c == 's'){
        return 1;
    }
    return c - '0';
}

void fillPolynomial(char *polynomialStr, int *qtyTerms, int (**result)[2]){
    char *polynomialTerm = strtok(polynomialStr, " + ");
    *result = malloc(sizeof(int[*qtyTerms][2]));
    while (polynomialTerm != NULL) {
        printf("%c %c %c \n\n", polynomialTerm[0] , polynomialTerm[1], polynomialTerm[2]);
        (*result)[*qtyTerms][0] = char2int(polynomialTerm[0]);
        (*result)[*qtyTerms][1] = char2int(polynomialTerm[2]);
        ++(*qtyTerms);

        polynomialTerm = strtok(NULL, " + ");
    }
}

void routhMatrix(int (*polynomial)[2], int rowsQty){

    int **matrix = (int **) malloc(rowsQty * sizeof(int *));  // aloca qty linhas

    int columnsQty = (int)(rowsQty/2) + 1;
    for (int i = 0; i < 2; i++) {
        matrix[i] = (int *) malloc(columnsQty * sizeof(int));  // aloca colunas para cada linha
    }


    matrix[0][0] = polynomial[0][1];
    matrix[1][0] = polynomial[1][1];

    printf("columnsQty: %d\n", columnsQty);

    for(int i=0;i<columnsQty;i++){
        if(i%2 == 0){
            int index = i == 0 ? 1 : (i == 2 ? i : i-1);
            matrix[0][index] = polynomial[i][0];
        }else{
            int index = i == 1 ? 1 : (i == 3 ? i-1 : i-2);
            matrix[1][index] = polynomial[i][0];
        }
    }

    for(int i=0;i<rowsQty;i++){
        for(int j=0;j<columnsQty;j++){
            printf("%d ", matrix[i][j]);
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
    int (*polynomial)[2] = NULL;
    fillPolynomial(polynomialStr, &qty, &polynomial);

    for(int i=0; i < qty; i++){
        printf("FIRST");
        printf("[%d , %d]\n",polynomial[i][0], polynomial[i][1]);
    }

    routhMatrix(polynomial, qty);

    free(polynomial);
    free(polynomialStr);
    return 0;
}
