//
//  main.cpp
//  SchoolJournalMain
//
//  Created by Marat Khisamutdinov on 7/22/21.
//
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const char *sign = " \t \r \n";

class People{
public:
    string fullname;
    vector<vector<string>> vect;
};
class Diary{
public:
    vector<People> vect_dia;
};


int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "rus");

    string st_path;
    string stud_name;
    char c_line[100];
    char *ptr;
    int stud_enter = 0;
    int subj_enter = 0;

    cout << "Дневник" << endl << "Введите путь до файла" << endl << "Путь: ";
    cin >> st_path;
    cout << endl << endl;

    People people;
    Diary diary;

    ifstream st_fail;
    st_fail.open(st_path);
    if(st_fail.is_open()){
        cout << "Файл " << st_path << " открылся";

        st_fail.getline(c_line, 100);
        while(!st_fail.eof()){
            ptr = strtok(c_line, sign);

            if(string(ptr) == "Ученик"){
                while((ptr = strtok(NULL, sign)) != NULL){
                    stud_enter++;
                    if(stud_enter == 1){
                        stud_name = string(ptr);
                    }else{
                        stud_name.push_back(' ');
                        stud_name.append(ptr);
                    }
                }
                stud_enter = 0;
            }else if(string(ptr) == "Предмет"){
                while((ptr = strtok(NULL, sign)) != NULL){

                }
            }
        }

    }else cout << "Файл " << st_path << " не открылся!!!!!";



    st_fail.close();
    return 0;

}