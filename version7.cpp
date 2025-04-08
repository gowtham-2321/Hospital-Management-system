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
    ifstream file("patients.txt");
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
    ifstream file("doctors.txt");
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

int getNextAppointmentID() {
    ifstream file("appointments.txt");
    int doctorID, patientID, id;
    string date, time, purpose, patientName, doctorName;
    id = 999;

    if (!file) {
        return 1000; 
    }

    while (file >> id >> doctorName >> doctorID >> patientName >> patientID >> date >> time >> purpose) {
        // goes through the file until the last valid entry and stores the data in the user defined variables
    }

    file.close();
    return id + 1; 
}

string findPatientName(int searchID) {
    ifstream file("patients.txt");
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
    ifstream file("doctors.txt");
    string name, gender, disease, contact, specialization, qualification;
    int age, id, experience;

    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return "";
    }

    while (file >> id >> name >> age >> gender >> contact >> specialization >> qualification >> experience ) {
        if (id == searchID) {
            file.close();
            return name;  // Return the name if ID matches
        }

    }

    file.close();
    return "Not Found";  // If no match is found
}


void deleteAppointment(int id) {
    ifstream file("appointments.txt");
    ofstream temp("Temp.txt");
    
    int doctorID, patientID, appointmentID;
    string date, time, purpose, patientName, doctorName;
    bool found = false;

    if (!file || !temp) {
        cout << "Error opening file!" << endl;
        return;
    }

    while (file >> appointmentID >> doctorName >> doctorID >> patientName >> patientID >> date >> time >> purpose) {
        if (appointmentID != id) {
            temp << appointmentID << ' ' << doctorName << ' ' << doctorID << ' ' << patientName << ' ' << patientID  << ' ' << date << ' ' << time << ' ' << purpose << '\n';
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove("appointments.txt");
        rename("Temp.txt", "appointments.txt");
        cout << "Appointment deleted successfully." << endl;
    } else {
        cout << "Appointment not found!" << endl;
        remove("Temp.txt"); // Cleanup temp file if no deletion occurs
    }
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
    friend void doctorCountDisplay(Doctor& doc);
private:
    int docCount = 0;
public:
    static int doctorCount;
    string specialization;
    string qualification;
    int experience, doctorID, i;

    Doctor() {}
    Doctor(int id, string n, int a, string g, string c, string spec, string qual, int exp, int count = 1) 
        : Person(n, a, g, c), specialization(spec), qualification(qual), experience(exp), doctorID(id), i(count) {
            docCount = doctorCount;
        }
    void display() override {
        cout << "\n[Doctor Information - "<< i << " ]" << endl;
        Person::display();
        cout << "Doctor ID: " << doctorID << "\nSpecialization: " << specialization << "\nQualification: " << qualification 
             << "\nExperience: " << experience << " years\n";
        cout << "-------------------------------------\n";    
    }
    void saveToFile() {
        ofstream file("doctors.txt", ios::app);
        doctorID = getNextDoctorID();
        file << doctorID << ' ' << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' 
             << specialization << ' ' << qualification << ' ' << experience << '\n';
        file.close();
    }
};
int Doctor::doctorCount = 0; // Initialize static member variable

void doctorCountDisplay(Doctor& doc) {
    doc.docCount = doc.doctorCount;
    cout << "Doctor Count: " << doc.docCount << endl;
}

// Patient class
class Patient : public Person {   
private:
    int patCount = 0;
public:
    friend void patientCountDisplay(Patient& pat);
    static int patientCount;
    int patientID, i;
    string disease;
    string address;

    Patient() {}
    Patient(string n, int a, string g, string c, int id, string dis, int count = 1) 
        : Person(n, a, g, c), patientID(id), disease(dis), i(count) {}
    void display() override {
        cout << "\n[Patient Information - " << i << "]"<<endl;
        Person::display();
        cout << "Patient ID: " << patientID << "\nDisease: " << disease <<"\n";
        cout << "-------------------------------------\n"; 
    }
    void saveToFile() {
        ofstream file("patients.txt", ios::app);
        file << name << ' ' << age << ' ' << gender << ' ' << contact << ' ' 
             << patientID << ' ' << disease <<'\n';
        file.close();
    }
};

int Patient::patientCount = 0; // Initialize static member variable

void patientCountDisplay(Patient& pat){
    pat.patCount = pat.patientCount;
    cout << "Patient Count: " << pat.patCount << endl;
}

// Appointment class
class Appointment {
public:
    int doctorID, patientID, appointmentID;
    string date, time, purpose, patientName, doctorName;

    Appointment() {}
    Appointment(int i, int d, int p, string dt, string tm, string purp) 
        : appointmentID(i), doctorID(d), patientID(p), date(dt), time(tm), purpose(purp) {
            patientName = findPatientName(patientID);
            doctorName = findDoctorName(doctorID);
        }
    void display() const {
        cout << "\n[Appointment Details - " << appointmentID << "]"<<endl;
        cout << "Date: " << date << "\nTime: " << time << "\nPurpose: " << purpose 
             << "\nDoctor: " << doctorName << "\nDoctorID: " << doctorID << "\nPatient: " << patientName << "\nPatientID: " << patientID << "\n";
        cout << "-------------------------------------\n";
    }

    void saveToFile() {
        ofstream file("appointments.txt", ios::app);
        file << appointmentID << ' ' << doctorName << ' ' << doctorID << ' ' << patientName << ' ' << patientID  << ' ' << date << ' ' << time << ' ' << purpose << '\n';
        file.close();
    }
};

// Prescription class
class Prescription {
public:
    int patientID, doctorID, i;
    string patientName,doctorName, medicine, dosage, instructions;

    Prescription() {}
    Prescription(int pID, int dID, string med, string dose, string instr, int count = 1, string patName = "Not Found", string docName = "Not Found") 
        : patientID(pID), doctorID(dID), medicine(med), dosage(dose), instructions(instr), i(count), patientName(patName), doctorName(docName) {}
    void display() const {
        cout << "\n[Prescription Details - " << i << "]"<<endl;
        cout << "Patient: " << patientName << "\nPatient ID: " << patientID << "\nPrescribed by: " << doctorName << "\nDoctor ID: " << doctorID << "\nMedicine: " << medicine << "\nDosage: " 
             << dosage << "\nInstructions: " << instructions << "\n";
        cout << "-------------------------------------\n"; 
    }
    void saveToFile() {
        ofstream file("prescriptions.txt", ios::app);
        file << patientName << ' ' << patientID << ' ' << doctorName << ' ' << doctorID << ' ' << medicine << ' ' << dosage << ' ' << instructions << '\n';
        file.close();
    }
};

void deleteDoctor(int id) {
    ifstream file("doctors.txt");
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
        remove("doctors.txt");
        rename("Temp.txt", "doctors.txt");
        Doctor doc;
        doc.doctorCount--;
        cout << "Doctor " << foundDoc << " deleted successfully." << endl;
    } else {
        cout << "Doctor not found!" << endl;
        remove("Temp.txt"); // Cleanup temp file if no deletion occurs
    }
}

