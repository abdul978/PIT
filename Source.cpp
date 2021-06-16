#include<iostream>
#include<string>
using namespace std;


class Person {
	string name;
	int age;
	char gender;
	Person* next;
public:
	Person(string n, int a, char g) {
		name = n;
		age = a;
		gender = g;
	}
	Person* getNext() { return next; }
	void setNext(Person* n) { next = n; }
	string getName() { return name; }
	int getAge() { return age; }
	char getGender() { return gender; }
	virtual string getOccupation() = 0;
	virtual string getQualification() = 0;
	virtual string getNIC() = 0;
	virtual string getB_Form() = 0;
};
class Adult :public Person {
	string occupation;
	string qualification;
	string NIC;

public:
	Adult(string n, int a, char g, string o, string q, string N) :Person(n, a, g) {
		occupation = o;
		qualification = q;
		NIC = N;
	}
	virtual string getOccupation() { return occupation; }
	virtual string getQualification() { return qualification; }
	virtual string getNIC() { return NIC; }
	virtual string getB_Form() {
		return 0;
	}
};
class Kid :public Person {
	string B_Form;
public:
	Kid(string n, int a, char g, string b) :Person(n, a, g) {
		B_Form = b;
	}
	virtual string getB_Form() { return B_Form; }
	virtual string getOccupation() {
		return 0;
	}
	virtual string getQualification() {
		return 0;
	}
	virtual string getNIC() {
		return 0;
	}

};
class Boogie {
	int boogie_ID;
	Boogie* next;
	Person* adult = nullptr;
	Person* kid = nullptr;
	string Family_Name;
	int numAdult = 0, numKid = 0;
public:
	Boogie() {}
	Boogie(int id) { 
		boogie_ID = id; 
	}
	void setFamily(string f) { Family_Name = f; }
	bool AddPassenger() {
		char inpAoK;
		cout << "Enter 'A' for Adult or 'K' for Kid\n";
		cin >> inpAoK;
		if (inpAoK == 'A') {
			if (numAdult == 4) { cout << "No more Adults can be accomodated on this Bogie.\n\n"; return 0; }
			else {
				string n, o, q, N;
				int a;
				char g;
				cout << "Enter Name: ";
				cin >> n;
				cout << "Enter Age: ";
				cin >> a;
				cout << "Enter 'M' for male or 'F' for female: ";
				cin >> g;
				cout << "Enter Occupation: ";
				cin >> o;
				cout << "Enter Qualification: ";
				cin >> q;
				cout << "Enter NIc number: ";
				cin >> N;
				Person* temp = new Adult(n, a, g, o, q, N);
				temp->setNext(adult);
				adult = temp;
				numAdult++;
				return 1;
			}
		}
		if (inpAoK == 'K') {
			if (numAdult == 6) { cout << "No more Kids can be accomodated on this Bogie.\n\n"; return 0; }
			else {
				string n, B;
				int a;
				char g;
				cout << "Enter Name: ";
				cin >> n;
				cout << "Enter Age: ";
				cin >> a;
				cout << "Enter 'M' for male or 'F' for female: ";
				cin >> g;
				cout << "Enter B-Form number: ";
				cin >> B;
				Person* temp = new Kid(n, a, g, B);
				temp->setNext(kid);
				kid = temp;
				numKid++;
				return 1;
			}
		}
		cout << "Wrong input entered.\n\n";
		return 0;




	}
	void Print() {
		cout << "Boogie Number: " << boogie_ID << endl;
		cout << "\t\t\t\t\tAdults\n\n";
		cout << "Name\t\t\tAge\t\t\tGender\t\t\tOccupation\t\t\tQualification\t\t\tNIC_Number\n\n";
		Person* temp = adult;
		while (temp != nullptr) {
			cout << temp->getName() << "\t\t\t" << temp->getAge() << "\t\t\t" << temp->getGender() << "\t\t\t" << temp->getOccupation() << "\t\t\t" << temp->getQualification() << "\t\t\t" << temp->getNIC() << endl;
			temp = temp->getNext();
		}
		cout << "\t\t\t\t\tKids\n\n";
		cout << "Name\t\t\tAge\t\t\tGender\t\t\tB_Form\n\n";
		temp = kid;
		while (temp != nullptr) {
			cout << temp->getName() << "\t\t\t" << temp->getAge() << "\t\t\t" << temp->getGender() << "\t\t\t" << temp->getB_Form() << endl;
			temp = temp->getNext();
		}


	}
	int getID() { return boogie_ID; }
	Boogie* getNext() {
		return next;
	}
	void setNext(Boogie* n) {
		next = n;
	}
	~Boogie();
};
class Train {
	Boogie* Engine;
public:
	Train() {
		Engine = nullptr;
	}
	void AddBoogie(int id) {
		Boogie* temp = new Boogie(id);
		if (Engine == nullptr)
			Engine = temp;
		else {
			Boogie* trav = Engine;
			while (trav->getNext() != nullptr)
				trav = trav->getNext();
			trav->setNext(temp);
		}
		temp->setNext(nullptr);
	}
	bool addPassenger(int id) {
		if (Engine == nullptr)
			return 0;
		Boogie* temp = Engine;
		while (temp != nullptr) {
			if (temp->getID() == id) {
				return temp->AddPassenger();
			}
			temp = temp->getNext();
		}
		return 0;
	}
	bool RemoveBoogie(int id) {
		Boogie* prev = Engine;
		Boogie* temp = Engine->getNext();
		if (Engine == nullptr) {
			return 0;
		}
		if (Engine->getID() == id) {
			temp = Engine;
			Engine = Engine->getNext();
			//delete temp;
			return 1;
		}
		while (temp->getNext() != nullptr) {
			if (temp->getID() == id) {
				prev->setNext(temp->getNext());

				//delete temp;
				return 1;
			}
			temp = temp->getNext();
			prev = prev->getNext();
		}
		return 0;
	}
	void PrintTrain() {
		Boogie* temp = new Boogie;
		temp = Engine;
		while (temp != nullptr) {
			cout << temp->getID() << " <- ";
			temp = temp->getNext();
		}
		cout << "END\n\n";
	}
	bool SearchBoogie(int id) {
		if (Engine == nullptr)
			return 0;
		Boogie* temp = Engine;
		while (temp != nullptr) {
			if (temp->getID() == id) {
				temp->Print();
				return 1;
			}
			temp = temp->getNext();
		}
		return 0;

	}
	~Train() {
	}
};


int main() {
	Train train;
	train.AddBoogie(1);
	train.AddBoogie(2);
	/*train.addPassenger(2);
	train.SearchBoogie(2);
	train.RemoveBoogie(1);*/
	train.AddBoogie(3);
	train.AddBoogie(4);
	train.AddBoogie(5);
	train.PrintTrain();
	train.RemoveBoogie(3);
	train.PrintTrain();


	system("Pause");
	return 0;
}