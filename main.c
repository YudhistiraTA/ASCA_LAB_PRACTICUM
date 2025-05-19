#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOK_FILE "databuku.txt"
#define TRANSACTION_FILE "datatransaksi.txt"

#include "file_interface.h"

void input_book(FileInterface *interface) {
  char code_buffer[50];
  char name_buffer[100];
  char type_buffer[100];
  int price;

  printf("\n=== Input Data Buku ===\n");
  printf("Masukkan kode buku : ");
  scanf(" %[^\n]", code_buffer);
  printf("Masukkan nama buku : ");
  scanf(" %[^\n]", name_buffer);
  printf("Masukkan jenis buku : ");
  scanf(" %[^\n]", type_buffer);
  printf("Masukkan harga buku : ");
  scanf("%d", &price);

  Book book;
  book.code = strdup(code_buffer);
  book.name = strdup(name_buffer);
  book.type = strdup(type_buffer);
  book.price = price;

  book_array_push(interface, book);
  printf("\nData buku berhasil ditambahkan!\n\n");
}

void input_transaction(FileInterface *interface) {
  char transaction_code[50];
  int index, quantity;

  printf("\n=== Input Transaksi ===\n");
  view_books(interface);

  printf("Masukkan kode transaksi : ");
  scanf(" %[^\n]", transaction_code);
  printf("Pilih index buku yang ingin dijual (mulai dari 0) : ");
  scanf("%d", &index);
  printf("Masukkan jumlah buku yang dijual : ");
  scanf("%d", &quantity);

  if (index < 0 || index >= interface->book_array_size) {
    printf("\nIndex tidak valid!\n\n");
    return;
  }

  Transaction transaction;
  transaction.transaction_code = strdup(transaction_code);
  transaction.quantity = quantity;
  transaction.book.code = strdup(interface->bookArray[index].code);
  transaction.book.name = strdup(interface->bookArray[index].name);
  transaction.book.type = strdup(interface->bookArray[index].type);
  transaction.book.price = interface->bookArray[index].price;

  transaction_array_push(interface, transaction);
  printf("\nTransaksi berhasil ditambahkan!\n\n");
}

void delete_book(FileInterface *fileInterface) {
  int index;

  view_books(fileInterface);

  printf("Masukkan index buku yang ingin dihapus: ");
  scanf("%d", &index);

  if (book_array_delete(fileInterface, index) == 0)
    printf("Buku berhasil dihapus.\n");
  else
    printf("Index tidak valid atau buku tidak ditemukan.\n");
}

void delete_transaction(FileInterface *fileInterface) {
  int index;

  view_transactions(fileInterface);

  printf("Masukkan index transaksi yang ingin dihapus: ");
  scanf("%d", &index);

  if (transaction_array_delete(fileInterface, index) == 0)
    printf("Transaksi berhasil dihapus.\n");
  else
    printf("Index tidak valid atau transaksi tidak ditemukan.\n");
}

int main() {
  FileInterface *fileInterface = file_interface_new();
  if (file_interface_load(fileInterface, BOOK_FILE, ITEM)) {
    printf("Failed to load book file.\n");
    file_interface_free(fileInterface);
    return 1;
  }
  if (file_interface_load(fileInterface, TRANSACTION_FILE, TRANSACTION)) {
    printf("Failed to load transaction file.\n");
    file_interface_free(fileInterface);
    return 1;
  }

  int choice;

  system("cls");

  while (1) {
    printf("=== Menu ===\n");
    printf("1. Input Buku\n");
    printf("2. Input Transaksi\n");
    printf("3. View Buku\n");
    printf("4. View Transaksi\n");
    printf("5. Delete Buku\n");
    printf("6. Delete Transaksi\n");
    printf("7. Exit\n\n");
    printf("Pilih menu : ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        input_book(fileInterface);
        break;
      case 2:
        input_transaction(fileInterface);
        break;
      case 3:
        view_books(fileInterface);
        break;
      case 4:
        view_transactions(fileInterface);
        break;
      case 5:
        delete_book(fileInterface);
        break;
      case 6:
        delete_transaction(fileInterface);
        break;
      case 7:
        printf("\nMenyimpan data...\n");
        if (file_interface_save(fileInterface, BOOK_FILE, ITEM) != 0) {
          printf("Failed to save book file.\n");
        }
        if (file_interface_save(fileInterface, TRANSACTION_FILE, TRANSACTION) !=
            0) {
          printf("Failed to save transaction file.\n");
        }
        file_interface_free(fileInterface);
        printf("\nProgram selesai.\n\n");
        return 0;
      default:
        printf("Pilihan tidak valid. Coba lagi.\n\n");
    }
  }
}