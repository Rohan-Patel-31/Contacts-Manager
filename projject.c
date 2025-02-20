#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "CMS.dat"

typedef struct {
    char fName[50];
    char lName[50];
    char address[50];
    char email[50];
    long long phNo;
} Contact;

void createContact(Contact *c) {
    printf("Enter your first name: ");
    scanf("%s", c->fName);
    printf("Enter your last name: ");
    scanf("%s", c->lName);
    printf("Enter phone: ");
    scanf("%lld", &c->phNo);
    printf("Enter address: ");
    getchar(); // clear buffer
    fgets(c->address, 50, stdin);
    c->address[strcspn(c->address, "\n")] = '\0'; // remove newline
    printf("Enter email: ");
    scanf("%s", c->email);
}

void showContact(Contact c) {
    printf("Name: %s %s\n", c.fName, c.lName);
    printf("Phone: %lld\n", c.phNo);
    printf("Address: %s\n", c.address);
    printf("Email: %s\n", c.email);
}

void addContact() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    Contact c;
    char ch;
    do {
        createContact(&c);
        fwrite(&c, sizeof(Contact), 1, fp);
        printf("Do you want to add another contact? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');

    fclose(fp);
    printf("Contact(s) added successfully!\n");
}

void listContacts() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No contacts found.\n");
        return;
    }

    Contact c;
    printf("\n==== List of Contacts ====\n");
    while (fread(&c, sizeof(Contact), 1, fp)) {
        showContact(c);
        printf("-------------------------\n");
    }
    fclose(fp);
}

void searchContact() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No contacts found.\n");
        return;
    }

    long long phone;
    int found = 0;
    printf("Enter phone number to search: ");
    scanf("%lld", &phone);

    Contact c;
    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (c.phNo == phone) {
            printf("\nContact Found:\n");
            showContact(c);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found.\n");

    fclose(fp);
}

void deleteContact() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    long long phone;
    int found = 0;
    printf("Enter phone number to delete: ");
    scanf("%lld", &phone);

    Contact c;
    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (c.phNo != phone) {
            fwrite(&c, sizeof(Contact), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Contact deleted successfully.\n");
    else
        printf("Contact not found.\n");
}

void editContact() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("No contacts found.\n");
        return;
    }

    long long phone;
    int found = 0;
    printf("Enter phone number to edit: ");
    scanf("%lld", &phone);

    Contact c;
    while (fread(&c, sizeof(Contact), 1, fp)) {
        if (c.phNo == phone) {
            printf("\nCurrent contact details:\n");
            showContact(c);
            printf("\nEnter new details:\n");
            createContact(&c);
            fseek(fp, -sizeof(Contact), SEEK_CUR);
            fwrite(&c, sizeof(Contact), 1, fp);
            found = 1;
            printf("Contact updated successfully.\n");
            break;
        }
    }

    if (!found)
        printf("Contact not found.\n");

    fclose(fp);
}

int main() {
    int choice;

    do {
        printf("\n==== Contact Management System ====\n");
        printf("1. Add Contact\n");
        printf("2. List Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Edit Contact\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                listContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                editContact();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
