#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Declare the Student structure
typedef struct {
    char first_name[100];
    char last_name[100];
    char grade_handled[100];
    char teacher_name[100];
    char project_title[100];
    float amount;
    float project_cost;
    char payment_type[10];
} Student;

// Declare the Teacher structure
typedef struct {
    char name[100];
    char section_name[100];
    char grade_handled[100];
    int num_students_handled;
    char password[100];
} Teacher;

// Function declarations
void loginAsTeacher();
void registerTeacher();
void addHomeroomProject();
void viewParentsRecords();
void viewStudentsRecords();
void login();
void readTeacherData();
void updateStudentRecord(Student student, float remaining_balance);
void parentsInformation();
void viewRecords(char *filename);

// Array to store the information of students who have paid
Student paidStudents[100];
int paidStudentsCount = 0;

// Main function
int main() {

    int loggedIn = 0; // Flag to track if user is logged in
    while (1) { // Infinite loop
        if (!loggedIn) { // If user is not logged in
            system("cls");
            printf("=======================================WELCOME TO HOMEROOM PAYMENT MANAGEMENT SYSTEM====================================\n");
            int choice;
            printf("\nAre you a:\n\n");
            printf("1. Teacher \n");
            printf("2. Principal \n");
            printf("3. Student \n");
            printf("4. Parent\n");
            printf("5. Logout\n");
            printf("Enter your choice (1 to 5): ");
            scanf("%d", &choice);
            getchar();

            switch (choice) {
                case 1:
                    loginAsTeacher();
                    loggedIn = 1;
                    break;
                case 2:
                    loginAsPrincipal();
                    loggedIn = 1;
                    break;
                case 3:
                    loginAsStudent();
                    loggedIn = 1;
                    break;
                case 4:
                    parentsInformation();
                    loggedIn = 1;
                    break;
                case 5:
                    printf("Logged out.\n");
                    return 0; // End the program when logging out
                default:
                    printf("Invalid choice. Please enter a number from 1 to 6.\n");
            }
        } else { // If user is logged in
            int choice;
            printf("1. Continue\n");
            printf("2. Logout\n");
            printf("Enter your choice (1 or 2): ");
            scanf("%d", &choice);
            getchar();

            if (choice == 1) {
                loggedIn = 0; // Continue the loop, prompting for login choice again
            } else if (choice == 2) {
                printf("Logged out.\n");
                return 0; // End the program when logging out
            } else {
                printf("Invalid choice. Please enter 1 or 2.\n");
            }
        }
    }
    return 0;
}

// Function to handle teacher login
void loginAsTeacher() {
    system("cls");
    printf("====================================WELCOME, TEACHER! WHAT WOULD YOU LIKE TO DO?:)======================================\n");

    int choice;
    printf("\nChoose an option:\n\n");
    printf("1. Register\n");
    printf("2. Log in\n");
    printf("3. Exit\n");
    printf("Enter your choice (1 to 3): ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            registerTeacher();
            break;
        case 2:
            login();
            break;
        case 3:
            printf("Exiting teacher login.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 3.\n");
    }
}

// Function to register a teacher
void registerTeacher() {
    system("cls");
    printf("=====================================REGISTER AS A TEACHER===================================\n");

    Teacher teacher;

    printf("\nEnter your name: ");
    fgets(teacher.name, sizeof(teacher.name), stdin);
    printf("Enter the name of your section: ");
    fgets(teacher.section_name, sizeof(teacher.section_name), stdin);
    printf("Enter the grade handled by you: ");
    fgets(teacher.grade_handled, sizeof(teacher.grade_handled), stdin);
    printf("Enter the number of students in your class: ");
    scanf("%d", &teacher.num_students_handled);
    getchar(); // Consume newline character from buffer
    printf("Enter a password: ");
    fgets(teacher.password, sizeof(teacher.password), stdin);

    FILE *fptr = fopen("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\teachers.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(fptr, "Name: %s", teacher.name);
    fprintf(fptr, "Section Name: %s", teacher.section_name);
    fprintf(fptr, "Grade Handled: %s", teacher.grade_handled);
    fprintf(fptr, "Number of Students: %d\n", teacher.num_students_handled);
    fprintf(fptr, "Password: %s\n", teacher.password);

    fclose(fptr);

    printf("Registration successful.\n");

    // Directly call the options menu after registration
    addHomeroomProject();
}

// Function to handle teacher login
void login() {
    system("cls");
    printf("=====================================TEACHER LOGIN===================================\n");

    char name[100];
    char password[100];

    printf("\nEnter your name: ");
    fgets(name, sizeof(name), stdin);
    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);

    // Directly proceed to options menu
    printf("Login successful.\n");
    addHomeroomProject();
}

