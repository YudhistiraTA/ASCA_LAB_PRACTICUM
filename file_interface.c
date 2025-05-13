#include "file_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FileInterface *file_interface_new() {
  FileInterface *file_interface = malloc(sizeof(FileInterface));
  if (!file_interface) {
    return NULL;
  }
  file_interface->book_array_size = 0;
  file_interface->book_array_capacity = 20;
  file_interface->bookArray =
      malloc(file_interface->book_array_capacity * sizeof(Book));
  if (!file_interface->bookArray) {
    free(file_interface);
    return NULL;
  }

  file_interface->transaction_array_size = 0;
  file_interface->transaction_array_capacity = 20;
  file_interface->transactionArray =
      malloc(file_interface->transaction_array_capacity * sizeof(Transaction));
  if (!file_interface->transactionArray) {
    free(file_interface->bookArray);
    free(file_interface);
    return NULL;
  }

  return file_interface;
}

int file_interface_load(FileInterface *fileInterface, const char *filename,
                        RecordType type) {
  if (!fileInterface) {
    return -1;
  }
  FILE *file = fopen(filename, "r");
  if (!file) {
    return 0; // File not found. fileInterface stay empty
  }
  if (type == ITEM) {
    if (bookfile_load(file, fileInterface) != 0) {
      fclose(file);
      return -1;
    }
  } else if (type == TRANSACTION) {
    if (transactionfile_load(file, fileInterface) != 0) {
      fclose(file);
      return -1;
    }
  }
  fclose(file);
  return 0;
}

int transactionfile_load(FILE *file, FileInterface *fileInterface) {
  if (!file || !fileInterface) {
    return -1;
  }
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file)) {
    Transaction transaction;
    char *code_buffer = strtok(buffer, ",");
    char *quantity_buffer = strtok(NULL, ",");
    char *book_code_buffer = strtok(NULL, ",");
    char *book_name_buffer = strtok(NULL, ",");
    char *book_type_buffer = strtok(NULL, ",");
    char *book_price_buffer = strtok(NULL, ",");
    if (!code_buffer || !quantity_buffer || !book_code_buffer ||
        !book_name_buffer || !book_type_buffer || !book_price_buffer) {
      return -1;
    }

    int quantity = atoi(quantity_buffer);
    int price = atoi(book_price_buffer);

    Book book;
    book.code = strdup(book_code_buffer);
    book.name = strdup(book_name_buffer);
    book.type = strdup(book_type_buffer);
    book.price = price;

    transaction.transaction_code = strdup(code_buffer);
    transaction.quantity = quantity;
    transaction.book = book;

    if (transaction_array_push(fileInterface, transaction) != 0) {
      free(transaction.transaction_code);
      free(book.code);
      free(book.name);
      free(book.type);
      return -1;
    }
  }

  return 0;
}

int bookfile_load(FILE *file, FileInterface *fileInterface) {
  if (!file || !fileInterface) {
    return -1;
  }
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file)) {
    Book book;
    char *code_buffer = strtok(buffer, ",");
    char *name_buffer = strtok(NULL, ",");
    char *type_buffer = strtok(NULL, ",");
    char *price_buffer = strtok(NULL, ",");
    if (!code_buffer || !name_buffer || !type_buffer || !price_buffer) {
      return -1;
    }
    int price = atoi(price_buffer);
    char *code = strdup(code_buffer);
    char *name = strdup(name_buffer);
    char *type = strdup(type_buffer);
    if (!code || !name || !type) {
      free(code);
      free(name);
      free(type);
      return -1;
    }
    book.code = code;
    book.name = name;
    book.type = type;
    book.price = price;
    if (book_array_push(fileInterface, book) != 0) {
      free(code);
      free(name);
      free(type);
      return -1;
    }
  }
  return 0;
}

int file_interface_save(FileInterface *file_interface, const char *filename,
                        RecordType type) {
  FILE *file = fopen(filename, "w");
  if (!file) return -1;
  int save_ok = 0;
  if (type == ITEM) {
    save_ok = bookfile_save(file, file_interface);
  } else if (type == TRANSACTION) {
    save_ok = transactionfile_save(file, file_interface);
  }
  if (fclose(file) != 0) save_ok = -1;
  return save_ok;
}

int bookfile_save(FILE *file, FileInterface *file_interface) {
  if (!file || !file_interface) return -1;
  for (size_t i = 0; i < file_interface->book_array_size; i++) {
    Book book = file_interface->bookArray[i];
    if (fprintf(file, "%s,%s,%s,%d\n", book.code, book.name, book.type,
                book.price) < 0) {
      return -1;
    };
  }
  return 0;
}

