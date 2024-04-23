#include "interface.h"
#include <iostream>
#include <string>

using namespace std;

string settings_file_path = "settings.dat";

class SettingsHolder{
static string settings_path;

static bool current_using_unicode;
static string current_encrypted_path;
static string current_unencrypted_path;
static string current_origin_folder_path;

static void   change_encrypted_path     (string path);
static void   change_unencrypted_path   (string path);
static void   change_origin_folder_path (string path);
static void   change_using_unicode      (bool using_unicode);

static string encrypted_path();
static string unencrypted_path();
static string origin_folder_path();
static bool   using_unicode();
};

CodeBreaker breaker;
void load_parameters(){}
void main_menu();
void alphabet_settings();
void file_settings(){}
void encryptions_menu();

_char spot_symbol(string p_symbol){
    if(p_symbol == "'''" || p_symbol == "'")
        return '\'';
    for(int i = 0; i < int(p_symbol.size()); i++)
        if(p_symbol[i] == '\'') {p_symbol.erase(i, 1); i--;}
    if(p_symbol.size() == 1)
        return p_symbol[0];
    else{
        cout << "invalid symbol";
        return '\0';
    }
}


void start_interface()
{
    load_parameters();
    cout << "Welcome to Vigenere encrypter! \n";

    std::cout << "Using " << CHECK << " encoding\n"<< std::endl;

    set_standart_en_alphabet();
    cout << "Standart English alphabet is set\n\n";

    main_menu();
    return;
}


void main_menu()
{
    bool run = true;
    string option;

    while(run){
        cout << "===Main menu:            \n";
        cout << "0 - Encryptions          \n";
        cout << "1 - Code Breaker         \n";
        cout << "2 - Alphabet settings    \n";
        cout << "3 - Filepath settings    \n";
        cout << "q - Exit programm      \n\n";
        cout << "Input: ";

        cin >> option;
        cout << "\n";

        if(option == "0")
            encryptions_menu();
        else if(option == "1")
            alphabet_settings();
        else if(option == "3")
            file_settings();
        else if(option == "q"){
            cout << "Press any key to close this window";
            return;
        }
        else
            cout << "incorrect input \n";

        cout << "\n========================================================================\n";
    }
}

void encryptions_menu(){
    bool run = true;
    string option;
    while(run){

        cout << "======Encryptions:                      \n";
        cout << "0 - Transform string of text            \n";
        cout << "1 - Reverse transform string of text    \n";
        cout << "2 - Transform text in file              \n";
        cout << "3 - Reverse transform text in file      \n";

        cout << "b - Go back to main menu         \n\n";
        cout << "Input: ";

        cin >> option;
        cout << "\n";

        if(option == "0"){
            string str;
            string key;

            cin.ignore();
            cout << "Input string: "; getline(cin, str);
            cout << "Input key:    "; getline(cin, key);
            _string wstr = _string(str.begin(), str.end());
            _string wkey = _string(key.begin(), key.end());

            _string wres = encrypt_str(wstr, wkey);
            str = string(wres.begin(), wres.end());
            cout << "Result is: " << str << endl;
        }
        else if(option == "1"){
            string str;
            string key;

            cin.ignore();
            cout << "Input string: "; getline(cin, str);
            cout << "Input key:    "; getline(cin, key);
            _string wstr = _string(str.begin(), str.end());
            _string wkey = _string(key.begin(), key.end());

            _string wres = unencrypt_str(wstr, wkey);
            str = string(wres.begin(), wres.end());
            cout << "Result is: " << str << endl;
        }
        else if(option == "2"){
            set_short_en_alphabet();
            cout << "Short English alphabet is set!\n";
        }
        else if(option == "3"){
            cout << "\n Input every symbol for the alphabet (space is also a symbol)"
                    "\n Input: ";
            string text;
            cin >> text;

            char new_line;
            cout << "Include \"new line\" ('\\n') symbol? (y/n):"; cin >> new_line;
            if(new_line == 'y' || new_line == 'Y')
                text.append("\n");

            make_alphabet_from_text(text);
        }
        else if(option == "4"){
            cout << "Input symbol: ";
        }
        else if(option == "b")
            return;
        else
            cout << "Incorrect input \n";
        cout << "\n========================================================================\n";
    }

}

void alphabet_settings()
{
    bool run = true;
    string option;
    while(run){

        cout << "======Alphabet settings:           \n";
        cout << "0 - Display alphabet in use        \n";
        cout << "1 - Set standart English alphabet  \n";
        cout << "2 - Set short English alphabet     \n";
        cout << "3 - Set custom alphabet            \n";
        cout << "4 - Set ultimate symbol            \n";
//        cout << "4 - Set standart Russian alphabet (Unicode is needed)\n\n";
        cout << "======Encodings (now using " << CHECK << "):        \n";
        cout << "A - Change to ASCII                \n";
        cout << "U - Change to Unicode              \n";

        cout << "b - Go back to main menu         \n\n";
        cout << "Input: ";

        cin >> option;
        cout << "\n";

        if(option == "0")
            display_alphabet();
        else if(option == "1"){
            set_standart_en_alphabet();
            cout << "Standart English alphabet is set!\n";
        }
        else if(option == "2"){
            set_short_en_alphabet();
            cout << "Short English alphabet is set!\n";
        }
        else if(option == "3"){
            cout << "\n Input every symbol for the alphabet (space is also a symbol)"
                    "\n Input: ";
            string text;
            cin >> text;

            char new_line;
            cout << "Include \"new line\" ('\\n') symbol? (y/n):"; cin >> new_line;
            if(new_line == 'y' || new_line == 'Y')
                text.append("\n");

            make_alphabet_from_text(text);
        }
        else if(option == "4"){
            cout << "Input symbol: ";
        }
        else if(option == "b")
            return;
        else
            cout << "Incorrect input \n";
        cout << "\n========================================================================\n";
    }
    cout << "Exit successful";
}


