/* Nama Program : mdate.c
	Deskripsi : Driver untuk menggunakan unit ADT Date
			yang ada di date.h dan date.c
*/

#include <stdio.h>
#include <conio.h>
#include "date.h"
#include "date.c"
#include <stdlib.h>

/* P R O G R A M   U T A M A   */
int main(){
	 date D1, D2, D3, D4;
	 char lagi = 'y';
	 char coba = 'y';

	/* Algoritma : Procedure yang isi bodynya call thd semua feature yang ada */
	while (lagi == 'y'){
		 //lakukan clear screen;
		 system ("cls");
		 CreateDate(&D1);
		 printf("Hasil CreateDate (&D1), maka D1 bernilai: ");
		 PrintObj(D1);
		 //lakukan set tanggal, bulan, dan tahun, simpan hasil ke var D2
		 ReadDate (&D2);
		 while (!isValid(D2)){
			 printf ("Tanggal tidak valid, ulangi\n");
			 ReadDate (&D2);
		 }
		 printf("\nSetelah perintah BacaDate(&D2), maka D2 bernilai : ");
		 //tampilkan D2
		 PrintObj(D2);
		 //dan seterusnya uji semua modul yang ada di file body 
		 //spesification-nya (date.cpp) dengan cara memanggil dari driver 
		 //(modul main) ini
		 if(isKabisat(D2)){
			 printf("Tahun %d adalah tahun kabisat\n", D2.Thn);
		 } else {
			 printf("Tahun %d bukan tahun kabisat\n", D2.Thn);
		 }
		 // beforeDate
		 DateBefore(D2);

		 //nextDate
		 NextDate(D2);
 
		 //set tanggal D3
		 ReadDate(&D3);

		 while (!isValid(D3))
		 {
			 printf("Tanggal tidak valid, ulangi\n");
			 ReadDate(&D3);
		 }
		 PrintObj(D3);

		 DifferenceDate(D2, D3);

		 printf("\ncoba lagi (y/t) ? ");
		 scanf("%c", &lagi);
	}

	

}