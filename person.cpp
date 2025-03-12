#include <iostream>
using namespace std;
class person{
    protected:
        string name;
        int age;
    public:
        person(string n, int a) : name(n), age(a) {}

     void displayInfo() {
        cout << "Name: " << name << ", Age: " << age <<"Gender"<<gender<< endl;
}
};
class Doctor :public person
{
  private:
      string Specialization;
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
class staff :public person
{
  private:
      string Department;
      int Staff_id;
      public:
        staff(string n, int a, string d,int i) : person(n, a), Department(d) ,Staff_id(i){}

    void displayInfo() {
        person::displayInfo();
        cout << "Department: " << Department << endl;
        cout << "Staff_id: " << Staff_id << endl;
    }
};