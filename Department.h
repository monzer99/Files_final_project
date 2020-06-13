#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

class Department;

bool lessthan(string s1, string s2) {

	for (int i = 0; i < s1.size() || i < s2.size(); i++) {
		
		if (s1[i] < s2[i]) {
			
			return true;
		}
		else if (s1[i] == s2[i]) {
			
			continue;
		}
		else {

			return false;
		}
	}
}

bool greaterthan(string s1, string s2) {

	for (int i = 0; i < s1.size() || i < s2.size(); i++) {

		if (s1[i] > s2[i]) {

			return true;
		}
		else if (s1[i] == s2[i]) {

			continue;
		}
		else {

			return false;
		}
	}
}

struct D_PrimaryKey {

	int dept_Id;
	int rrn;
};

struct D_SecondryKey {

	string departmentName;
	int dept_Id;
};

struct D_SecondryKey2 {

	string headDepartmentName;
	int dept_Id;
};


void D_sortPrimaryKey(D_PrimaryKey pkData[], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i + 1; j < size; j++) {

			if (pkData[j].dept_Id < pkData[min].dept_Id) {

				min = j;
			}
		}

		D_PrimaryKey p;
		p = pkData[i];
		pkData[i] = pkData[min];
		pkData[min] = p;
	}
}

int D_get_RRN_by_id(D_PrimaryKey pkData[], int size, int targetId) {

	int first, last, mid;

	first = 0;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (pkData[mid].dept_Id == targetId) {

			return pkData[mid].rrn;
		}
		else if (pkData[mid].dept_Id > targetId) {

			last = mid - 1;
		}
		else if (pkData[mid].dept_Id < targetId) {

			first = mid + 1;
		}
	}

	return -1;
}


void D_sortSecondryKey(D_SecondryKey skData[], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i + 1; j < size; j++) {

			if (lessthan(skData[j].departmentName,skData[min].departmentName)) {

				min = j;
			}
		}

		D_SecondryKey s;
		s = skData[i];
		skData[i] = skData[min];
		skData[min] = s;
	}
}


int D_get_Id_by_Name(D_SecondryKey skData[], int size, string targetName) {

	int first, last, mid;

	first = 0;
	mid = size / 2;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (skData[mid].departmentName == targetName) {

			return skData[mid].dept_Id;
		}
		else if (greaterthan(skData[mid].departmentName,targetName)) {

			last = mid - 1;
		}
		else if (lessthan(skData[mid].departmentName,targetName)) {

			first = mid + 1;
		}
	}

	return -1;
}


void D_sortSecondryKey2(D_SecondryKey2 skData[], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i + 1; j < size; j++) {

			if (lessthan(skData[j].headDepartmentName, skData[min].headDepartmentName)) {

				min = j;
			}
		}

		D_SecondryKey2 s;
		s = skData[i];
		skData[i] = skData[min];
		skData[min] = s;
	}
}

int D_get_Id_by_HeadDepartmentName(D_SecondryKey2 skData[], int size, string targetName) {

	int first, last, mid;

	first = 0;
	mid = size / 2;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (skData[mid].headDepartmentName == targetName) {

			return skData[mid].dept_Id;
		}
		else if (greaterthan(skData[mid].headDepartmentName, targetName)) {

			last = mid - 1;
		}
		else if (lessthan(skData[mid].headDepartmentName, targetName)) {

			first = mid + 1;
		}
	}

	return -1;
}

class Department {
	
public:
	Department();
	~Department() {};
	void setDepartmentId(int id);
	void setDepartmentName(string name);
	void setHeadOfDepartment(string name);
	void writeToFileByRRN(int rrn,fstream &departmentfile, fstream &primarykeyfile, fstream &secondrykeyfile, fstream& secondrykeyfile2);
	void writeToFile(fstream& departmentfile, fstream& primarykeyfile, fstream& secondrykeyfile, fstream& secondrykeyfile2);
	void readFromFile(int rrn, fstream &departmentfile);
	int getDepartmentId();
	string getDepartmentName();
	string getHeadOfDepartmentName();

private:
	int department_id;
	string department_name;
	string headOfDepartment;
};

Department::Department() {

	department_id = 0;
	department_name = "";
	headOfDepartment = "";
}

void Department::setDepartmentId(int id) {

	department_id = id;
}

void Department::setDepartmentName(string name) {

	department_name = name;
}

void Department::setHeadOfDepartment(string name) {

	headOfDepartment = name;
}

int Department::getDepartmentId() {

	return department_id;
}

string Department::getDepartmentName() {

	return department_name;
}

string Department::getHeadOfDepartmentName() {

	return headOfDepartment;
}

void Department::writeToFile(fstream& departmentfile, fstream& primarykeyfile, fstream& secondrykeyfile, fstream& secondrykeyfile2) {
	
	D_PrimaryKey pk;
	D_SecondryKey sk;
	D_SecondryKey2 sk2;

	departmentfile.seekp(0, ios::end);
	
	pk.dept_Id = department_id;
	pk.rrn = departmentfile.tellp() / sizeof(Department);

	sk.dept_Id = department_id;
	sk.departmentName = department_name;

	sk2.dept_Id = department_id;
	sk2.headDepartmentName = headOfDepartment;

	departmentfile.write((char*)this, sizeof(Department));
	primarykeyfile.write((char*)&pk, sizeof(D_PrimaryKey));
	secondrykeyfile.write((char*)&sk, sizeof(D_SecondryKey));
	secondrykeyfile2.write((char*)&sk2, sizeof(D_SecondryKey2));

}


