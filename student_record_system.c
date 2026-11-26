/*
 * Student Record System
 * ---------------------
 * A simple menu-driven program in C to add, display, search,
 * update and delete student records.
 * All records are saved in a binary file "students.dat",
 * so the data stays even after the program is closed.
 */

/* stdio.h gives us printf, scanf and all file functions like fopen, fread, fwrite */
#include <stdio.h>

/* stdlib.h gives us exit() to stop the program */
#include <stdlib.h>

/* Name of the file where all student records are stored */
#define FILE_NAME "students.dat"

/* Name of the temporary file used while updating or deleting a record */
#define TEMP_FILE "temp.dat"

/* A structure that groups all the details of one student together */
struct Student {
    int rollNo;           /* Roll number of the student (must be unique) */
    char name[50];        /* Full name of the student (can have spaces) */
    char course[30];      /* Course name, for example BCA or B.Tech */
    int semester;         /* Current semester number */
    char phone[15];       /* Phone number stored as text */
    float percentage;     /* Percentage marks, between 0 and 100 */
};

/* Function declarations (prototypes) so main() knows these functions exist */
void clearInput(void);
int readInt(void);
float readPercentage(void);
int rollExists(int roll);
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
void printHeader(void);
void printStudent(struct Student s);

/*
 * clearInput()
 * Removes any extra characters left in the keyboard buffer
 * (for example, when the user types letters instead of a number).
 */
void clearInput(void) {
    int ch;
    /* Keep reading characters until we reach the end of the line */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* do nothing, just throw the character away */
    }
}

/*
 * readInt()
 * Reads a whole number from the user.
 * If the user types something wrong (like letters), it asks again.
 */
int readInt(void) {
    int value;
    /* scanf returns 1 when it reads a number successfully */
    while (scanf("%d", &value) != 1) {
        /* If the input has ended (Ctrl+D), stop the program safely */
        if (feof(stdin)) {
            printf("\nInput ended. Exiting.\n");
            exit(0);
        }
        /* Wrong input, so clear the buffer and ask again */
        clearInput();
        printf("Invalid input! Please enter a number: ");
    }
    /* Clear the remaining Enter key from the buffer */
    clearInput();
    return value;
}

/*
 * readPercentage()
 * Reads the percentage and makes sure it is between 0 and 100.
 */
float readPercentage(void) {
    float value;
    /* Keep asking until we get a valid number between 0 and 100 */
    while (1) {
        if (scanf("%f", &value) != 1) {
            /* If the input has ended (Ctrl+D), stop the program safely */
            if (feof(stdin)) {
                printf("\nInput ended. Exiting.\n");
                exit(0);
            }
            /* User did not type a number */
            clearInput();
            printf("Invalid input! Enter percentage (0-100): ");
        } else if (value < 0 || value > 100) {
            /* Number is outside the allowed range */
            clearInput();
            printf("Percentage must be between 0 and 100. Try again: ");
        } else {
            /* Valid value, clear the Enter key and return it */
            clearInput();
            return value;
        }
    }
}

/*
 * rollExists()
 * Checks the file to see if a roll number is already used.
 * Returns 1 if it exists, otherwise returns 0.
 */
int rollExists(int roll) {
    struct Student s;
    /* Open the file in "rb" mode = read binary */
    FILE *fp = fopen(FILE_NAME, "rb");

    /* If the file does not exist yet, no roll number can exist */
    if (fp == NULL) {
        return 0;
    }

    /* Read one record at a time until the end of the file */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            fclose(fp);   /* Always close the file before leaving */
            return 1;     /* Found a matching roll number */
        }
    }

    fclose(fp);
    return 0;             /* Roll number not found */
}

/*
 * printHeader()
 * Prints the column titles of the table.
 */
void printHeader(void) {
    printf("-----------------------------------------------------------------------------\n");
    printf("%-8s %-22s %-12s %-5s %-15s %-10s\n",
           "Roll No", "Name", "Course", "Sem", "Phone", "Percentage");
    printf("-----------------------------------------------------------------------------\n");
}

/*
 * printStudent()
 * Prints one student's details as a single row of the table.
 */
void printStudent(struct Student s) {
    /* %-22.22s means: left aligned, 22 wide, and cut if longer than 22 */
    printf("%-8d %-22.22s %-12.12s %-5d %-15s %-10.2f\n",
           s.rollNo, s.name, s.course, s.semester, s.phone, s.percentage);
}

/*
 * addStudent()
 * Takes a new student's details from the user and saves them
 * at the end of the file.
 */
