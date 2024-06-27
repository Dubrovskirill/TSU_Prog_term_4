#include<string>
#include<iostream>

#include"HashTable.h"

int main() {

    FirstHashFunction first;
    ThirdHashFunction third;
    HashTable<std::string> foo(&third, 10);
    foo.print();
    foo.insert(1, "1");
    foo.insert(1, "2");
    foo.insert(1, "3");
    foo.insert(21, "1");
    foo.insert(31, "1");
    foo.insert(41, "1");
    foo.insert(61, "1");
    foo.insert(16, "1");
    foo.insert(12, "1");
    foo.insert(211, "1");
    foo.insert(111, "1");
    foo.insert(1231, "1");
    foo.insert(1241231, "1");
    foo.insert(121231, "1");

    foo.print();

    foo.resize(200);
    foo.print();

    foo.setHashFunction(nullptr);
    foo.print();

    foo.setHashFunction(&first);
    foo.print();

    foo.resize(2);
    foo.insert(323, "23");
    foo.erase(11);
    for (int i = 0; i < 200; ++i) {
        foo.erase(i);
    }


    foo.resize(1);
    foo.erase(1);
    foo.insert(1, "1");
    foo.print();

    return -1;
    FirstHashFunction* hash1 = new FirstHashFunction;
    SecondHashFunction* hash2 = new SecondHashFunction;
    ThirdHashFunction* hash3 = new ThirdHashFunction;

    HashTable<std::string> hashTable(hash2,10);

    HashTable<std::string> hashTable2(hash2, 20);
    hashTable.insert(15, "apple");
    hashTable.insert(20, "banana");
    hashTable.insert(30, "cherry");
    hashTable.insert(20, "grape"); // Попробуем вставить дубликат по ключу 20


    std::cout << "HashTable after insertions:" << std::endl;
    hashTable.print();

    // Проверяем наличие элементов
    std::cout << "Contains key 20: " << (hashTable.contains(20) ? "true" : "false") << std::endl;
    std::cout << "Contains key 40: " << (hashTable.contains(40) ? "true" : "false") << std::endl;

    // Изменяем размер таблицы
    hashTable.resize(20);
    std::cout << "\nHashTable after resizing to 20:" << std::endl;
    hashTable.print();

    // Очищаем таблицу
    hashTable.clear();
    std::cout << "\nHashTable after clearing:" << std::endl;
    hashTable.print();

    // Вставляем элементы
    hashTable.insert(15, "orange");
    hashTable.insert(25, "mango");
    hashTable.insert(5, "grapefruit");

    // Выводим таблицу
    std::cout << "\nHashTable after inserting elements:" << std::endl;
    hashTable.print();

    // Удаляем элемент
    if (hashTable.erase(25)) {
        std::cout << "\nElement with key 25 deleted" << std::endl;
    }
    else {
        std::cout << "\nElement with key 25 not found" << std::endl;
    }

    // Выводим таблицу
    std::cout << "\nHashTable after deleting element with key 25:" << std::endl;
    hashTable.print();

    // Доступ и изменение значений с помощью оператора []
    hashTable[15] = "pineapple";  // Изменяем значение
    std::cout << "\nValue for key 15: " << hashTable[15] << std::endl;

    // Попытка доступа к несуществующему ключу (добавит новую запись)
    //std::cout << "\nValue for key 100: " << hashTable[100] << std::endl;

    // Выводим таблицу
    std::cout << "\nFinal HashTable:" << std::endl;
    hashTable.print();

    // Замена хеш-функции
    hashTable.setHashFunction(hash3);
    std::cout << "\nHashTable after changing hash function:" << std::endl;
    hashTable.print();

    return 0;
}