void Department::writeToFileByRRN(int rrn,fstream& departmentfile, fstream& primarykeyfile, fstream& secondrykeyfile, fstream& secondrykeyfile2) {

	D_PrimaryKey pk;
	D_SecondryKey sk;
	D_SecondryKey2 sk2;

	pk.dept_Id = department_id;
	pk.rrn = rrn;

	sk.dept_Id = department_id;
	sk.departmentName = department_name;

	sk2.dept_Id = department_id;
	sk2.headDepartmentName = headOfDepartment;

	departmentfile.seekp(0, ios::end);
	int size = departmentfile.tellp() / sizeof(Department);

	if (rrn > size or rrn < 0) {

		cout << "Wrong RRN ...! " << endl;
	}
	else {

		departmentfile.seekp(rrn * sizeof(Department), ios::beg);
		primarykeyfile.seekp(rrn * sizeof(D_PrimaryKey), ios::beg);
		secondrykeyfile.seekp(rrn * sizeof(D_SecondryKey), ios::beg);
		secondrykeyfile2.seekp(rrn * sizeof(D_SecondryKey2), ios::beg);
		departmentfile.write((char*)this, sizeof(Department));
		primarykeyfile.write((char*)&pk, sizeof(D_PrimaryKey));
		secondrykeyfile.write((char*)&sk, sizeof(D_SecondryKey));
		secondrykeyfile2.write((char*)&sk2, sizeof(D_SecondryKey2));
	}

}


void Department::readFromFile(int rrn, fstream& departmentfile) {

	departmentfile.seekg(0, ios::end);

	if (departmentfile.tellg() / sizeof(Department) < rrn or rrn < 0) {

		cout << "Error rrn ...!" << endl;
		return;
	}
	else {
		departmentfile.seekg(0);
		departmentfile.seekg(rrn * sizeof(Department), ios::beg);
		departmentfile.read((char*)this, sizeof(Department));
	}
}


void setDepartmentInformation(Department& d) {

	int department_id;
	string department_name;
	string headOfDepartment;

	try {

		cout << "Enter Department ID : ";
		cin >> department_id;
		cout << endl;

		cout << "Enter Department Name : ";
		cin.ignore();
		getline(cin, department_name);
		cout << endl;


		cout << "Enter Head Of Department Name : ";
		getline(cin, headOfDepartment);
		cout << endl;

	}
	catch (...) {

		cout << "Input Error ...! " << endl;
	}

	d.setDepartmentId(department_id);
	d.setDepartmentName(department_name);
	d.setHeadOfDepartment(headOfDepartment);
}

void viewDepartmentInformation(Department d) {

	cout << "Department ID : " << d.getDepartmentId() << endl;
	cout << "Department Name : " << d.getDepartmentName() << endl;
	cout << "Head Of Department Name : " << d.getHeadOfDepartmentName() << endl;

}

int D_getDataByPrimaryKey(int id, fstream& primarykeyfile) {


	primarykeyfile.seekg(0, ios::end);
	int size = primarykeyfile.tellg() / sizeof(D_PrimaryKey);
	primarykeyfile.seekg(0, ios::beg);

	D_PrimaryKey* pkData = new D_PrimaryKey[size];

	for (int i = 0; i < size; i++) {

		primarykeyfile.read((char*)&pkData[i], sizeof(D_PrimaryKey));
	}

	D_sortPrimaryKey(pkData, size);
	
	int rrn = D_get_RRN_by_id(pkData, size, id);

	return rrn;
}


int D_getDataBySecondryKey(string name, fstream& secondrykeyfile) {

	secondrykeyfile.seekg(0, ios::end);
	int size = secondrykeyfile.tellg() / sizeof(D_SecondryKey);
	secondrykeyfile.seekg(0, ios::beg);

	D_SecondryKey* skData = new D_SecondryKey[size];

	for (int i = 0; i < size; i++) {

		secondrykeyfile.read((char*)&skData[i], sizeof(D_SecondryKey));
	}

	D_sortSecondryKey(skData, size);

	int id = D_get_Id_by_Name(skData, size, name);

	return id;
}

int D_getDataBySecondryKey2(string name, fstream& secondrykeyfile) {

	secondrykeyfile.seekg(0, ios::end);
	int size = secondrykeyfile.tellg() / sizeof(D_SecondryKey);
	secondrykeyfile.seekg(0, ios::beg);

	D_SecondryKey2* skData = new D_SecondryKey2[size];

	for (int i = 0; i < size; i++) {

		secondrykeyfile.read((char*)&skData[i], sizeof(D_SecondryKey2));
	}

	D_sortSecondryKey2(skData, size);

	int id = D_get_Id_by_HeadDepartmentName(skData, size, name);

	return id;
}
