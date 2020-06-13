#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <string>
#include <vector>
#include "Department.h"

using namespace std;

struct PrimaryKey {

	int studentId;
	int rrn;
};

struct SecondryKey {

	string studentName;
	int studentId;
};

struct SecondryKey2 {

	int studentId;
	int deptId;
};

void sortPrimaryKey(PrimaryKey pkData [], int size) {

	int min;

	for (int i = 0; i < size; i++) {

		min = i;
		for (int j = i+1; j < size; j++) {

			if (pkData[j].studentId < pkData[min].studentId) {

				min = j;
			}
		}
		
		PrimaryKey p;
		p = pkData[i];
		pkData[i]   = pkData[min];
		pkData[min] = p;
	}
}

int get_RRN_by_id(PrimaryKey pkData[], int size, int targetId) {

	int first, last, mid;

	first = 0;
	mid = size / 2;
	last = size - 1;

	while (first <= last) {

		mid = (first + last) / 2;

		if (pkData[mid].studentId == targetId) {
			
			return pkData[mid].rrn;
		}
		else if (pkData[mid].studentId > targetId) {

			last = mid - 1;
		}
		else if (pkData[mid].studentId < targetId) {

			first = mid + 1;
		}
	}

	return -1;

}

vector<string> query_partition(string query) { // this function will take query of type string and will return vector of string have the same query but in parts 

	vector<string> new_query;
	string sub_string = "";

	for (int i = 0; i <= query.size(); i++) {
		
		if (query[i] == ' ' || query.size() == i) { 
			
			new_query.push_back(sub_string);
			sub_string = "";
		}
		else {

			sub_string += query[i];
		}
	}

	return new_query;
}

void to_lower(string& phase) {

	for (int i = 0; i < phase.size(); i++) {

		if (phase[i] >= 'A' && phase[i] <= 'Z') {

			phase[i] = char(phase[i] + 32);
		}
	}
}

int which_query_user_inter(vector<string> query) { //this function take the query and check if the query is valid or not and if it valid return the query number to perform

	int valid_query1 = 0;
	int valid_query2 = 0;
	int valid_query3 = 0;

	string query1[9] = { "find", "the", "students", "with", "gpa", "between", "x", "and" ,"y" };
	string query2[14] = { "find", "the", "students", "joined", "a", "department", "managed", "by", "a", "staff", "member", "with", "name", "staffname" };
	string query3[9] = { "find", "the","department", "with", "max", "number", "of", "staff", "members" };

	for (int i = 0; i < query.size(); i++) {

		if (query[i] == query1[i] or i == 6 or i == 8) { // we made an exception in index number 7 and 9 because they may take any value 

			++valid_query1;
		}

		if (query[i] == query2[i] || i == 13) { // we made an exception in index 14 because in index 14 will contain the name of staff managed the department

			++valid_query2;
		}

		if (query[i] == query3[i]) {
			
			++valid_query3;
		}
		
	}
	
	if (valid_query1 == 9) {

		return 1;
	}
	else if (valid_query2 == 14) {

		return 2;
	}
	else if (valid_query3 == 9) {
		
		return 3;
	}
	else {

		return -1;
	}

}


class Student {

public:
	void setStudentId(int id);
	void setStudentName(string name);
	void setStudentLevel(int level);
	void setStudentGpa(float gpa);
	void setDepartmentId(int dept_id/*fstream &departmentFile*/);
	void writeInFile(int rrn, fstream& file, fstream& primarykeyfile, fstream& secondrykeyfile);
	void readFromFile(int rrn, fstream& studentinfofile);
	void displayStudentWithGpaBetween(fstream &studentsfile,float lessGpa, float MaxGpa);
	void displayStudentInDepartment(fstream& studentsfile, int dept_id, string departmentManager);
	int getStudentId();
	int getStudentlevel();
	int getDepartmentId();
	float getStudentGpa();
	string getStudentName();

private:
	bool isDeleted = false;
	int nextDel = -1;
	int studentId;
	int studentLevel;
	int deptId = 111;
	float studentGpa;
	string studentName;
};

void setInformation(Student &s) {
	
	int studentId = 0;
	int studentLevel = 0;
	int departmentid = 0;
	float studentGpa = 0;
	string studentName = "";
	
	try {

		cout << "Enter Student ID : ";
		cin >> studentId;
		cout << endl;

		cout << "Enter Student Name : ";
		cin.ignore();
		getline(cin, studentName);
		cout << endl;

		cout << "Enter Student Level : ";
		cin >> studentLevel;
		cout << endl;

		cout << "Enter Student GPA : ";
		cin >> studentGpa;
		cout << endl;

		cout << "Enter Department Id : ";
		cin >> departmentid;
		cout << endl;
	}
	catch(...){

		cout << "Input Error ...! " << endl;
	}
	
	s.setStudentId(studentId);
	s.setStudentName(studentName);
	s.setStudentLevel(studentLevel);
	s.setStudentGpa(studentGpa);
	s.setDepartmentId(departmentid);
}