void deletePatient(int id) {
    ifstream file("patients.txt");
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
        remove("patients.txt");
        rename("Temp.txt", "patients.txt");
        Patient pat;
        pat.patientCount--;
        cout << "Patient " << foundPat << " deleted successfully." << endl;
    } else {
        cout << "Patient not found!" << endl;
        remove("Temp.txt"); // Cleanup temp file if no deletion occurs
    }
}

void getInputDoctor(){
    string name, gender, contact, specialization, qualification;
    int age, id, experience;
    cout << "===========================\n";
    cout << "Enter Doctor Details:\n";
    cout << "===========================\n";
    cout << "Name of the Doctor: ";
    cin >> name;
    while(true){
        try
        {
            cout << "Age of the Doctor: ";
            cin >>  age;
            if (cin.fail())
            {
                throw "Invalid Data Type! Please enter a valid age.";
            }
            if (age <=0)
            {
                throw "Invalid Age! Please enter a valid age.";
            }
            break;
            
        }
        catch(const char* e)
        {
            cout<< e << endl;
            cin.clear();              // reset fail state
            cin.ignore(1000, '\n');   // discard invalid input
        }  
    }
    cout << "Gender of the Doctor: ";
    cin >> gender;
    cout << "Ph. Number of the Doctor: ";
    cin >> contact;
    cout << "Specialisation of the Doctor: ";
    cin >> specialization;
    cout << "Qualification of the Doctor: ";
    cin >> qualification ;
    while(true){
        try
        {
            cout << "No. of years of Experience: ";
            cin >>  experience;
            if (cin.fail())
            {
                throw "Invalid Data Type! Please enter a valid age.";
            }
            if (experience <=0)
            {
                throw "Invalid Age! Please enter a valid age.";
            }
            break;
            
        }
        catch(const char* e)
        {
            cout<< e << endl;
            cin.clear();              // reset fail state
            cin.ignore(1000, '\n');   // discard invalid input
        }  
    }
    id = getNextDoctorID();
    Doctor* doc = new Doctor(id, name, age, gender, contact, specialization, qualification, experience);  // dynamically allocated object
    doc->saveToFile();
    doc->doctorCount++;
    delete doc; // Free the allocated memory
    clearScreen();
    cout << "========= Hospital Management System =========\n";
    cout << "Doctor "<<name<<" has been added successfully!";
    pauseScreen();
}

