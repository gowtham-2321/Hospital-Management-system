#include <iostream>
#include <fstream>
using namespace std;

// Base class
class Person { // creating a class
public:
    string name;
    int age;
    string gender;
    string contact;

    Person() {}
    Person(string n, int a, string g, string c) : name(n), age(a), gender(g), contact(c) {}
    virtual void display() {
        cout << "-------------------------------------\n";
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender << "\nContact: " << contact << endl;
        cout << "-------------------------------------\n";
    }
};

// Doctor class
class Doctor : public Person { //Inheritance
public:
    string specialization;
    string qualification;
    int experience;

    Doctor() {}
    Doctor(string n, int a, string g, string c, string spec, string qual, int exp) 
        : Person(n, a, g, c), specialization(spec), qualification(qual), experience(exp) {}
    void display() override {
        cout << "\n[Doctor Information]" << endl;
        Person::display();
        cout << "Specialization: " << specialization << "\nQualification: " << qualification 
             << "\nExperience: " << experience << " years\n";
    }
    void saveToFile() {
        ofstream file("doctors.txt", ios::app);
        file << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' 
             << specialization << ' ' << qualification << ' ' << experience << '\n';
        file.close();
    }
};

// Patient class
class Patient : public Person {
public:
    int patientID;
    string disease;
    string address;

    Patient() {}
    Patient(string n, int a, string g, string c, int id, string dis, string addr) 
        : Person(n, a, g, c), patientID(id), disease(dis), address(addr) {}
    void display() override {
        cout << "\n[Patient Information]" << endl;
        Person::display();
        cout << "Patient ID: " << patientID << "\nDisease: " << disease << "\nAddress: " << address << "\n";
    }
    void saveToFile() {
        ofstream file("patients.txt", ios::app);
        file << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' 
             << patientID << ' ' << disease << ' ' << address << '\n';
        file.close();
    }
};

// Appointment class
class Appointment {
public:
    string doctorName;
    string patientName;
    string date;
    string time;
    string purpose;

    Appointment() {}
    Appointment(string d, string p, string dt, string tm, string purp) 
        : doctorName(d), patientName(p), date(dt), time(tm), purpose(purp) {}
    void display() {
        cout << "\n[Appointment Details]" << endl;
        cout << "Date: " << date << "\nTime: " << time << "\nPurpose: " << purpose 
             << "\nDoctor: " << doctorName << "\nPatient: " << patientName << "\n";
    }
    void saveToFile() {
        ofstream file("appointments.txt", ios::app);
        file << doctorName << ' ' << patientName << ' ' << date << ' ' << time << ' ' << purpose << '\n';
        file.close();
    }
};

// Prescription class
class Prescription {
public:
    string patientName;
    string medicine;
    string dosage;
    string instructions;

    Prescription() {}
    Prescription(string p, string med, string dose, string instr) 
        : patientName(p), medicine(med), dosage(dose), instructions(instr) {}
    void display() {
        cout << "\n[Prescription Details]" << endl;
        cout << "Patient: " << patientName << "\nMedicine: " << medicine << "\nDosage: " 
             << dosage << "\nInstructions: " << instructions << "\n";
    }
    void saveToFile() {
        ofstream file("prescriptions.txt", ios::app);
        file << patientName << ' ' << medicine << ' ' << dosage << ' ' << instructions << '\n';
        file.close();
    }
};

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void menu() {
    int choice;
    do {
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Doctor\n2. Add Patient\n3. Book Appointment\n4. View Doctors\n";
        cout << "5. View Patients\n6. View Appointments\n7. Create Prescription\n8. View Prescriptions\n9. Exit\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, gender, contact, specialization, qualification;
            int age, experience;
            cout << "Enter doctor details (Name Age Gender Contact Specialization Qualification Experience): ";
            cin >> name >> age >> gender >> contact >> specialization >> qualification >> experience;
            Doctor doc(name, age, gender, contact, specialization, qualification, experience);  // creating object
            doc.saveToFile();
        } else if (choice == 2) {
            string name, gender, contact, disease, address;
            int age, id;
            cout << "Enter patient details (Name Age Gender Contact ID Disease Address): ";
            cin >> name >> age >> gender >> contact >> id >> disease >> address;
            Patient pat(name, age, gender, contact, id, disease, address);
            pat.saveToFile();
        } else if (choice == 3) {
            string doctorName, patientName, date, time, purpose;
            cout << "Enter appointment details (Doctor Patient Date Time Purpose): ";
            cin >> doctorName >> patientName >> date >> time >> purpose;
            Appointment app(doctorName, patientName, date, time, purpose);
            app.saveToFile();
        } else if (choice == 4) {
            ifstream file("doctors.txt");
            string line;
            while (getline(file, line)) cout << line << '\n';
            file.close();
            pauseScreen();
        } else if (choice == 5) {
            ifstream file("patients.txt");
            string line;
            while (getline(file, line)) cout << line << '\n';
            file.close();
            pauseScreen();
        } else if (choice == 6) {
            ifstream file("appointments.txt");
            string line;
            while (getline(file, line)) cout << line << '\n';
            file.close();
            pauseScreen();
        } else if (choice == 7) {
            string patientName, medicine, dosage, instructions;
            cout << "Enter prescription details (Patient Medicine Dosage Instructions): ";
            cin >> patientName >> medicine >> dosage >> instructions;
            Prescription pres(patientName, medicine, dosage, instructions);
            pres.saveToFile();
        }
        else if (choice == 8) {
            ifstream file("prescriptions.txt");
            string line;
            while (getline(file, line)) cout << line << '\n';
            file.close();
            pauseScreen();
        }
    } while (choice != 9);
}

int main() {
    menu();
    return 0;
}
