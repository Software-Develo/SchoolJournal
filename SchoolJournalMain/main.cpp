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

const string num = "0123456789";
const string letters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФЧЦШЩЫЭЮЯ";
const string symbol = "?!@#$%^&*()_+-='|/.,><:;";
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
    string lexem;
    string subject;
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
            lexem = string(ptr);
            if(lexem == "Ученик"){
                while((ptr = strtok(NULL, sign)) != NULL){
                    stud_enter++;
                    if(stud_enter == 1){
                        stud_name = lexem;
                    }else{
                        stud_name.push_back(' ');
                        stud_name.append(lexem);
                    }
                }
                stud_enter = 0;
            }else if(lexem == "Предмет"){
                while((ptr = strtok(NULL, sign)) != NULL){
                    if(lexem.find_first_of(letters) != string::npos){// Если в лексеме есть хоть одна буква
                        subj_enter++;
                        if(subj_enter == 1){
                            subject = lexem;
                        }else{
                            subject.push_back(' ');
                            subject.append(lexem);
                        }
                    }else if(lexem.find_first_of(letters) == string::npos && lexem.find_first_of(symbol) == string::npos && lexem.find_first_of(num) != string::npos){

                    }
                }
            }
        }

    }else cout << "Файл " << st_path << " не открылся!!!!!";



    st_fail.close();
    return 0;

}