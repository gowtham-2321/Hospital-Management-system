#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


//global functions
void pauseScreen() {
    string con;
    cout << "\nType continue to continue: ";
    cin>> con;
    if(con == "continue")
    {
        return;
    }
    else{
        pauseScreen();
    }
}
void clearScreen(){
    system("cls");
}

int getNextPatientID() {
    ifstream file("Patients.txt");
    string name, gender, disease, contact;
    int age, id = 99;  

    if (!file) {
        return 100; 
    }

    while (file >> name >> age >> gender >> contact >> id >> disease) {
        // goes through the file until the last valid entry and stores the data in the user defined variables
    }

    file.close();
    return id + 1; 
}

int getNextDoctorID() {
    ifstream file("Doctors.txt");
    string name, gender, disease, contact, specialization, qualification;
    int age, id, experience; 
    id = 299;

    if (!file) {
        return 300; 
    }

    while (file >> id >> name >> age >> gender >> specialization >> qualification >> experience ) {
        // goes through the file until the last valid entry and stores the data in the user defined variables
    }

    file.close();
    return id + 1; 
}

string findPatientName(int searchID) {
    ifstream file("Patients.txt");
    string name, gender, disease, contact;
    int age, id;

    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return "";
    }

    while (file >> name >> age >> gender >> contact >> id >> disease) {
        if (id == searchID) {
            file.close();
            return name;  // Return the name if ID matches
        }
    }

    file.close();
    return "Not Found";  // If no match is found
}

string findDoctorName(int searchID) {
    ifstream file("Doctors.txt");
    string name, gender, disease, contact, specialization, qualification;
    int age, id, experience;

    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return "";
    }

    while (file >> id >> name >> age >> gender >> specialization >> qualification >> experience ) {
        if (id == searchID) {
            file.close();
            return name;  // Return the name if ID matches
        }
    }

    file.close();
    return "Not Found";  // If no match is found
}

