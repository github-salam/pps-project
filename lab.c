#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// constant variable

#define max_admin 2
#define max_patient 2 // using linked list
#define max_appoinment_patient 2
#define max_doctor_list 2 // using array

// structure for patient record
typedef struct Patient
{
    char name[50];
    int age;
    char gender[10];
    char blood_group[5];
    char cabine_room[10];
    char number[15];
    long long int fees_paid;
    long long int fees_due;
    char deases_details[500];
    char passcode[15];
    struct Patient *next;
} patient;

// structure for admin
typedef struct admin
{
    char username[50];
    char password[50];
    char secret_code[10];
} admin;

// structure for dr list
typedef struct Doctor
{
    char name[50];
    char speciality[20];
    int visit_fee;
    char academic_history[400];
} doctor;

// structure appoinment for patient pannel
typedef struct Appointment
{
    char name[50];
    char number[15];
    long long int confirmation_fee;
    struct Appointment *next;
} appointment;

int count_admin_registration = 0, patient_manage_control = 0, appoinment_manage_control = 0, doctor_control = 0, registration_apeal = 1;

doctor doctors[max_doctor_list];
admin admins[max_admin];
patient *head_patient = NULL;
appointment *head_appointment = NULL;
appointment *tail_appointment = NULL;

// Function prototypes ------------------------- later on
void displayMainMenu();
void displayAdminMenu();
void displayPatientMenu();

// admin login function
void admin_login(char *username, char *password, char *secret_code);

// admin register function
void register_admin(char *username, char *password, char *secret_code);

// ------------------------------patient adding function -----------------------------------
void add_patient();

// ------------------------------doctor adding function -----------------------------------
void add_doctor();

// ------------------------------doctor display function -----------------------------------
void display_doctor();

// -------------------------------patient removing function -----------------------------
void remove_patient();

// ----------------------------- Display all patient --------------------------------
void display_patient();

// ---------------------------- Display a specific patient --------------------------
void display_spec_patient(char name[50]);

// ---------------------------- change patient password -----------------------------
void change_password(patient *p);

// --------------------------- find a patient function -----------------------------
void find_patient();

// -------------------------- Find patient cabin for admin function ----------------
void find_patient_cabin();

// admin wrok function
void admin_work();

// Function to clear the terminal screen
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}

// Function to wait for the user to press Enter
void pressEnterToContinue()
{
    printf("\n\t\t\tPress Enter to continue...");
    while (getchar() != '\n')
        ;      // Clear input buffer
    getchar(); // Wait for Enter
}

// ------------------------ Function for frequently asked question ----------------------
void readFrequentlyAskedQuestions()
{
    FILE *file = fopen("frequently_asked_question.txt", "r");

    if (file == NULL)
    {
        printf("\n\n\t\t\t---> Unable to open the file 'frequently_asked_question.txt'\n\n");
        return;
    }

    printf("\n\n\t\t\t---------------- Frequently Asked Questions ----------------\n\n");

    char line[1000]; // Assuming questions are not longer than 1000 characters
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}

// -------------------------------- linked list functionality usuages here -----------------------------

//----------------------- patient appoinment enqueue --------------------------
void enqueue_appointment()
{
    appointment *new_appointment = malloc(sizeof(appointment));
    if (appoinment_manage_control >= max_appoinment_patient)
    {
        printf("\n\n\t\t\t---> Sorry there are no available seat for appoinment.\n\n");
        free(new_appointment);
        return;
    }

    char name[50], number[15];
    long long int confirmation_fee;

    printf("\n\t\t\tEnter name : ");
    fflush(stdin);
    fgets(name, 50, stdin);
    printf("\t\t\tEnter number : ");
    fgets(number, 15, stdin);
    printf("\t\t\tEnter Confirmation Fees : ");
    scanf("%lld", &confirmation_fee);
    fflush(stdin);

    strcpy(new_appointment->name, name);
    strcpy(new_appointment->number, number);
    new_appointment->confirmation_fee = confirmation_fee;
    new_appointment->next = NULL;

    if (head_appointment == NULL)
    {
        head_appointment = new_appointment;
        tail_appointment = new_appointment;
    }
    else
    {
        tail_appointment->next = new_appointment;
        tail_appointment = new_appointment;
    }
    appoinment_manage_control++;
    printf("\n\n\t\t\t---> Appointment for %s \t\t\t\t\tadded to the queue.\n\n", name);
    pressEnterToContinue();
    clearScreen();
}