void getInputPatient(){
    string name, gender, contact, disease;
    int age, id;
    cout << "===========================\n";
    cout << "Enter patient details\n";
    cout << "===========================\n";
    cout << "Name of the Patient: ";
    cin >> name;
    while(true){
        try
        {
            cout << "Age of the Patient: ";
            cin >>  age;
            if (cin.fail())
            {
                throw "Invalid Data Type! Please enter a valid age.";
            }
            if (age < 0)
            {
                throw "Invalid Age! Please enter a valid age.";
            }
            break;
            
        }
        catch(string e)
        {
            cout<< e << endl;
        }  
    }
    cout << "Gender of the Patient: ";
    cin >> gender;
    cout << "Contact Details of the Patient: ";
    cin >> contact;
    cout << "Disease of the Patient: ";
    cin >> disease;
    id = getNextPatientID();
    Patient* pat = new Patient(name, age, gender, contact, id, disease); // dynamically allocated object
    pat->saveToFile();
    pat->patientCount++;
    delete pat; // Free the allocated memory
    clearScreen();
    cout << "========= Hospital Management System =========\n";
    cout << "Patient "<<name<<" has been added successfully!";
    pauseScreen();
}

void getInputAppointment(){
    string date, time, purpose;
    int doctorID, patientID, id;
    cout << "=============================\n";
    cout << "Enter Appointment Details\n";
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
    id = getNextAppointmentID();
    Appointment * app = new Appointment(id, doctorID, patientID, date, time, purpose);
    app->saveToFile();
    delete app; // Free the allocated memory
    clearScreen();
    cout << "========= Hospital Management System =========\n";
    cout << "The Appointment has been made successfully!";
    pauseScreen();

}

void getInputPrescription(){
    int patientID, doctorID;
    string medicine, dosage, instructions;
    cout << "=============================\n";
    cout << "Enter Prescription Details\n";
    cout << "=============================\n";
    cout << "Doctor's id: ";
    cin >> doctorID;
    cout << "Patient's id: ";
    cin >> patientID;
    cout << "Medicine Prescribed: ";
    cin >> medicine;
    cout << "Dosage of the prescribed medicine: ";
    cin >> dosage;
    cout << "Instructions: ";
    cin >> instructions;
    Prescription * pres = new Prescription(patientID, doctorID, medicine, dosage, instructions); // dynamically allocated object
    pres->saveToFile();
    delete pres; // Free the allocated memory
    clearScreen();
    cout << "========= Hospital Management System =========\n";
    cout << "The Prescription has been recorded successfully!";
    pauseScreen();
}

