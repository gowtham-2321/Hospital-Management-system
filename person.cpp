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
        cout << "Name: " << name << ", Age: " << age <<"Gender"<<gender<< endl;
}
};
class Doctor :public person
{
  private:
      string Specialization;
      int Experience;

      public:
        Doctor(string n, int a, string s,string g ) : person(n, a, g), Specialization(s) {}

    void displayInfo() {
        person::displayInfo();
        cout << "Specialization: " << Specialization << endl;
    
    }
~Doctor();
};
class Patient:public person
{
  private:
      string Disease;
      public:
        Patient(string n, int a, string d,string g) : person(n, a, g), Disease(d) {}

    void displayInfo() {
        person::displayInfo();
        cout << "Disease: " << Disease << endl;
    }
~Patient();
};
class Admin:public person
{
  private:
      string Department;
      int Admin_id;
      public:
        Admin(string n, int a, string d,string g,int i) : person(n, a,g), Department(d) ,Admin_id(i){}

    void displayInfo() {
        person::displayInfo();
        cout << "Department: " << Department << endl;
        cout << "Admin_id: " << Admin_id << endl;
    }
~Admin();
};
class staff :public person
{
  private:
      string Department;
      int Staff_id;
      public:
        staff(string n, int a, string d,string g,int i) : person(n, a,g), Department(d) ,Staff_id(i){}

    void displayInfo() {
        person::displayInfo();
        cout << "Department: " << Department << endl;
        cout << "Staff_id: " << Staff_id << endl;
    }
~staff();
};