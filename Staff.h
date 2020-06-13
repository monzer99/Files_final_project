#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <string>
#include <vector>
#include "Department.h"

using namespace std;


struct S_PrimaryKey {

	int staffId;
	int rrn;
};


struct S_SecondryKey {

	string staffName;
	int staffId;
};


struct S_SecondryKey2 {

	float staffDegree;
	int staffId;
};


void S_sortPrimaryKey(S_PrimaryKey skData[], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i + 1; j < size; j++) {

			if (skData[j].staffId < skData[min].staffId) {

				min = j;
			}
		}

		S_PrimaryKey s;
		s = skData[i];
		skData[i] = skData[min];
		skData[min] = s;
	}
}


int S_get_RRN_by_id(S_PrimaryKey skData[], int size, int targetId) {

	int first, last, mid;

	first = 0;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (skData[mid].staffId == targetId) {

			return skData[mid].rrn;
		}
		else if (skData[mid].staffId > targetId) {

			last = mid - 1;
		}
		else if (skData[mid].staffId < targetId) {

			first = mid + 1;
		}
	}

	return -1;
}


void S_sortSecondryKey(S_SecondryKey skData[], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i + 1; j < size; j++) {

			if (lessthan(skData[j].staffName, skData[min].staffName)) {

				min = j;
			}
		}

		S_SecondryKey s;
		s = skData[i];
		skData[i] = skData[min];
		skData[min] = s;
	}
}


int S_get_Id_by_Name(S_SecondryKey skData[], int size, string targetName) {

	int first, last, mid;

	first = 0;
	mid = size / 2;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (skData[mid].staffName == targetName) {

			return skData[mid].staffId;
		}
		else if (greaterthan(skData[mid].staffName, targetName)) {

			last = mid - 1;
		}
		else if (lessthan(skData[mid].staffName, targetName)) {

			first = mid + 1;
		}
	}

	return -1;
}


void S_sortSecondryKey2(S_SecondryKey2 skData[], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i + 1; j < size; j++) {

			if (skData[j].staffDegree < skData[min].staffDegree) {

				min = j;
			}
		}

		S_SecondryKey2 s;
		s = skData[i];
		skData[i] = skData[min];
		skData[min] = s;
	}
}


int S_get_Id_by_Degree(S_SecondryKey2 skData[], int size, float targetDegree) {

	int first, last, mid;

	first = 0;
	mid = size / 2;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (skData[mid].staffDegree == targetDegree) {

			return skData[mid].staffId;
		}
		else if (skData[mid].staffDegree > targetDegree) {

			last = mid - 1;
		}
		else if (skData[mid].staffDegree < targetDegree) {

			first = mid + 1;
		}
	}

	return -1;
}


class Staff {

public:
	void   setStaffId(int id);
	void   setDeptId(int id);
	void   setStaffDegree(float degree);
	void   setStaffName(string name);
	void   writeInFile(fstream& staffFile, fstream& primarykeyFile, fstream& secondrykeyFile, fstream& staffSecondryKey2);
	void   readFromFile(fstream& staffFile, int rrn);
	int    getStaffId();
	int    getDeptId();
	float  getStaffDegree();
	string getStaffName();

private:
	int    staffId;
	int    dept_Id;
	float  staffDegree;
	string staffName;
};


void Staff::setStaffId(int id) {

	staffId = id;
}


void Staff::setDeptId(int id) {

	dept_Id = id;
}


void Staff::setStaffDegree(float degree) {

	staffDegree = degree;
}


void Staff::setStaffName(string name) {

	staffName = name;
}


int Staff::getStaffId() {

	return staffId;
}


int Staff::getDeptId() {

	return dept_Id;
}


float Staff::getStaffDegree() {

	return staffDegree;
}


string Staff::getStaffName() {

	return staffName;
}


void Staff::writeInFile(fstream &staffInfo, fstream &staffPrimarykey, fstream &staffSecondrykey, fstream &staffSecondryKey2) {

	S_PrimaryKey pk;
	S_SecondryKey sk;
	S_SecondryKey2 sk2;
	int size;

	staffInfo.seekp(0, ios::end);
	size = staffInfo.tellp() / sizeof(Staff);

	pk.staffId = staffId;
	pk.rrn = size;

	sk.staffId = staffId;
	sk.staffName = staffName;

	sk2.staffId = staffId;
	sk2.staffDegree = staffDegree;

	staffInfo.write((char*)this, sizeof(Staff));
	staffPrimarykey.write((char*)&pk, sizeof(S_PrimaryKey));
	staffSecondrykey.write((char*)&sk, sizeof(S_SecondryKey));
	staffSecondryKey2.write((char*)&sk2, sizeof(S_SecondryKey2));

}