template <typename T>
void displayDetails(T& obj){
    obj.display();
}

void displayDoctors(){
    int doctorID, age,experience;
    string name, gender, contact, specialization, qualification;
    ifstream file("doctors.txt");
    int i = 1;
    while (file >> doctorID >> name >> age >> gender >> contact >> specialization >> qualification >> experience)
    {
        Doctor doc(doctorID, name,age, gender, contact, specialization, qualification, experience);
        doc.i = i;
        displayDetails(doc);
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
        Patient pat(name,age,gender,contact, patientID, disease); 
        pat.i = i;
        displayDetails(pat);
        i++;
    }
    file.close();
    pauseScreen();
}
void displayAppointment(){
    int doctorID, patientID, age, id;
    string date, time, purpose, patientName, doctorName;

    ifstream file("appointments.txt");
    while (file >> id >> doctorName >> doctorID >> patientName >> patientID >> date >> time >> purpose ){
        Appointment app(id, doctorID, patientID, date, time, purpose);
        displayDetails(app);
    }
    file.close();
    pauseScreen();
}
void displayPrescription(){
    int patientID, doctorID;
    string patientName,doctorName, medicine, dosage, instructions;

    ifstream file("prescriptions.txt");
    int i = 1;
    while (file >> patientName >> patientID >> doctorName >> doctorID >> medicine >> dosage >> instructions ){
        Prescription pres( doctorID, patientID, medicine, dosage, instructions, i, patientName, doctorName);
        displayDetails(pres);
        i++;
    }
    file.close();
    pauseScreen();
}

void menu() {
    int choice;
    do {
        clearScreen();
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Doctor\n2. Add Patient\n3. Book Appointment\n4. Create Prescription\n";
        cout << "5. View Doctors\n6. View Patients\n7. View Appointments\n8. View Prescriptions\n";
        cout << "9. Delete Doctor\n10. Delete Patient\n11. Delete Appointment\n12. Exit\n";
        cout << "==============================================\n";
        while (true)
        {
            try{
                cout << "Enter your choice: ";
                cin >> choice;
                if (cin.fail()) {
                    throw "Invalid Data Type! Please enter a valid choice.";
                }
                if (choice < 1 || choice > 12) {
                    throw "Invalid Choice! Please enter a number between 1 and 12.";
                }
                break;
            }
            catch(const char* e)
            {
                cout<< e << endl;
                cin.clear();              // reset fail state
                cin.ignore(1000, '\n');   // discard invalid input
            }
        }
        if (choice == 1) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            getInputDoctor();
        }
        else if (choice == 2) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            getInputPatient();
        }
        else if (choice == 3) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            getInputAppointment();
        }
        else if (choice == 4) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            getInputPrescription();
        }
        else if (choice == 5) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            displayDoctors();
        }
        else if (choice == 6) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            displayPatients();
        }
        else if (choice == 7) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            displayAppointment();
        }
        else if (choice == 8) {
            clearScreen();
            displayPrescription();
        }
        else if (choice == 9) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            int doctorID;
            cout<< "Enter DoctorId: ";
            cin>> doctorID;
            deleteDoctor(doctorID);
            pauseScreen();
        }
        else if (choice == 10) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            int patientID;
            cout<< "Enter PatientID: ";
            cin>> patientID;
            deletePatient(patientID);
            pauseScreen(); 
        }
        else if (choice == 11) {
            clearScreen();
            cout << "========= Hospital Management System =========\n";
            int appID;
            cout<< "Enter AppointmentID: ";
            cin>> appID;
            deleteAppointment(appID);
            pauseScreen(); 
        }
        
    } while (choice != 12);
    clearScreen();
}

int main() {
    menu();
    return 0;
}
