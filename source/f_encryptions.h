#ifndef G_H
#define G_H

#include "f_alphabet.h"
#include "unicode_ascii.h"

_string encrypt_str(_string str, _string key);
_string unencrypt_str(_string str, _string key);

void    encrypt_str(_string *str, _string key);
void    unencrypt_str(_string *str, _string key);

std::string encrypt_file(std::string filename, std::string key);
std::string unencrypt_file(std::string filename, std::string key);

std::string encrypt_file_safe(std::string filename, std::string key);
std::string unencrypt_file_safe(std::string filename, std::string key);




#endif // G_H