// ---------------------------------------- main function started from here ----------------------------------//

int main()
{

    char secret_code[10], username[50], password[50];
    int choose, admin_username_control = 1, choose_pannel;
    int exitLoop = 0; // Flag to control loop exit

    do
    {

        // -------------------- shundor -------------------------------------

        printf("\n\n\n\t\t\t\t\t---------------------------------------------------------\n");
        printf("\t\t------------------------|\tHello and Welcome to 'DIU Tiny Hospital'\t|------------------------\n");
        printf("\t\t\t\t\t---------------------------------------------------------\n");

        // -------------------- shundor -------------------------------------

        printf("\n\n\t\tPlease select your path : \n\n\t\t(1) ADMIN PANEL\t\t\t(2) PATIENT PANEL\t\t\t(3) QUIT\n\n\n");
        printf("\t\tEnter your selection : ");
        scanf("%d", &choose_pannel);

        if (choose_pannel == 1)
        {
            do
            {
                clearScreen();

                // -------------------- shundor -------------------------------------

                printf("\t\t\t\t\t\t-------------------------------------------------\n");
                printf("\t\t--------------------------------|\tHello and Welcome to 'ADMIN PANEL'\t|---------------------\n");
                printf("\t\t\t\t\t\t-------------------------------------------------\n");

                // -------------------- shundor -------------------------------------

                printf("\n\t\t\tChoose an option.\n\t\t\t1) Admin Registration\n\t\t\t2) Admin Login\n\t\t\t3) Back\n\t\t\tEnter Here : ");
                scanf("%d", &choose);
                if (choose == 1)
                {
                    clearScreen();
                    printf("\n\t\t\t ---> Complete the registration process <---\n\n");
                    while (admin_username_control)
                    {
                        printf("\n\t\t\tEnter Username : ");
                        scanf("%s", username);
                        admin_username_control = 0;
                        for (int m = 0; m < count_admin_registration; m++)
                        {
                            if (strcmp(username, admins[m].username) == 0)
                            {
                                printf("\t\t\tUsername is already taken. Try another.\n");
                                admin_username_control = 1; // Set it to 1 to indicate the username is taken
                                break;
                            }
                        }
                        if (admin_username_control == 0)
                        {
                            break; // Exit the loop if the username is not taken
                        }
                    }

                    printf("\t\t\tEnter Password : ");
                    scanf("%s", password);
                    printf("\t\t\tEnter a code for your Identity : ");
                    scanf("%s", secret_code);
                    if (strcmp(secret_code, "1e1f") == 0 || strcmp(secret_code, "2f2e") == 0 || strcmp(secret_code, "3f3f") == 0)
                    {
                        register_admin(username, password, secret_code);
                        admin_username_control = 1;
                    }
                    else
                    {
                        printf("\n\n\t\t\t---> Please collect secret code from authority.\n\n");
                        admin_username_control = 1;
                    }
                    pressEnterToContinue();
                }
                else if (choose == 2)
                {
                    clearScreen();
                    printf("\n\t\t\t ---> Complete login procedure <---\n");
                    printf("\n\t\t\tEnter Username : ");
                    scanf("%s", username);
                    printf("\t\t\tEnter Password : ");
                    scanf("%s", password);
                    printf("\t\t\tEnter a code for your Identity : ");
                    scanf("%s", secret_code);
                    if (strcmp(secret_code, "1e1f") == 0 || strcmp(secret_code, "2f2e") == 0 || strcmp(secret_code, "3f3f") == 0)
                    {
                        clearScreen();
                        admin_login(username, password, secret_code);

                        // ------------------------------- here after login -------------------------
                        if (registration_apeal == 1)
                        {
                            admin_work();
                        }
                        else if (registration_apeal == 0)
                        {
                            continue;
                        }
                        else
                        {
                            printf("\t\t\tPlease registered yourself\n");
                        }
                    }
                    else
                    {
                        printf("Warning!!!, wrong code!\n");
                    }
                    pressEnterToContinue();
                }
                else if (choose == 3)
                {
                    printf("\n\n\t\t\t---> Backing...\n\n");
                    printf("\n\t\t\t\t\t\t\tBacked!\n\n");
                    pressEnterToContinue();
                    clearScreen();
                }
            } while (choose != 3);
        }
        else if (choose_pannel == 2)
        {
            clearScreen();

            do
            {
                printf("\n\n\t\t\t ---> Welcome to patient portal <---\n");

                printf("\n\n\t\t\tChoose an option.\n\t\t\t1) Quick appoinment\n\t\t\t2) Patient Login\n\t\t\t3) Doctor List\n\t\t\t4) Frequently asked question\n\t\t\t5) Back\n\n\t\t\tEnter Here : ");
                scanf("%d", &choose);

                if (choose == 1)
                {
                    clearScreen();
                    printf("\n\t\t\t ---> Give Information for make a appoinment <---\n");
                    enqueue_appointment();
                }
                else if (choose == 2)
                {
                    clearScreen();
                    printf("\n\t\t\t ---> Provide information to login <---\n");
                    printf("\n");
                    find_patient();
                    pressEnterToContinue();
                    clearScreen();
                }
                else if (choose == 3)
                {
                    clearScreen();
                    display_doctor();
                    pressEnterToContinue();
                    clearScreen();
                }
                else if (choose == 4)
                {
                    clearScreen();
                    readFrequentlyAskedQuestions();
                    pressEnterToContinue();
                    clearScreen();
                }
                else if(choose == 5){
                    break;
                }
                else{
                    printf("\n\t\t\t ---> Select valid info <----\n");
                    pressEnterToContinue();
                }

            } while (1);
            clearScreen();
        }
        else
        {
            printf("\n\n\t\t\t\t\t\t---> Quit from all operation <---\n\n");
            printf("\t\t\t\t\t\t\t____________________________\n\n");
        }
    } while (choose_pannel != 3);

    return 0;
}

