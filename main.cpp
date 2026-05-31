#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>

using namespace std;

const string version = "0.1";

char actions[2] = {'C', 'D'};
string save_file_name;

const char* appdata = getenv("APPDATA");
string config_path = string(appdata) + "\\todo\\config.txt";

void SetCustomPath(string path) {
    save_file_name = path;
}

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
         << "-list" << endl
         << "-path [path]" << endl;
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

    //Check if config path and file exist. If not create them
    if(!filesystem::exists(string(appdata) + "\\todo")) {
        filesystem::create_directories(string(appdata) + "/todo");
    }
    if(!filesystem::exists(config_path)) {
        ofstream file(config_path);
        file.close();
    }

    //Check if there is a todos.txt path. If not use the predefined one.
    ifstream config_file(config_path);
    getline(config_file, save_file_name);
    config_file.close();

    if(save_file_name.empty()) {
        ofstream config_file(config_path);
        config_file << string(appdata) + "\\todo\\todos.txt";
        config_file.close();

        ofstream file(string(appdata) + "\\todo\\todos.txt");
        file.close();
        
        save_file_name = string(appdata) + "\\todo\\todos.txt";
    }

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

        if(action == "-path") {
            if(argc == 3) {
                string path = argv[2];

               const char* arr = path.c_str(); 

               char last_char {};
               size_t len = strlen(arr);
               for(int i = 0; i < len; i++) {
                    if(arr[i] == '\\') {
                        if(arr[i + 1] != '\\' && arr[i - 1] != '\\') {
                            cout << "Error at " << i << "   ---->   '" << arr[i - 2] << arr[i - 1] << arr[i] << arr[i + 1] << arr[i + 2] << "'" << endl 
                                 << "needs double backslash or singular slash" <<endl;
                            return 0;
                        }
                    }
                    last_char = arr[i];
               }

                SetCustomPath(path);
            }
            else {
                cout << save_file_name << endl;
                Help();
            } 
        }
    }
    else {
        PresentProgram();
    }

    return 0;
}