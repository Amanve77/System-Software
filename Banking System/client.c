#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void role_selection_menu(int sock);

void send_request(int sock, const char *request) {
    if (write(sock, request, strlen(request)) < 0) {
        perror("Write failed");
        close(sock);
        exit(1);  // Handle the error directly inside the function.
    }
}

void receive_response(int sock, char *buffer, size_t buffer_size) {
    int bytes_read = read(sock, buffer, buffer_size);
    if (bytes_read < 0) {
        perror("Error receiving data from server");
        close(sock);
        exit(1);
    }
    buffer[bytes_read] = '\0'; 
}

void receive_tresponse(int sock) {
    char buffer[BUFFER_SIZE];

    while (1) {
        ssize_t bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) {
            perror("Error receiving data");
            break;
        }
        buffer[bytes] = '\0';  // Null-terminate the buffer
        if (strcmp(buffer, "END") == 0) {
            break;  // Stop reading if "END" is received
        }
        printf("%s", buffer);  // Print the received transaction
    }
}

void display_customer_menu(int sock) {
    int choice;
    char buffer[BUFFER_SIZE];
    while (1) {
        printf("\n--- Customer Menu ---\n");
        printf("1. View Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Funds\n");
        printf("5. Apply for a Loan\n");
        printf("6. Change Password\n");
        printf("7. Adding Feedback\n");
        printf("8. View Transaction History\n");
        printf("9. Logout\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        

        switch (choice) {
            case 1:
                // Send request to server to view balance
                send_request(sock, "VIEW_BALANCE");
                // Receive and display balance
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("Your Balance: %s\n", buffer);
                break;
            case 2:
                // Handle deposit
                send_request(sock, "DEPOSIT_MONEY");
                printf("Enter amount to deposit: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                float depo = atof(buffer);
                sprintf(buffer, "%.2f", depo);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 3:
                // Handle withdrawal
                send_request(sock, "WITHDRAW_MONEY");
                printf("Enter amount to withdraw: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                float with = atof(buffer);
                sprintf(buffer, "%.2f", with);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 4:
                // Handle withdrawal
                send_request(sock, "TRANSFER_FUNDS");
                printf("Enter user ID of receiver:");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                //read(sock, buffer, BUFFER_SIZE);
                printf("Enter amount to transfer: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 5:
                // Handle withdrawal
                send_request(sock, "APPLY_LOAN");
                printf("Enter amount of loan: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                float loan = atof(buffer);
                sprintf(buffer, "%.2f", loan);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 6:
                // Handle withdrawal
                send_request(sock, "CHANGE_PWD");
                printf("Enter new password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 7:
                // Handle withdrawal
                send_request(sock, "FEEDBACK");
                printf("Enter your feedback: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 8:
                // Handle withdrawal
                send_request(sock, "VIEW_TRANSACTION");
                // Receive and display the transaction history
                printf("Transaction History:\n");
                receive_tresponse(sock);
                break;
            case 9:
                // Handle withdrawal
                send_request(sock, "LOGOUT");
                receive_response(sock, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                close(sock);
                return;
            case 10:
                close(sock);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        fflush(stdout);
    }
}

void display_employee_menu(int sock) {
    int choice;
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("\n--- Employee Menu ---\n");
        printf("1. Add New Customer\n");
        printf("2. Manage Customer Accounts\n");
        printf("3. View Assigned Loan Applications\n");
        printf("4. Approve Loans\n");
        printf("5. View Customer Transactions\n");
        printf("6. Change Password\n");
        printf("7. Logout\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                // Implement account management logic
                send_request(sock, "ADD_CUSTOMER");

                printf("Enter User ID: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter First Name: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter Last Name: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter Password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; 
                send_request(sock, buffer);

                printf("Enter Balance: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  
                send_request(sock, buffer);

                printf("Enter Loan Amount: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  
                send_request(sock, buffer);

                printf("Enter Status: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  
                send_request(sock, buffer);

                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 2:
                char buffer[BUFFER_SIZE];
                int uid2;

                    // Prompt user for customer ID
                    printf("Enter Customer ID to manage: ");
                    scanf("%d", &uid2);
                    snprintf(buffer, sizeof(buffer), "%d", uid2);
                    send_request(sock, "MANAGE_CUSTOMER");
                    write(sock, buffer, strlen(buffer)); // Send Customer ID to server

                    // Receive customer details
                    receive_response(sock, buffer, BUFFER_SIZE);
                    printf("%s\n", buffer); // Display customer details

                    // Prompt for action (modify, delete, reset password)
                    printf("Select an option:\n");
                    printf("1. Modify Customer\n");
                    printf("2. Delete Customer\n");
                    printf("3. Reset Password\n");
                    printf("4. Exit\n");
                    int option;
                    scanf("%d", &option);
                    snprintf(buffer, sizeof(buffer), "%d", option);
                    write(sock, buffer, strlen(buffer)); // Send option to server

                    switch (option) {
                        case 1: // Modify Customer
                            {
                                float new_balance, new_loan;
                                char new_fname[50], new_lname[50], new_status[20];

                                printf("Enter new first name: ");
                                scanf("%s", new_fname);
                                write(sock, new_fname, strlen(new_fname)); // Send new balance

                                // Get new loan amount
                                printf("Enter new second name: ");
                                scanf("%s", new_lname);
                                write(sock, new_lname, strlen(new_lname));

                                // Get new balance
                                printf("Enter new balance: ");
                                scanf("%f", &new_balance);
                                snprintf(buffer, sizeof(buffer), "%.2f", new_balance);
                                write(sock, buffer, strlen(buffer)); // Send new balance

                                // Get new loan amount
                                printf("Enter new loan amount: ");
                                scanf("%f", &new_loan);
                                snprintf(buffer, sizeof(buffer), "%.2f", new_loan);
                                write(sock, buffer, strlen(buffer)); // Send new loan amount

                                // Get new status
                                printf("Enter new status: ");
                                scanf("%s", new_status);
                                write(sock, new_status, strlen(new_status)); // Send new status

                                // Receive response from server
                                receive_response(sock, buffer, BUFFER_SIZE);
                                printf("%s\n", buffer);
                            }
                            break;

                        case 2: // Delete Customer
                            // No additional data needed, just receive response
                            receive_response(sock, buffer, BUFFER_SIZE);
                            printf("%s\n", buffer);
                            break;

                        case 3: // Reset Password
                            {
                                char new_password[50];

                                // Get new password
                                printf("Enter new password: ");
                                scanf("%s", new_password);
                                write(sock, new_password, strlen(new_password)); // Send new password

                                // Receive response from server
                                receive_response(sock, buffer, BUFFER_SIZE);
                                printf("%s\n", buffer);
                            }
                            break;

                        case 4: // Exit
                            // Receive exit confirmation message
                            receive_response(sock, buffer, BUFFER_SIZE);
                            printf("%s\n", buffer);
                            break;

                        default:
                            printf("Invalid option.\n");
                            break;
                    }
                break;
            case 3:
                send_request(sock, "VIEW_LOAN_APPL");
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("Loan Application Details:\n%s\n", buffer);
                break;
            case 4:
                send_request(sock, "APP/REJ_LOANS");

                printf("Enter Loan ID to update: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);  // Send loan ID

                printf("Enter new status (Approved/Rejected): ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);  // Send new status

                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 5:
                send_request(sock, "VIEW_CUST_TRANS");
                break;
            case 6:
                // Handle withdrawal
                send_request(sock, "CHANGE_PWD");
                printf("Enter new password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 7:
                // Handle withdrawal
                send_request(sock, "LOGOUT");
                receive_response(sock, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                close(sock);
                return;
            case 8:
                close(sock);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        fflush(stdout);
    }
}


void display_manager_menu(int sock) {
    int choice;
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("\n--- Manager Menu ---\n");
        printf("1. Activate/Deactivate Customer Accounts\n");
        printf("2. Assign Loan Application Process to Employees\n");
        printf("3. Review Customer Feedback\n");
        printf("4. Change Password\n");
        printf("5. Logout\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                char action[20];
                send_request(sock, "ACT/DEACT CUST ACC");

                printf("Enter User ID: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter action (ACTIVATE/DEACTIVATE): ");
                fgets(action, sizeof(action), stdin);
                action[strcspn(action, "\n")] = '\0';  // Remove newline

                send_request(sock, action);  // Send action

                receive_response(sock, buffer, BUFFER_SIZE);  // Get server response
                printf("%s\n", buffer);
                break;
            case 2:
                int empID;
                send_request(sock, "ASSIGN LOAN");

                printf("Enter Loan ID: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter Employee ID to assign the loan: ");
                scanf("%d", &empID);
                getchar();
                sprintf(buffer, "%d", empID);
                send_request(sock, buffer);  // Send Employee ID

                receive_response(sock, buffer, BUFFER_SIZE);  // Receive response
                printf("%s\n", buffer);
                break;
            case 3:
                send_request(sock, "VIEW_FEEDBACK");  // Request feedback

                printf("Customer Feedback:\n");
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);  // Display all feedback

                printf("Enter Feedback ID to mark as 'Reviewed': ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
                send(sock, buffer, strlen(buffer), 0);  // Send feedback ID to server

                // Receive confirmation message
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
            case 4:
                send_request(sock, "CHANGE_PWD");
                printf("Enter new password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 5:
                send_request(sock, "LOGOUT");
                receive_response(sock, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                close(sock);
                return;
            case 6:
                close(sock);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void display_admin_menu(int sock) {
    int choice;
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("\n--- Administrator Menu ---\n");
        printf("1. Add New Bank Employee\n");
        printf("2. Modify Customer/Employee Details\n");
        printf("3. Manage User Roles\n");
        printf("4. Change Password\n");
        printf("5. Logout\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                send_request(sock, "ADD_EMPLOYEE");

                printf("Enter Employee ID: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter First Name: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter Last Name: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';
                send_request(sock, buffer);

                printf("Enter Password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0'; 
                send_request(sock, buffer);

                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 2:
                int c;
                printf("1. Modify Employee Details\n");
                printf("2. Modify Customer Details\n");
                printf("Enter Your choice: ");
                scanf("%d", &c);
                getchar();
                if(c == 1)
                {
                    int uid2;

                    // Prompt user for customer ID
                    printf("Enter Customer ID to manage: ");
                    scanf("%d", &uid2);
                    snprintf(buffer, sizeof(buffer), "%d", uid2);
                    send_request(sock, "MANAGE_CUSTOMER");
                    write(sock, buffer, strlen(buffer)); // Send Customer ID to server

                    // Receive customer details
                    receive_response(sock, buffer, BUFFER_SIZE);
                    printf("%s\n", buffer); // Display customer details

                    // Prompt for action (modify, delete, reset password)
                    printf("Select an option:\n");
                    printf("1. Modify Customer\n");
                    printf("2. Delete Customer\n");
                    printf("3. Reset Password\n");
                    printf("4. Exit\n");
                    int option;
                    scanf("%d", &option);
                    snprintf(buffer, sizeof(buffer), "%d", option);
                    write(sock, buffer, strlen(buffer)); // Send option to server

                    switch (option) {
                        case 1: // Modify Customer
                            {
                                float new_balance, new_loan;
                                char new_fname[50], new_lname[50], new_status[20];

                                printf("Enter new first name: ");
                                scanf("%s", new_fname);
                                write(sock, new_fname, strlen(new_fname)); // Send new balance

                                // Get new loan amount
                                printf("Enter new second name: ");
                                scanf("%s", new_lname);
                                write(sock, new_lname, strlen(new_lname));

                                // Get new balance
                                printf("Enter new balance: ");
                                scanf("%f", &new_balance);
                                snprintf(buffer, sizeof(buffer), "%.2f", new_balance);
                                write(sock, buffer, strlen(buffer)); // Send new balance

                                // Get new loan amount
                                printf("Enter new loan amount: ");
                                scanf("%f", &new_loan);
                                snprintf(buffer, sizeof(buffer), "%.2f", new_loan);
                                write(sock, buffer, strlen(buffer)); // Send new loan amount

                                // Get new status
                                printf("Enter new status: ");
                                scanf("%s", new_status);
                                write(sock, new_status, strlen(new_status)); // Send new status

                                // Receive response from server
                                receive_response(sock, buffer, BUFFER_SIZE);
                                printf("%s\n", buffer);
                            }
                            break;

                        case 2: // Delete Customer
                            // No additional data needed, just receive response
                            receive_response(sock, buffer, BUFFER_SIZE);
                            printf("%s\n", buffer);
                            break;

                        case 3: // Reset Password
                            {
                                char new_password[50];

                                // Get new password
                                printf("Enter new password: ");
                                scanf("%s", new_password);
                                write(sock, new_password, strlen(new_password)); // Send new password

                                // Receive response from server
                                receive_response(sock, buffer, BUFFER_SIZE);
                                printf("%s\n", buffer);
                            }
                            break;

                        case 4: // Exit
                            // Receive exit confirmation message
                            receive_response(sock, buffer, BUFFER_SIZE);
                            printf("%s\n", buffer);
                            break;

                        default:
                            printf("Invalid option.\n");
                            break;
                    }
                } 
                if(c == 2)
                {
                    int uid2;

                    // Prompt user for customer ID
                    printf("Enter Employee ID to manage: ");
                    scanf("%d", &uid2);
                    snprintf(buffer, sizeof(buffer), "%d", uid2);
                    send_request(sock, "MANAGE_EMPLOYEE");
                    write(sock, buffer, strlen(buffer)); // Send Customer ID to server

                    // Receive customer details
                    receive_response(sock, buffer, BUFFER_SIZE);
                    printf("%s\n", buffer); // Display customer details

                    // Prompt for action (modify, delete, reset password)
                    printf("Select an option:\n");
                    printf("1. Modify Employee\n");
                    printf("2. Delete Employee\n");
                    printf("3. Reset Password\n");
                    printf("4. Exit\n");
                    int option;
                    scanf("%d", &option);
                    snprintf(buffer, sizeof(buffer), "%d", option);
                    write(sock, buffer, strlen(buffer)); // Send option to server

                    switch (option) {
                        case 1: 
                            {
                                char new_fname[50], new_lname[50], new_status[20];

                                // Get new balance
                                printf("Enter new first name: ");
                                scanf("%s", new_fname);
                                write(sock, new_fname, strlen(new_fname)); // Send new balance

                                // Get new loan amount
                                printf("Enter new second name: ");
                                scanf("%s", new_lname);
                                write(sock, new_lname, strlen(new_lname)); // Send new loan amount

                                // Get new status
                                printf("Enter new status: ");
                                scanf("%s", new_status);
                                write(sock, new_status, strlen(new_status)); // Send new status

                                // Receive response from server
                                receive_response(sock, buffer, BUFFER_SIZE);
                                printf("%s\n", buffer);
                            }
                            break;

                        case 2: // Delete Customer
                            // No additional data needed, just receive response
                            receive_response(sock, buffer, BUFFER_SIZE);
                            printf("%s\n", buffer);
                            break;

                        case 3: // Reset Password
                            {
                                char new_password[50];

                                // Get new password
                                printf("Enter new password: ");
                                scanf("%s", new_password);
                                write(sock, new_password, strlen(new_password)); // Send new password

                                // Receive response from server
                                receive_response(sock, buffer, BUFFER_SIZE);
                                printf("%s\n", buffer);
                            }
                            break;

                        case 4: // Exit
                            // Receive exit confirmation message
                            receive_response(sock, buffer, BUFFER_SIZE);
                            printf("%s\n", buffer);
                            break;

                        default:
                            printf("Invalid option.\n");
                            break;
                    }
                }
                break;
            case 3:
                send_request(sock, "MANAGE_USER_ROLES");

                printf("Enter ID to modify role: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
                send(sock, buffer, strlen(buffer), 0);  // Send ID

                printf("Enter new role (Manager/Employee): ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
                send(sock, buffer, strlen(buffer), 0);  // Send new role

                // Receive and print confirmation from the server
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 4:
                // Handle withdrawal
                send_request(sock, "CHANGE_PWD");
                printf("Enter new password: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                send_request(sock, buffer);
                receive_response(sock, buffer, BUFFER_SIZE);
                printf("%s\n", buffer);
                break;
            case 5:
                // Handle withdrawal
                send_request(sock, "LOGOUT");
                receive_response(sock, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                close(sock);
                return;
            case 6:
                close(sock);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}


void login(int sock, const char *role) {
    char id[10], password[50], buffer[BUFFER_SIZE];

    // Enter login credentials
    printf("Enter ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    scanf("%s", password);

    // Send ID and password to server
    sprintf(buffer, "%s %s", id, password);
    send(sock, buffer, strlen(buffer), 0);

    // Receive authentication response
    int bytes_read = read(sock, buffer, BUFFER_SIZE);
    buffer[bytes_read] = '\0';

    if (strcmp(buffer, "SUCCESS") == 0) {
        printf("Login Successful! Welcome, %s.\n", role);
        // Display role-specific menu
        if (strcmp(role, "customer") == 0) {
            display_customer_menu(sock);
        } else if (strcmp(role, "employee") == 0) {
            display_employee_menu(sock);
        } else if (strcmp(role, "manager") == 0) {
            display_manager_menu(sock);
        } else if (strcmp(role, "admin") == 0) {
            display_admin_menu(sock);
        }
    } else {
        printf("Login Failed: %s\n", buffer);
    }
}

void role_selection_menu(int sock)
{
    char role[20];
    printf("Select Role (customer/employee/manager/admin): ");
    scanf("%s", role);

    // Send role to server
    send(sock, role, strlen(role), 0);

    login(sock, role);
}


int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char role[20];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    printf("Connected to the server!\n");

    role_selection_menu(sock);

    close(sock);
    return 0;
}
