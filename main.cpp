#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include "Department.h"
#include "Staff.h"

using namespace std;

int main()
{
    fstream studentsinfo, primarykeyinfo, secondrykeyinfo;
    fstream departmentinfo, dept_primarykeyinfo, dept_secondrykeyinfo, dept_secondrykeyinfo2;
    fstream staffinfo, staff_primarykeyinfo, staff_secondrykeyinfo, staff_secondrykeyinfo2;
    Student    s1, s2;
    Department d1, d2;
    Staff      st1, st2;
    string     name;
    string     query;
    vector<string> query2;
    int        choice;
    int        id;
    int        rrn;
    
    studentsinfo.open("students_info.txt", ios::out | ios::in);
    primarykeyinfo.open("students_primary_key.txt", ios::out | ios::in);
    secondrykeyinfo.open("students_secondry_key.txt", ios::out | ios::in);

    departmentinfo.open("department_info.txt", ios::out | ios::in);
    dept_primarykeyinfo.open("department_primary_key.txt", ios::out | ios::in);
    dept_secondrykeyinfo.open("department_secondry_key.txt", ios::out | ios::in);
    dept_secondrykeyinfo2.open("department_secondry_key2.txt", ios::out | ios::in);

    staffinfo.open("staff_info.txt", ios::out | ios::in);
    staff_primarykeyinfo.open("staff_primrykey_info.txt", ios::out | ios::in);
    staff_secondrykeyinfo.open("staff_secondrykey_info.txt", ios::out | ios::in);
    staff_secondrykeyinfo2.open("staff_secondrykey_info2.txt", ios::out | ios::in);


    cout << "how many Students would you like to add " << endl; 
    cin >> choice;

    for (int i = 0; i < choice; i++) {

        setInformation(s1);
        s1.writeInFile(i, studentsinfo, primarykeyinfo, secondrykeyinfo);
    }

    cout << "how many Department would you like to add : " << endl;
    cin >> choice;

    for (int i = 0; i < choice; i++) {

        setDepartmentInformation(d1);
        d1.writeToFile(departmentinfo, dept_primarykeyinfo, dept_secondrykeyinfo, dept_secondrykeyinfo2);
    }
    
    cout << "how many Staff would you like to add : " << endl;
    cin >> choice;

    for (int i = 0; i < choice; i++) {

        setStaffInformation(st1);
        st1.writeInFile(staffinfo, staff_primarykeyinfo, staff_secondrykeyinfo, staff_secondrykeyinfo2);
    }
    cin.ignore();

    while (true) {
        
        cout << "\nWrite your query : " << endl;

        getline(cin,query);
        
        to_lower(query);

        query2 = query_partition(query);
        
        choice = which_query_user_inter(query2);

        switch (choice) {

            case 1: 
            {
                float gpa1 = 0.0, gpa2 = 0.0;
                gpa1 = stof(query2[6]);
                gpa2 = stof(query2[8]);
                s2.displayStudentWithGpaBetween(studentsinfo, gpa1, gpa2);
                break;
            }
            case 2:
            {
                name = query2[13];
                id = D_getDataBySecondryKey2(name, dept_secondrykeyinfo2);
                s2.displayStudentInDepartment(studentsinfo, id, name);
                break;
            }
            case 3:
            {
                id = S_getMaxDeptId(staffinfo);
                rrn = D_getDataByPrimaryKey(id, dept_primarykeyinfo);
                d2.readFromFile(rrn, departmentinfo);
                viewDepartmentInformation(d2);
                break;
            }
            default: 
            {
                cout << "Error Query ...!" << endl;
                break;
            }
        
        }
    }
    
    studentsinfo.close();
    primarykeyinfo.close();
    secondrykeyinfo.close();

    departmentinfo.close();
    dept_primarykeyinfo.close();
    dept_secondrykeyinfo.close();
    dept_secondrykeyinfo2.close();

    staffinfo.close();
    staff_primarykeyinfo.close();
    staff_secondrykeyinfo.close();
    staff_secondrykeyinfo2.close();

    return 0;
}
