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

    virtual ~Customer() { }
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

        cout << "Enter Table Number (1-50): ";
        cin >> tableNo;

        try {
            if (tableNo <= 0 || tableNo > 50)
                throw tableNo;  // throw invalid table number
        }
        catch (int t) {
            cout << " Invalid Table Number: " << t 
                 << " (Tables available: 1–50 only)\n";
            return; // stop reservation
        }

        cout << "Enter Date (dd/mm/yyyy): ";
        cin >> date;

        ofstream fout("reservations.txt", ios::app);
        if (!fout) {
            cerr << " File could not be opened.\n";
            return;
        }

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
        cout << "1. Paneer Butter Masala - ₹250\n";
        cout << "2. Veg Biryani - ₹180\n";
        cout << "3. Dal Tadka - ₹150\n";
        cout << "4. Roti - ₹20\n";
    }
};


template <class T>
class Billing {
    T amount;
public:
    Billing(T a = 0) { amount = a; }

    Billing operator+(Billing b) {
        Billing temp;
        temp.amount = amount + b.amount;
        return temp;
    }

    void showBill() const {
        cout << "\nTotal Bill Amount: ₹" << amount << endl;
    }
};


int main() {
    int ch;
    Reservation r1;
    VIPCustomer v;
    FoodMenu menu;

    Billing<float> bill1(250.50), bill2(330.25), totalBill;

    cout << " RESTAURANT RESERVATION SYSTEM \n";

    do {
        cout << "\n1. Make Reservation";
        cout << "\n2. View Reservations";
        cout << "\n3. VIP Customer";
        cout << "\n4. Display Menu (Abstract Class)";
        cout << "\n5. Calculate Total Bill (Template + Operator Overload)";
        cout << "\n6. Exit\nEnter choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            r1.makeReservation();
            break;

        case 2: {
            ifstream fin("reservations.txt");
            if (!fin) {
                cerr << " Unable to open reservations file.\n";
                break;
            }
            string n, d; long p; int t;
            cout << "\nReservation List:\n";
            while (fin >> n >> p >> t >> d)
                cout << "Name: " << n << " | Phone: " << p
                     << " | Table: " << t << " | Date: " << d << endl;
            fin.close();
            Reservation::totalReservations();
            break;
        }

        case 3:
            v.getData();
            v.showData();
            cout << endl;
            break;

        case 4:
            menu.displayMenu();
            break;

        case 5:
            totalBill = bill1 + bill2;
            totalBill.showBill();
            break;

        case 6:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (ch != 6);

    return 0;
}
