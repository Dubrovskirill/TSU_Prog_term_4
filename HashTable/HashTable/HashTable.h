#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>

// interface of the hash function
class HashFunction {
public:
    virtual ~HashFunction() = default;
    virtual int hash(const int key, const int m_tableSize) const = 0;
    virtual HashFunction* clone() const = 0;
};


class FirstHashFunction : public HashFunction {
public:
    ~FirstHashFunction() override = default;

    int hash(const int key, const int m_tableSize) const override {
        int h = key % m_tableSize;
        return (h + c + d) % m_tableSize;
    }

    HashFunction* clone() const override {
        return new FirstHashFunction(*this);
    }

private:
    const int c = 0;
    const int d = 3;
};

class SecondHashFunction : public HashFunction {
public:
    ~SecondHashFunction() override = default;

    int hash(const int key, const int m_tableSize) const override {
        double a = (1 - std::sqrt(5)) / 2;
        int h = key % m_tableSize;
        return static_cast<int>(std::floor(h * a * m_tableSize)) % m_tableSize;
    }

    HashFunction* clone() const override {
        return new SecondHashFunction(*this);
    }
};

class ThirdHashFunction : public HashFunction {
public:
    ~ThirdHashFunction() override = default;

    int hash(const int key, const int m_tableSize) const override {
        int h = key % m_tableSize;
        return (h + i * (1 + key % (m_tableSize - 2))) % m_tableSize;
    }

    HashFunction* clone() const override {
        return new ThirdHashFunction(*this);
    }

private:
    const int i = 1;
};

template <typename T>
class HashTable
{
private:
    struct Node {
        int m_key;
        T m_value;
        Node* m_next;
        Node(int key, const T& value) : m_key(key), m_value(value) {}
    };

    int m_tableSize;
    std::vector<std::list<Node>> m_table;
    HashFunction* m_hashFunction;
public:

    HashTable();
    HashTable(const HashTable& other);
    HashTable(HashFunction* hashFunc, int size);
    ~HashTable();

 
    void resize(int newSize);
    void clear();
    void print() const;
    void insert(int key, const T& value);

    bool contains(const int key) const;
    HashTable& operator=(const HashTable& other);
};



template<typename T>
HashTable<T>::HashTable() 
    : HashTable(new FirstHashFunction, 10)
{}


template<typename T>
HashTable<T>::HashTable(const HashTable& other) : m_tableSize(other.m_tableSize), m_hashFunction(nullptr) {
  
    if (other.m_hashFunction) {
        m_hashFunction = other.m_hashFunction->clone();
    }

   
    m_table.clear();
    m_table.resize(m_tableSize);
    for (int i = 0; i < m_tableSize; ++i) {
        Node* current = other.m_table[i];
        while (current) {
            insert(current->key, current->value);
            current = current->next;
        }
    }
}

template <typename T>
HashTable<T>::HashTable(HashFunction* hashFunc, int size) :
    m_tableSize(size), m_hashFunction(hashFunc)
{
    m_table.clear(); 
    m_table.resize(m_tableSize);
}

template<typename T>
HashTable<T>::~HashTable() {
    clear(); 
    delete m_hashFunction;
}

template <typename T>
void HashTable<T>::resize(int newSize) {
    std::vector<std::list<Node>> newTable(newSize);

    for (int i = 0; i < m_tableSize; ++i) {
        for (auto it = m_table[i].begin(); it != m_table[i].end(); ) {
            int newIndex = m_hashFunction->hash(it->m_key, newSize);
           
            newTable[newIndex].splice(newTable[newIndex].end(), m_table[i], it++);
        }
    }

    m_tableSize = newSize;
    m_table = std::move(newTable);
}

template <typename T>
void HashTable<T>::clear() {
    for (int i = 0; i < m_tableSize; ++i) {
        
        for (auto it = m_table[i].begin(); it != m_table[i].end(); ++it) {
            delete& (*it); 
        }

        m_table[i].clear();  
    }
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable& other) {
    if (this == &other) { 
        return *this;
    }

    clear(); 
    delete m_hashFunction; 

    m_tableSize = other.m_tableSize; 

    
    if (other.m_hashFunction != nullptr) {
        m_hashFunction = other.m_hashFunction->clone();
    }
    else {
        m_hashFunction = nullptr;
    }

    m_table.resize(m_tableSize); 

   
    for (int i = 0; i < m_tableSize; ++i) {
        Node* current = other.m_table[i];
        while (current != nullptr) {
            insert(current->key, current->value); 
            current = current->next;
        }
    }

    return *this; 
}

template <typename T>
void HashTable<T>::print() const {
    for (int i = 0; i < m_tableSize; ++i) {
        std::cout << "Index " << i << ": ";

        
        for (const Node& node : m_table[i]) {
            std::cout << "(" << node.m_key << ", " << node.m_value << ") ";
        }

        std::cout << std::endl;
    }
}

template <typename T>
void HashTable<T>::insert(int key, const T& value) {
    int index = m_hashFunction->hash(key, m_tableSize); 

   
    for (Node& node : m_table[index]) {
        if (node.m_key == key) {
            node.m_value = value; 
            return;
        }
    }

    
    m_table[index].push_back(Node(key, value));
}


template <typename T>
bool HashTable<T>::contains(const int key) const {
    int index = m_hashFunction->hash(key, m_tableSize); 

   
    for (const Node& node : m_table[index]) {
        if (node.m_key == key) { 
            return true; 
        }
    }

    return false; 
}