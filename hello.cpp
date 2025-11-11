#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Customer {
protected:
    string name;
    long phone;
public:
    Customer() { name = "Unknown"; phone = 0; }
    Customer(string n, long p) { name = n; phone = p; }
    virtual void getData() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Phone: ";
        cin >> phone;
    }
    virtual void showData() const {
        cout << "Name: " << name << " | Phone: " << phone;
    }
    virtual ~Customer() { } // Virtual destructor
};


class Table {
protected:
    int tableNo;
    int capacity;
public:
    Table(int t = 1, int c = 4) {
        tableNo = t;
        capacity = c;
    }
    void showTable() const {
        cout << "Table No: " << tableNo << " | Capacity: " << capacity;
    }
};


class VIPCustomer : public Customer {
    int discount;
public:
    VIPCustomer() : discount(10) {}
    void getData() {
        Customer::getData();
        cout << "VIP discount is 10%\n";
    }
    void showData() const {
        cout << "VIP Name: " << name << " | Phone: " << phone
             << " | Discount: " << discount << "%";
    }
};


class Reservation : public Customer, public Table {
    string date;
    static int count; 
public:
    Reservation() { date = "00/00/0000"; count++; }

    void makeReservation() {
        getData();
        cout << "Enter Table Number: ";
        cin >> tableNo;
        cout << "Enter Date (dd/mm/yyyy): ";
        cin >> date;

        ofstream fout("reservations.txt", ios::app);
        fout << name << " " << phone << " " << tableNo << " " << date << endl;
        fout.close();
        cout << "\n Reservation saved successfully!\n";
    }

    void display() const {
        cout << "Name: " << name << " | Phone: " << phone
             << " | Table: " << tableNo << " | Date: " << date << endl;
    }

    static void totalReservations() {
        cout << "\nTotal Reservations (this session): " << count << endl;
    }

    
    Reservation operator+(Reservation r2) {
        Reservation temp;
        temp.name = name + "_" + r2.name;
        temp.phone = phone + r2.phone;
        temp.tableNo = tableNo + r2.tableNo;
        temp.date = "Combined";
        return temp;
    }

    ~Reservation() { }
};
int Reservation::count = 0;


class BaseMenu {
public:
    virtual void displayMenu() = 0;
    virtual ~BaseMenu() { }
};


class FoodMenu : public BaseMenu {
public:
    void displayMenu() {
        cout << "\n---- MENU ----\n";
        cout << "1. Paneer Butter Masala - 250\n";
        cout << "2. Veg Biryani - 180\n";
        cout << "3. Dal Tadka - 150\n";
        cout << "4. Roti - 20\n";
    }
};


class Bill {
    float amount;
    friend void showBill(Bill);
public:
    Bill(float a = 0) { amount = a; }
};
void showBill(Bill b) {
    cout << "\nTotal Bill Amount: ₹" << b.amount << endl;
}


template <class T>
class Manager {
    T* data;
    int size;
public:
    Manager(int s) {
        size = s;
        data = new T[size];
    }
    void setItem(int i, T val) {
        if (i >= 0 && i < size)
            data[i] = val;
    }
    void showItems() const {
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }
    ~Manager() { delete[] data; }
};


int main() {
    int ch;
    Reservation r1, r2, r3;
    VIPCustomer v;
    FoodMenu menu;
    Bill b(580.75);
    Manager<string> manager(3);

    cout << "==== RESTAURANT RESERVATION SYSTEM ====\n";


    do {
        cout << "\n1. Make Reservation";
        cout << "\n2. View Reservations";
        cout << "\n3. Combine Two Reservations (+ Operator)";
        cout << "\n4. VIP Customer";
        cout << "\n5. Display Menu (Abstract Class)";
        cout << "\n6. Show Bill (Friend Function)";
        cout << "\n7. Use Template Manager";
        cout << "\n8. Exit\nEnter choice: ";
        cin >> ch;

        if (ch == 1)
            r1.makeReservation();

        else if (ch == 2) {
            ifstream fin("reservations.txt");
            string n, d; long p; int t;
            cout << "\n Reservation List:\n";
            while (fin >> n >> p >> t >> d)
                cout << "Name: " << n << " | Phone: " << p
                     << " | Table: " << t << " | Date: " << d << endl;
            fin.close();
            Reservation::totalReservations();
        }

        else if (ch == 3) {
            cout << "\nEnter first reservation:\n";
            r1.makeReservation();
            cout << "\nEnter second reservation:\n";
            r2.makeReservation();
            r3 = r1 + r2; 
            cout << "\nCombined Reservation:\n";
            r3.display();
        }

        else if (ch == 4) {
            v.getData();
            v.showData();
            cout << endl;
        }

        else if (ch == 5)
            menu.displayMenu();

        else if (ch == 6)
            showBill(b);

        else if (ch == 7) {
            manager.setItem(0, "Manager1");
            manager.setItem(1, "Manager2");
            manager.setItem(2, "Manager3");
            cout << "\nRestaurant Managers: ";
            manager.showItems();
        }

        else if (ch == 8)
            cout << "\nGoodbye!\n";
        else
            cout << "\nInvalid choice!\n";

    } while (ch != 8);

    return 0;
}