// Function to handle adding homeroom project by logged-in teacher
void addHomeroomProject() {
    int choice;
    printf("\nChoose an option:\n\n");
    printf("1. Add Homeroom Project\n");
    printf("2. View Parents Homeroom Payment Records\n");
    printf("3. View Students Homeroom Payment Records\n");
    printf("4. View Remaining Balance Records\n");
    printf("5. Logout\n");
    printf("Enter your choice (1 to 5): ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: {
            char name[100];
            char gradeHandled[100];
            char sectionName[100];
            char projectTitle[100];
            float projectCost;
            int studentCount;

            printf("Enter teacher's name: ");
            fgets(name, sizeof(name), stdin);

            printf("Enter grade handled by teacher: ");
            fgets(gradeHandled, sizeof(gradeHandled), stdin);

            printf("Enter name of the section: ");
            fgets(sectionName, sizeof(sectionName), stdin);

            printf("Enter the title of the project: ");
            fgets(projectTitle, sizeof(projectTitle), stdin);

            printf("Enter the total cost of the project: ");
            scanf("%f", &projectCost);

            printf("Enter the number of students in the classroom: ");
            scanf("%d", &studentCount);
            getchar(); // Consume newline character from buffer

            float costPerStudent = projectCost / studentCount;

            time_t now;
            time(&now);
            struct tm *local = localtime(&now);
            char dateTime[100];
            strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", local);

            FILE *fptr = fopen("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\teachers_homeroom_projects.txt", "a");
            if (fptr == NULL) {
                printf("Error opening file for writing.\n");
                return;
            }

            fprintf(fptr, "Date and Time: %s\n", dateTime);
            fprintf(fptr, "Teacher's Name: %s", name);
            fprintf(fptr, "Grade Handled: %s", gradeHandled);
            fprintf(fptr, "Section Name: %s", sectionName);
            fprintf(fptr, "Project Title: %s", projectTitle);
            fprintf(fptr, "Project Cost: %.2f\n", projectCost);
            fprintf(fptr, "Number of Students: %d\n", studentCount);
            fprintf(fptr, "Cost per Student: %.2f\n\n", costPerStudent);

            fclose(fptr);

            printf("Teacher's information written to the file successfully.\n");
            break;
        }
        case 2:
            // View Parents records
            viewRecords("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\parents_records.txt");
            break;
        case 3:
            // View student records
            viewRecords("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\student_records.txt");
            break;
        case 4:
            // View remaining records
            viewRecords("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\remaining_balances.txt");
            break;
        case 5:
            printf("Logged out.\n");
            exit(0); // End the program when logging out
            break;
        default:
            printf("Invalid choice. Please enter a number from 1 to 5.\n");
    }
}

// Function to handle principal login
void loginAsPrincipal() {
    system("cls");
    printf("=====================================WELCOME PRINCIPAL!, WHAT WOULD YOU LIKE TO DO?:)===================================\n");
    printf("\nLogged in as Principal.\n\n");

    int choice;
    printf("\nChoose an option:\n\n");
    printf("1. View Homeroom Projects of Teachers\n");
    printf("2. View Students Homeroom Payment Records\n");
    printf("3. View Parents Homeroom Payment Records\n");
    printf("4. Logout\n");
    printf("Enter your choice (1 to 4): ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1:
            // View homeroom payment
            viewRecords("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\teachers_homeroom_projects.txt");
            break;
        case 2:
            // View student records
            viewRecords("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\student_records.txt");
            break;
        case 3:
            // View parents records
            viewRecords("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\parents_records.txt");
            break;
        case 4:
            printf("Logged out.\n");
            exit(0); // End the program when logging out
        default:
            printf("Invalid choice. Please enter a number from 1 to 4.\n");
    }
}

