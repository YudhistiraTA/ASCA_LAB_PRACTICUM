# Compile Instruction

Jangan lupa compile file_interface.c juga

```sh
gcc main.c file_interface.c
```

# Flow

Proses buka dan tutup file lewat API `file_interface_load` dan `file_interface_save`. Sisanya hanya manipulasi dan baca struct `FileInterface->bookArray` atau `FileInterface->transactionArray`.

Field `size` dan `capacity` untuk penggunaan internal push dan mungkin delete. Gunanya untuk keep track ukuran array supaya bisa di-realloc kalau sudah habis.

API `book_array_push` dan `transaction_array_push` bisa dipakai untuk flow tambah data. Tinggal simpan input user ke struct baru, terus oper ke function ini. Sudah otomatis realloc kalau size melebihi capacity.

# Catatan Menu

Pilihan input dipisah jadi input data buku dan input data transaksi

# Pembagian tugas

0. Load file (databuku.txt dan datatransaksi.txt) - Yudhistira
1. Menu loop - Mas Willy
2. Input Buku - Mbak Refa
3. Input transaksi - Mbak Refa
4. View History - Mbak Seraf
5. View Buku - Mbak Seraf
6. Delete History - Mas Alfian
7. Delete Buku - Mas Alfian
8. Exit (save ke file databuku.txt dan datatransaksi.txt) - Yudhistira