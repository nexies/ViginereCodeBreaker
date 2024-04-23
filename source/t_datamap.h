#ifndef DATAMAP_H
#define DATAMAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "f_alphabet.h"
#include "f_encryptions.h"
#include "unicode_ascii.h"


using namespace std;

typedef unsigned int uint;

class letter_count : public vector<char_int>{
public:
    letter_count() : vector<char_int>(alphabet_size)
    {
        for(int i = 0; i < int(this->size()); i++)
            (*this)[i].first = symbol[i];
    }
};


class CodeBreaker
{
    // Constructors:
public:
    CodeBreaker(){};
    CodeBreaker(std::string filename);

    // Fields:
public:
    std::string filename;

    _string text;
    map<_string, map<_char, uint>> threes;
    letter_count letters;


    map<int, float> possible_key_lenghts;
    int key_lenght = 0;

    bool key_done = false;
    _string predicted_key;

    // Functions:
public:

    void stats();  // Надо что-то выводить
    void display_letter_frequency();

    ///predictions
    void    predict_key_lenght(int bottom_limit, int upper_limit);
    void    predict_key_lenght(int upper_limit = 100);
    _string predict_key();
    _string shorter_key_if_possible(_string key);

    ///processing
    void    unencrypt(std::string filename);

private:
    ///analisys
    void count_letters();
    letter_count count_each_nth_letter(int n);
    vector<letter_count> count_letters_with_step(int step);

    double match_index(int len);

private: // For futher realisation
    vector<_string> predict_probable_keys();   // Расчет n наиболее вероятных значений ключа

    void count_threes();  // Расчет вероятности появления символов тройками, а не одиночными символами
    double metric();      // Расчет похожести получившейся в результате работы дешифратора строки на осысленный текст
};

    // Outside class methods:
int     compare_letters(const void *p_left, const void *p_right);      // для работы qsort с letter_count
int compare_match_index(const void *p_left, const void *p_right);  // для работы qsort с predict_key_lenght

#endif // DATAMAP_H
