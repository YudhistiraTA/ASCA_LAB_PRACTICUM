/**
 * Interface for managing book files.
 * Disk read are only done on load and save.
 * All other operations are done in memory through the BookFile struct.
 * Functions with int return type return 0 on success and -1 on failure.
 */
#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H
#include <stdio.h>
#include <stdlib.h>

// Item or Transaction record
typedef enum RecordType {
  ITEM,
  TRANSACTION,
} RecordType;

// Book structure
// Contains code, name, type and price
typedef struct Book {
  char *code;
  char *name;
  char *type;
  int price;
} Book;

// Transaction structure
// Contains transaction code, quantity and embedded copy of book structure
typedef struct Transaction {
  char *transaction_code;
  int quantity;
  Book book;
} Transaction;

// FileInterface structure
// Contains arrays of books and transactions, their sizes and capacities
typedef struct FileInterface {
  Book *bookArray;
  Transaction *transactionArray;
  size_t book_array_size;
  size_t book_array_capacity;
  size_t transaction_array_size;
  size_t transaction_array_capacity;
} FileInterface;

// Create a new book file. For internal use only.
FileInterface *file_interface_new();

// Load transaction data of file from a text file
// To be used by file_interface_load only
int transactionfile_load(FILE *file, FileInterface *fileInterface);

// Load transaction data of file from a text file
// To be used by file_interface_load only
int bookfile_load(FILE *file, FileInterface *fileInterface);

// Loads a book file from a text file and store it in the appropriate array type (transaction or book).
int file_interface_load(FileInterface *fileInterface, const char *filename,
                        RecordType type);

// Save book data to a text file
// To be used by file_interface_save only
int bookfile_save(FILE *file, FileInterface *file_interface);

// Save transaction data to a text file
// To be used by file_interface_save only
int transactionfile_save(FILE *file, FileInterface *file_interface);

// Creates a new file based on type. Overwrites the old one if it exists.
int file_interface_save(FileInterface *file_interface, const char *filename,
                        RecordType type);

// Pushes a new book to the book array. Automatically resizes
// the array if needed.
int book_array_push(FileInterface *file_interface, const Book book);

// Pushes a new transaction to the transaction file. Automatically resizes
// the array if needed.
int transaction_array_push(FileInterface *file_interface,
                           const Transaction transaction);

// Frees the memory allocated for the file interface.
int file_interface_free(FileInterface *file_interface);

// Deletes a book from the book array given an index. Frees the memory allocated for the book.
int book_array_delete(FileInterface *fileInterface, size_t index);

// Deletes a transaction from the transaction array given an index. Frees the memory allocated for the transaction.
int transaction_array_delete(FileInterface *fileInterface, size_t index);

// Frees the memory allocated for the book or transaction at the given index.
void freeFileInterfaceArrProps(FileInterface *fileInterface, RecordType type, size_t idx);

// Displays the books in the book array
void view_books(FileInterface *fileInterface);

// Displays the transactions in the transaction array
void view_transactions(FileInterface *fileInterface);

#endif  // FILE_INTERFACE_H