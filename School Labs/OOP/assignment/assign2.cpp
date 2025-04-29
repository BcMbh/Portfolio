#include <iostream>
#include <string>
#include <limits> // for numeric_limits

using namespace std;

// Base class for a person
class Person {
protected:
    string name;

public:
    Person(const string& n) : name(n) {}
    virtual void display() const = 0; // Pure virtual function for display
    virtual ~Person() {} // Virtual destructor
};

// Derived class for a patient
class Patient : public Person {
private:
    int age;
    string phoneNumber;
    string bookingTime;
    string doctorName;

public:
    Patient(const string& n, int a, const string& phone, const string& time, const string& docName)
        : Person(n), age(a), phoneNumber(phone), bookingTime(time), doctorName(docName) {}

    void display() const override {
        cout << "Name:" << name << "\nBooking Time: " << bookingTime << "\nDoctor: " << doctorName << "\n";
        if (age < 12) {
            cout << "Kid";
        } else if (age < 18) {
            cout << "Teenager";
        } else {
            cout << "Adult";
        }
        cout << endl;
    }
};

// Derived class for a doctor
class Doctor : public Person {
private:
    string gender;

public:
    Doctor(const string& n, const string& g) : Person(n), gender(g) {}

    void display() const override {
        cout << "Name: " << name << ", Gender: " << gender << endl;
    }

    string getName() const {
        return name;
    }
};

class Clinic; // Forward declaration

// Friend function declaration
void cancelAppointment(Clinic& cl);

class Clinic {
private:
    Patient** patients; // Dynamic array to store patient details
    int patientCount;
    int maxPatients;
    Doctor** doctors; // Dynamic array to store doctors
    int doctorCount;

public:
    Clinic() : patientCount(0), maxPatients(5), doctorCount(2) {
        patients = new Patient*[maxPatients];
        doctors = new Doctor*[doctorCount];
        doctors[0] = new Doctor("Dr. John Doe", "Male");
        doctors[1] = new Doctor("Dr. Jane Doe", "Female");
    }

    ~Clinic() {
        for (int i = 0; i < patientCount; ++i) {
            delete patients[i];
        }
        delete[] patients;
        for (int i = 0; i < doctorCount; ++i) {
            delete doctors[i];
        }
        delete[] doctors;
    }

    void bookAppointment(const string& name, int age, const string& phone, const string& time) {
        if (patientCount < maxPatients) {
            int doctorChoice;
            displayDoctors();
            cout << "Enter the number of the doctor you want to choose: ";
            while (!(cin >> doctorChoice) || doctorChoice < 1 || doctorChoice > doctorCount) {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters
            }

            string doctorName = doctors[doctorChoice - 1]->getName();
            patients[patientCount++] = new Patient(name, age, phone, time, doctorName); // Add patient to array
            cout << "Appointment booked with Dr. " << doctorName << endl;
        } else {
            cout << "Waiting list is full." << endl;
        }
    }

    void displayWaitingList() const {
        if (patientCount == 0) {
            cout << "No patients in the waiting list." << endl;
        } else {
            cout << "Waiting list:" << endl;
            for (int i = 0; i < patientCount; ++i) {
                cout << i + 1 << ". ";
                patients[i]->display();
            }
        }
        waitForContinue();
    }

    friend void cancelAppointment(Clinic& clinic);

private:
    void displayDoctors() const {
        cout << "Available doctors:" << endl;
        for (int i = 0; i < doctorCount; ++i) {
            cout << i + 1 << ". ";
            doctors[i]->display();
        }
    }

    void waitForContinue() const {
        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cin.get(); // Wait for Enter key press
    }
};

// Friend function definition
void cancelAppointment(Clinic& clinic) {
    if (clinic.patientCount == 0) {
        cout << "No appointments to cancel." << endl;
        clinic.waitForContinue();
        return;
    }

    clinic.displayWaitingList();

    int cancelIndex;
    cout << "Enter the number of the appointment to cancel: ";
    cin >> cancelIndex;

    if (cancelIndex < 1 || cancelIndex > clinic.patientCount) {
        cout << "Invalid appointment number." << endl;
        cout << "Cancel Fail, Please Try Again" << endl;
        clinic.waitForContinue();
    } else {
        delete clinic.patients[cancelIndex - 1];
        for (int i = cancelIndex - 1; i < clinic.patientCount - 1; ++i) {
            clinic.patients[i] = clinic.patients[i + 1];
        }
        --clinic.patientCount;
        cout << "Appointment cancelled." << endl;
        clinic.waitForContinue();
    }
}

// Function prototypes
void clearScreen(); // Function to clear the screen

int main() {
    Clinic cl; // Create an instance of the Clinic class

    int patientChoice;
    do {
        clearScreen(); // Clear the screen before displaying the menu
        cout << "\nWelcome to Cyberjaya Clinic\n";
        cout << "\nPatient Menu:\n";
        cout << "1. Book an Appointment\n";
        cout << "2. View Waiting List\n";
        cout << "3. Cancel an Appointment\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> patientChoice)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters
        }

        switch (patientChoice) {
            case 1: {
                string name;
                int age;
                string phone;
                string time;
                cout << "Enter name: ";
                cin.ignore(); // Ignore newline character left in the buffer
                getline(cin, name);
                cout << "Enter age: ";
                while (!(cin >> age) || age <= 0 || age >= 150) {
                    cout << "Invalid input. Please enter a valid age (0 < age < 150): ";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters
                }
                cout << "Enter phone number: ";
                while (!(cin >> phone) || phone.length() != 10) {
                    cout << "Invalid input. Please enter a 10-digit phone number: ";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters
                }
                cout << "Enter booking time (10-20, e.g., 14 for 2pm): ";
                while (!(cin >> time) || stoi(time) < 10 || stoi(time) > 20) {
                    cout << "Invalid input. Please enter a booking time between 10 and 20: ";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters
                }

                cl.bookAppointment(name, age, phone, time); // Use the class function
                break;
            }
            case 2:
                cl.displayWaitingList(); // Use the class function
                break;
            case 3:
                cancelAppointment(cl); // Use the friend function
                break;
            case 4:
                cout << "Exiting patient menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (patientChoice != 4);

    return 0;
}

// Function definition to clear the screen
void clearScreen() {
    // Clear screen based on OS
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For other systems (Unix/Linux)
    #endif
}