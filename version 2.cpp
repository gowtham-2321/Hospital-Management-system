#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define MAX_DOCTORS 100
#define MAX_PATIENTS 100
#define MAX_APPOINTMENTS 100

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
    virtual void saveToFile(ofstream &file) {
        file << name << " " << age << " " << gender << " " << contact << " ";
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
    void saveToFile(ofstream &file) override {
        Person::saveToFile(file);
        file << specialization << " " << qualification << " " << experience << "\n";
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
    void saveToFile(ofstream &file) override {
        Person::saveToFile(file);
        file << patientID << " " << disease << " " << address << "\n";
    }
};

void saveDoctor(Doctor d) {
    ofstream file("doctors.txt", ios::app);
    d.saveToFile(file);
    file.close();
}

void savePatient(Patient p) {
    ofstream file("patients.txt", ios::app);
    p.saveToFile(file);
    file.close();
}

void viewDoctors() {
    ifstream file("doctors.txt");
    if (!file) {
        cout << "No doctor records found!\n";
        return;
    }
    string name, gender, contact, specialization, qualification;
    int age, experience;
    while (file >> name >> age >> gender >> contact >> specialization >> qualification >> experience) {
        Doctor d(name, age, gender, contact, specialization, qualification, experience);
        d.display();
    }
    file.close();
}

void viewPatients() {
    ifstream file("patients.txt");
    if (!file) {
        cout << "No patient records found!\n";
        return;
    }
    string name, gender, contact, disease, address;
    int age, id;
    while (file >> name >> age >> gender >> contact >> id >> disease >> address) {
        Patient p(name, age, gender, contact, id, disease, address);
        p.display();
    }
    file.close();
}

void menu() {
    int choice;
    do {
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Doctor\n2. Add Patient\n3. View Doctors\n4. View Patients\n5. Exit\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            string name, gender, contact, specialization, qualification;
            int age, experience;
            cout << "Enter doctor details (Name Age Gender Contact Specialization Qualification Experience): ";
            cin >> name >> age >> gender >> contact >> specialization >> qualification >> experience;
            Doctor d(name, age, gender, contact, specialization, qualification, experience);
            saveDoctor(d);
        } else if (choice == 2) {
            string name, gender, contact, disease, address;
            int age, id;
            cout << "Enter patient details (Name Age Gender Contact ID Disease Address): ";
            cin >> name >> age >> gender >> contact >> id >> disease >> address;
            Patient p(name, age, gender, contact, id, disease, address);
            savePatient(p);
        } else if (choice == 3) {
            viewDoctors();
        } else if (choice == 4) {
            viewPatients();
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
