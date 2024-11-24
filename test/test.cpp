#include<iostream>

using namespace std;

class Persons
{
	char name[30];
	int age;

	public:
		void getdata();
		void putdata();
};

void Persons::putdata()
{
	cout<<"Nom: ";
	cin>>name;

	cout<<"Age: ";
	cin>>age;
}

void Persons::getdata()
{
	cout<< "Nom: " << name << "\n";
	cout<< "Age: " << age << "\n";
}

int main ()
{
	const int size=3 ;
	Persons persons[size] ;

	for(int i=0; i < size; i++)
	{
		cout<<"Entrez les informations sur la personne "<< (i+1) <<"\n";
		persons[i].putdata();
	}

	cout.flush();

	for(int i=0; i < size; i++)
	{
		cout<<"\nPersonne "<< (i+1) <<"\n";
		persons[i].getdata();
	}

	return 0;
}
