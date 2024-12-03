#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define file_name "student.dat"
#define TOTAL_CLASSES 50 

typedef struct student
{
   char name[30];
   int id;
   int contact;
   char dob[50];
   char address[100];
   float cgpa;
   char enrolled_couces[200];
   float payment;
   int data_structure_attendance;
   int data_structure_lab_attendance;
   int writing_comprehension_attendance;
   int physics_attendance;
   int electrical_circuit_attendance;
   float totalWaiver;
   struct student *next;
}student;

student *head = NULL;

void loadData()
{
    FILE *file;
    file = fopen(file_name,"rb");
    if(file == NULL){
        printf("No Data Inserted\n");
    }
    student *newStudent;
    while(1)
    {
        newStudent = malloc(sizeof(student));
        if(fread(newStudent,sizeof(student),1,file) !=1){
            free(newStudent);
            break;
        }
        newStudent->next = head;
        head = newStudent;
    }

    fclose(file);
    
}


void saveData()
{
    FILE *file;
    file = fopen(file_name,"wb");
    if(file == NULL){
        printf("Unable to open file\n");
        return;
    }
    student *temp = head;
    while(temp != NULL)
    {
        fwrite(temp,sizeof(student),1,file);
        temp = temp->next;
    }

    fclose(file);
    //printf("Data saved Successfully\n");

}

void addStudent()
{  getchar();
   student *new_student;
   new_student = malloc(sizeof(student));

   printf("Enter Student Name\n");
   fgets(new_student->name,30,stdin);
   strtok(new_student->name,"\n");

   printf("Enter Student ID\n");
   scanf("%d",&new_student->id);

   printf("Enter Mobile Number\n");
   scanf("%d",&new_student->contact);
   
   getchar();
   printf("Enter DOB\n");
   fgets(new_student->dob,50,stdin);
   strtok(new_student->dob,"\n");

   printf("Enter Present Adress\n");
   fgets(new_student->address,100,stdin);
   strtok(new_student->address,"\n");

   new_student->enrolled_couces[0] = '\0';
   
   new_student->next = head;
   head = new_student;

   printf("Student added successfully!\n");
   saveData();
}



void Course(student *head,int id)
{
   student *temp = head;
    while (temp != NULL && temp->id != id)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Error: No student found with ID %d.\n", id);
        return;
    }
    printf("Hello, %s\n", temp->name);
    
    printf("Available Cources for \"Fall-24\"  Are : \n");
    printf("__________________________________________________\n");
    printf("| SN |        Course Title        |  Course Code |\n");
    printf("|____|____________________________|______________|\n");
    printf("| 01 |Data Structure              |    CSE-123   |\n");         
    printf("|____|____________________________|______________|\n");
    printf("| 02 |Data Structure Lab          |    CSE-124   |\n");     
    printf("|____|____________________________|______________|\n");
    printf("| 03 |Writting and Comprehension  |    CSE-102   |\n");
    printf("|____|____________________________|______________|\n");
    printf("| 04 |Physic-2                    |    CSE-102   |\n");
    printf("|____|____________________________|______________|\n");
    printf("| 05 |Electrical Circuit          |    CSE-121   |\n");
    printf("|____|____________________________|______________|\n");

    printf("Write down the Course Code to Enroll: ");
    getchar();
    fgets(temp->enrolled_couces, 200, stdin);
    strtok(temp->enrolled_couces, "\n");

    printf("Courses successfully enrolled for %s!\n", temp->name);
    saveData();

}