void addStudent(void) {
    struct Student s;
    FILE *fp;

    printf("\n--- Add New Student ---\n");

    /* Ask for roll number and make sure it is positive and not repeated */
    printf("Enter Roll Number: ");
    s.rollNo = readInt();
    if (s.rollNo <= 0) {
        printf("Roll number must be a positive number.\n");
        return;
    }
    if (rollExists(s.rollNo)) {
        printf("A student with roll number %d already exists!\n", s.rollNo);
        return;
    }

    /* " %49[^\n]" reads a full line with spaces (max 49 characters) */
    printf("Enter Name: ");
    scanf(" %49[^\n]", s.name);
    clearInput();

    printf("Enter Course: ");
    scanf(" %29[^\n]", s.course);
    clearInput();

    printf("Enter Semester: ");
    s.semester = readInt();

    /* %14s reads the phone number without spaces (max 14 characters) */
    printf("Enter Phone Number: ");
    scanf(" %14s", s.phone);
    clearInput();

    printf("Enter Percentage (0-100): ");
    s.percentage = readPercentage();

    /* Open the file in "ab" mode = append binary (adds to the end) */
    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Error: could not open file!\n");
        return;
    }

    /* Write the whole structure into the file in one go */
    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

/*
 * displayStudents()
 * Reads every record from the file and shows them in a table.
 */
void displayStudents(void) {
    struct Student s;
    int count = 0;    /* Counts how many records were shown */
    FILE *fp = fopen(FILE_NAME, "rb");

    /* If the file does not open, there is no data saved yet */
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    /* Read and print records one by one */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        /* Print the title and table header only before the first record */
        if (count == 0) {
            printf("\n--- All Student Records ---\n");
            printHeader();
        }
        printStudent(s);
        count++;
    }
    fclose(fp);

    /* The file may exist but be empty (after deleting everyone) */
    if (count == 0) {
        printf("\nNo records found.\n");
    } else {
        printf("-----------------------------------------------------------------------------\n");
        printf("Total students: %d\n", count);
    }
}

/*
 * searchStudent()
 * Finds a student by roll number and shows the details.
 */
void searchStudent(void) {
    struct Student s;
    int roll;
    int found = 0;    /* 0 = not found, 1 = found */
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    roll = readInt();

    /* Go through every record and compare the roll number */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            printf("\nStudent found:\n");
            printHeader();
            printStudent(s);
            found = 1;
            break;    /* Stop searching once we find the student */
        }
    }
    fclose(fp);

    if (found == 0) {
        printf("No student found with roll number %d.\n", roll);
    }
}

/*
 * updateStudent()
 * Changes the details of an existing student.
 * It copies all records to a temp file, writing the new details
 * for the matching student, then replaces the old file with the temp file.
 */
void updateStudent(void) {
    struct Student s;
    int roll;
    int found = 0;
    FILE *fp, *temp;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    roll = readInt();

    /* First check if the student exists before asking for new details */
    if (rollExists(roll) == 0) {
        printf("No student found with roll number %d.\n", roll);
        fclose(fp);
        return;
    }

    /* Open the temp file in "wb" mode = write binary (creates a new empty file) */
    temp = fopen(TEMP_FILE, "wb");
    if (temp == NULL) {
        printf("Error: could not create temp file!\n");
        fclose(fp);
        return;
    }

    /* Copy every record; change only the one we want to update */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            printf("Current details:\n");
            printHeader();
            printStudent(s);

            /* Roll number stays the same, ask for the other details */
            printf("\nEnter new Name: ");
            scanf(" %49[^\n]", s.name);
            clearInput();

            printf("Enter new Course: ");
            scanf(" %29[^\n]", s.course);
            clearInput();

            printf("Enter new Semester: ");
            s.semester = readInt();

            printf("Enter new Phone Number: ");
            scanf(" %14s", s.phone);
            clearInput();

            printf("Enter new Percentage (0-100): ");
            s.percentage = readPercentage();

            found = 1;
        }
        /* Write the record (old or updated) into the temp file */
        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    /* Delete the old file and rename temp file to the real file name */
    remove(FILE_NAME);
    rename(TEMP_FILE, FILE_NAME);

    if (found == 1) {
        printf("Student updated successfully!\n");
    }
}

/*
 * deleteStudent()
 * Removes a student from the file.
 * It copies every record EXCEPT the one to delete into a temp file,
 * then replaces the old file with the temp file.
 */
void deleteStudent(void) {
    struct Student s;
    int roll;
    int found = 0;
    FILE *fp, *temp;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    roll = readInt();

    temp = fopen(TEMP_FILE, "wb");
    if (temp == NULL) {
        printf("Error: could not create temp file!\n");
        fclose(fp);
        return;
    }

    /* Copy all records except the one we want to delete */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.rollNo == roll) {
            found = 1;    /* Skip this record, so it is not copied */
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found == 1) {
        /* Replace the old file with the new one that has no deleted record */
        remove(FILE_NAME);
        rename(TEMP_FILE, FILE_NAME);
        printf("Student with roll number %d deleted successfully!\n", roll);
    } else {
        /* Nothing was deleted, so just throw away the temp file */
        remove(TEMP_FILE);
        printf("No student found with roll number %d.\n", roll);
    }
}

/*
 * main()
 * Program starts here. It shows the menu again and again
 * until the user chooses Exit.
 */
int main(void) {
    int choice;

    /* do-while loop: show the menu at least once, repeat until choice is 6 */
    do {
        printf("\n========================================\n");
        printf("         STUDENT RECORD SYSTEM\n");
        printf("========================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice (1-6): ");
        choice = readInt();

        /* switch-case calls the right function based on the choice */
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Thank you! Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a number from 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
