#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename);
    string text;
    char name[100];
    int x,y,z,sum=0;
    while(getline(file,text)){
        char format[] = "%[^:]: %d %d %d";
        sscanf(text.c_str(),format,name,&x,&y,&z);
        sum=x+y+z;
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
        
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: \n";
    string line;
    getline(cin,line);
    int idx = line.find(' ');
    command = line.substr(0,idx);
    key = line.substr(idx+1);
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    int size = names.size();
    bool f=false;
    for(int i=0; i<size; i++){
        string name;
        name = toUpperStr(names[i]);
        if(name==key) {
            cout << "---------------------------------\n";
            cout << names[i] << "\'s score = " << scores[i] << endl;
            cout << names[i] << "\'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            f=true;
            break;
        }
        
    }
    if(f==false){
            cout << "---------------------------------\n";
            cout << "Cannot found." << endl;
            cout << "---------------------------------\n";
        }
   
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int size = grades.size();
    bool f=false;
    cout << "---------------------------------\n";
    for(int i=0;i<size;i++){
        string g = string()+grades[i];
        if(g==key){
            cout << names[i] << " (" << scores[i] << ")\n";
            f=true;
        }
        
    }
    if(f==false){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}