void displayStudent() {
    if (head == NULL) {
        printf("\nNo students in the database.\n");
        return;
    }

    // Define column widths
    int nameWidth = 20;             // Increased width for Name
    int idWidth = 12;               // Increased width for ID
    int contactWidth = 15;
    int dobWidth = 10;
    int addressWidth = 25;
    int cgpaWidth = 6;
    int enrolledWidth = 36;         // Increased width for Enrolled Courses

    printf("\n================================================================ STUDENT DATABASE ================================================================\n");
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n", 
           nameWidth, "Name", idWidth, "ID", contactWidth, "Contact", dobWidth, "DOB", addressWidth, "Address", cgpaWidth, "CGPA", enrolledWidth, "Enrolled Courses");
    printf("==================================================================================================================================================\n");

    student *temp = head;
    while (temp != NULL) {
        // Truncate Name and Address if too long
        char truncatedName[21];
        strncpy(truncatedName, temp->name, 20);
        truncatedName[20] = '\0';  // Ensure null-termination
        
        char truncatedAddress[26];
        strncpy(truncatedAddress, temp->address, 25);
        truncatedAddress[25] = '\0';  // Ensure null-termination

        // Truncate Enrolled Courses if too long
        char truncatedCourses[41];
        strncpy(truncatedCourses, temp->enrolled_couces, 40);
        truncatedCourses[40] = '\0';  // Ensure null-termination
        
        // Print student data
        printf("| %-*s | %-*d | %-*d | %-*s | %-*s | %-*.2f | %-*s |\n", 
               nameWidth, truncatedName, idWidth, temp->id, contactWidth, temp->contact, dobWidth, temp->dob, 
               addressWidth, truncatedAddress, cgpaWidth, temp->cgpa, enrolledWidth, 
               temp->enrolled_couces[0] == '\0' ? "Not Enrolled" : truncatedCourses);

        temp = temp->next;
    }

    printf("==================================================================================================================================================\n");
}

void del(student **head,int id){
    student *temp,*prev = NULL;
    temp = *head;

    if(temp != NULL && temp->id == id)
    {
        *head = temp->next;
        free(temp);
        printf("Student with ID = %d removed.\n", id);
        return;
    }
    while(temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL && temp->id != id)
    {
        printf("No Student with this %d Id",id);
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Student with ID = %d removed.\n", id);
    saveData();
}

float calculateGrade(float marks) {
    if (marks >= 80 && marks <= 100)
        return 4.00;
    else if (marks >= 70 && marks <= 79)
        return 3.50;
    else if (marks >= 60 && marks <= 69)
        return 3.00;
    else if (marks >= 50 && marks <= 59)
        return 2.50;
    else if (marks >= 40 && marks <= 49)
        return 2.00;
    else
        return 0.00;
}

void marks(student *head, int id) {
    float m1, m2, m3, m4, m5, s1, s2, s3, s4, s5, cgpa = 0;
    student *temp = head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: No student found with ID %d.\n", id);
        return;
    }

    printf("---- Obtained Marks in the Following Courses ----\n");
    printf("1. Data Structure: ");
    scanf("%f", &m1);
    printf("2. Electrical Circuit: ");
    scanf("%f", &m2);
    printf("3. Physics - 2: ");
    scanf("%f", &m3);
    printf("4. Math - 2: ");
    scanf("%f", &m4);
    printf("5. English - 2: ");
    scanf("%f", &m5);

    s1 = calculateGrade(m1);
    s2 = calculateGrade(m2);
    s3 = calculateGrade(m3);
    s4 = calculateGrade(m4);
    s5 = calculateGrade(m5);

    if (s1 == 0.00 || s2 == 0.00 || s3 == 0.00 || s4 == 0.00 || s5 == 0.00) {
        cgpa = 0.00;
    } else {
        cgpa = (s1 + s2 + s3 + s4 + s5) / 5;
    }
    temp->cgpa = cgpa;

    printf("\nCGPA successfully calculated for %s (ID: %d): %.2f\n", temp->name, temp->id, cgpa);
    saveData();
}

void addPayment(student *head, int id) {
    student *temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: No student found with ID %d.\n", id);
        return;
    }

    float paymentAmount;
    printf("Enter payment amount for %s (ID: %d): ", temp->name, temp->id);
    scanf("%f", &paymentAmount);

    if (paymentAmount < 0) {
        printf("Invalid payment amount. Payment cannot be negative.\n");
        return;
    }

    temp->payment += paymentAmount;
    printf("Payment of %.2f added successfully for %s (ID: %d). Total payment: %.2f\n", 
           paymentAmount, temp->name, temp->id, temp->payment);

    saveData();

}
void viewPayment(student *head, int id) {
    student *temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("\n============================\n");
        printf("   PAYMENT DETAILS\n");
        printf("============================\n");
        printf("Error: Invalid ID!\n");
        printf("============================\n");
        return;
    }
    printf("\n====================================\n");
    printf("          PAYMENT DETAILS\n");
    printf("====================================\n");
    printf("Name         : %s\n", temp->name);
    printf("Paid Amount  : %.2f\n", temp->payment);
    printf("====================================\n");
}


