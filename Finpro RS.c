#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

struct node {
	char nama[41];	//menyimpan nama pasien
	int umur;	//menyimpan umur pasien
	char tanggal[11];	//menyimpan tanggal pasien mengantre
	char waktu[6];	//menyimpan waktu pasien mengantre
	char deskripsi[51];	//menyimpan gejala/keluhan pasien
	int noAntre;	//menyimpan nomor antrean pasien
	char noHp[16];	//menyimpan nomor HP pasien
	struct node *next;	//menyimpan alamat node berikutnya
	struct node *prev;	//menyimpan alamat node sebelumnya
};

void menu1(struct node **head, struct node **tail, int kodeAntrean) {
	//Membuat node baru
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->next = NULL;
	newNode->prev = NULL;
	
	char sudahBenar;
	
	//Untuk menginputkan data pasien
	do{
		int digit;
		system("cls");
		printf("~~~~~ TAMBAHKAN ANTRIAN ~~~~~\n");
		
		do{
			printf("Masukkan nama (maks 40): ");
			scanf("%[^\n]", newNode->nama);
			getchar();
			digit = strlen(newNode->nama);
		}while(digit>40);
		
		printf("Masukkan umur: ");
		scanf("%d", &newNode->umur);
		getchar();
		
		do{
			printf("Masukkan gejala (maks 50): ");
			scanf("%[^\n]", newNode->deskripsi);
			getchar();
			digit = strlen(newNode->deskripsi);
		}while(digit>50);
		
		
		printf("Masukkan nomor HP: ");
		scanf("%[^\n]", newNode->noHp);
		getchar();
		
		printf("\nApakah data yang anda masukkan sudah benar? [y/n] : ");
		scanf("%c", &sudahBenar);
		getchar();
	}while(sudahBenar == 'n');
	
	newNode->noAntre = kodeAntrean;
		
	time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(newNode->tanggal, sizeof(newNode->tanggal), "%d-%m-%Y", t);  // Menyimpan tanggal ketika mengantre
    strftime(newNode->waktu, sizeof(newNode->waktu), "%H:%M", t);         // Menyimpan waktu ketika mengantre
	
	//Pengkondisian untuk double linked list
	if(*head == NULL) {
		//Jika antrean kosong
		*head = newNode;
		*tail = newNode;
	}
	else {
		//Jika antrean sudah ada, menghubungkan newNode dengan tail
		(*tail)->next = newNode;
		newNode->prev = *tail;
		*tail = newNode;
	}
}

void menu2(struct node **head, struct node **tail){
	//Jika antrian kosong
	if(*head == NULL){
		printf("\nAntrian kosong!");
		return;	
	}
	
	//Jika antrian ada
	system("cls");
	int kodeBatal;
	printf("~~~~~ MEMBATALKAN ANTREAN PASIEN ~~~~~\n\n");
	printf("Masukkan kode antrian: ");
	scanf("%d", &kodeBatal);
	getchar();
	
	struct node *ptr = *head;
	
	do{
		if(ptr->noAntre == kodeBatal){	//Jika nomor antrean ditemukan
			if(ptr == *head){	//Jika yang dibatalkan adalah head
				*head = (*head)->next;
				if(*head != NULL) (*head)->prev = NULL;  //mengosongkan alamat prev pada head
				else *tail = NULL; //Jika head NULL maka tail juga NULL, maka antrean sudah habis
			}
			else if(ptr == *tail){	//Jika yang dibatalkan adalah tail
				*tail = (*tail)->prev;
				(*tail)->next = NULL;
			}
			else{	//Jika yang dibatalkan diantara head dan tail
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
			}
			free(ptr);
			printf("Antrean dengan kode %03d dibatalkan\n", kodeBatal);
			return;
		}
		else{	//Jika nomor antrean tidak sama, maka ptr maju
			ptr = ptr->next;
		}
	}while(ptr != NULL);
	printf("Kode %03d tidak terdaftar pada antrean\n", kodeBatal);
}