// ------------------------------------------------- admin login -------------------------------------------

void admin_login(char *username, char *password, char *secret_code)
{
    for (int i = 0; i < max_admin; i++)
    {
        if (strcmp(secret_code, admins[i].secret_code) == 0)
        {
            if ((strcmp(username, admins[i].username) == 0 && strcmp(password, admins[i].password) == 0))
            {
                if (strcmp(admins[i].secret_code, "1e1f") == 0 || strcmp(admins[i].secret_code, "2f2e") == 0 || strcmp(admins[i].secret_code, "3f3f") == 0)
                {
                    // -------------------- shundor -------------------------------------

                    printf("\n\n\n\t\t\t########--------\tWelcome %s! Nice to meet you. Have a great work today.\t--------########\n\n", admins[i].username);

                    // -------------------- shundor -------------------------------------

                    registration_apeal = 1;

                    // ********************************** after admin login ************************

                    return;
                }
            }
            else
            {
                printf("\n\n\t\t\t---> \tIncorrect username or password! Try AGAIN!!!\n\n");
                registration_apeal = 0;
                return;
            }
        }
        if (i < max_admin)
        {
            continue;
        }
        else
        {
            printf("\n\n\t\t\t---> Secret code is incorrect\n\n");
            registration_apeal = 0;
            return;
        }
    }
    printf("\n\n\t\t\t---> Sorry! you are not registered yet.\n\n");
    registration_apeal = 2;
}

//---------------------------------------------------- admin register -------------------------

void register_admin(char *username, char *password, char *secret_code)
{
    if (count_admin_registration >= max_admin)
    {
        printf("\n\n\t\t\t---> Maximum Admins Reached. You cannot be an admin anymore!\n\n");
    }
    else
    {
        strcpy(admins[count_admin_registration].username, username);
        strcpy(admins[count_admin_registration].password, password);
        strcpy(admins[count_admin_registration].secret_code, secret_code);
        count_admin_registration++;
        printf("\n\n\t\t\t---> Congratulations - You can now work as an admin!\n\n");
    }
}

