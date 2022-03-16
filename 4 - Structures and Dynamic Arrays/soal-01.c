/*EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
*Modul            : 4 - Structures and Dynamic Arrays
*Percobaan        : Structures and Dynamic Arrays
*Hari dan Tanggal : Rabu, 16 Maret 2022
*Nama (NIM)       : Surya Dharma (13220027)
*Asisten (NIM)    : Elkhan Julian Brillianshah (13219059)
*Nama File        : soal-01.c
*Deskripsi        : Program menghasilkan perkalian dari matriks A dan B
*/

#include <stdio.h>
#include <stdlib.h>

// Deklarasi struct bernama Matrix
typedef struct {
	int nRow;
	int nCol;
	int *matrix;
} Matrix;

// Deklarasi fungsi untuk membebaskan memori
void freeMatrix(Matrix mat)
{
    free(mat.matrix);
}

// Fungsi untuk inisialisasi matriks temp untuk hasil perkalian
void fill_matrix_temp(int nRow, int nCol, int **matrix)
{
    for(int i = 0; i < nRow; ++i){
        for(int j = 0; j < nCol; ++j){
            matrix[i][j] = 0;
        }
    }
}

void fill_matrix(Matrix mat)
{
    int temp[mat.nRow][mat.nCol];
        for(int i = 0; i < mat.nRow; ++i){
            for(int j = 0; j < mat.nCol; ++j){
                temp[i][j] = (i * mat.nCol) + j;
                mat.matrix[(i * mat.nCol) + j] = temp[i][j];
            }
        }
}

int mult_matrix(Matrix A, Matrix B, int id_brs_A, int id_kol_B)
{
    int temp = 0;
    int id_A, id_B;
    for(int i = 0; i < A.nCol; ++i){
        id_A = (id_brs_A * A.nCol) + i;
        id_B = (i * B.nCol) + id_kol_B;
        temp += (A.matrix[(id_brs_A * A.nCol) + i]) * (B.matrix[(i * B.nCol) + id_kol_B]);
    }
    return temp;
}


int main(void) {
    Matrix A, B, C;

	// Inisialisasi matrix A
	printf("Jumlah baris matrix A: ");
	scanf("%d", &A.nRow);
	printf("Jumlah kolom matrix A: ");
	scanf("%d", &A.nCol);


	// Inisialisasi matrix B
	printf("Jumlah baris matrix B: ");
	scanf("%d", &B.nRow);
	printf("Jumlah kolom matrix B: ");
	scanf("%d", &B.nCol);


	if(A.nCol != B.nRow){
        printf("Ukuran matriks A dan B tidak sesuai.\n");
	}
	else {
        // Deklarasi matriks
        A.matrix = (int*)calloc((A.nRow * A.nCol), sizeof(int));
        B.matrix = (int*)calloc((B.nRow * B.nCol), sizeof(int));
        C.matrix = (int*)calloc((A.nRow * B.nCol), sizeof(int));
        C.nRow = A.nRow;
        C.nCol = B.nCol;

        // Mengisi matriks A
        fill_matrix(A);

        // Mengisi matriks B
        fill_matrix(B);

        // Deklarasi dan inisiasi matriks temp_hasil untuk menampung hasil perkalian matriks
        int **temp_hasil = (int**)malloc(C.nRow*sizeof(int*));
        for(int i = 0; i < C.nRow; ++i){
            temp_hasil[i] = (int*)malloc(sizeof(int));
        }
        fill_matrix_temp(C.nRow, C.nCol, temp_hasil);

        // Melakukan assign hasil perkalian ke matriks C
        for(int i = 0; i < C.nRow; ++i){
            for(int j = 0; j < C.nCol; ++j){
                temp_hasil[i][j] = mult_matrix(A, B, i, j);
                C.matrix[(i*C.nCol) + j] = temp_hasil[i][j];
            }
        }

        // Mencetak output
        printf("Hasil perkalian matriks A*B: \n");
        for(int i = 0; i < C.nRow; ++i){
            for(int j = 0; j < C.nCol; ++j){
                printf("%d ", C.matrix[(i*C.nCol) + j]);
            }
            printf("\n");
        }
        printf("\n");


        // Bebaskan memory matriks A dan B
        freeMatrix(A);
        freeMatrix(B);
        freeMatrix(C);

        for(int i = 0; i < C.nRow; ++i){
            free(temp_hasil[i]);
        }
        free(temp_hasil);
	}

	return 0;
}