void menu3(struct node *head){
	if(head == NULL){
		printf("\nAntrean kosong!");
		return;	
	}
	system("cls");
	
	int count = 0;
	printf("~~~~~ DAFTAR ANTREAN ~~~~~\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("|Kode |Nama                                      |Umur |Gejala                                              |Waktu  |\n");
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	do{
		printf("| %03d | %-40s | %-3d | %-50s | %-5s |\n", head->noAntre, head->nama, head->umur, head->deskripsi, head->waktu);
		head = head->next;
		count++;
	}while(head != NULL);
	printf("---------------------------------------------------------------------------------------------------------------------\n");
	printf("\nTersisa %d antrean!", count);
}

void menu4(struct node **head, struct node **tail)
{
	if(*head == NULL) {
		printf("\nAntrean kosong!");
	}
	else
	{	
		system("cls");
		
		printf("~~~~~ PANGGILAN KEPADA PASIEN %03d ~~~~~\n\n", (*head)->noAntre);
		printf(" Nama	: %s\n", (*head)->nama);
		printf(" Gejala	: %s\n", (*head)->deskripsi);
		printf(" Umur	: %d\n", (*head)->umur);
		printf(" No. HP	: %s\n", (*head)->noHp);
		printf(" Tanggal: %s\n", (*head)->tanggal);
		printf(" Waktu	: %s", (*head)->waktu);	
	
		//Pengkondisian penghapusan node setelah dipanggil
		if((*head)->next == NULL)	//Jika tersisa 1 pasien
		{
			free(*head);
			*head = NULL;
			*tail = NULL;
		}
		else	//Jika ada lebih dari 1 pasien
		{	
			struct node *temp = *head;
			*head = (*head)->next;
			(*head)->prev = NULL;
			free(temp);
		}
		printf("\n\nSilahkan hubungi pasien tersebut!");
	}
}

void menu5(struct node *head){
	if(head == NULL) {
		printf("\nAntrean kosong!");
		return;
	}
	
	struct node *ptr = head;
	
	int kodeCek;
	system("cls");
	printf("~~~~~ CEK STATUS ANTREAN ~~~~~\n\n");
	printf("Masukkan kode antrean: ");
	scanf("%d", &kodeCek);
	getchar();
	
	int count = 0;
	do{
		if(ptr->noAntre == kodeCek){
			if(count == 0) printf("Antrean berikutnya adalah anda!");
			else printf("Terdapat %d antrean sebelum anda, lalu anda segera dipanggil", count);
			return;
		}
		else {
			count++;
			ptr = ptr->next;
		}
	}while(head != NULL);
	printf("Kode antrean tidak terdaftar!");
}

int main(){
	struct node *head=NULL; //penunjuk awal antrean
	struct node *tail=NULL; // penunjuk akhir antrean
	
	int kodeAntrean = 1;
	
	int pilihan;
	do {	
		system("cls");
		printf("Antrean Rumah Sakit Tawa Sehat\n");
		printf("-------------------------------\n");
		printf("|1.| Tambahkan antrean        |\n");
		printf("|2.| Batalkan antrean         |\n");
		printf("|3.| Tampilkan antrean        |\n");
		printf("|4.| Panggil pasien           |\n");
		printf("|5.| Status antrean           |\n");
		printf("|0.| Exit                     |\n");
		printf("-------------------------------\n");
		printf("Pilihan: ");
		scanf("%d", &pilihan);
		getchar();
		
		switch(pilihan) {
			case 1:
				menu1(&head, &tail, kodeAntrean);
				printf("\nBerhasil menambahkan antrean baru!\nKode antrean: %03d", kodeAntrean);
				kodeAntrean++;
				printf("\n\nPress any key to continue. . .");
				getch();
				break;
			case 2:
				menu2(&head, &tail);
				printf("\n\nPress any key to continue. . .");
				getch();
				break;
			case 3:
				menu3(head);
				printf("\n\nPress any key to continue. . .");
				getch();
				break;
			case 4:
				menu4(&head, &tail);
				printf("\n\nPress any key to continue. . .");
				getch();
				break;
			case 5:
				menu5(head);
				printf("\n\nPress any key to continue. . .");
				getch();
				break;
			case 0:
				printf("\nTerimakasih! \n\nProgram telah berakhir!\n");
				break;
			default:
				printf("Anda salah memasukkan pilihan!");
				printf("\n\nPress any key to continue. . .");
				getch();
		}
	}while(pilihan != 0);
	 
	return 0;
}
