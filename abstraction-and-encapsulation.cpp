#include <iostream>
#include <vector>

using namespace std;

class Employee {
protected:
    int id;
    string name;
public:
    Employee(int id, string name) : id(id), name(name) {}
    virtual double calculateSalary() const = 0;
    virtual void display() const = 0;
    int getId() const { return id; }
    virtual ~Employee() {}
};

class FullTime : public Employee {
    double salary;
public:
    FullTime(int id, string name, double salary) : Employee(id, name), salary(salary) {}
    double calculateSalary() const override { return salary; }
    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Fixed Monthly Salary: $" << salary << "\n\n";
    }
};

class PartTime : public Employee {
    double hourlyWage;
    double hoursWorked;
public:
    PartTime(int id, string name, double hourlyWage, double hoursWorked)
        : Employee(id, name), hourlyWage(hourlyWage), hoursWorked(hoursWorked) {}
    double calculateSalary() const override { return hourlyWage * hoursWorked; }
    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Hourly Wage: $" << hourlyWage << "\n"
             << "Hours Worked: " << hoursWorked << "\n"
             << "Total Salary: $" << calculateSalary() << "\n\n";
    }
};

class Contractual : public Employee {
    double paymentPerProject;
    double projectsCompleted;
public:
    Contractual(int id, string name, double paymentPerProject, double projectsCompleted)
        : Employee(id, name), paymentPerProject(paymentPerProject), projectsCompleted(projectsCompleted) {}
    double calculateSalary() const override { return paymentPerProject * projectsCompleted; }
    void display() const override {
        cout << "Employee: " << name << " (ID: " << id << ")\n"
             << "Contract Payment Per Project: $" << paymentPerProject << "\n"
             << "Projects Completed: " << projectsCompleted << "\n"
             << "Total Salary: $" << calculateSalary() << "\n\n";
    }
};

vector<Employee*> employees;
vector<int> employeeIds;

bool isUniqueID(int id) {
    for (int i = 0; i < employeeIds.size(); i++) {
        if (employeeIds[i] == id) {
            return false;
        }
    }
    return true;
}

double getValidDouble(string prompt) {
    string input;
    double value;
    cout << prompt;
    cin >> input;
    
    for (int i = 0; i < input.length(); i++) {
        if ((input[i] < '0' || input[i] > '9') && input[i] != '.') {
            cout << "Invalid input! Enter a valid positive number.\n";
            return getValidDouble(prompt);
        }
    }
    
    value = stod(input);
    if (value <= 0) {
        cout << "Invalid input! Enter a valid positive number.\n";
        return getValidDouble(prompt);
    }
    return value;
}

void addFullTime() {
    int id;
    double salary;
    string name;
    
    id = (int)getValidDouble("Enter Employee ID: ");
    while (!isUniqueID(id)) {
        cout << "Duplicate ID! Enter a unique ID.\n";
        id = (int)getValidDouble("Enter Employee ID: ");
    }
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    salary = getValidDouble("Enter Fixed Monthly Salary: $");
    
    employees.push_back(new FullTime(id, name, salary));
    employeeIds.push_back(id);
}

void addPartTime() {
    int id;
    double hourlyWage, hoursWorked;
    string name;
    
    id = (int)getValidDouble("Enter Employee ID: ");
    while (!isUniqueID(id)) {
        cout << "Duplicate ID! Enter a unique ID.\n";
        id = (int)getValidDouble("Enter Employee ID: ");
    }
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    hourlyWage = getValidDouble("Enter Hourly Wage: $");
    hoursWorked = getValidDouble("Enter Hours Worked: ");
    
    employees.push_back(new PartTime(id, name, hourlyWage, hoursWorked));
    employeeIds.push_back(id);
}

void addContractual() {
    int id;
    double paymentPerProject, projectsCompleted;
    string name;
    
    id = (int)getValidDouble("Enter Employee ID: ");
    while (!isUniqueID(id)) {
        cout << "Duplicate ID! Enter a unique ID.\n";
        id = (int)getValidDouble("Enter Employee ID: ");
    }
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    paymentPerProject = getValidDouble("Enter Payment Per Project: $");
    projectsCompleted = getValidDouble("Enter Projects Completed: ");
    
    employees.push_back(new Contractual(id, name, paymentPerProject, projectsCompleted));
    employeeIds.push_back(id);
}

void displayPayroll() {
    cout << "------ Employee Payroll Report ------\n";
    for (int i = 0; i < employees.size(); i++) {
        employees[i]->display();
    }
}

int main() {
    int choice;
    do {
        cout << "\nMenu\n";
        cout << "1 - Full-time Employee\n";
        cout << "2 - Part-time Employee\n";
        cout << "3 - Contractual Employee\n";
        cout << "4 - Display Payroll Report\n";
        cout << "5 - Exit\n";
        choice = (int)getValidDouble("Enter your choice: ");
        
        if (choice == 1) addFullTime();
        else if (choice == 2) addPartTime();
        else if (choice == 3) addContractual();
        else if (choice == 4) displayPayroll();
        else if (choice == 5) cout << "Exiting...\n";
        else cout << "Invalid choice! Try again.\n";
        
    } while (choice != 5);
    
    for (int i = 0; i < employees.size(); i++) delete employees[i];
    return 0;
}