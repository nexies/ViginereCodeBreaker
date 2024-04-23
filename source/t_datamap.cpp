#include <sstream>
#include <vector>
#include <algorithm>
#include "t_datamap.h"
#include "string"

CodeBreaker::CodeBreaker(string p_filename)
{
    this->filename = p_filename;

    _stringstream buffer;
    _ifstream in;

    in.open(filename);
    buffer << in.rdbuf();

    this->text = buffer.str();
    in.close();

}

//PUBLIC===================================================================
void CodeBreaker::stats()
{
    count_letters();
//    count_threes();

    display_letter_frequency();
    //display_file_size();
    //display_alphabet();
    //display_key_predictions();
    //display_metrics();
}

void CodeBreaker::display_letter_frequency()
{
    letter_count display = letters;

    std::qsort(&display[0], display.size(), sizeof(char_int), compare_letters);

    for(uint a = 0; a < display.size(); a++){
        wcout << L"'" << display[a].first << L"' : " << display[a].second << endl;
    }
}

void CodeBreaker::predict_key_lenght(int upper_limit)
{
    return predict_key_lenght(1, upper_limit);
}

void CodeBreaker::predict_key_lenght(int bottom_limit, int upper_limit)
{

    float biggest_match_index = 0.05;
    int optimal_lenght = 0;
    bottom_limit = bottom_limit > 0? bottom_limit : 1;

    for(int i = bottom_limit; i < upper_limit; i++){
        float current_match_index = match_index(i);
        if(current_match_index > biggest_match_index){
            biggest_match_index = current_match_index;
            optimal_lenght = i;
        }
    }

    if(optimal_lenght != 0){
        std::cout << "Highest match index with " << optimal_lenght << " letters" << std::endl;
        key_lenght = optimal_lenght;
        return;
    }

    std::cout << "Couldn't find the key lenght for file \"" << filename << "\". \n" <<
                 "   Maybe its lenght is greater than " << upper_limit << ", or the encrypted text is not meaningful. \n" <<
                 "   Try searching with other bounds. \n   You can use find_key_lenght(int bottom_limit, int upper_limit)" << std::endl;
}

_string CodeBreaker::predict_key()
{
    if(key_lenght == 0)
        predict_key_lenght();

    _string key = _string(key_lenght, symbol[index[' ']]);

    vector<letter_count> steps = count_letters_with_step(key_lenght);

    for(int j = 0; j < key_lenght; j++){
        qsort(&steps[j][0], steps[j].size(), sizeof(char_int), compare_letters);
        _char most_popular = steps[j].front().first;
        _char key_symbol = symbol[index[most_popular] - index[' ']];
        key[j] = key_symbol;
    }

    predicted_key = shorter_key_if_possible(key);
    key_done = true;

    cout << "Predicted key: \"" << string(predicted_key.begin(), predicted_key.end()) << "\""<< endl;

    return key;
}

_string CodeBreaker::shorter_key_if_possible(_string key)
{
    int len = key.size();

    for(int i = 1; i <= len/2; i++){
        if(len % i == 0){
            bool all_same = true;
            _string left_piece = key.substr(0, i);
            for(int j = 1; j < len/i; j++){
                _string right_piece = key.substr(j*i, i);
                if(left_piece != right_piece){
                    all_same = false;
                    break;
                }
            }
            if(all_same){
                cout << "Reduced key lenght from " << len << " to " << left_piece.size() << "\n";
                _string shorter_key = left_piece;
                return shorter_key;
            }
        }
    }
    return key;
}

void CodeBreaker::unencrypt(string filename)
{
    _ofstream out;
    out.open(filename);

    if(key_done == false)
        predict_key();

    unencrypt_str(&text, predicted_key);

    out << text;
    out.close();
    cout << "Result saved in \"" << filename << "\"" << endl;
}

//PRIVATE=============================================================================
    ///analisys
void CodeBreaker::count_letters()
{
    for(int i = 0; i < int(text.size()); i += 1){
        _char c = text[i];
        letters[index[c]].second += 1;
    }
}

letter_count CodeBreaker::count_each_nth_letter(int step)
{
    letter_count out;

    for(int i = 0; i < int(text.size()); i += step){
        out[index[text[i]]].second++;
    }
    return out;
}

vector<letter_count> CodeBreaker::count_letters_with_step(int step)
{
    vector<letter_count> steps(step);
    for(int i = 0; i < int(text.size())/step; i++){
        _string piece = text.substr(i * step, step);
        for(int j = 0; j < step; j++){
            steps[j][index[piece[j]]].second++;
        }
    }
    return steps;
}

double CodeBreaker::match_index(int len)
{
    letter_count letters_with_step = count_each_nth_letter(len);

    double out = 0;

    for(uint a = 0; a < letters.size(); a++){
        out += double(letters_with_step[a].second * letters_with_step[a].second);
    }
    out /= (double(text.size())/len) * (double(text.size())/len);

    return out;
}

//OUTSIDE CLASS=======================================================================

int compare_letters(const void *p_left, const void *p_right){
    return ((*(char_int*)p_right).second - (*(char_int*)p_left).second);
}

int compare_match_index(const void *p_left, const void *p_right){
    float left = *(float*)p_left;
    float right = *(float*)p_right;
         if(left > right) return 1;
    else if(right > left) return -1;
    else                  return 0;
}

//FOR FUTHER REALISATION==============================================================

void CodeBreaker::count_threes()
{
    for(int i = 0; i < int (text.size()) - 3; i++){
        _string piece = text.substr(i, 3);
        char c = text.at(i + 3);
        threes.emplace(pair<_string, map<_char, uint>>(piece, map<_char, unsigned int>()));
        threes[piece].emplace(pair<_char, uint>(c, 0));
        threes[piece][c]++;
    }
}

double CodeBreaker::metric()
{
    return double();
}

vector<_string> CodeBreaker::predict_probable_keys()
{
    return vector<_string>();
}