// ------------------------------patient adding function -----------------------------------

void add_patient()
{
    if (patient_manage_control < max_patient)
    {
        patient *new_patient = malloc(sizeof(patient));

        // Input patient details as before
        char name[50], gender[10], blood_group[5], cabine_room[10], number[15], deases_details[500], passcode[15];
        long long int fees_paid, fees_due;
        int age;

        fflush(stdin);
        printf("\n\t\t\tEnter Patient Name : ");
        fgets(name, 50, stdin);

        printf("\t\t\tEnter Patient Age : ");
        scanf("%d", &age);
        fflush(stdin);

        printf("\t\t\tEnter Patient gender : ");
        fgets(gender, 10, stdin);

        printf("\t\t\tEnter Patient Blood Group : ");
        fgets(blood_group, 5, stdin);

        printf("\t\t\tEnter Patient Cabine Room : ");
        fgets(cabine_room, 10, stdin);

        printf("\t\t\tEnter Patient Number : ");
        fgets(number, 15, stdin);

        printf("\t\t\tEnter Patient paid fees : ");
        scanf("%lld", &fees_paid);
        fflush(stdin);

        printf("\t\t\tEnter Patient due fees : ");
        scanf("%lld", &fees_due);
        fflush(stdin);

        printf("\t\t\tEnter Diagonse information : ");
        fgets(deases_details, 500, stdin);

        printf("\t\t\tProvide a passcode for this patient : ");
        fgets(passcode, 15, stdin);

        strcpy(new_patient->name, name);
        new_patient->age = age;
        strcpy(new_patient->gender, gender);
        strcpy(new_patient->blood_group, blood_group);
        strcpy(new_patient->cabine_room, cabine_room);
        strcpy(new_patient->number, number);
        new_patient->fees_paid = fees_paid;
        new_patient->fees_due = fees_due;
        strcpy(new_patient->deases_details, deases_details);
        strcpy(new_patient->passcode, passcode);
        new_patient->next = NULL; // Initialize the next pointer to NULL

        if (head_patient == NULL)
        {
            head_patient = new_patient; // If the list is empty, make the new patient the head
        }
        else
        {
            // Otherwise, traverse the list to find the last patient
            patient *temp_patient = head_patient;
            while (temp_patient->next != NULL)
            {
                temp_patient = temp_patient->next;
            }
            // Update the next pointer of the last patient to point to the new patient
            temp_patient->next = new_patient;
        }

        patient_manage_control++;
        // printf("Patient added successfully\n");

        // Write patient information to the file
        FILE *file = fopen("patient_info.txt", "a");

        if (file == NULL)
        {
            printf("\n\n\t\t\t---> Unable to open the file 'patient_info.txt' for writing\n\n");
            free(new_patient); // Free allocated memory before returning
            return;
        }

        fprintf(file, "Name: %s", new_patient->name);
        fprintf(file, "Age: %d\n", new_patient->age);
        fprintf(file, "Gender: %s", new_patient->gender);
        fprintf(file, "Blood Group: %s", new_patient->blood_group);
        fprintf(file, "Cabin Room: %s", new_patient->cabine_room);
        fprintf(file, "Number: %s", new_patient->number);
        fprintf(file, "Paid Amount: %lld\n", new_patient->fees_paid);
        fprintf(file, "Due Amount: %lld\n", new_patient->fees_due);
        fprintf(file, "Disease Details: %s\n", new_patient->deases_details);
        fprintf(file, "Passcode: %s\n", new_patient->passcode);
        fprintf(file, "\n");

        fclose(file); // Close the file after writing

        printf("\n\n\t\t\t---> Congratulation, Patient registered successfully\n\n");
    }
    else
    {
        printf("\n\n\t\t\t---> Sorry, there are no available slots for more patients!\n\n");
    }
}

// -------------------------------patient removing function -----------------------------

