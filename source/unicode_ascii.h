#ifndef UNICODE_ASCII_H
#define UNICODE_ASCII_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


#ifdef USING_UNICODE
typedef wchar_t              _char;
typedef std::wstring         _string;
typedef std::wstringstream   _stringstream;
typedef std::wifstream       _ifstream;
typedef std::wofstream       _ofstream;
#define CHECK "Unicode"
#else
typedef char                 _char;
typedef std::string          _string;
typedef std::stringstream    _stringstream;
typedef std::ifstream        _ifstream;
typedef std::ofstream        _ofstream;
#define CHECK "ASCII"
#endif


#endif // UNICODE_ASCII_H
