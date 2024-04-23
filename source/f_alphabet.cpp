#include "f_alphabet.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

symbol_of_an_index symbol;
index_of_a_symbol index;
int alphabet_size;

int ultimate_symbol = -1;

string where_alphabet_from = "Alphabet is empty";

_char symbol_of_an_index::operator[](int p_index)
{
    p_index = p_index % int(this->size());
    return p_index >= 0? (*this).at(p_index) : (*this).at(p_index + int(this->size()));
}

int index_of_a_symbol::operator[](_char p_symbol)
{
    if(this->find(p_symbol) == this->end())
        return this->at(symbol[ultimate_symbol]);

    return map<_char, int>::operator[](p_symbol);
}


void set_standart_en_alphabet()
{
    clean_alphabet();
    where_alphabet_from = "Standart English alphabet: \n";
    for(int i = 32; i < 126; i++){
        index.emplace(char_int(_char(i), i - 32));
        symbol.emplace(int_char(i - 32, _char(i)));
    }
    index.emplace('\n', 94);
    symbol.emplace(94, '\n');
    index.emplace('\r', 95);
    symbol.emplace(95, '\r');
    alphabet_size = 96;

    ultimate_symbol = index[' '];
}

void make_alphabet_from_text(_string text)
{
    clean_alphabet();
    map<_char, int> middle_map;
    for(int i = 0; i < int(text.size()); i++){
        middle_map.emplace(pair<_char, int>(text[i], 0));
    }

    int i = 0;
    for(pair<const _char, const int> a: middle_map){
        index.emplace(char_int(a.first, i));
        symbol.emplace(int_char(i, a.first));
        i++;
    }
    where_alphabet_from = "Custom alphabet\n";
    alphabet_size = i;
}

void make_alphabet_from_file(string filename)
{
    clean_alphabet();
    _ifstream in;
    in.open(filename);
    _stringstream buffer;
    buffer << in.rdbuf();

    make_alphabet_from_text(buffer.str());
    where_alphabet_from = "Alphabet made from text in file \"" + string(filename.begin(), filename.end()) + ".txt\" \n";
}

void display_alphabet()
{
    cout << where_alphabet_from;
    for(int_char a: symbol){
        wcout << a.first << L" : '" << a.second << L"' " << endl;
    }
    cout << endl;

    if(ultimate_symbol == -1){cout << "Ultimate symbol is not set\n"; return;}

    wcout << L"Ultimate symbol is '" << symbol[ultimate_symbol] << L"'. " << endl;
}

void set_short_en_alphabet()
{
    clean_alphabet();
    where_alphabet_from = "Short English alphabet: \n";
    for(int i = 97; i < 123; i++){
        index.emplace(char_int(_char(i), i - 97));
        symbol.emplace(int_char(i - 97, _char(i)));
    }
    index.emplace(' ', 26);
    symbol.emplace(26, ' ');
    alphabet_size = 27;
    ultimate_symbol = index[' '];
}



void set_ultimate_symbol(_char p_symbol)
{
    if(index.find(p_symbol) == index.end()){
        cout << "Ultimate symbol failure: Symbol isn't contained in the alphabet \n";
        return;
    }
    ultimate_symbol = index[p_symbol];
}

void clean_alphabet()
{
    index.clear();
    symbol.clear();
    alphabet_size = 0;
    ultimate_symbol = -1;
    where_alphabet_from = "Alphabet is empty";
}