void remove_patient()
{
    patient *new_patient = malloc(sizeof(patient));
    new_patient->next = head_patient;
    patient *temp_patient = new_patient;

    if (patient_manage_control == 0)
    {
        printf("\n\t\t\t--->  No patient to releaze\n\n");
        return;
    }

    char name[50];
    printf("\n\t\t\tEnter patient name : ");
    fflush(stdin);
    fgets(name, 50, stdin);

    while (temp_patient->next != NULL)
    {

        if (strcmp(temp_patient->next->name, name) == 0)
        {
            printf("\n\n\t\t\t%s \t\t\t-->>is release now!\n\n", name);
            patient *free_patient = temp_patient->next;
            temp_patient->next = temp_patient->next->next;
            free(free_patient);
            patient_manage_control--;
            break;
        }
        else
        {
            temp_patient = temp_patient->next;
        }
    }
    head_patient = new_patient->next;
}

// admin wrok function
void admin_work()
{
    int choose_patient_option;
    do
    {
        printf("\n\t\t\tSelect What will you do -\n\t\t\t1) Register a patient\n\t\t\t2) Realese a patient\n\t\t\t3) Find a patients cabin\n\t\t\t4) Display all patients\n\t\t\t5) Add a doctor\n\t\t\t6) Display all doctor\n\t\t\t7) Back\n");
        printf("\t\t\tEnter the option : ");
        scanf("%d", &choose_patient_option);

        if (choose_patient_option == 1)
        {
            clearScreen();
            printf("\n\n\t\t\t ---> Give the information to complete patient registation <---\n\n");
            add_patient();
            pressEnterToContinue();
            clearScreen();
            printf("\n\t\t\t ---> Patient panel <---\n\n");
        }
        else if (choose_patient_option == 2)
        {
            clearScreen();
            printf("\n\n\t\t\t ---> Give the information to remove patient <---\n\n");
            remove_patient();
            pressEnterToContinue();
            clearScreen();
            printf("\n\t\t\t ---> Patient panel <---\n\n");
        }
        else if (choose_patient_option == 3)
        {
            clearScreen();
            printf("\n\n\t\t\t ---> Give the information to find cabin <---\n\n");
            find_patient_cabin();
            pressEnterToContinue();
            clearScreen();
            printf("\n\t\t\t ---> Patient panel <---\n\n");
        }
        else if (choose_patient_option == 4)
        {
            clearScreen();
            display_patient();
            pressEnterToContinue();
            clearScreen();
            printf("\n\t\t\t ---> Patient panel <---\n\n");
        }
        else if (choose_patient_option == 5)
        {
            clearScreen();
            printf("\n\n\t\t\t ---> Give the information to add doctor <---\n\n");
            add_doctor();
            pressEnterToContinue();
            clearScreen();
            printf("\n\t\t\t ---> Patient panel <---\n\n");
        }
        else if (choose_patient_option == 6)
        {
            clearScreen();
            display_doctor();
            pressEnterToContinue();
            clearScreen();
            printf("\n\t\t\t ---> Patient panel <---\n\n");
        }
        else
        {
            printf("\n\n\t\t\t---> Backing...\n\n");
            printf("\n\t\t\t\t\t\t\tBacked!\n\n");
            // pressEnterToContinue();
        }

    } while (choose_patient_option != 7);
}

// ----------------------------- Display all patient --------------------------------

void display_patient()
{
    patient *temp_patient = head_patient;
    if (temp_patient == NULL)
    {
        printf("\n\n\t\t\t--->  Sorry no patient registered yet!\n\n");
    }
    else
    {
        printf("\n\n\t\t\t----------------------Registered Patient--------------------\n\n");
        while (temp_patient != NULL)
        {
            printf("\n\n\t\t\tPatient Name : %s", temp_patient->name);
            printf("\t\t\tPatient Age : %d\n", temp_patient->age);
            printf("\t\t\tPatient Gender : %s", temp_patient->gender);
            printf("\t\t\tPatient Blood Group : %s", temp_patient->blood_group);
            printf("\t\t\tPatient Cabin Room : %s", temp_patient->cabine_room);
            printf("\t\t\tPatient Number : %s", temp_patient->number);
            printf("\t\t\tPatient Paid : %lld\n", temp_patient->fees_paid);
            printf("\t\t\tPatient Due : %lld\n", temp_patient->fees_due);
            printf("\t\t\tPatient Deases : %s\n", temp_patient->deases_details);

            temp_patient = temp_patient->next;
        }
    }
}

