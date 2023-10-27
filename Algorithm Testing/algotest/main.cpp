#include <msp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_reading(void);
int reading(int min, int max, int sign);
void test_reading(void);

#define row 4 // constant # of switches
#define col 9 // variable # of modules (SWs)
#define req 2 // variable # of required modules (SWs)

/*
1. SW_matrix -> input
    SOC array ->input
2. Sort SOC array in decreasing order, save the index max SOC
3. Considering that we are using 2 batt,
    acc to the index replace the column with BO array transpose
*/

void main(void)
{
    init_reading();
    int flag = 2;
    int temp, n, i, j, k; // variable # of required modules (SWs)
    int SW_matrix[row][col];
    int SW_matrix_sorted[row][col];
    int SOC[2][col]; // pwm_channel_soc[]
    int SOC_sorted[2][col];
    int A[row][req]; // # of required columns depends on a lot of factors
    int I[req]; // indices
    int BO[req][row];
    int state_1[row] = { 1, 0, 0, 1 };
    int state_2[row] = { 0, 1, 1, 0 };
    for (i = 0; i < col; ++i) SOC[1][i] = i; // indices // tbd can be done in init

    while (flag)
    {
        /* STEP 1:
        - MPC decides the magnitude and polarity of the voltage required

           STEP 2:
        - MTPA, MTPV and FW algorithms decides the % share of the UC and Batteries for producing the required voltage.
        - Assume 3 battery cells, and 2 UC cells.
        */

        // GENERATE TEST VALUES

        int Vreq = reading(0, 50, reading(0, 1, 0));
        printf("\n----------------------------------------------------\nVreq = %d\n\n", Vreq);
        for (i = 0; i < col; ++i) SOC[0][i] = reading(0, 200, 0);

        /* STEP 3:
        - Each column of switching matrix tells whether a sub module is on/off and what combination of UC and Battery is being used in each Sub module.
        - The sorting algorithm sorts the columns of SW matrix twice.
        - Once based on the SOC of battery cells and other based on the SOC of UCs and names them A and B respectively.
        - A the order of batteries in the decreasing order of battery voltage is Vb4 > Vb3 > Vb1 > Vb2...> Vb8,
        - and that of UCs is VUC4 > VUC3 > VUC1 > VUC2...> VUC8 then the respective A and B matrix would be:
        */

        // RESET TO DEFAULT VALUES

        for (i = 0; i < 2; ++i) for (j = 0; j < col; ++j) SW_matrix[i][j] = 1;
        for (i = 2; i < 4; ++i) for (j = 0; j < col; ++j) SW_matrix[i][j] = 0;
        //for (i = 0; i < col; ++i) SW_matrix[3][i] = i + 1; // for testing

        // PRINT ORIGINAL MATRIX, ORIGINAL SOC, AND INDICES

        printf("Original SW_matrix & SOC (w/ Indices):\n");
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j) printf("%d   ", SW_matrix[i][j]);
            printf("\n");
        }
        for (i = 0; i < 2; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                printf("%d ", SOC[i][j]);
                if (i == 1) printf(" ");
                if ((i == 1) && (SOC[1][j] < 10)) printf(" ");
                if ((i == 0) && (SOC[0][j] < 10)) printf(" ");
                if ((i == 0) && (SOC[0][j] < 100)) printf(" ");
            }
            printf("\n");
        }

        // CREATE SORTED MATRIX AND ORIGINAL SOC

        for (i = 0; i < row; ++i) for (j = 0; j < col; ++j) SW_matrix_sorted[i][j] = SW_matrix[i][j];
        for (i = 0; i < 2; ++i) for (j = 0; j < col; ++j) SOC_sorted[i][j] = SOC[i][j];

        for (i = 0; i < col; ++i)
        {
            for (j = i + 1; j < col; ++j)
            {
                if (SOC_sorted[0][i] < SOC_sorted[0][j])
                {
                    for (k = 0; k < 2; ++k)
                    {
                        temp = SOC_sorted[k][i];
                        SOC_sorted[k][i] = SOC_sorted[k][j];
                        SOC_sorted[k][j] = temp;
                    }
                    for (k = 0; k < row; ++k)
                    {
                        temp = SW_matrix_sorted[k][i];
                        SW_matrix_sorted[k][i] = SW_matrix_sorted[k][j];
                        SW_matrix_sorted[k][j] = temp;
                    }
                }
            }
        }

        // PRINT SORTED MATRIX AND SORTED SOC

        printf("\nSorted SW_matrix & SOC (w/ Indices):\n");
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j) printf("%d   ", SW_matrix_sorted[i][j]);
            printf("\n");
        }
        for (i = 0; i < 2; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                printf("%d ", SOC_sorted[i][j]);
                if (i == 1) printf(" ");
                if ((i == 1) && (SOC_sorted[1][j] < 10)) printf(" ");
                if ((i == 0) && (SOC_sorted[0][j] < 10)) printf(" ");
                if ((i == 0) && (SOC_sorted[0][j] < 100)) printf(" ");
            }
            printf("\n");
        }

        // PRINT ORIGINAL MATRIX AND ORIGINAL SOC (TO ENSURE THEY'VE REMAIN UNCHANGED)

        printf("\n(Unchanged) Original SW_matrix & SOC (w/ Indices):\n");
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j) printf("%d   ", SW_matrix[i][j]);
            printf("\n");
        }
        for (i = 0; i < 2; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                printf("%d ", SOC[i][j]);
                if (i == 1) printf(" ");
                if ((i == 1) && (SOC[1][j] < 10)) printf(" ");
                if ((i == 0) && (SOC[0][j] < 10)) printf(" ");
                if ((i == 0) && (SOC[0][j] < 100)) printf(" ");
            }
            printf("\n");
        }

        /* STEP 4:
        - The algorithm then picks top 3 battery cells from matrix A and top 2 UC cells from matrix B and creates a new matrix A' and B' respectively.
        - A' contains SMs which needs to provide VB and B' contains SMs which needs to provide VUC. In this case study, A' and B' would be:
        */

        // EXTRACT RESULTS AND INDICES

        for (i = 0; i < row; ++i) for (j = 0; j < req; ++j) A[i][j] = SW_matrix_sorted[i][j];
        for (i = 0; i < req; ++i) I[i] = SOC_sorted[1][i];

        // PRINT EXTRACTED RESULTS AND INDICES

        printf("\nA (w/ Indices):\n");
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < req; ++j) printf("%d   ", A[i][j]);
            printf("\n");
        }
        for (i = 0; i < req; ++i)
        {
            printf("%d  ", I[i]);
            if (I[i] < 10) printf(" ");
        }

        /* Step 6:
        - Matrix BO is created which contains the switching states for SM which needs to turn battery only
        */

        int BO[req][row] = {};

        // TRANSPOSE RESULTS

        for (i = 0; i < row; ++i) for (j = 0; j < req; ++j) BO[j][i] = A[i][j];

        // PRINT TRANSPOSED RESULTS

        printf("\n\nBO = A':\n");
        for (i = 0; i < req; ++i)
        {
            for (j = 0; j < row; ++j)
            {
                printf("%d   ", BO[i][j]);
                if (j == row - 1) printf("\n");
            }
        }

        // EVALUATE TRANSPOSED RESULTS

        for (n = 0; n < req; ++n)
        {
            if (0 < Vreq) for (i = 0; i < row; ++i) BO[n][i] = state_1[i];
            else for (i = 0; i < row; ++i) BO[n][i] = state_2[i];
        }

        // PRINT EVALUATED TRANSPOSED RESULTS

        printf("\nBO Evaluated:\n");
        for (i = 0; i < req; ++i)
        {
            for (j = 0; j < row; ++j)
            {
                printf("%d   ", BO[i][j]);
                if (j == row - 1) printf("\n");
            }
        }

        /* Step 9:
        - Default state of each SM is [1 1 0 0 [previous state]] Thus, the updated Switch matrix for k+1th instant would be
        */

        // UN-TRANSPOSE EVALUATED TRANSPOSED RESULTS

        for (i = 0; i < row; ++i) for (j = 0; j < req; ++j) A[i][j] = BO[j][i];

        // PRINT NEW EVALUATED RESULTS AND INDICES

        printf("\nNew A = BO' (w/ Indices):\n");
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < req; ++j) printf("%d   ", A[i][j]);
            printf("\n");
        }
        for (i = 0; i < req; ++i)
        {
            printf("%d  ", I[i]);
            if (I[i] < 10) printf(" ");
        }

        // INSERT NEW EVALUATED RESULTS INTO ORIGINAL MATRIX USING INDICES

        for (i = 0; i < req; ++i)
        {
            for (j = 0; j < row; ++j)
            {
                SW_matrix[j][I[i]] = A[j][i];
            }
        }

        // PRINT NEW MATRIX AND ORIGINAL SOC

        printf("\n\nNew SW_matrix & SOC (w/ Indices):\n");
        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j) printf("%d   ", SW_matrix[i][j]);
            printf("\n");
        }
        for (i = 0; i < 2; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                printf("%d ", SOC[i][j]);
                if (i == 1) printf(" ");
                if ((i == 1) && (SOC[1][j] < 10)) printf(" ");
                if ((i == 0) && (SOC[0][j] < 10)) printf(" ");
                if ((i == 0) && (SOC[0][j] < 100)) printf(" ");
            }
            printf("\n");
        }
        flag--;
    }
}

void init_reading(void)
{
    srand(time(0));
}

int reading(int min, int max, int sign)
{
    return(((int) pow(-1, sign)) * ((rand() % (max - min + 1)) + min));
}

void test_reading(void)
{
    int i, min = 0, max = 50, n = row;
    init_reading();
    int test[row] = {};
    for (i = 0; i < n; ++i) test[i] = reading(min, max, reading(0, 1, 0));
    for (i = 0; i < n; ++i) printf("%d ", test[i]);
}