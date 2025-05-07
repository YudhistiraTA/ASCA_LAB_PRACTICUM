#include "file_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BookFile *bookfile_new() {
  BookFile *bookfile = malloc(sizeof(BookFile));
  if (!bookfile) {
    return NULL;
  }
  bookfile->size = 0;
  bookfile->capacity = 20;
  bookfile->bookArray = malloc(bookfile->capacity * sizeof(Book));
  if (!bookfile->bookArray) {
    free(bookfile);
    return NULL;
  }
  return bookfile;
}

BookFile *bookfile_load(const char *filename) {
  BookFile *bookfile = bookfile_new();
  if (!bookfile) {
    return NULL;
  }
  FILE *file = fopen(filename, "r");
  if (!file) {
    return bookfile;
  }
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file)) {
    Book book;
    char *code_buffer = strtok(buffer, ",");
    char *name_buffer = strtok(NULL, ",");
    char *type_buffer = strtok(NULL, ",");
    char *price_buffer = strtok(NULL, ",");
    if (!code_buffer || !name_buffer || !type_buffer || !price_buffer) {
      continue;
    }
    int price = atoi(price_buffer);
    char *code = strdup(code_buffer);
    char *name = strdup(name_buffer);
    char *type = strdup(type_buffer);
    if (!code || !name || !type) {
      free(code);
      free(name);
      free(type);
      continue;
    }
    book.code = code;
    book.name = name;
    book.type = type;
    book.price = price;
    if (bookfile_push(bookfile, book) != 0) {
      free(code);
      free(name);
      free(type);
      continue;
    }
  }
  fclose(file);
  return bookfile;
}

int bookfile_save(BookFile *bookfile, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) {
    return -1;
  }
  for (size_t i = 0; i < bookfile->size; i++) {
    Book book = bookfile->bookArray[i];
    fprintf(file, "%s,%s,%s,%d\n", book.code, book.name, book.type, book.price);
  }
  fclose(file);
  return 0;
}

int bookfile_push(BookFile *bookfile, const Book book) {
  if (bookfile->size >= bookfile->capacity) {
    bookfile->capacity *= 2;
    Book *newArray =
        realloc(bookfile->bookArray, bookfile->capacity * sizeof(Book));
    if (!newArray) {
      return -1;
    }
    bookfile->bookArray = newArray;
  }
  bookfile->bookArray[bookfile->size++] = book;
  return 0;
}

int bookfile_free(BookFile *bookfile) {
  if (!bookfile) {
    return -1;
  }
  for (size_t i = 0; i < bookfile->size; i++) {
    free(bookfile->bookArray[i].code);
    free(bookfile->bookArray[i].name);
    free(bookfile->bookArray[i].type);
  }
  free(bookfile->bookArray);
  free(bookfile);
  return 0;
}