void selfEnroll(student *head, int id) {
    student *temp = head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: No student found with ID %d.\n", id);
        return;
    }

    if (temp->cgpa == 0.00) {
        printf("You are not eligible for enrollment as you have not passed or Marks are not Added yet.\n");
        return;
    }

    if (temp->payment < 33000) {
        printf("You are not eligible for enrollment as the required payment of 33,000 is not made.\n");
        printf("Total payment made: %.2f\n", temp->payment);
        return;
    }

    // Display available courses
    printf("\nAvailable Courses for Self-Enrollment \"Fall-24\":\n");
    printf("__________________________________________________\n");
    printf("| SN |        Course Title        |  Course Code |\n");
    printf("|____|____________________________|______________|\n");
    printf("| 01 |Data Structure              |    CSE-123   |\n");         
    printf("|____|____________________________|______________|\n");
    printf("| 02 |Data Structure Lab          |    CSE-124   |\n");     
    printf("|____|____________________________|______________|\n");
    printf("| 03 |Writing and Comprehension   |    CSE-102   |\n");
    printf("|____|____________________________|______________|\n");
    printf("| 04 |Physics-2                   |    CSE-102   |\n");
    printf("|____|____________________________|______________|\n");
    printf("| 05 |Electrical Circuit          |    CSE-121   |\n");
    printf("|____|____________________________|______________|\n");

    // Allow student to enroll in courses
    printf("\nWrite down the Course Code(s) to Enroll (separate multiple codes with commas): ");
    getchar(); // Clear input buffer
    fgets(temp->enrolled_couces, 200, stdin);
    strtok(temp->enrolled_couces, "\n"); // Remove newline character

    printf("Courses successfully enrolled for %s!\n", temp->name);
    saveData();
}

void updateAttendance(student *head, int id) {
    student *temp = head;

    // Locate the student
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: No student found with ID %d.\n", id);
        return;
    }

    printf("Updating attendance for %s (ID: %d)\n", temp->name, temp->id);
    printf("Enter attendance for the following subjects:\n");

    printf("1. Data Structure: ");
    scanf("%d", &temp->data_structure_attendance);

    printf("2. Data Structure Lab: ");
    scanf("%d", &temp->data_structure_lab_attendance);

    printf("3. Writing and Comprehension: ");
    scanf("%d", &temp->writing_comprehension_attendance);

    printf("4. Physics-2: ");
    scanf("%d", &temp->physics_attendance);

    printf("5. Electrical Circuit: ");
    scanf("%d", &temp->electrical_circuit_attendance);

    printf("Attendance updated successfully for %s (ID: %d).\n", temp->name, temp->id);
    saveData();
}


// For viewing ATTENDANCE !!!!!

void viewAttendance(student *head, int id) {
    student *temp = head;

    // Locate the student
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: No student found with ID %d.\n", id);
        return;
    }

    printf("Attendance record for %s (ID: %d):\n", temp->name, temp->id);
    printf("---------------------------------------------\n");

    printf("1. Data Structure: %d/%d (%.2f%%)\n",
           temp->data_structure_attendance, TOTAL_CLASSES,
           (float)temp->data_structure_attendance / TOTAL_CLASSES * 100);

    printf("2. Data Structure Lab: %d/%d (%.2f%%)\n",
           temp->data_structure_lab_attendance, TOTAL_CLASSES,
           (float)temp->data_structure_lab_attendance / TOTAL_CLASSES * 100);

    printf("3. Writing and Comprehension: %d/%d (%.2f%%)\n",
           temp->writing_comprehension_attendance, TOTAL_CLASSES,
           (float)temp->writing_comprehension_attendance / TOTAL_CLASSES * 100);

    printf("4. Physics-2: %d/%d (%.2f%%)\n",
           temp->physics_attendance, TOTAL_CLASSES,
           (float)temp->physics_attendance / TOTAL_CLASSES * 100);

    printf("5. Electrical Circuit: %d/%d (%.2f%%)\n",
           temp->electrical_circuit_attendance, TOTAL_CLASSES,
           (float)temp->electrical_circuit_attendance / TOTAL_CLASSES * 100);
}