void Staff::readFromFile(fstream &staffinfo, int rrn) {
	
	int size;

	staffinfo.seekg(0, ios::end);
	size = staffinfo.tellg() / sizeof(Staff);
	
	if (rrn > size || rrn < 0) {
		
		cout << "Error RRN ...!" << endl;
		return;
	}

	staffinfo.seekg(rrn * sizeof(Staff), ios::beg);
	staffinfo.read((char*)this, sizeof(Staff));

}


void setStaffInformation(Staff& s) {

	int staff_id;
	int dept_id;
	float staffDegree;
	string staff_name;
	
	try {

		cout << "Enter Staff ID : ";
		cin >> staff_id;
		cout << endl;

		cout << "Enter Staff Name : ";
		cin.ignore();
		getline(cin, staff_name);
		cout << endl;


		cout << "Enter Staff Degree : ";
		cin >> staffDegree;
		cout << endl;

		cout << "Enter Staff Department Id : ";
		cin >> dept_id;
		cout << endl;

	}
	catch (...) {

		cout << "Input Error ...! " << endl;
	}

	s.setStaffId(staff_id);
	s.setDeptId(dept_id);
	s.setStaffName(staff_name);
	s.setStaffDegree(staffDegree);
}

void viewStaffInformation(Staff s) {

	cout << "Staff ID : " << s.getStaffId() << endl;
	cout << "Staff Name : " << s.getStaffName() << endl;
	cout << "Staff Degree : " << s.getStaffDegree() << endl;
	cout << "Staff Deparment Id : " << s.getDeptId() << endl;
}

int S_getDataByPrimaryKey(int id, fstream& primarykeyfile) {


	primarykeyfile.seekg(0, ios::end);
	int size = primarykeyfile.tellg() / sizeof(S_PrimaryKey);
	primarykeyfile.seekg(0, ios::beg);

	S_PrimaryKey* pkData = new S_PrimaryKey[size];

	for (int i = 0; i < size; i++) {

		primarykeyfile.read((char*)&pkData[i], sizeof(S_PrimaryKey));
	}

	S_sortPrimaryKey(pkData, size);

	int rrn = S_get_RRN_by_id(pkData, size, id);

	return rrn;
}


int S_getDataBySecondryKey(string name, fstream& secondrykeyfile) {

	secondrykeyfile.seekg(0, ios::end);
	int size = secondrykeyfile.tellg() / sizeof(S_SecondryKey);
	secondrykeyfile.seekg(0, ios::beg);

	S_SecondryKey* skData = new S_SecondryKey[size];

	for (int i = 0; i < size; i++) {

		secondrykeyfile.read((char*)&skData[i], sizeof(S_SecondryKey));
	}

	S_sortSecondryKey(skData, size);

	int id = S_get_Id_by_Name(skData, size, name);

	return id;
}


int S_getDataBySecondryKey2(float degree, fstream& secondrykeyfile) {

	secondrykeyfile.seekg(0, ios::end);
	int size = secondrykeyfile.tellg() / sizeof(S_SecondryKey2);
	secondrykeyfile.seekg(0, ios::beg);

	S_SecondryKey2* skData = new S_SecondryKey2[size];

	for (int i = 0; i < size; i++) {

		secondrykeyfile.read((char*)&skData[i], sizeof(S_SecondryKey2));
	}

	S_sortSecondryKey2(skData, size);

	int id = S_get_Id_by_Degree(skData, size, degree);

	return id;
}


int counter(int number, Staff s[], int size) {

	int counter1 = 0;
	for (int i = 0; i < size; i++) {

		if (number == s[i].getDeptId()) {

			counter1++;
		}
	}

	return counter1;
}


int S_getMaxDeptId(fstream& file) {

	file.seekg(0, ios::end);
	int size = file.tellg() / sizeof(Staff);
	file.seekg(0, ios::beg);

	Staff* sData = new Staff[size];

	for (int i = 0; i < size; i++) {

		file.read((char*)&sData[i], sizeof(Staff));
	}

	int max = 0;
	int id;

	for (int i = 0; i < size; i++) {

		if (counter(sData[i].getDeptId(), sData, size) > max) {

			max = counter(sData[i].getDeptId(), sData, size);
			id = sData[i].getDeptId();
		}
	}
	
	return id;
}