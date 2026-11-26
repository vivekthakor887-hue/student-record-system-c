# Student Record System (C Language)

A simple menu-driven **Student Record System** written in C. You can add, view, search, update and delete student records. All records are saved in a binary file (`students.dat`), so the data is still there after you close the program.

This is a 1st-semester college project, so it only uses basic C concepts.

## Features

- Add a new student (roll number, name, course, semester, phone, percentage)
- Display all students in a neat table
- Search a student by roll number
- Update a student's details
- Delete a student
- Data is saved permanently in a file
- Input checks:
  - Roll numbers cannot repeat
  - Percentage must be between 0 and 100
  - Shows "No records found" when there is no data
  - Asks again if you type letters where a number is expected
- Names and courses can contain spaces (for example "Rahul Kumar Sharma")

## Concepts Used

| Concept | What it does in this project |
|---|---|
| **Structure (`struct`)** | Groups all the details of one student (roll no, name, course, etc.) into one unit. |
| **Functions** | Each task (add, display, search, update, delete) is in its own function, so the code is easy to read. |
| **Arrays** | Character arrays (`char name[50]`) store text like name, course and phone. |
| **Loops** | A `do-while` loop keeps showing the menu; `while` loops read records from the file. |
| **Switch-case** | Calls the correct function based on the menu choice. |
| **If-else** | Used for checks like duplicate roll numbers and valid percentage. |
| **File handling** | `fopen`, `fread`, `fwrite`, `fclose`, `remove` and `rename` save and read data from `students.dat`. |

## How to Run on Mac (Terminal)

1. Open **Terminal** and go to the project folder:
   ```bash
   cd student-record-system-c
   ```
2. Compile the program:
   ```bash
   clang -Wall student_record_system.c -o student_record_system
   ```
3. Run it:
   ```bash
   ./student_record_system
   ```

> If `clang` is not found, install the Xcode command line tools first with `xcode-select --install`.

## How to Run in Xcode (Mac)

1. Open **Xcode**.
2. Click **File > New > Project**.
3. Choose **macOS** at the top, then select **Command Line Tool** and click **Next**.
4. Enter a Product Name (for example `StudentRecordSystem`) and set **Language: C**. Click **Next** and save it anywhere.
5. In the left sidebar, open **main.c**.
6. Delete everything in `main.c` and paste the full code from `student_record_system.c`.
7. Press the **Run** button (▶) at the top left, or press **Cmd + R**.
8. The output shows in the **console at the bottom** of the Xcode window. Click inside the console to type your menu choices.

> Note: In Xcode, `students.dat` is created inside Xcode's build folder, not in your project folder.

## How to Run Online (onlinegdb.com)

1. Go to [https://www.onlinegdb.com](https://www.onlinegdb.com).
2. Select **Language: C** from the dropdown at the top right.
3. Delete the sample code and paste the full code from `student_record_system.c`.
4. Click **Run**.
5. Type your inputs in the console at the bottom.

> Note: Online compilers may delete `students.dat` after the session ends, so saved data may not stay there.

## Sample Output

```
========================================
         STUDENT RECORD SYSTEM
========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Update Student
5. Delete Student
6. Exit
----------------------------------------
Enter your choice (1-6): 1

--- Add New Student ---
Enter Roll Number: 101
Enter Name: Rahul Sharma
Enter Course: BCA
Enter Semester: 1
Enter Phone Number: 9876543210
Enter Percentage (0-100): 85.5
Student added successfully!
```

Display All Students:

```
--- All Student Records ---
-----------------------------------------------------------------------------
Roll No  Name                   Course       Sem   Phone           Percentage
-----------------------------------------------------------------------------
101      Rahul Sharma           BCA          1     9876543210      85.50
102      Priya Patel            B.Tech CSE   1     9123456780      92.25
103      Amit Kumar Singh       BSc IT       2     9988776655      78.00
-----------------------------------------------------------------------------
Total students: 3
```

## Project Files

| File | Purpose |
|---|---|
| `student_record_system.c` | The full C program |
| `README.md` | Project details and how to run it |
| `VIVA_NOTES.md` | How the program works plus common viva questions and answers |
| `.gitignore` | Stops the compiled program and data file from being uploaded |

## Future Scope

- **Login system:** username and password before using the menu
- **GUI:** a window-based interface instead of the text menu
- **Sort by percentage:** show toppers first
- **Export to CSV:** save records in a file that opens in Excel