void searchStudent(student *head) {
    int choice;
    int id;
    char name[30];
    float minCGPA, maxCGPA;

    printf("\n=================================================\n");
    printf("                 SEARCH MENU                     \n");
    printf("=================================================\n");
    printf("  [1] Search by ID\n");
    printf("  [2] Search by Name\n");
    printf("  [3] Display Sorted Students (by Name)\n");
    printf("  [4] Display Sorted Students (by CGPA)\n");
    printf("  [5] Search by CGPA Range\n");
    printf("=================================================\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    student *temp = head;
    student *sortedList = NULL, *current, *newNode;

    switch (choice) {
        case 1:
            printf("\nEnter Student ID: ");
            scanf("%d", &id);

            while (temp != NULL) {
                if (temp->id == id) {
                    printf("\nStudent Found:\n");
                    printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
                    return;
                }
                temp = temp->next;
            }
            printf("\nStudent with ID %d not found.\n", id);
            break;

        case 2:
            printf("\nEnter Student Name: ");
            fgets(name, 30, stdin);
            strtok(name, "\n");

            while (temp != NULL) {
                if (strcmp(temp->name, name) == 0) {
                    printf("\nStudent Found:\n");
                    printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
                    return;
                }
                temp = temp->next;
            }
            printf("\nStudent with name %s not found.\n", name);
            break;

        case 3:
            while (temp != NULL) {
                newNode = malloc(sizeof(student));
                *newNode = *temp;
                newNode->next = NULL;

                if (sortedList == NULL || strcmp(newNode->name, sortedList->name) < 0) {
                    newNode->next = sortedList;
                    sortedList = newNode;
                } else {
                    current = sortedList;
                    while (current->next != NULL && strcmp(current->next->name, newNode->name) < 0) {
                        current = current->next;
                    }
                    newNode->next = current->next;
                    current->next = newNode;
                }
                temp = temp->next;
            }

            printf("\nSorted Students (by Name):\n");
            temp = sortedList;
            while (temp != NULL) {
                printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
                temp = temp->next;
            }
            break;

        case 4:
            while (temp != NULL) {
                newNode = malloc(sizeof(student));
                *newNode = *temp;
                newNode->next = NULL;

                if (sortedList == NULL || newNode->cgpa > sortedList->cgpa) {
                    newNode->next = sortedList;
                    sortedList = newNode;
                } else {
                    current = sortedList;
                    while (current->next != NULL && current->next->cgpa > newNode->cgpa) {
                        current = current->next;
                    }
                    newNode->next = current->next;
                    current->next = newNode;
                }
                temp = temp->next;
            }

            printf("\nSorted Students (by CGPA):\n");
            temp = sortedList;
            while (temp != NULL) {
                printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
                temp = temp->next;
            }
            break;

        case 5:
            printf("\nEnter Minimum CGPA: ");
            scanf("%f", &minCGPA);
            printf("Enter Maximum CGPA: ");
            scanf("%f", &maxCGPA);

            printf("\nStudents with CGPA in Range %.2f - %.2f:\n", minCGPA, maxCGPA);
            while (temp != NULL) {
                if (temp->cgpa >= minCGPA && temp->cgpa <= maxCGPA) {
                    printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
                }
                temp = temp->next;
            }
            break;

        default:
            printf("\nInvalid choice. Please try again.\n");
    }
}

void waiverCalculator(student *head) {
    int userType;
    int id;
    float cgpa;
    float totalWaiver = 0.0;
    char condition[20];
    char password[20];

    printf("\n=================================================\n");
    printf("              WAIVER CALCULATOR                 \n");
    printf("=================================================\n");
    printf("  [1] User Mode\n");
    printf("  [2] Admin Mode\n");
    printf("=================================================\n");
    printf("\nEnter your choice: ");
    scanf("%d", &userType);

    switch (userType) {
        case 1:
            printf("\nEnter Student ID: ");
            scanf("%d", &id);

            student *temp = head;
            while (temp != NULL) {
                if (temp->id == id) {
                    printf("\nStudent Found:\n");
                    printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
                    printf("Your Total Waiver: %.2f%%\n", temp->totalWaiver);
                    return;
                }
                temp = temp->next;
            }

            printf("\nStudent with ID %d not found.\n", id);
            break;

        case 2: 
            printf("\nEnter Admin Password: ");
            scanf("%s", password);

            if (strcmp(password, "admin123") != 0) {
                printf("\nIncorrect Password. Access Denied.\n");
                return;
            }
            printf("\nEnter the Student ID to calculate waiver: ");
            scanf("%d", &id);

            student *tempAdmin = head;
            while (tempAdmin != NULL) {
                if (tempAdmin->id == id) {
                    cgpa = tempAdmin->cgpa;
                    printf("\nStudent Found:\n");
                    printf("Name: %s, ID: %d, CGPA: %.2f\n", tempAdmin->name, tempAdmin->id, cgpa);

                    if (cgpa == 4.0) {
                        printf("Base Waiver: 50%%\n");
                        totalWaiver = 50.0;
                    } else if (cgpa >= 3.9) {
                        printf("Base Waiver: 35%%\n");
                        totalWaiver = 35.0;
                    } else if (cgpa >= 3.8) {
                        printf("Base Waiver: 25%%\n");
                        totalWaiver = 25.0;
                    } else {
                        printf("Base Waiver: 0%%\n");
                        totalWaiver = 0.0;
                    }
                    printf("\nWould you like to apply extra waivers? (Y/N): ");
                    scanf("%s", condition);

                    if (strcmp(condition, "Y") == 0 ||strcmp(condition, "y") == 0 ) {
                        int reason;
                        printf("\nSelect reason for extra waiver:\n");
                        printf("  [1] Financial Assistance\n");
                        printf("  [2] Dean Approval\n");
                        printf("  [3] Other\n");
                        printf("Enter your choice: ");
                        scanf("%d", &reason);

                        switch (reason) {
                            case 1:
                                printf("Applying 20%% waiver for Financial Assistance.\n");
                                totalWaiver += 20.0;
                                break;
                            case 2:
                                printf("Applying 15%% waiver for Dean Approval.\n");
                                totalWaiver += 15.0;
                                break;
                            case 3:
                                printf("Enter custom waiver percentage: ");
                                float customWaiver;
                                scanf("%f", &customWaiver);
                                totalWaiver += customWaiver;
                                break;
                            
                            default:
                                printf("Invalid choice. No extra waiver applied.\n");
                        }
                    }
                    if (totalWaiver > 100.0) {
                        totalWaiver = 100.0;
                    }
                    tempAdmin->totalWaiver = totalWaiver;

                    printf("\nTotal Waiver Granted: %.2f%%\n", totalWaiver);
                    return;
                }
                tempAdmin = tempAdmin->next;
            }

            printf("\nStudent with ID %d not found.\n", id);
            break;

        default:
            printf("\nInvalid choice. Please try again.\n");
    }
}

void showWaiverPercentage(student *head) {
    int id;
    printf("\n====================================\n");
    printf("      SHOW WAIVER PERCENTAGE        \n");
    printf("====================================\n");

    printf("Enter Student ID: ");
    scanf("%d", &id);

    student *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nStudent Found:\n");
            printf("Name: %s, ID: %d, CGPA: %.2f\n", temp->name, temp->id, temp->cgpa);
            printf("Total Waiver Percentage: %.2f%%\n", temp->totalWaiver);
            return;
        }
        temp = temp->next;
    }

    printf("\nStudent with ID %d not found.\n", id);
}