// Function to handle student login
void loginAsStudent() {
    system("cls");
    printf("=================================WELCOME STUDENT, PLEASE PROVIDE YOUR INFORMATION:)=====================================\n");
     // Declare Student struct variable
    Student student;
    float partial_payment = 0.0; // Declare and initialize partial payment amount

    printf("\nEnter your first name: ");
    fgets(student.first_name, sizeof(student.first_name), stdin);
    printf("Enter your last name: ");
    fgets(student.last_name, sizeof(student.last_name), stdin);
    printf("Enter your grade: ");
    fgets(student.grade_handled, sizeof(student.grade_handled), stdin);
    printf("Enter the name of your teacher: ");
    fgets(student.teacher_name, sizeof(student.teacher_name), stdin);
    printf("Enter the name of your project: ");
    fgets(student.project_title, sizeof(student.project_title), stdin);
    printf("Enter the total amount of the project: ");
    scanf("%f", &student.amount);
    printf("Do you want to pay partially or fully? (partially/fully): ");
    scanf("%s", student.payment_type);
    // Clear input buffer
    while (getchar() != '\n');

    if (strcmp(student.payment_type, "partially") == 0) {
        printf("Enter the partial payment amount: ");
        scanf("%f", &partial_payment);
        // Clear input buffer
        while (getchar() != '\n');

        student.amount -= partial_payment;

        printf("Balance left: %.2f\n", student.amount);
    }

    printf("Student data received.\n");

    // If the student has paid, add them to the array
    if (strcmp(student.payment_type, "fully") == 0 || strcmp(student.payment_type, "partially") == 0) {
        paidStudents[paidStudentsCount] = student;
        paidStudentsCount++;

        // Open the file for writing (in append mode to add new student data)
        FILE *fptr = fopen("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\student_records.txt", "a");
        if (fptr == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        // Write student information to the file
        fprintf(fptr, "Student Name: %s %s\n", student.first_name, student.last_name);
        fprintf(fptr, "Grade: %s\n", student.grade_handled);
        fprintf(fptr, "Teacher's Name: %s\n", student.teacher_name);
        fprintf(fptr, "Project Title: %s\n", student.project_title);
        fprintf(fptr, "Total Amount Paid: %.2f\n", student.amount);
        if (strcmp(student.payment_type, "partially") == 0) {
            fprintf(fptr, "Partial Payment: %.2f\n", partial_payment);
            fprintf(fptr, "Balance Left: %.2f\n", student.amount);
        }
        fprintf(fptr, "Payment Type: %s\n\n", student.payment_type);

        fclose(fptr);

        printf("Student record written to the file successfully.\n");
    }

}

// Function to handle paying remaining balance


// Function to update student record if remaining balance is fully paid
void updateStudentRecord(Student student, float remaining_balance) {
    // Open the file for reading and writing
    FILE *fptr = fopen("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\student_records.txt", "a+");
    if (fptr == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }

    char line[256];
    int found = 0;

    // Loop through each line in the file
    while (fgets(line, sizeof(line), fptr)) {
        // Check if the line contains the student's details
        if (strstr(line, student.first_name) != NULL &&
            strstr(line, student.last_name) != NULL &&
            strstr(line, student.grade_handled) != NULL &&
            strstr(line, student.teacher_name) != NULL &&
            strstr(line, student.project_title) != NULL) {
            found = 1;

            // Move the file pointer back to the beginning of the line
            fseek(fptr, -(strlen(line)), SEEK_CUR);

            // Update the record if remaining balance is zero
            if (remaining_balance == 0) {
                fprintf(fptr, "Student Name: %s %s\n", student.first_name, student.last_name);
                fprintf(fptr, "Grade: %s\n", student.grade_handled);
                fprintf(fptr, "Teacher's Name: %s\n", student.teacher_name);
                fprintf(fptr, "Project Title: %s\n", student.project_title);
                fprintf(fptr, "Payment Type: fully\n\n"); // Update payment type to fully paid
                printf("Remaining balance fully paid. Student record updated.\n");
            } else {
                printf("Remaining balance updated: %.2f\n", remaining_balance);
            }
            break;
        }
    }

    if (!found) {
        printf("Student record successfully stored");
    }

    fclose(fptr);
}


// New function to handle parents' information
// Function to handle parents information
void parentsInformation() {
    system("cls");
    printf("=================================WELCOME PARENT, PLEASE PROVIDE YOUR INFORMATION:)=====================================\n");
    // Declare variables to store parent information
    char parent_name[100];
    char student_name[100];
    char phone_number[20];
    float amount_to_pay;
    char payment_type[10];

    // Prompt user to input parent information
    printf("Enter parent's name: ");
    fgets(parent_name, sizeof(parent_name), stdin);
    printf("Enter student's name: ");
    fgets(student_name, sizeof(student_name), stdin);
    printf("Enter phone number: ");
    fgets(phone_number, sizeof(phone_number), stdin);
    printf("Enter amount to pay: ");
    scanf("%f", &amount_to_pay);
    printf("Do you want to pay partially or fully? (partially/fully): ");
    scanf("%s", payment_type);
    // Clear input buffer
    while (getchar() != '\n');

    // Calculate remaining balance if payment is partial
    float remaining_balance = 0.0;
    if (strcmp(payment_type, "partially") == 0) {
        float partial_payment;
        printf("Enter the partial payment amount: ");
        scanf("%f", &partial_payment);
        // Clear input buffer
        while (getchar() != '\n');

        remaining_balance = amount_to_pay - partial_payment;
    }

    // Get current date and time
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    char dateTime[100];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", local);

    // Write parent information to a separate file
    FILE *fptr_parents = fopen("C:\\Users\\ToffD\\OneDrive\\Desktop\\File handling\\parents_records.txt", "a");
    if (fptr_parents == NULL) {
        printf("Error opening file for writing parent information.\n");
        return;
    }

    // Write parent information to the file
    fprintf(fptr_parents, "Parent's Name: %s\n", parent_name);
    fprintf(fptr_parents, "Student's Name: %s\n", student_name);
    fprintf(fptr_parents, "Phone Number: %s\n", phone_number);
    fprintf(fptr_parents, "Amount to Pay: %.2f\n", amount_to_pay);
    fprintf(fptr_parents, "Payment Type: %s\n", payment_type);
    if (strcmp(payment_type, "partially") == 0) {
        fprintf(fptr_parents, "Remaining Balance: %.2f\n", remaining_balance);
    }
    fprintf(fptr_parents, "Date and Time: %s\n\n", dateTime);

    fclose(fptr_parents);

    printf("Parent information written to the file successfully.\n");
}

// Function to view records from a file
void viewRecords(char *filename) {
    system("cls");
    printf("====================================VIEWING RECORDS FROM FILE========================================\n");
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fptr)) {
        printf("%s", line);
    }

    fclose(fptr);
}
