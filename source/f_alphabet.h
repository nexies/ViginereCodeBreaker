#ifndef F_ALPHABET_H
#define F_ALPHABET_H

#include <map>

#include "unicode_ascii.h"

//typedef std::map<_char, int> index_of_a_symbol;
class index_of_a_symbol : public std::map<_char, int>{
public:
    int   operator[] (_char symbol);    // --- если символа в алфавите нет, возвращает ultimate_symbol
};

class symbol_of_an_index : public std::map<int, _char>{
public:
    _char operator[] (int index);
};

typedef std::pair<_char, int> char_int;
typedef std::pair<int, _char> int_char;

extern symbol_of_an_index symbol;       // --- хранение алфавита. Возвращает символ по его индексу
extern index_of_a_symbol index;         // --- хранение алфавита. Возвращает индекс запрошенного символа
extern int alphabet_size;               // --- хранит размер текущего алфавита (не необходимо)

extern int ultimate_symbol;             // --- заменяет собой все символы, не входящие в алфавит

/* unnecessary functions:
*    void set_alphabet(int size, wchar symbols[]);
*    void add_symbol(wchar symbol);
*/

void make_alphabet_from_text(_string text);          // --- создает алфавит по тексту (все символы, встречающиеся в тексте)
void make_alphabet_from_file(std::string filename);  // --- создает алфавит по тексту внутри файла

void set_standart_en_alphabet();        // --- символы ASCII с номерами 32-126, + '\r'
void set_short_en_alphabet();           // --- только буквы английского алфавита в нижнем рег. + пробел
void set_standart_ru_alphabet();        //undone
void set_standart_en_ru_alphabet();     //undone

void clean_alphabet();

void set_ultimate_symbol(_char symbol); // --- задает ultimate_symbol. Не выполняется, если такого символа в алфавите нет

void display_alphabet();                // --- печатает алфавит на экран

#endif // F_ALPHABET_H
