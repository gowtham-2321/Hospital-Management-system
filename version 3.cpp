#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define MAX_DOCTORS 100
#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100
#define MAX_PRESCRIPTIONS 100

// Base class
class Person {
protected:
    string name;
    int age;
    string gender;
    string contact;
public:
    Person() {}
    Person(string n, int a, string g, string c) : name(n), age(a), gender(g), contact(c) {}
    virtual void display() {
        cout << "-------------------------------------\n";
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender << "\nContact: " << contact << endl;
        cout << "-------------------------------------\n";
    }
};

// Derived class - Doctor
class Doctor : public Person {
public:
    string specialization;
    string qualification;
    int experience;

    Doctor() {}
    Doctor(string n, int a, string g, string c, string spec, string qual, int exp) : Person(n, a, g, c), specialization(spec), qualification(qual), experience(exp) {}
    void display() override {
        cout << "\n[Doctor Information]" << endl;
        Person::display();
        cout << "Specialization: " << specialization << "\nQualification: " << qualification << "\nExperience: " << experience << " years\n";
    }
};

// Derived class - Patient
class Patient : public Person {
public:
    int patientID;
    string disease;
    string address;

    Patient() {}
    Patient(string n, int a, string g, string c, int id, string dis, string addr) : Person(n, a, g, c), patientID(id), disease(dis), address(addr) {}
    void display() override {
        cout << "\n[Patient Information]" << endl;
        Person::display();
        cout << "Patient ID: " << patientID << "\nDisease: " << disease << "\nAddress: " << address << "\n";
    }
};

// Class for Appointment
class Appointment {
public:
    Doctor doctor;
    Patient patient;
    string date;
    string time;
    string purpose;

    Appointment() {}
    Appointment(Doctor d, Patient p, string dt, string tm, string purp) : doctor(d), patient(p), date(dt), time(tm), purpose(purp) {}
    void display() {
        cout << "\n[Appointment Details]" << endl;
        cout << "Date: " << date << "\nTime: " << time << "\nPurpose: " << purpose << "\n";
        doctor.display();
        patient.display();
    }
};

// Class for Prescription
class Prescription {
public:
    Patient patient;
    string medicine;
    string dosage;
    string instructions;

    Prescription() {}
    Prescription(Patient p, string med, string dose, string instr) : patient(p), medicine(med), dosage(dose), instructions(instr) {}
    void display() {
        cout << "\n[Prescription Details]" << endl;
        patient.display();
        cout << "Medicine: " << medicine << "\nDosage: " << dosage << "\nInstructions: " << instructions << "\n";
    }
};

Doctor doctors[MAX_DOCTORS];
Patient patients[MAX_PATIENTS];
Appointment appointments[MAX_APPOINTMENTS];
Prescription prescriptions[MAX_PRESCRIPTIONS];
int doctorCount = 0, patientCount = 0, appointmentCount = 0, prescriptionCount = 0;

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void menu() {
    int choice;
    do {
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Doctor\n";
        cout << "2. Add Patient\n";
        cout << "3. Book Appointment\n";
        cout << "4. View Doctors\n";
        cout << "5. View Patients\n";
        cout << "6. View Appointments\n";
        cout << "7. Create Prescription\n";
        cout << "8. View Prescriptions\n";
        cout << "9. Exit\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 1 && doctorCount < MAX_DOCTORS) {
            string name, gender, contact, specialization, qualification;
            int age, experience;
            cout << "Enter doctor details (Name Age Gender Contact Specialization Qualification Experience): ";
            cin >> name >> age >> gender >> contact >> specialization >> qualification >> experience;
            doctors[doctorCount++] = Doctor(name, age, gender, contact, specialization, qualification, experience);
        } else if (choice == 2 && patientCount < MAX_PATIENTS) {
            string name, gender, contact, disease, address;
            int age, id;
            cout << "Enter patient details (Name Age Gender Contact ID Disease Address): ";
            cin >> name >> age >> gender >> contact >> id >> disease >> address;
            patients[patientCount++] = Patient(name, age, gender, contact, id, disease, address);
        } else if (choice == 3 && doctorCount > 0 && patientCount > 0 && appointmentCount < MAX_APPOINTMENTS) {
            string date, time, purpose;
            cout << "Enter appointment details (Date Time Purpose): ";
            cin >> date >> time >> purpose;
            appointments[appointmentCount++] = Appointment(doctors[0], patients[0], date, time, purpose);
        } else if (choice == 7 && patientCount > 0 && prescriptionCount < MAX_PRESCRIPTIONS) {
            string medicine, dosage, instructions;
            cout << "Enter prescription details (Medicine Dosage Instructions): ";
            cin >> medicine >> dosage >> instructions;
            prescriptions[prescriptionCount++] = Prescription(patients[0], medicine, dosage, instructions);
        } else if (choice == 6) {
            for (int i = 0; i < appointmentCount; i++) appointments[i].display();
            pauseScreen();
        } else if (choice == 8) {
            for (int i = 0; i < prescriptionCount; i++) prescriptions[i].display();
            pauseScreen();
        }
    } while (choice != 9);
}

int main() {
    menu();
    return 0;
}
