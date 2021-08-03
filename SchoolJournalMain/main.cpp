//
//  main.cpp
//  SchoolJournalMain
//
//  Created by Marat Khisamutdinov on 7/22/21.
//
//  /Users/maratkhisamutdinov/Desktop/spisok.txt

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;


const string space = "     ";
const string num = "0123456789";
const string letters = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФЧЦШЩЫЭЮЯ";
const string symbol = "?!@#$%^&*()_+-='|/.,><:;";
const char *sign = " \t \r \n";

string fullname;
string name;
int a = 0;
int i = 0;
int j = 0;

class People{
public:
    string peo_name;
    vector<vector<string>> vect_peo;
};
class Diary{
    vector<string> input;
    string name;
    string subj;
    string mark;
    int number = 0;
    bool know_fullname = false;
    bool have = false;
    bool correct = false;
public:
    vector<People> vect_dia;

    bool new_fullname(){// Новое имя
        cout << "Фамилия и имя ученика: ";
        cin.get();
        getline(cin, fullname);
        for(i = 0; i < vect_dia.size(); i++){
            if(fullname == vect_dia[i].peo_name) return false;// Если это ФИ уже существует, то это не новый ученик
        }
        return true;// Иначе true
    }
    int adding_subject(){// Добавить предмет
        if(know_fullname){// Если знаем ФИ
            cout << "Название предмета: ";
            cin.get();
            getline(cin, subj);
            for(a = 0; a < vect_dia.size(); a++){
                if(vect_dia[a].peo_name == fullname){// Если нашли ученика
                    for(i = 0; i < vect_dia[a].vect_peo.size(); i++){
                        if(vect_dia[a].vect_peo[i][0] == subj){// Если нашли этот предмет
                            cout << "Оценка: ";
                            cin >> mark;
                            vect_dia[a].vect_peo[i].emplace_back(mark);// Записываем оценку к этому предмету
                            have = true;
                            break;
                        }
                    }
                    if(have) break;
                }
            }
            if(!have){// Если такого предмета нет
                correct = false;
                input.clear();// Очищаем вектор
                for(a = 0; a < vect_dia.size(); a++) {
                    if(vect_dia[a].peo_name == fullname) {// Если нашли ученика
                        input.emplace_back(subj);// В вектор записываем предмет
                        while(!correct) {
                            cout << "Добавить оценку - 1, ничего не делать - 2" << space;
                            cin >> number;
                            switch (number) {
                                case 1:
                                    correct = true;
                                    cout << "Оценка: ";
                                    cin >> mark;
                                    input.emplace_back(mark);
                                    break;
                                case 2:
                                    correct;
                                    return 0;
                            }
                        }
                        vect_dia[a].vect_peo.emplace_back(input);// Вектор записываем в другой вектор
                    }
                }

            }
        }
        else{

        }
        return 0;
    }
    int adding_student(){// Добавить ученика
        if(new_fullname()){// Если это новый ученик

        }
        else{
            cout << "Такой ученик уже существует. Чтобы добавить предмет к нему нажмите 1, чтобы добавить оценку нажмите 2, если ничего, то 3" << space;
            cin >> number;
            switch(number){
                case 1:
                    know_fullname = true;// Знаем его ФИ
                    adding_subject();// Добавление предмета
                case 3:
                    return 0;
            }
        }
        return 0;
    }
    void editing_diary(){
        cout << "Нажимайте на цифры на клавиатуре взависимости от того, что нужно выбрать" << endl;
        cout << "Добавить ученика - 1" << space;
        cin >> number;
        switch(number){
            case 1:
                adding_student();// Функция для добавления учеников
        }
    }
    void print(){// Выводим вектор на экран
        for(a = 0; a < vect_dia.size(); a++){
            i = 0;
            cout << endl << "Ученик" << "\t" << vect_dia[a].peo_name << ":" << endl;
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
                people.peo_name = name;
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
        diary.editing_diary();
        diary.print();

    }else cout << "Файл " << st_path << " не открылся!!!!!" << endl;

    st_fail.close();
    return 0;

}