void viewInformation(Student s) {
	
	cout << "Student ID : "	   << s.getStudentId()    << endl;
	cout << "Student Name : "  << s.getStudentName()  << endl;
	cout << "Student Level : " << s.getStudentlevel() << endl;
	cout << "Student GPA : "   << s.getStudentGpa()   << endl;
	cout << "Department ID : " << s.getDepartmentId() << endl;

}

void Student::setStudentId(int id) {

	studentId = id;
}


void Student::setStudentName(string name) {

	studentName = name;
}


void Student::setStudentLevel(int level) {

	studentLevel = level;
}


void Student::setStudentGpa(float gpa) {

	studentGpa = gpa;
}


void Student::setDepartmentId(int dept_id /*fstream &departmentfile*/) {

	this->deptId = dept_id;
	/*
	Department d;
	departmentfile.seekg(0, ios::end);
	int size = departmentfile.tellg() / sizeof(Department);

	int number = rand() % size;

	departmentfile.seekg(number * sizeof(Department), ios::beg);
	departmentfile.read((char*)&d, sizeof(Department));

	deptId = d.getDepartmentId();
	*/
}


int Student::getStudentId() {

	return studentId;
}


int Student::getStudentlevel() {

	return studentLevel;
}


int Student::getDepartmentId() {

	return deptId;
}


float Student::getStudentGpa() {

	return studentGpa;
}


string Student::getStudentName() {

	return studentName;
}



void Student::writeInFile(int rrn, fstream& studentinfofile, fstream& primarykeyfile, fstream& secondrykeyfile) {

	if (studentinfofile.bad() || primarykeyfile.bad() || secondrykeyfile.bad()) {

		cout << "Error in file ...!" << endl;
		return;
	}

	int size;
	PrimaryKey pk;
	SecondryKey sk;

	studentinfofile.seekp(0, ios::end);
	size = studentinfofile.tellp() / sizeof(Student);

	pk.studentId = studentId;
	pk.rrn = rrn;

	sk.studentName = studentName;
	sk.studentId = studentId;

	if (rrn > size or rrn < 0) {

		cout << "Error RRN ...! " << endl;
		return;
	}

	studentinfofile.seekp(rrn * sizeof(Student) + sizeof(int), ios::beg);
	primarykeyfile.seekp(rrn * sizeof(PrimaryKey), ios::beg);
	secondrykeyfile.seekp(rrn * sizeof(SecondryKey), ios::beg);

	studentinfofile.write((char*)this, sizeof(Student));
	primarykeyfile.write((char*)&pk, sizeof(PrimaryKey));
	secondrykeyfile.write((char*)&sk, sizeof(SecondryKey));

}


void Student::readFromFile(int rrn, fstream& studentinfofile) {

	studentinfofile.seekg(0);
	studentinfofile.seekg(rrn * sizeof(Student) + sizeof(int), ios::beg);
	studentinfofile.read((char*)this, sizeof(Student));
}

void Student::displayStudentWithGpaBetween(fstream& studentsfile, float lessGpa, float MaxGpa) {

	studentsfile.seekg(0, ios::end);
	
	int size = studentsfile.tellp() / sizeof(Student);
	Student* students = new Student[size];

	studentsfile.seekg(sizeof(int), ios::beg);

	for (int i = 0; i < size; i++) {

		studentsfile.read((char*)&students[i], sizeof(Student));
	}
	
	cout << "\nThis List Of Students Who Have GPA Between " << lessGpa << " and " << MaxGpa << "\n";

	for (int i = 0; i < size; i++) {
		
		if (students[i].getStudentGpa() >= lessGpa && students[i].getStudentGpa() <= MaxGpa) {

			cout <<"Id: " << students[i].getStudentId() << " , Name: " << students[i].getStudentName() << endl;
		}
	}

}

void Student::displayStudentInDepartment(fstream& studentsfile, int dept_id, string departmentManager) {

	studentsfile.seekg(0, ios::end);

	int size = studentsfile.tellp() / sizeof(Student);
	Student* students = new Student[size];

	studentsfile.seekg(sizeof(int), ios::beg);

	for (int i = 0; i < size; i++) {

		studentsfile.read((char*)&students[i], sizeof(Student));
	}

	cout << "\nThis List Of Students Who joined the Department managed by " << departmentManager << " : \n";

	for (int i = 0; i < size; i++) {

		if (students[i].getDepartmentId() == dept_id) {

			cout << "Id: " << students[i].getStudentId() << " , Name: " << students[i].getStudentName() << endl;
		}
	}
}


int getPrimaryKey(int id, fstream &primarykeyfile) {
	
	
	primarykeyfile.seekg(0, ios::end);
	int size = primarykeyfile.tellg() / sizeof(PrimaryKey);
	primarykeyfile.seekg(0, ios::beg);

	PrimaryKey* pkData = new PrimaryKey[size];
		
	for (int i = 0; i < size; i++) {

		primarykeyfile.read((char*)&pkData[i], sizeof(PrimaryKey));
	}

	sortPrimaryKey(pkData, size);

	int rrn = get_RRN_by_id(pkData, size, id);

	return rrn;
}