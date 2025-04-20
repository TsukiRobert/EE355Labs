
#include "person.h"
#include "misc.h"
#include <iostream>
#include <utility>
using namespace std;

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    // TODO: complete the method!
}

Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    string type;
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(b_date);
    for(int i = 0; i < email.length(); i++){
        if(email[i] == ')'){
            type = email.substr(1, i-1);
            email = email.substr(i+2);
            break;
        }
    }
    this->email = new Email(type, email);
    for(int i = 0; i < phone.length(); i++){
        if(phone[i] == ')'){
            type = phone.substr(1, i-1);
            phone = phone.substr(i+2);
            break;
        }
    }
    this->phone = new Phone(type, phone);
}

Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    getline(cin,f_name);

    cout << "Last Name: ";
    getline(cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    getline(cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    // code here
    getline(cin, type);
    
    cout << "Email address: ";
    // code here
    getline(cin, temp);
    this->email = new Email(type, temp);

    cout << "Type of phone number: ";
    // code here
    getline(cin, type);
    cout << "Phone number: ";
    // code here
    // code here
    getline(cin, temp);
    this->phone = new Phone(type, temp);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    ifstream infile(filename);
    if (!infile.is_open()){
        cerr << "Error opening file!" << endl;
        return;
    }
    string type, fileline;
    getline(infile, fileline);
    this->f_name = fileline;
    getline(infile, fileline);
    this->l_name = fileline;
    getline(infile, fileline);
    this->birthdate = new Date(fileline);
    getline(infile,fileline);
    string myphone, mymail;
    for(int i = 0; i < fileline.length(); i++){
        if(fileline[i] == ')'){
            type = fileline.substr(1, i-1);
            myphone = fileline.substr(i+2);
            break;
        }
    }
    this->phone = new Phone(type, myphone);
    getline(infile, fileline);
    for(int i = 0; i < fileline.length(); i++){
        if(fileline[i] == ')'){
            type = fileline.substr(1, i-1);
            mymail = fileline.substr(i+2);
            break;
        }
    }
    this->email = new Email(type, mymail);
}
   




bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return (this->f_name == rhs.f_name && this->l_name == rhs.l_name && this->birthdate->get_month() == rhs.birthdate->get_month() && this->birthdate->get_day() == rhs.birthdate->get_day() && this->birthdate->get_year() == rhs.birthdate->get_year());
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
    cout << l_name <<", " << f_name << endl;
    birthdate->print_date("Month D, YYYY");
    cout << "Phone ";
    phone->print();
    cout << "Email ";
    email->print();
    for (Person* f : myfriends){
        cout << codeName(f->f_name, f->l_name) << " (" << f->f_name << " " << f->l_name << ")" << endl;
    }
}

void Person::makeFriend(Person* newfriend){
    for (Person* f : myfriends){
        if (newfriend == f || newfriend == this){ //handling adding an existing friend/oneself
            return;
        }
    }
    myfriends.push_back(newfriend);
}

void Person::print_friends (){
    vector<pair<string,Person*>> person_and_code;
    for (Person* f : myfriends){
        string individual_code = codeName (f->f_name, f->l_name);
        person_and_code.push_back({individual_code, f});
    }

    for (int i = 0; i < person_and_code.size()-1; i++){ //selection sort
        int current_min = i;
        for (int j = i+1; j<person_and_code.size(); j++){ 
            if (person_and_code[current_min].first.substr(0,2) > person_and_code[j].first.substr(0,2)){
                current_min = j;
            }
        }
        pair<string,Person*> temp = person_and_code[current_min];
        person_and_code[current_min] = person_and_code[i];
        person_and_code[i] = temp;
    }

    cout << this-> f_name << ", " << this->l_name << endl;
    cout << "--------------------------------" << endl;

    for (pair<string,Person*> p : person_and_code){
        cout << p.second->f_name << ", " << p.second->l_name << endl;
    }

}