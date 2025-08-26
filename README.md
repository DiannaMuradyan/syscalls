# 🖥️ Linux Syscall Demo in C (with Inline Assembly)

This project demonstrates the use of **Linux system calls** directly via **inline assembly** in C, without using the standard C library (`libc`).  

It includes implementations for file I/O, process termination, memory management (`brk`/`sbrk`), and helper functions like `itoa` and `strlen`.  
The program showcases how syscalls are invoked at a low level and how memory can be managed manually.

---

## 🚀 Features

- **Implemented Syscalls:**
  - `open` → Open a file
  - `read` → Read data from a file
  - `write` → Write data to file or stdout
  - `close` → Close a file
  - `exit` → Exit the program
  - `brk` / `sbrk` → Manage heap memory  

- **Helper Functions:**
  - `itoa(int num, char* str)` → Convert integer to string
  - `strlength(char* str)` → Get string length  

- **Memory Management:**
  - Reserve additional memory (`1MB`) using `sbrk`.
  - Cast newly allocated memory for use as buffer.  

- **File I/O Demo:**
  - Opens `file.txt`
  - Reads up to `1000` bytes into allocated buffer
  - Converts the number of bytes read into a string
  - Prints the result:  
    ```
    <n> : bytes have been read
    ```

---

## 📂 Project Structure

```
.
├── syscall_demo.c # Main source file (inline assembly + syscalls)
├── file.txt # Input file to test reading
└── README.md # Documentation
```
---

## 🏗️ Compilation and Running

Since this program does not use `main()` but rather `_start()`, compile with `gcc` but **disable linking to libc**:

```bash
gcc -nostdlib -no-pie -o syscall_demo syscall_demo.c
./syscall_demo
```
