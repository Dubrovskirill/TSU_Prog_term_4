#include<string>
#include<iostream>

#include"HashTable.h"

int main()
{
    FirstHashFunction* hash1 = new FirstHashFunction;
    SecondHashFunction* hash2 = new SecondHashFunction;
    ThirdHashFunction* hash3 = new ThirdHashFunction;
    
    HashTable<std::string> hashTable;
   
    HashTable<std::string> hashTable2(hash3,20);
    hashTable.insert(4, "apple");
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

    return 0;

	

	return 0;
}