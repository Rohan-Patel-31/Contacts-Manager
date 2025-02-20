#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

class contact {
private:
    char fName[50], lName[50], address[50], email[50];
    long long phNo;

public:
    void createContact() {
        cout << "Enter your first name: ";
        cin >> fName;
        cout << "Enter your last name: ";
        cin >> lName;
        cout << "Enter phone: ";
        cin >> phNo;
        cout << "Enter address: ";
        cin.ignore();
        cin.getline(address, 50);
        cout << "Enter email: ";
        cin >> email;
    }

    void showContact() {
        cout << "Name: " << fName << " " << lName << endl;
        cout << "Phone: " << phNo << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
    }

    void writeOnFile() {
        char ch;
        ofstream f1("CMS.dat", ios::binary | ios::app);

        if (!f1) {
            cout << "Error opening file!" << endl;
            return;
        }

        do {
            createContact();
            f1.write(reinterpret_cast<char*>(this), sizeof(*this));
            cout << "Do you have next data? (y/n): ";
            cin >> ch;
        } while (ch == 'y' || ch == 'Y');

        cout << "Contact has been Successfully Created..." << endl;
        f1.close();
    }

    void readFromFile() {
        ifstream f2("CMS.dat", ios::binary);

        if (!f2) {
            cout << "Error opening file!" << endl;
            return;
        }

        cout << "\n================================\n";
        cout << "LIST OF CONTACTS" << endl;
        cout << "================================\n";

        while (f2.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            showContact();
            cout << "\n================================\n";
        }

        f2.close();
    }

    void searchOnFile() {
        ifstream f3("CMS.dat", ios::binary);
        long long phone;

        if (!f3) {
            cout << "Error opening file!" << endl;
            return;
        }

        cout << "Enter phone no.: ";
        cin >> phone;

        bool found = false;
        while (f3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phone == phNo) {
                showContact();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n\nNo record found" << endl;
        }

        f3.close();
    }

    void deleteFromFile() {
        long long num;
        bool flag = false;
        ofstream f4("temp.dat", ios::binary);
        ifstream f5("CMS.dat", ios::binary);

        if (!f5 || !f4) {
            cout << "Error opening file!" << endl;
            return;
        }

        cout << "Enter phone no. to delete: ";
        cin >> num;

        while (f5.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phNo != num) {
                f4.write(reinterpret_cast<char*>(this), sizeof(*this));
            } else {
                flag = true;
            }
        }

        f5.close();
        f4.close();

        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        if (flag)
            cout << "\n\n\tContact Deleted..." << endl;
        else
            cout << "\n\n\tContact Not Found..." << endl;
    }

    void editContact() {
        long long num;
        fstream f6("CMS.dat", ios::binary | ios::in | ios::out);

        if (!f6) {
            cout << "Error opening file!" << endl;
            return;
        }

        cout << "Edit contact" << endl;
        cout << "\n===============================\n\n";
        cout << "Enter the phone number to be edited: ";
        cin >> num;

        bool found = false;
        while (f6.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (phNo == num) {
                cout << "Enter new record\n";
                createContact();
                int pos = -static_cast<int>(sizeof(*this));
                f6.seekp(pos, ios::cur);
                f6.write(reinterpret_cast<char*>(this), sizeof(*this));
                cout << "\n\n\tContact Successfully Updated..." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n\nNo record found" << endl;
        }

        f6.close();
    }
};

int main() {
    system("clear");

    cout << "\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

    while (true) {
        contact c1;
        int choice;

        system("clear");

        cout << "\nCONTACT MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";
        cout << "\n=====================\n";
        cout << "[1] Add a new Contact\n";
        cout << "[2] List all Contacts\n";
        cout << "[3] Search for contact\n";
        cout << "[4] Delete a Contact\n";
        cout << "[5] Edit a Contact\n";
        cout << "[0] Exit";
        cout << "\n=====================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("clear");
                c1.writeOnFile();
                break;

            case 2:
                system("clear");
                c1.readFromFile();
                break;

            case 3:
                system("clear");
                c1.searchOnFile();
                break;

            case 4:
                system("clear");
                c1.deleteFromFile();
                break;

            case 5:
                system("clear");
                c1.editContact();
                break;

            case 0:
                system("clear");
                cout << "\n\n\n\t\t\tThank you for using CMS." << endl << endl;
                exit(0);

            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }

        int opt;
        cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin >> opt;

        if (opt == 0) {
            system("clear");
            cout << "\n\n\n\t\t\tThank you for using CMS." << endl << endl;
            exit(0);
        }
    }

    return 0;
}