#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string version = "0.1";

char actions[2] = {'C', 'D'};
const string save_file_name = "D:\\Programmier Projekte\\C++\\TodoApp\\todos.txt";

void DeleteLine(int line) {
    string todo;
    string temp_savefile;
    ifstream save_file_input(save_file_name);

    int i {};
    while(getline(save_file_input, todo)) {
        if(i != line) {
            temp_savefile.append(todo);
            temp_savefile.append("\n");
        }
        i++;
    }
    ofstream save_file(save_file_name);
    save_file << temp_savefile;
    save_file.close();
}

void CreateTodo(string name_of_new_todo) {
    cout << "Creating Todo: <" << name_of_new_todo << ">" << endl;

    ofstream save_file(save_file_name, ios::app);
    save_file << name_of_new_todo << endl;
    save_file.close();
}

void ListTodos() {
    ifstream save_file_input(save_file_name);
    string todo;

    int i {};
    while(getline(save_file_input, todo)) {
        cout << todo << "   [" << i << "]" << endl;
        i++;
    }
    cout << endl;

    save_file_input.close();

    /*cout << "What action do you want to do?" << endl << endl
         << "Create new ToDo. (C)" << endl
         << "Delete a ToDo. (D)" << endl;

    char user_action {};
    cin >> user_action;
    cin.ignore();

    for(int i = 0; i < sizeof(actions); i++) {
        if(actions[i] == user_action) {
            if(user_action == 'C') {
                cout << "Enter your Todo!" << endl << endl;

                string new_todo_name;
                getline(cin, new_todo_name);

                CreateTodo(new_todo_name);
                ListTodos();
            }

            if(user_action == 'D') {
                cout << "Which Todo to delete? (Id)" << endl;

                int id_to_delete {};
                cin >> id_to_delete;

                DeleteLine(id_to_delete);
                ListTodos();
            }
        }
    }*/
}

void Help() {
    cout << "Valid Commands:" << endl
         << "-create [name]" << endl
         << "-delete [id]" << endl
         << "-list" << endl;
}

void PresentProgram() {
    cout << "***Todo list for KURT***" << endl << endl
         << "Version: " << version << endl << endl
         << "-help for help" << endl << endl
         << "Written in C++" << endl
         << "By: ClckZ" << endl;
}

int main(int argc, char* argv[]) {
    string action;
    if(argc >= 2) {
        action = argv[1];

        if(action == "-create") {
            if(argc == 3) {
                string second_argument = argv[2];
                CreateTodo(second_argument);
            }
            else {
                Help();
            }   
        }

        if(action == "-delete") {
            if(argc == 3) {
                int id = stoi(argv[2]);
                DeleteLine(id);
            }
            else {
                Help();
            }   
        }

        if(action == "-list") {
            ListTodos();  
        }
    }
    else {
        PresentProgram();
    }

    return 0;
}