#include <iostream>
using namespace std;
class person{
    protected:
        string name;
        int age;
        string gender;
    public:
        person(string n, int a, string g) : name(n), age(a), gender(g) {}

     void displayInfo() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
class Doctor :public person
{
  private:
      string Specialization;
      int Experience;

      public:
        Doctor(string n, int a, string s) : person(n, a), Specialization(s) {}

    void displayInfo() {
        person::displayInfo();
        cout << "Specialization: " << Specialization << endl;
    }
};
class Patient:public person
{
  private:
      string Disease;
      public:
        Patient(string n, int a, string d) : person(n, a), Disease(d) {}

    void displayInfo() {
        person::displayInfo();
        cout << "Disease: " << Disease << endl;
    }
};
class Admin:public person
{
  private:
      string Department;
      int Admin_id;
      public:
        Admin(string n, int a, string d,int i) : person(n, a), Department(d) ,Admin_id(i){}

    void displayInfo() {
        person::displayInfo();
        cout << "Department: " << Department << endl;
        cout << "Admin_id: " << Admin_id << endl;
    }
};