// Display specific patient

void display_spec_patient(char name[50])
{
    patient *temp_patient = head_patient;
    while (temp_patient != NULL)
    {
        if (strcmp(temp_patient->name, name) == 0)
        {
            printf("\n\nName : %s", temp_patient->name);
            printf("Age : %d\n", temp_patient->age);
            printf("Gender : %s", temp_patient->gender);
            printf("Blood Group : %s", temp_patient->blood_group);
            printf("Cabin Room : %s", temp_patient->cabine_room);
            printf("Number : %s", temp_patient->number);
            printf("Paid Amount: %lld\n", temp_patient->fees_paid);
            printf("Due Amount: %lld\n", temp_patient->fees_due);
            printf("Deases : %s", temp_patient->deases_details);
            printf("Password : %s\n", temp_patient->passcode);
            break;
        }
    }
}

// Change patient password ---------

void change_password(patient *p)
{
    char new_passcode[15];
    fflush(stdin);
    printf("\t\t\tEnter new passcode : ");
    fgets(new_passcode, 15, stdin);
    strcpy(p->passcode, new_passcode);
    printf("\n\n\t\t\t---> Password have changed!\n");
}

// --------------------------- find a patient function -----------------------------
void find_patient()
{
    char name[50];
    char passcode[15];

    fflush(stdin);
    printf("\n\t\t\tEnter name : ");
    fgets(name, 50, stdin);
    printf("\t\t\tEnter passcode : ");
    fgets(passcode, 15, stdin);

    patient *temp_patient = head_patient;

    while (temp_patient != NULL)
    {
        if (strcmp(temp_patient->name, name) == 0)
        {
            if (strcmp(temp_patient->passcode, passcode) == 0)
            {
                printf("\n\n\t\t\t---> Welcome %s\n\n", temp_patient->name);
                pressEnterToContinue();
                clearScreen();
                int choose_patient_pref;
                do
                {
                    printf("\n\t\t\tLooking at - \n\t\t\t1) My information\n\t\t\t2) Change password\n\t\t\t3) Log Out\n\t\t\tEnter your choose : ");
                    scanf("%d", &choose_patient_pref);

                    if (choose_patient_pref == 1)
                    {
                        pressEnterToContinue();
                        clearScreen();
                        printf("\n\t\t\t ---> My information <---\n");
                        display_spec_patient(name);
                        pressEnterToContinue();
                        clearScreen();
                    }
                    else if (choose_patient_pref == 2)
                    {
                        printf("\n\t\t\t ---> To change password follow instruction <---\n");
                        char old_passcode[15];
                        fflush(stdin);
                        printf("\n\t\t\tEnter old passcode : ");
                        fgets(old_passcode, 15, stdin);

                        if (strcmp(temp_patient->passcode, old_passcode) == 0)
                        {
                            change_password(temp_patient);
                        }
                        else
                        {
                            printf("\n\n\t\t\t---> Wrong password!\n");
                        }
                        pressEnterToContinue();
                        clearScreen();
                    }
                    else if (choose_patient_pref == 3)
                    {
                        printf("\n\n\t\t\t---> Logging...\n\n");
                        printf("\n\t\t\t\t\t\t\tLog Out!\n\n");
                        return;
                    }
                } while (choose_patient_pref != 3);
                break;
            }
            else
            {
                printf("\n\n\t\t\t---> Enter correct password!\n\n");
                break;
            }
        }
        else
        {
            temp_patient = temp_patient->next;
        }
    }

    printf("\n\n\t\t\t---> Sorry there is no such patient exist\n\n");
}

