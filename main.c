/**
 * COMP6112036
 * ASCA - LAB
 * Team Practicum
 * 1. Yudhistira Tribuana Authar - 2802629824
 * 2. Serafim Trim Satyaningrim - 2802644964
 * 3. Refa Eka Febriana - 2802643570
 * 4. Willy Fernando - 2802649870
 * 5. Muhammad Alfian Hamzah - 2802649883
 * All functions are documented. Hover over the function name to see the description.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File names
#define BOOK_FILE "databuku.txt"
#define TRANSACTION_FILE "datatransaksi.txt"

#include "file_interface.h"

/** Function Prototypes */

// Prompt user to input book data and push it to the book array
void input_book(FileInterface *interface);

// Prompt user to input transaction data and push it to the transaction array
void input_transaction(FileInterface *interface);

// Display all books in the book array and then prompt user to select a book by index to delete
void delete_book(FileInterface *fileInterface);

// Display all transactions in the transaction array and then prompt user to select a transaction by index to delete
void delete_transaction(FileInterface *fileInterface);

int main() {
  // Initialize file interface
  FileInterface *fileInterface = file_interface_new();

  // Loading data from files and error handling
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

  // Main menu loop
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

// Controller for input book data flow
void input_book(FileInterface *interface) {
  char code_buffer[50];
  char name_buffer[100];
  char type_buffer[100];
  int price;

  // Prompt user for book data
  printf("\n=== Input Data Buku ===\n");
  printf("Masukkan kode buku : ");
  scanf(" %[^\n]", code_buffer);
  printf("Masukkan nama buku : ");
  scanf(" %[^\n]", name_buffer);
  printf("Masukkan jenis buku : ");
  scanf(" %[^\n]", type_buffer);
  printf("Masukkan harga buku : ");
  scanf("%d", &price);

  // Assign values to book structure
  Book book;
  book.code = strdup(code_buffer);
  book.name = strdup(name_buffer);
  book.type = strdup(type_buffer);
  book.price = price;

  // Push and realloc if necessary
  book_array_push(interface, book);
  printf("\nData buku berhasil ditambahkan!\n\n");
}

// Controller for input transaction data flow
void input_transaction(FileInterface *interface) {
  char transaction_code[50];
  int index, quantity;

  // Display all books
  printf("\n=== Input Transaksi ===\n");
  view_books(interface);

  // Prompt user for transaction data
  printf("Masukkan kode transaksi : ");
  scanf(" %[^\n]", transaction_code);
  printf("Pilih index buku yang ingin dijual (mulai dari 0) : ");
  scanf("%d", &index);
  printf("Masukkan jumlah buku yang dijual : ");
  scanf("%d", &quantity);

  // Validate index
  if (index < 0 || index >= interface->book_array_size) {
    printf("\nIndex tidak valid!\n\n");
    return;
  }

  // Assign values to transaction structure
  Transaction transaction;
  transaction.transaction_code = strdup(transaction_code);
  transaction.quantity = quantity;
  transaction.book.code = strdup(interface->bookArray[index].code);
  transaction.book.name = strdup(interface->bookArray[index].name);
  transaction.book.type = strdup(interface->bookArray[index].type);
  transaction.book.price = interface->bookArray[index].price;

  // Push and realloc if necessary
  transaction_array_push(interface, transaction);
  printf("\nTransaksi berhasil ditambahkan!\n\n");
}

// Controller for delete book data flow
void delete_book(FileInterface *fileInterface) {
  int index;

  // Display all books
  view_books(fileInterface);

  // Prompt user for index to delete
  printf("Masukkan index buku yang ingin dihapus: ");
  scanf("%d", &index);

  // Validate index and delete
  if (book_array_delete(fileInterface, index) == 0)
    printf("Buku berhasil dihapus.\n");
  else
    printf("Index tidak valid atau buku tidak ditemukan.\n");
}

// Controller for delete transaction data flow
void delete_transaction(FileInterface *fileInterface) {
  int index;

  // Display all transactions
  view_transactions(fileInterface);

  // Prompt user for index to delete
  printf("Masukkan index transaksi yang ingin dihapus: ");
  scanf("%d", &index);

  // Validate index and delete
  if (transaction_array_delete(fileInterface, index) == 0)
    printf("Transaksi berhasil dihapus.\n");
  else
    printf("Index tidak valid atau transaksi tidak ditemukan.\n");
}