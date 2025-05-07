/**
 * Interface for managing book files.
 * Disk read are only done on load and save.
 * All other operations are done in memory through the BookFile struct.
 * Functions with int return type return 0 on success and -1 on failure.
 */
#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H
#include <stdlib.h>

typedef struct Book {
  char *code;
  char *name;
  char *type;
  int price;
} Book;

typedef struct BookFile {
  Book *bookArray;
  size_t size;
  size_t capacity;
} BookFile;

// Creates a new book file. For internal use only.
BookFile *bookfile_new();

// Loads a book file from a text file
BookFile *bookfile_load(const char *filename);

// Creates a new book file. Overwrites the old one if it exists.
int bookfile_save(BookFile *bookfile, const char *filename);

// Pushes a new book to the book file. Automatically resizes the array if needed.
int bookfile_push(BookFile *bookfile, const Book book);

// Deletes a book from the book file by index.
// Not implemented yet.
int bookfile_delete(BookFile *bookfile, size_t index);

// Displays all books in the book file.
// Not implemented yet.
int bookfile_display(const BookFile *bookfile);

// Frees the memory allocated for the book file.
int bookfile_free(BookFile *bookfile);

#endif // FILE_INTERFACE_H