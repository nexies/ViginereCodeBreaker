#include "f_encryptions.h"
#include "fstream"
#include "sstream"
#include "iostream"
#include "string"

using namespace std;

_string encrypt_str(_string str, _string key){
    _string out = str;

    for(int i = 0; i < int(out.size()); i++){
        out[i] = symbol[index[str[i]] + index[key[i%key.size()]]];
    }
    return out;
}

_string unencrypt_str(_string str, _string key){
    _string out = str;

    for(int i = 0; i < int(out.size()); i++){
        out[i] = symbol[index[str[i]] - index[key[i%key.size()]]];
    }
    return out;
}

void encrypt_str(_string *str, _string key)
{
    uint64_t uint_size = uint64_t(str->size());
    int int_size = int(str->size());
    for(uint64_t i = 0; i < uint64_t(str->size()); i++){
        (*str)[i] = symbol[index[(*str)[i]] + index[key[i%key.size()]]];
    }
}

void unencrypt_str(_string *str, _string key)
{
    for(uint64_t i = 0; i < uint64_t(str->size()); i++){
        (*str)[i] = symbol[index[(*str)[i]] - index[key[i%key.size()]]];
    }
}

string encrypt_file(string filename, string key){
    _ifstream in;
    _stringstream buffer;
    _ofstream out;
    _string text;

    in.open(filename);

    out.open(filename.substr(0, filename.size() - 4) + " enc. " + key + ".txt");

    buffer << in.rdbuf();
    text = buffer.str();
    int text_size = int(text.size());

    _string _key(key.begin(), key.end());

    encrypt_str(&text, _key);
    out << text;

    out.close();
    in.close();

    string result_filename = filename.substr(0, filename.size() - 4) + " enc. " + key + ".txt";
    cout << "Encryption saved in \"" << result_filename << "\"" << endl;
    return result_filename;
}

string unencrypt_file(string filename, string key){
    _ifstream in;
    _stringstream buffer;
    _ofstream out;
    _string text;

    in.open(filename);
    out.open(filename.substr(0, filename.size()-4) + " unc. " + key + ".txt");

    buffer << in.rdbuf();
    text = buffer.str();

    _string _key(key.begin(), key.end());
    unencrypt_str(&text, _key);
    out << text;

    out.close();
    in.close();

    string result_filename = filename.substr(0, filename.size()-4) + " unc. " + key + ".txt";
    cout << "Unencryption saved in \"" << result_filename << "\"" << endl;
    return result_filename;
}


string encrypt_file_safe(string filename, string key){
    _ifstream in;
    _ofstream out;
    _char c;

    in.open(filename);
    out.open(filename.substr(0, filename.size() - 4) + " enc. " + key + ".txt");

    _string _key(key.begin(), key.end());

    int i = 0;
    int key_size = _key.size();
    while(in >> c){
        c = symbol[index[c] + index[_key[i]]];
        out << c;
        i = (i + 1) % key_size;
    }

    out.close();
    in.close();

    string result_filename = filename.substr(0, filename.size() - 4) + " enc. " + key + ".txt";
    cout << "Encryption saved in \"" << result_filename << "\"" << endl;
    return result_filename;
}

string unencrypt_file_safe(string filename, string key){
    _ifstream in;
    _ofstream out;
    _char c;

    in.open(filename);

    out.open(filename.substr(0, filename.size() - 4) + " enc. " + key + ".txt");

    _string _key(key.begin(), key.end());

    int i = 0;
    int key_size = _key.size();
    while(in >> c){
        c = symbol[index[c] - index[_key[i]]];
        out << c;
        i = (i + 1) % key_size;
    }
    out.close();
    in.close();

    string result_filename = filename.substr(0, filename.size() - 4) + " enc. " + key + ".txt";
    cout << "Encryption saved in \"" << result_filename << "\"" << endl;
    return result_filename;
}

