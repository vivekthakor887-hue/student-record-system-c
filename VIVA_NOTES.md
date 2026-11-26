# Viva Notes: Student Record System

## How the Program Works (Big Picture)

1. When the program starts, `main()` shows a menu inside a `do-while` loop.
2. The user enters a choice (1 to 6), and `switch-case` calls the matching function.
3. Every student is stored as one `struct Student` record.
4. Records are saved in a **binary file** named `students.dat` using `fwrite()` and read back using `fread()`.
5. Because the data is in a file, it stays saved after the program closes.
6. The menu repeats until the user chooses **6 (Exit)**.

## The Structure

```c
struct Student {
    int rollNo;
    char name[50];
    char course[30];
    int semester;
    char phone[15];
    float percentage;
};
```

One `struct Student` holds all the details of one student. We write the whole struct to the file in one go with `fwrite`, and read it back with `fread`.

## Function by Function

| Function | What it does |
|---|---|
| `main()` | Shows the menu in a loop and uses `switch-case` to call the right function. Stops when the choice is 6. |
| `clearInput()` | Throws away extra characters left in the keyboard buffer (like the Enter key) so the next input works correctly. |
| `readInt()` | Reads a whole number. If the user types letters, it shows an error and asks again. |
| `readPercentage()` | Reads the percentage and keeps asking until the value is between 0 and 100. |
| `rollExists(roll)` | Opens the file in `"rb"` mode, reads every record, and returns 1 if the roll number is already there, otherwise 0. Used to stop duplicate roll numbers. |
| `printHeader()` | Prints the column titles of the table (Roll No, Name, Course...). |
| `printStudent(s)` | Prints one student as one row of the table using `printf` with fixed widths like `%-22s`. |
| `addStudent()` | Takes the details from the user, checks the roll number is new, then opens the file in `"ab"` (append) mode and writes the record at the end with `fwrite`. |
| `displayStudents()` | Opens the file in `"rb"` mode and reads records one by one with `fread` in a `while` loop, printing each row. Shows "No records found" if the file is missing or empty. |
| `searchStudent()` | Asks for a roll number, reads the file record by record, and prints the student if the roll number matches. |
| `updateStudent()` | Copies every record from `students.dat` to `temp.dat`. When it reaches the matching student, it asks for new details and writes the new version instead. Then it deletes the old file with `remove()` and renames `temp.dat` to `students.dat` with `rename()`. |
| `deleteStudent()` | Copies every record **except** the one to delete into `temp.dat`. Then it removes the old file and renames the temp file. If the roll number is not found, it just removes the temp file. |

## Key Input Tricks

- `scanf(" %49[^\n]", s.name);` reads a full line **including spaces** (up to 49 characters). The space before `%` skips any leftover Enter key. `[^\n]` means "read everything until Enter".
- We never use `gets()` because it does not check the size and can overflow the array.
- The numbers `49`, `29` and `14` are one less than the array size, so there is room for the `'\0'` at the end of the string.

---

## 15 Likely Viva Questions (with Easy Answers)

**1. What is a structure (`struct`) in C?**
A structure is a user-defined data type that groups different types of data (int, char array, float) under one name. Here, `struct Student` holds all the details of one student.

**2. Why did you use a structure instead of separate variables?**
It keeps all details of one student together, so we can read or write a full student record with one `fread` or `fwrite`.

**3. Why do we need file handling?**
Without a file, all data is lost when the program closes. File handling saves the data permanently on the disk.

**4. What is the difference between a text file and a binary file?**
A text file stores data as readable characters. A binary file stores data exactly as it is in memory. Binary is easier for saving whole structs with `fwrite`/`fread`.

**5. What does `fopen()` mode `"rb"` mean?**
Read binary. It opens an existing file only for reading. If the file does not exist, `fopen` returns `NULL`.

**6. What does mode `"ab"` mean?**
Append binary. It opens the file and adds new data at the end without deleting old data. If the file does not exist, it creates it.

**7. What does mode `"wb"` mean?**
Write binary. It creates a new empty file. If the file already exists, its old content is erased.

**8. What do `fwrite()` and `fread()` do?**
`fwrite(&s, sizeof(struct Student), 1, fp)` writes one student record to the file. `fread` reads one record from the file into the variable `s`. `fread` returns 1 when it reads a record and 0 at the end of the file.

**9. Why do we check `if (fp == NULL)`?**
`fopen` returns `NULL` when it cannot open the file (for example, the file does not exist yet). Checking this stops the program from crashing.

**10. Why is `fclose()` important?**
It saves any pending data to the disk and frees the file so other parts of the program can use it.

**11. How does delete work using a temp file?**
We read every record from `students.dat` and copy all of them to `temp.dat` **except** the one we want to delete. Then we delete the old file with `remove()` and rename `temp.dat` to `students.dat` with `rename()`.

**12. How does update work?**
Same idea as delete: copy all records to a temp file, but for the matching roll number, write the new details instead of the old ones. Then replace the old file with the temp file.

**13. How do you stop duplicate roll numbers?**
Before adding, the `rollExists()` function reads all records and checks if the roll number is already saved. If it is, we show an error and do not add the student.

**14. Why did you use `do-while` for the menu instead of `while`?**
A `do-while` loop runs at least once, so the menu is shown at least one time before checking the exit condition.

**15. Why not use `gets()` to read the name?**
`gets()` does not check how many characters it reads, so a long name can overflow the array and crash the program. It was removed from the C standard. We use `scanf(" %49[^\n]")`, which reads spaces and has a size limit.

**Bonus: What is `switch-case`?**
It picks one block of code to run based on the value of a variable. Here, it runs the right function for the menu choice, and `default` handles invalid choices.

**Bonus: What does `sizeof(struct Student)` do?**
It gives the size in bytes of one student record, so `fread`/`fwrite` know how many bytes to read or write.
