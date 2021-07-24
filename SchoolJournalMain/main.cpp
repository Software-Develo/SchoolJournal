//
//  main.cpp
//  SchoolJournalMain
//
//  Created by Marat Khisamutdinov on 7/22/21.
//
// /Users/maratkhisamutdinov/Desktop/spisok.txt

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
    vector<vector<string>> vect_peo;
};
class Diary{
    int i = 0;
    int j = 0;
public:
    vector<People> vect_dia;

    void print(){// Выводим вектор на экран
        for(int a = 0; a < vect_dia.size(); a++){
            cout << endl << "Ученик" << "\t" << vect_dia[a].fullname << ":" << endl;
            while(i < vect_dia[a].vect_peo.size()) {
                cout << "\t" << "Предмет" << "\t";
                while (j < vect_dia[a].vect_peo[i].size()) {
                    cout << vect_dia[a].vect_peo[i][j] << " ";
                    j++;
                }
                cout << endl;
                j = 0;
                i++;
            }
            i = 0;
        }
        cout << endl;
    }
};

int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "rus");

    string st_path;
    string name;
    string subject;
    char c_line[100];
    char *ptr;
    int stud_enter = 0;
    int subj_enter = 0;
    bool ItIsEnd = false;
    bool ItIsWord = false;

    cout << "Дневник" << endl << "Введите путь до файла" << endl << "Путь: ";
    cin >> st_path;
    cout << endl << endl;

    People people;
    Diary diary;

    ifstream st_fail;
    st_fail.open(st_path);
    if(st_fail.is_open()){
        cout << "Файл " << st_path << " открылся" << endl;
        vector<string> vect;
        st_fail.getline(c_line, 100);
        while(!st_fail.eof()){
            ptr = strtok(c_line, sign);
            if(string(ptr) == "Ученик"){
                if(ItIsEnd){
                    diary.vect_dia.push_back(people);
                    people.vect_peo.clear();
                }
                while((ptr = strtok(NULL, sign)) != NULL){
                    stud_enter++;
                    if(stud_enter == 1){
                        name = string(ptr);
                    }else{
                        name.push_back(' ');
                        name.append(string(ptr));
                    }
                }
                people.fullname = name;
                stud_enter = 0;
            }else if(string(ptr) == "Предмет"){
                subj_enter = 0;
                while((ptr = strtok(NULL, sign)) != NULL){
                    if(string(ptr).find_first_of(letters) != string::npos){// Если в лексеме есть хоть одна буква
                        subj_enter++;
                        if(subj_enter == 1){
                            subject = string(ptr);
                        }else{
                            subject.push_back(' ');
                            subject.append(string(ptr));
                        }
                        ItIsWord = true;
                    }
                    // Если нет букв, символов, но есть цифры
                    else if(string(ptr).find_first_of(letters) == string::npos && string(ptr).find_first_of(symbol) == string::npos && string(ptr).find_first_of(num) != string::npos){
                        if(ItIsWord) {subj_enter = 0; ItIsWord = false;}
                        subj_enter++;
                        if(subj_enter == 1){
                            vect.push_back(subject);
                            vect.push_back(string(ptr));
                        }else{
                            vect.push_back(string(ptr));
                        }
                    }
                }
                if(ptr == NULL && ItIsWord) vect.push_back(subject);
                people.vect_peo.push_back(vect);
                vect.clear();
                ItIsEnd = true;
            }

            st_fail.getline(c_line, 100);
        }
        diary.vect_dia.push_back(people);
        people.vect_peo.clear();
        diary.print();
    }else cout << "Файл " << st_path << " не открылся!!!!!" << endl;
    st_fail.close();
    return 0;

}