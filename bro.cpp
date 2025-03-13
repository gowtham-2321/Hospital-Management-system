#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;
    string gender;
    string contact;
public:
    Person(string n, int a, string g, string c) : name(n), age(a), gender(g), contact(c) {}
    virtual void display() {
        cout << "-------------------------------------\n";
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender << "\nContact: " << contact << endl;
        cout << "-------------------------------------\n";
    }
};

// Derived class - Doctor
class Doctor : public Person {
private:
    string specialization;
    string qualification;
    int experience;
public:
    Doctor(string n, int a, string g, string c, string spec, string qual, int exp) : Person(n, a, g, c), specialization(spec), qualification(qual), experience(exp) {}
    void display() override {
        cout << "\n[Doctor Information]" << endl;
        Person::display();
        cout << "Specialization: " << specialization << "\nQualification: " << qualification << "\nExperience: " << experience << " years\n";
    }
};

// Derived class - Patient
class Patient : public Person {
private:
    int patientID;
    string disease;
    string address;
public:
    Patient(string n, int a, string g, string c, int id, string dis, string addr) : Person(n, a, g, c), patientID(id), disease(dis), address(addr) {}
    void display() override {
        cout << "\n[Patient Information]" << endl;
        Person::display();
        cout << "Patient ID: " << patientID << "\nDisease: " << disease << "\nAddress: " << address << "\n";
    }
};

// Class for Medicine
class Medicine {
private:
    string name;
    double price;
    string manufacturer;
    string expiryDate;
public:
    Medicine(string n, double p, string m, string e) : name(n), price(p), manufacturer(m), expiryDate(e) {}
    void display() {
        cout << "\n[Medicine Details]" << endl;
        cout << "Name: " << name << "\nPrice: " << price << "\nManufacturer: " << manufacturer << "\nExpiry Date: " << expiryDate << "\n";
    }
};

// Class for Prescription
class Prescription {
private:
    Doctor doctor;
    Patient patient;
    vector<Medicine> medicines;
    string date;
public:
    Prescription(Doctor d, Patient p, string dt) : doctor(d), patient(p), date(dt) {}
    void addMedicine(Medicine m) {
        medicines.push_back(m);
    }
    void display() {
        cout << "\n[Prescription Details]" << endl;
        cout << "Date: " << date << "\n";
        doctor.display();
        patient.display();
        cout << "\nMedicines Prescribed:" << endl;
        for (Medicine m : medicines) {
            m.display();
        }
    }
};

// Class for Appointment
class Appointment {
private:
    Doctor doctor;
    Patient patient;
    string date;
    string time;
    string purpose;
public:
    Appointment(Doctor d, Patient p, string dt, string tm, string purp) : doctor(d), patient(p), date(dt), time(tm), purpose(purp) {}
    void display() {
        cout << "\n[Appointment Details]" << endl;
        cout << "Date: " << date << "\nTime: " << time << "\nPurpose: " << purpose << "\n";
        doctor.display();
        patient.display();
    }
};

void clearScreen() {
    system("CLS");
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void menu() {
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointments;
    vector<Prescription> prescriptions;
    
    int choice;
    do {
        clearScreen();
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Doctor\n";
        cout << "2. Add Patient\n";
        cout << "3. Book Appointment\n";
        cout << "4. Create Prescription\n";
        cout << "5. View Doctors\n";
        cout << "6. View Patients\n";
        cout << "7. View Appointments\n";
        cout << "8. View Prescriptions\n";
        cout << "9. Exit\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            clearScreen();
            string name, gender, contact, specialization, qualification;
            int age, experience;
            cout << "Enter doctor details (Name Age Gender Contact Specialization Qualification Experience): ";
            cin >> name >> age >> gender >> contact >> specialization >> qualification >> experience;
            doctors.push_back(Doctor(name, age, gender, contact, specialization, qualification, experience));
        } else if (choice == 2) {
            clearScreen();
            string name, gender, contact, disease, address;
            int age, id;
            cout << "Enter patient details (Name Age Gender Contact ID Disease Address): ";
            cin >> name >> age >> gender >> contact >> id >> disease >> address;
            patients.push_back(Patient(name, age, gender, contact, id, disease, address));
        } else if (choice == 3) {
            clearScreen();
            if (doctors.empty() || patients.empty()) {
                cout << "Add at least one doctor and one patient before booking an appointment!\n";
            } else {
                string date, time, purpose;
                cout << "Enter appointment details (Date Time Purpose): ";
                cin >> date >> time >> purpose;
                appointments.push_back(Appointment(doctors[0], patients[0], date, time, purpose));
            }
        } else if (choice == 4) {
            clearScreen();
            if (doctors.empty() || patients.empty()) {
                cout << "Add at least one doctor and one patient before creating a prescription!\n";
            } else {
                string date;
                cout << "Enter prescription date: ";
                cin >> date;
                prescriptions.push_back(Prescription(doctors[0], patients[0], date));
            }
        } else if (choice >= 5 && choice <= 8) {
            clearScreen();
            if (choice == 5) for (Doctor& d : doctors) d.display();
            else if (choice == 6) for (Patient& p : patients) p.display();
            else if (choice == 7) for (Appointment& a : appointments) a.display();
            else if (choice == 8) for (Prescription& p : prescriptions) p.display();
            pauseScreen();
        }
    } while (choice != 9);
}

int main() {
    menu();
    return 0;
}