int transactionfile_save(FILE *file, FileInterface *file_interface) {
  if (!file || !file_interface) return -1;
  for (size_t i = 0; i < file_interface->transaction_array_size; i++) {
    Transaction transaction = file_interface->transactionArray[i];
    if (fprintf(file, "%s,%d,%s,%s,%s,%d\n", transaction.transaction_code,
                transaction.quantity, transaction.book.code,
                transaction.book.name, transaction.book.type,
                transaction.book.price) < 0) {
      return -1;
    };
  }
  return 0;
}

int book_array_push(FileInterface *file_interface, const Book book) {
  if (!file_interface) return -1;
  if (file_interface->book_array_size >= file_interface->book_array_capacity) {
    file_interface->book_array_capacity *= 2;
    Book *newArray =
        realloc(file_interface->bookArray,
                file_interface->book_array_capacity * sizeof(Book));
    if (!newArray) {
      return -1;
    }
    file_interface->bookArray = newArray;
  }
  file_interface->bookArray[file_interface->book_array_size++] = book;
  return 0;
}

int transaction_array_push(FileInterface *file_interface,
                           const Transaction transaction) {
  if (!file_interface) return -1;
  if (file_interface->transaction_array_size >=
      file_interface->transaction_array_capacity) {
    file_interface->transaction_array_capacity *= 2;
    Transaction *newArray = realloc(
        file_interface->transactionArray,
        file_interface->transaction_array_capacity * sizeof(Transaction));
    if (!newArray) {
      return -1;
    }
    file_interface->transactionArray = newArray;
  }
  file_interface->transactionArray[file_interface->transaction_array_size++] =
      transaction;
  return 0;
}

int file_interface_free(FileInterface *file_interface) {
  if (!file_interface) return 0;

  for (size_t i = 0; i < file_interface->book_array_size; i++) {
    free(file_interface->bookArray[i].code);
    free(file_interface->bookArray[i].name);
    free(file_interface->bookArray[i].type);
  }
  for (size_t i = 0; i < file_interface->transaction_array_size; i++) {
    free(file_interface->transactionArray[i].transaction_code);
    free(file_interface->transactionArray[i].book.code);
    free(file_interface->transactionArray[i].book.name);
    free(file_interface->transactionArray[i].book.type);
  }

  free(file_interface->bookArray);
  free(file_interface->transactionArray);
  free(file_interface);

  return 0;
}

int book_array_delete(FileInterface *fileInterface, const char *bookCode) {
  if (!fileInterface || !bookCode) return -1;

  for (size_t bookIdx = 0; bookIdx < fileInterface->book_array_size; bookIdx++) {
    if (strcmp(fileInterface->bookArray[bookIdx].code, bookCode) == 0) {
      freeFileInterfaceArrProps(fileInterface, ITEM, bookIdx);

      memmove(
        &fileInterface->bookArray[bookIdx],
        &fileInterface->bookArray[bookIdx + 1],
        (fileInterface->book_array_size - bookIdx - 1) * sizeof(Book)
      );

      fileInterface->book_array_size--;

      return 0;
    }
  }

  return -1;
}

int transaction_array_delete(FileInterface *fileInterface, const char *trxCode) {
  if (!fileInterface || !trxCode) return -1;

  for (size_t trxIdx = 0; trxIdx < fileInterface->transaction_array_size; trxIdx++) {
    if (strcmp(fileInterface->transactionArray[trxIdx].transaction_code, trxCode) == 0) {
      freeFileInterfaceArrProps(fileInterface, TRANSACTION, trxIdx);

      memmove(
        &fileInterface->transactionArray[trxIdx],
        &fileInterface->transactionArray[trxIdx + 1],
        (fileInterface->transaction_array_size - trxIdx - 1) * sizeof(Transaction)
      );

      fileInterface->transaction_array_size--;

      return 0;
    }
  }

  return -1;
}

void freeFileInterfaceArrProps(FileInterface *fileInterface, RecordType type, size_t idx) {
  if (type == ITEM) {
    free(fileInterface->bookArray[idx].code);
    free(fileInterface->bookArray[idx].name);
    free(fileInterface->bookArray[idx].type);
  }

  if (type == TRANSACTION) {
    free(fileInterface->transactionArray[idx].transaction_code);
    free(fileInterface->transactionArray[idx].book.code);
    free(fileInterface->transactionArray[idx].book.name);
    free(fileInterface->transactionArray[idx].book.type);
  }
}