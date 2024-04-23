//IN FILE unicode_ascii.h use
//#define USING_UNICODE
//to switch from ASCII to UTF-8

//#define USING_UNICODE

#include "unicode_ascii.h"
#include "t_datamap.h"
#include "interface.h"

using namespace std;

// ПЛАН ДЕЙСТВИЙ
/*
 * 1. Научиться находить длину ключа     //done
 * 2. Высчитывать ключ посимвольно, основываясь на том, что пробел - самый популярный символ //done
 * 3. Режимы работы в UTF-8 и ASCII.     //done
 *
 * Для дальнейшей реализации:
 * 1. Ввести поддержку русского и англо-русского алфавита
 * 2. Натренировать DataMap на бОльшем количестве тескта и научиться записывать DataMap в файл для хранения (для каждого алфавита отдельно)
 * 3. Научиться предсказывать возможные значения ключа используя DataMap и переберать их
 * 4. Научиться считать метрику
 * 5. Переберая возможные ключи, выводить результаты с наибольшим значением по метрике
 *
 *
*/

int main()
{
//    start_interface();  // не завершено

    cout << "Using " << CHECK << endl;
    set_standart_en_alphabet();

    string Sherlock_Holmes = "../Books/Sherlock Holmes.txt";
    string The_Hobbit = "../Books/The Hobbit.txt";
    string Moby_Dick = "../Books/Moby Dick Or The Whale.txt";
    string War_and_Peace = "../Books/War and Peace.txt";

    War_and_Peace = encrypt_file(War_and_Peace, "some very very long phrase to be a good key");         // Применение шифра Виженера
//    unencrypt_file(War_and_Peace, "Should work");                       // Применение обратного шифра Виженера

//    Sherlock_Holmes = encrypt_file(Sherlock_Holmes, "something different");
//    unencrypt_file(Sherlock_Holmes, "something different");

    CodeBreaker cdbrk(War_and_Peace);
//    CodeBreaker sherlock(Sherlock_Holmes);

//    cdbrk.stats();
//    cdbrk.predict_key_lenght();
//    cdbrk.key_lenght = 14;
//    cdbrk.predict_key();

    cdbrk.unencrypt("../CodeBreaker Results/WP auto.txt");
//    sherlock.unencrypt("../CodeBreaker Results/Sherlock Holmes auto.txt");

    return 0;
}


//TRASH=================================================================================


/*
    DataMap map("../Vigenere/texts/Sherlock Holmes Edited.txt");
    map.stats_from_file();

    vector<letter_count> sorted;
    for(letter_count a: map.letters){
        sorted.push_back(a);
    }

    qsort(sorted.data(), sorted.size(), sizeof(letter_count), compare_letters);
    for(int i = 0; i < int(sorted.size()); i++){
        cout << "'" << sorted[i].first << "' : " << sorted[i].second << endl;
    }
*/

/*
    ifstream in;
    in.open("texts/Sherlock Holmes.txt");
    stringstream buffer;
    buffer << in.rdbuf();
    in.close();

    string str = buffer.str();
//    for(index_symbol a: symbol)
//        str += a.second;
    cout << str << endl << "==============================================" << endl;
    string enc = encrypt_str(str, "some random shit about ponies");
    cout << enc << endl << "==============================================" << endl;

    string unc = unencrypt_str(enc, "some random shit about ponies");
    cout << unc;
    */
