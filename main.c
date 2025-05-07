#include <stdio.h>

#include "file_interface.h"

int main() {
  BookFile *bookfile = bookfile_load("books.txt");
  if (!bookfile) {
    printf("Failed to load book file.\n");
    return 1;
  }
  bookfile_save(bookfile, "books.txt");
  bookfile_free(bookfile);
  return 0;
}
