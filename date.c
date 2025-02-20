/* File        : date.c */
/* Deskripsi   : Unit untuk keperluan ADT Date */

/***************************/
/*  BODY PRIMITIF DATE     */
/***************************/

#include <stdio.h>
#include <math.h>
#include "date.h"

/*********** Operasi Primitif ************/
/* Constructor Membentuk sebuah DATE, dengan nilai default adalah 01/01/1900 */
void CreateDate (date * D){
	SetTgl (01, &(* D));
	SetBln (01, &(* D));
	SetThn (1900, &(* D));
}

/******* Selector komponen **********/
/* Mengambil bagian Tgl dari date */
int GetTgl (date D){
	return(D.Tgl);
}

/* Mengambil bagian Bln dari date */
int GetBln (date D){
	return(D.Bln);
}

/* Mengambil bagian Thn dari date */
int GetThn (date D){
	return(D.Thn);
}


/****** Pengubah komponen ******/
/* Memberi nilai untuk Tgl */
void SetTgl (int NewTgl, date * D){
	(* D).Tgl = NewTgl;
}

/* Memberi nilai untuk Bln */
void SetBln (int NewBln, date * D){
	(* D).Bln = NewBln;
}

/* Memberi nilai untuk Thn */
void SetThn (int NewThn, date * D){
	(* D).Thn = NewThn;
}


/****** Kelompok Interaksi dengan I/O device, BACA/TULIS ******/
/* Membentuk DATE dari iTgl, iBln dan iThn yang dibaca dari keyboard */
void ReadDate (date * D){
	int iTgl, iBln, iThn;
	printf ("Masukkan tanggal : "); scanf ("%d", &iTgl);
	printf ("Masukkan bulan : "); scanf ("%d", &iBln);
	printf ("Masukkan tahun : "); scanf ("%d", &iThn);
	SetTgl (iTgl, D);
	SetBln (iBln, D);
	SetThn (iThn, D);
}

/* Memeriksa apakah suatu tanggal valid, yaitu dengan memperhatikan batas akhir per bulan */
boolean isValid(date D){
	if ((GetThn(D) < 1900)||(GetThn(D) > 30000)||(GetBln(D) < 1) ||(GetBln(D) > 12)||(GetTgl(D) < 1)||(GetTgl(D) > getEndDate(D)))
		return (false);
	else
		return (true);
}

/* Print nilai D dengan format dd/mm/yyyy */
void PrintObj (date D){
	printf ("%d/%d/%d\n", GetTgl(D), GetBln(D), GetThn(D));
}

/****** Operator Relasional ******/
/* Memeriksa apakah suatu tanggal adalah kabisat; Dipakai untuk bulan == 2 saja
Harusnya kabisat adalah thn yang habis dibagi 4, atau habis dibagi 100 dan 400, tapi implementasinya seringkali hanya menggunakan 4 sebagai pembagi */
boolean isKabisat (date D){
	if ((GetThn(D) % 4 == 0)&&(GetThn(D) % 100 != 0)||(GetThn(D) % 400 == 0))
		return (true);
	else
		return (false);
}

/***** Predikat lain *******/
/* Memberikan tanggal terakhir dari sebuah bulan */
int getEndDate (date D){
	if (GetBln(D) == 2)
		if (isKabisat(D))
			return (29);
		else
			return (28);
	else if (GetBln(D) == 1 || GetBln(D) == 3 || GetBln(D) == 5 || GetBln(D) == 7 || GetBln(D) == 8 || GetBln(D) == 10 || GetBln(D) == 12)
		return (31);
	else
		return (30);
}

/* Menampilkan tanggal sebelumnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal sebelumnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika jan, thn-1 */
void DateBefore (date D){
	if (isValid(D) == false) {
		printf ("Tanggal tidak valid\n");
	} 
	else {
		if (D.Tgl == 1) {
			if (D.Bln == 1) {
				D.Bln = 12;
				D.Thn = D.Thn - 1;
			} else {
				D.Bln = D.Bln - 1;
			}
			D.Tgl = getEndDate(D);
		} else {
			D.Tgl = D.Tgl - 1;
		}
	printf("%d/%d/%d\n", D.Tgl, D.Bln, D.Thn);
}
}

/* Menampilkan tanggal berikutnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal berikutnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika des, thn+1 */
void NextDate (date D){
	if (isValid(D) == false) {
		printf ("Tanggal tidak valid\n");
	} 
	else {
		if (D.Tgl == getEndDate(D)) {
			D.Tgl = 1;
		if (D.Bln == 12) {
			D.Bln = 1;
			D.Thn = D.Thn + 1;
		} else {
			D.Bln = D.Bln + 1;
		} 
	} else {
		D.Tgl = D.Tgl + 1;
	}
	printf("%d/%d/%d\n", D.Tgl, D.Bln, D.Thn);
}
}
/* Memberikan total hari dari tahun 1900 hingga n
	 */
int hitungHariTahun(int n){
	int total = 0;
	date temp;

	for (int i = 1900; i < n; i++){
		temp.Thn = i;
		if (isKabisat(temp))
			total = total + 366;
		else
			total = total + 365;
	}
	return total;
}

// Memberikan total hari dari bulan 1 hingga n
int hitungHariBulan(date D){
	int bulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int totalHari = 0;

	if (isKabisat(D)){
		bulan[1] = 29;
	}

	for (int i = 0; i < D.Bln - 1; i++){
		totalHari = totalHari + bulan[i];
	}
	return totalHari;
}

// Memberikan total hari dari tanggal 1 hingga n
int hitungHari(date D){
	int totalHari = hitungHariTahun(D.Thn) + hitungHariBulan(D);
	return totalHari + D.Tgl;
}

/* Menampilkan selisih dua tanggal
	I.S = 2 buah Tanggal tertentu diketahui
	F.S = Tampil selisih dua buah tanggal
	Asumsi : 1 tahun = 365 hari */
void DifferenceDate (date D1, date D2){
	int selisih = hitungHari(D2) - hitungHari(D1);

	printf ("Selisih antara tanggal %d/%d/%d dan %d/%d/%d adalah %d hari\n", D1.Tgl, D1.Bln, D1.Thn, D2.Tgl, D2.Bln, D2.Thn, selisih);
}
