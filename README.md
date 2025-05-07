# Compile Instruction

Jangan lupa compile file_interface.c juga

```sh
gcc main.c file_interface.c
```

# Flow

Proses buka dan tutup file lewat API `bookfile_load` dan `bookfile_save`. Sisanya hanya manipulasi dan baca struct `BookFile->bookArray`.

Field `size` dan `capacity` untuk penggunaan internal `bookfile_push` dan mungkin `bookfile_delete`. Gunanya untuk keep track ukuran array supaya bisa di-realloc
kalau sudah habis.

Yang sudah implementasi
1. bookfile_load
2. bookfile_save
3. bookfile_new
4. bookfile_push

API `bookfile_push` bisa dipakai untuk flow tambah data. Tinggal simpan input user ke struct Book baru, terus oper ke function ini. Sudah otomatis realloc kalau
size melebihi capacity.
