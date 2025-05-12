#include <stdio.h>
#define BOOK_FILE "databuku.txt"
#define TRANSACTION_FILE "datatransaksi.txt"

#include "file_interface.h"

int main() {
  /** Data loading start */
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
  /** Data loading end */

  /** Main loop */
  while (0) {
  }
  /** Main loop end*/


  /** Data saving */
  if (file_interface_save(fileInterface, BOOK_FILE, ITEM) != 0) {
    printf("Failed to save book file.\n");
    file_interface_free(fileInterface);
    return 1;
  }
  if (file_interface_save(fileInterface, TRANSACTION_FILE, TRANSACTION) != 0) {
    printf("Failed to save transaction file.\n");
    file_interface_free(fileInterface);
    return 1;
  }
  /** Data saving end*/

  file_interface_free(fileInterface);
  return 0;
}