void deleteDoctor(int id) {
    ifstream file("Doctors.txt");
    ofstream temp("Temp.txt");
    
    string name, specialization, qualification, gender, contact, foundDoc;
    int age, experience, doctorID;
    bool found = false;

    if (!file || !temp) {
        cout << "Error opening file!" << endl;
        return;
    }

    while (file >> doctorID >> name >> age >> gender >> contact >> specialization >> qualification >> experience) {
        if (doctorID != id) {
            temp << doctorID << ' ' << name << ' ' << age << ' ' << gender << ' ' << contact << ' '
                 << specialization << ' ' << qualification << ' ' << experience << '\n';
        } else {
            found = true;
            foundDoc = name;
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove("Doctors.txt");
        rename("Temp.txt", "Doctors.txt");
        cout << "Doctor " << foundDoc << " deleted successfully." << endl;
    } else {
        cout << "Doctor not found!" << endl;
        remove("Temp.txt"); // Cleanup temp file if no deletion occurs
    }
}

void deletePatient(int id) {
    ifstream file("Patients.txt");
    ofstream temp("Temp.txt");
    
    string name, gender, disease, contact, foundPat;
    int age, patientID;
    bool found = false;

    if (!file || !temp) {
        cout << "Error opening file!" << endl;
        return;
    }

    while (file >> name >> age >> gender >> contact >> patientID >> disease) {
        if (patientID != id) {
            temp << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' << patientID << ' ' << disease << '\n';
        } else {
            found = true;
            foundPat = name;
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove("Patients.txt");
        rename("Temp.txt", "Patients.txt");
        cout << "Patient " << foundPat << " deleted successfully." << endl;
    } else {
        cout << "Patient not found!" << endl;
        remove("Temp.txt"); // Cleanup temp file if no deletion occurs
    }
}
void displayDoctors(){
    int doctorID, age,experience;
    string name, gender, contact, specialization, qualification;
    ifstream file("doctors.txt");
    int i = 1;
    while (file >> doctorID >> name >> age >> gender >> contact >> specialization >> qualification >> experience)
    {
        cout << "\n[Doctor Information - " << i << "]"<< endl;
        cout << "-------------------------------------\n";
        cout << "Name: " << name <<"\nDoctor ID: " << doctorID << "\nAge: " << age << "\nGender: " << gender << "\nContact: " << contact << endl;
        cout << "Specialization: " << specialization << "\nQualification: " << qualification 
             << "\nExperience: " << experience << " years\n";
        cout << "-------------------------------------\n";
        i++;
    }
    file.close();
    pauseScreen();
}

void displayPatients(){
    int patientID, age;
    string name, gender, contact, disease;
    ifstream file("patients.txt");
    int i = 1;
    while (file >> name >> age >> gender >> contact >> patientID >> disease){
        cout << "\n[Patient Information - " << i << "]"<<endl;
        cout << "-------------------------------------\n";
        cout << "Name: " << name << "\nPatient ID: " << patientID << "\nAge: " << age << "\nGender: " << gender << "\nContact: " << contact << endl;
        cout << "\nDisease: " << disease <<"\n";
        cout << "-------------------------------------\n";
        i++;
    }
    file.close();
    pauseScreen();
}

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
    int experience, doctorID;

    Doctor() {}
    Doctor(int id, string n, int a, string g, string c, string spec, string qual, int exp) 
        : Person(n, a, g, c), specialization(spec), qualification(qual), experience(exp), doctorID(id) {}
    void display() override {
        cout << "\n[Doctor Information]" << endl;
        Person::display();
        cout << "Specialization: " << specialization << "\nQualification: " << qualification 
             << "\nExperience: " << experience << " years\n";
    }
    void saveToFile() {
        ofstream file("doctors.txt", ios::app);
        doctorID = getNextDoctorID();
        file << doctorID << ' ' << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' 
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
    Patient(string n, int a, string g, string c, int id, string dis) 
        : Person(n, a, g, c), patientID(id), disease(dis){}
    void display() override {
        cout << "\n[Patient Information]" << endl;
        Person::display();
        cout << "Patient ID: " << patientID << "\nDisease: " << disease <<"\n";
    }
    void saveToFile() {
        ofstream file("patients.txt", ios::app);
        file << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' 
             << patientID << ' ' << disease <<'\n';
        file.close();
    }
};

// Appointment class
class Appointment {
public:
    int doctorID, patientID;
    string date, time, purpose, patientName, doctorName;

    Appointment() {}
    Appointment(int d, int p, string dt, string tm, string purp) 
        : doctorID(d), patientID(p), date(dt), time(tm), purpose(purp) {}
    void display() {
        cout << "\n[Appointment Details]" << endl;
        cout << "Date: " << date << "\nTime: " << time << "\nPurpose: " << purpose 
             << "\nDoctor: " << doctorName << "\nPatient: " << patientName << "\n";
    }

    void saveToFile() {
        ofstream file("appointments.txt", ios::app);
        patientName = findPatientName(patientID);
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

void menu() {
    int choice;
    do {
        clearScreen();
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Doctor\n2. Add Patient\n3. Book Appointment\n4. View Doctors\n";
        cout << "5. View Patients\n6. View Appointments\n7. Create Prescription\n8. View Prescriptions\n9. Exit\n";
        cout << "10. Delete Patient\n11. Delete Doctor\n12. Delete Appointment\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            string name, gender, contact, specialization, qualification;
            int age, id, experience;
            cout << "===========================\n";
            cout << "Enter Doctor Details:\n";
            cout << "===========================\n";
            cout << "Name of the Doctor: ";
            cin >> name;
            cout << "Age of the Doctor: ";
            cin >>  age;
            cout << "Gender of the Doctor: ";
            cin >> gender;
            cout << "Ph. Number of the Doctor: ";
            cin >> contact;
            cout << "Specialisation of the Doctor: ";
            cin >> specialization;
            cout << "Qualification of the Doctor: ";
            cin >> qualification ;
            cout << "No. of years of Experience: ";
            cin >> experience;
            id = getNextDoctorID();
            Doctor doc(id, name, age, gender, contact, specialization, qualification, experience);  // creating object
            doc.saveToFile();
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            cout << "Doctor "<<name<<" has been added successfully!";
            pauseScreen();
        }
        else if (choice == 2) {
            clearScreen();
            string name, gender, contact, disease;
            int age, id;
            cout << "===========================\n";
            cout << "Enter patient details\n";
            cout << "===========================\n";
            cout << "Name of the Patient: ";
            cin >> name;
            cout << "Age of the Patient: ";
            cin >>  age;
            cout << "Gender of the Patient: ";
            cin >> gender;
            cout << "Contact Details of the Doctor: ";
            cin >> contact;
            cout << "Disease of the Patient: ";
            cin >> disease;
            id = getNextPatientID();
            Patient pat(name, age, gender, contact, id, disease);
            pat.saveToFile();

        }
        else if (choice == 3) {
            clearScreen();
            string date, time, purpose;
            int doctorID, patientID;
            cout << "=============================\n";
            cout << "Enter Appointment Details";
            cout << "=============================\n";
            cout << "Doctor's id: ";
            cin >> doctorID;
            cout << "Patient's id: ";
            cin >> patientID;
            cout << "Date of the Appointment: ";
            cin >> date;
            cout << "Time of the Appointment: ";
            cin >> time;
            cout << "Purpose of the Appointment: ";
            cin >> purpose;
            Appointment app(doctorID, patientID, date, time, purpose);
            app.saveToFile();

        }
        else if (choice == 4) {
            clearScreen();
            displayDoctors();
        }
        else if (choice == 5) {
            clearScreen();
            displayPatients();
        }
        else if (choice == 6) {
            clearScreen();
            ifstream file("appointments.txt");
            string line;
            while (getline(file, line)) cout << line << '\n';
            file.close();
            pauseScreen();
        }
        else if (choice == 7) {
            clearScreen();
            string patientName, medicine, dosage, instructions;
            cout << "Enter prescription details (Patient Medicine Dosage Instructions): ";
            cin >> patientName >> medicine >> dosage >> instructions;
            Prescription pres(patientName, medicine, dosage, instructions);
            pres.saveToFile();
        }
        else if (choice == 8) {
            clearScreen();
            ifstream file("prescriptions.txt");
            string line;
            while (getline(file, line)) cout << line << '\n';
            file.close();
            pauseScreen();
        }
        else if (choice == 10) {
            clearScreen();
            int patientID;
            cout<< "Enter PatientID: ";
            cin>> patientID;
            deletePatient(patientID);
            pauseScreen();
            
        }
        else if (choice == 11) {
            clearScreen();
            int doctorID;
            cout<< "Enter DoctorId: ";
            cin>> doctorID;
            deleteDoctor(doctorID);
            pauseScreen();
        }
    } while (choice != 9);
    clearScreen();
}

int main() {
    menu();
    return 0;
}
