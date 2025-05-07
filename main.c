#include <stdio.h>

#include "file_interface.h"

int main() {
  BookFile *bookfile = bookfile_load("books.txt");
  if (!bookfile) {
    printf("Failed to load book file.\n");
    return 1;
  }
  if (bookfile_save(bookfile, "books.txt") != 0) {
    printf("Failed to save book file.\n");
    bookfile_free(bookfile);
    return 1;
  }
  bookfile_free(bookfile);
  return 0;
}