void menu(char *checker) {
    int choice;
    int id;

    while (1) {
        printf("\n");
        printf("=================================================\n");
        printf("        Student Database Management System      \n");
        printf("=================================================\n");

        if (strcmp(checker, "admin") == 0) {
            printf("  Admin Menu:\n");
            printf("-------------------------------------------------\n");
            printf("  [1] Add Student\n");
            printf("  [2] Display Students\n");
            printf("  [3] Enroll in Courses\n");
            printf("  [4] Delete Student\n");
            printf("  [5] Add Marks\n");
            printf("  [6] Add Payment\n");
            printf("  [7] Update Attendance\n");
            printf("  [8] View Attendance\n");
            printf("  [9] Show Payment Details\n");
            printf("  [10] Search Students\n");
            printf("  [11] Waiver Calculation\n");
            printf("  [0] Exit\n");
            printf("-------------------------------------------------\n");
        } else {
            printf("  User Menu:\n");
            printf("-------------------------------------------------\n");
            printf("  [1] Display Students\n");
            printf("  [2] Self Enrollement\n");
            printf("  [3] Show Attendance\n");
            printf("  [4] Show Payment Details\n");
            printf("  [5] Show Waiver Details\n");
            printf("  [0] Exit\n");
            printf("-------------------------------------------------\n");
        }

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        system("cls");

        if (strcmp(checker, "admin") == 0) {
            switch (choice) {
                case 1: 
                    addStudent(); 
                    break;
                case 2: 
                    displayStudent(); 
                    break;
                case 3: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    Course(head, id); 
                    break;
                case 4: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    del(&head, id);
                    break;
                case 5: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    marks(head, id);
                    break;
                case 6: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    addPayment(head, id);
                    break;
                case 7: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    updateAttendance(head, id);
                    break;
                case 8: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    viewAttendance(head, id);
                    break;
                case 9: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    viewPayment(head, id);
                    break;

                case 10:
                    searchStudent(head);
                    break;

                case 11:
                waiverCalculator(head);
                break;
    

                case 0: 
                    saveData();
                    exit(0);
                default: 
                    printf("\nInvalid choice. Please try again.\n");
            }
        } 
        else {
            switch (choice) {
                case 1: 
                    displayStudent(); 
                    break;
                case 2: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    selfEnroll(head, id); 
                    break;
                case 3: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    viewAttendance(head, id);
                    break;
                case 4: 
                    printf("\nEnter Student ID: ");
                    scanf("%d", &id);
                    viewPayment(head, id);
                    break;
                case 5:
                    showWaiverPercentage(head);
                    break;
                case 0: 
                    saveData();
                    exit(0);
                default: 
                    printf("\nInvalid choice. Please try again.\n");
            }
        }

        printf("\n");
    }
}