// ------------------------ Find apatient cabin --------------------
void find_patient_cabin()
{
    char name[50];
    printf("\n\t\t\tEnter Patient Name : ");
    fflush(stdin);
    fgets(name, 50, stdin);
    patient *temp_patient = head_patient;

    while (temp_patient != NULL)
    {
        if (strcmp(temp_patient->name, name) == 0)
        {
            printf("\n\t\t\t%s \t\t\t-->>is at cabin room : %s\n\n", temp_patient->name, temp_patient->cabine_room);
            return;
        }
        else
        {
            temp_patient = temp_patient->next;
        }
    }

    printf("\n\t\t\t---> Oh, sorry. There is no such patient\n\n");

    return;
}

// doctor adding using array ----------------------
void add_doctor()
{
    if (doctor_control < max_doctor_list)
    {
        char name[50];
        char speciality[20];
        int visit_fee;
        char academic_history[400];

        fflush(stdin);
        printf("\n\t\t\tEnter doctor name : ");
        fgets(name, 50, stdin);
        printf("\t\t\tEnter speciality : ");
        fgets(speciality, 20, stdin);
        printf("\t\t\tEnter visit fee : ");
        scanf("%i", &visit_fee);
        fflush(stdin);
        printf("\t\t\tEnter doctor academic history : ");
        fgets(academic_history, 400, stdin);

        strcpy(doctors[doctor_control].name, name);
        strcpy(doctors[doctor_control].speciality, speciality);
        doctors[doctor_control].visit_fee = visit_fee;
        strcpy(doctors[doctor_control].academic_history, academic_history);

        printf("\n\n\t\t\t---> Doctor is successfully added to the doctor list\n\n");
        doctor_control++;
    }
    else
    {
        printf("\n\n\t\t\t---> Sorry, Maximum doctors in the doctor list!\n\n");
    }
}

// ------------------------------doctor display function -----------------------------------
void display_doctor()
{
    if (doctor_control == 0)
    {
        printf("\n\n\t\t\t---> This hospital has no dotor currently!\n");
    }
    else
    {
        printf("\n\n\t\t\t---> All doctors information is given below : \n\n");

        int temp_doctor_control = 0;
        for (temp_doctor_control = 0; temp_doctor_control < doctor_control; temp_doctor_control++)
        {
            printf("\t---->Name : %s\n", doctors[temp_doctor_control].name);
            printf("\t\tSpeciality : %s", doctors[temp_doctor_control].speciality);
            printf("\t\tVisiting Fee : %d\n", doctors[temp_doctor_control].visit_fee);
            printf("\t\tEducation Background : %s\n\n", doctors[temp_doctor_control].academic_history);
        }
    }
}

// Display main menu options
void displayMainMenu()
{
    printf("\n\t\t\t\t\t\t---------------------------------------------------------\n");
    printf("\t\t--------------------------------|\tHello and Welcome to 'DIU Tiny Hospital'\t|-----------------------------\n");
    printf("\t\t\t\t\t\t---------------------------------------------------------\n");
    printf("\n\t\tPlease select your path:\n\n");
    printf("\t\t(1) ADMIN PANEL\t\t\t(2) PATIENT PANEL\t\t\t(3) QUIT\n\n");
}

// Display admin menu options
void displayAdminMenu()
{
    printf("\n\t\t\t\t\t\t---------------------------------------------------------\n");
    printf("\t\t--------------------------------|\t\tHello and Welcome to 'ADMIN PANEL'\t|-----------------------------\n");
    printf("\t\t\t\t\t\t---------------------------------------------------------\n");
    printf("\n\t\t\tChoose an option:\n");
    printf("\t\t\t1) Admin Registration\n\t\t\t2) Admin Login\n\t\t\t3) Back\n\n");
}

// Display patient menu options
void displayPatientMenu()
{
    printf("\n\t\t\t\t\t\t---------------------------------------------------------\n");
    printf("\t\t--------------------------------|\tHello and Welcome to 'Patient Portal'\t\t|-----------------------------\n");
    printf("\t\t\t\t\t\t---------------------------------------------------------\n");
    printf("\n\t\t\tChoose an option:\n");
    printf("\t\t\t1) Quick appointment\n\t\t\t2) Patient Login\n\t\t\t3) Doctor List\n\t\t\t4) Frequently asked question\n\t\t\t5) Back\n\n");
}
