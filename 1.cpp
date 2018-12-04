#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int check_file (fstream& file) {
    if (file.is_open()==0) { // if the file is not open, we open it
       file.open("StudentsGrades.db",ios::in|ios::out);
       if (file.is_open()==0) return -1; // if the file is still not open, this means it does not exist and we cannot search
       }
    return 0;
}
int main () {
    long long int fn,grade,input,input2,pos,temp;
    /* fn and grade - store faculty number and grade respectively
       input and input2 are for the operations delete and update
       pos is for storing the position of the read text
       temp is temporary variable */
    string command,name1,name2; // variables for storing command and the first and last name respectively
    fstream file; // variable for the file
    bool flag;
    for (;;) {
        cin >> command ;
        if (command=="exit") break; // if command is exit, the program has to finish
        else if (command=="create") { // if command is create, we input data for a person and store it in the file
                if (file.is_open()==0) { // we check if the file is already open
                   file.open("StudentsGrades.db",ios::in|ios::out); // if the file is not open, we open it
                   if (file.is_open()==0) { // if the file is still not open, this means that it does not exist and we create it
                      file.open("StudentsGrades.db",ios::in|ios::out|ios::trunc);
                      }
                   }
                cin >> fn >> name1 >> name2 >> grade ; // we input the data for some student
                file.clear(); // we clear the flags
                file.seekg(0,ios_base::end); // we position the stream at the end of the file
                file << fn << " " << name1 << " " << name2 << " " << grade << "\n"; // we save the data in the file
                cout << "Record saved!\n";
                }
        else if (command=="sequentialSearch") { // if command is sequentialSearch we search for a person in the file
                if (check_file(file)==-1) continue;
                cin >> input ; // we input a faculty number for the search
                file.clear(); // we clear the flags
                file.seekg(0,ios_base::beg); // we position the stream at the beginning of the file
                for (;;) {
                    if (!(file >> fn >> name1 >> name2 >> grade)) break; // this statement checks if we are at the end of the file
                    if (input==fn) { // if the current faculty number is the same as the input faculty number, we found the student
                       cout << fn << " " << name1 << " " << name2 << " " << grade << "\n";
                       break;
                       }
                    }
                }
        else if (command=="delete") {
                if (check_file(file)==-1) continue;
                cin >> input ; // we input a faculty number for the deletion
                file.clear(); // we clear the flags
                file.seekg(0,ios_base::beg); // we position the stream at the beginning of the file
                ofstream copy1; // file with the information after the delete operation
                copy1.open("Copy.db",ios::out);
                flag=0; // variable to know if the faculty number is found
                for (;;) {
                    if (!(file >> fn >> name1 >> name2 >> grade)) break; // this statement checks if we are at the end of the file
                    if (input!=fn) copy1 << fn << " " << name1 << " " << name2 << " " << grade << "\n"; // we write the information for the other students in the copy file
                    else flag=1; // set the flag if we find the student
                    }
                copy1.close(); // close the copy file
                file.close(); // close the original file
                remove("StudentsGrades.db"); // remove the original file
                rename("Copy.db","StudentsGrades.db"); // rename the copy file to be with the name of the original
                file.open("StudentsGrades.db",ios::in|ios::out); // open the file
                if (flag==0) cout << "Record not found!\n";
                else cout << "Record deleted!\n";
                }
        else if (command=="update") {
                if (check_file(file)==-1) continue;
                cin >> input >> input2 ; // we input a faculty number for the deletion
                file.clear(); // we clear the flags
                file.seekg(0,ios_base::beg); // we position the stream at the beginning of the file
                flag=0; // variable to know if the faculty number is found
                pos=0;
                for (;;) {
                    if (!(file >> fn >> name1 >> name2 >> grade)) break; // this statement checks if we are at the end of the file
                    temp=fn;
                    for (;;) { // cycle for calculating the number of digits of fn
                        if (temp==0) break;
                        pos++;
                        temp/=10;
                        }
                    pos++; // increase pos for the space after fn
                    pos+=name1.size()+1; // increase pos by the length of the string and the space after it
                    pos+=name2.size()+1; // increase pos by the length of the string and the space after it
                    if (input==fn) { // if the current faculty number is the same as the input faculty number, we found the student
                       file.seekp(pos,ios_base::beg); // set the position of the put pointer to pos
                       file << input2 ;
                       flag++;
                       break;
                       }
                    pos+=1+2; // increase pos by the length of the digit (1) and the new line after it (2)
                    }
                if (flag==0) cout << "Record not found!\n";
                else cout << "Record saved!\n";
                }
        }
    file.close(); // we close the file because we finished the work with it
    cout << endl ;
    return 0;
}