int main() {
    int choice;
    char user[50];
    char password[50];

    while (1) {
        printf("\n=====================================================\n");
        printf("  Welcome to the Student Database Management System\n");
        printf("=====================================================\n");
        printf("  [1] Log in as Admin\n");
        printf("  [2] Log in as Student\n");
        printf("  [0] Exit\n");
        printf("=====================================================\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        system("cls");

        switch (choice) {
            case 1:
                printf("\n--- Admin Login ---\n");
                printf("Enter User Name: ");
                scanf("%s", user);
                printf("Enter Password: ");
                scanf("%s", password);

                if (strcmp(user, "1") == 0 && strcmp(password, "1") == 0) {
                    loadData();
                    menu("admin");
                } else {
                    printf("\nIncorrect Admin Credentials. Please try again.\n");
                }
                break;

            case 2:
                printf("\n--- Student Login ---\n");
                printf("Enter User Name: ");
                scanf("%s", user);
                printf("Enter Password: ");
                scanf("%s", password);

                if (strcmp(user, "2") == 0 && strcmp(password, "2") == 0) {
                    loadData();
                    menu("user");
                } else {
                    printf("\nIncorrect Student Credentials. Please try again.\n");
                }
                break;

            case 0:
                printf("\n==================================================\n");
                printf("          Exiting the System. Goodbye!           \n");
                printf("==================================================\n");

                exit(0);

            default:
                printf("\nInvalid choice. Please select a valid option.\n");
        }
    }
}
