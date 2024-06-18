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

    void print() const;
    void insert(int key, const T& value);
    void resize(int newSize);
    void clear();
    void setHashFunction(HashFunction* newHashFunction);

    bool contains(const int key) const;
    bool erase(int key);

    HashTable& operator=(const HashTable& other);
    T& operator[](int key);
};



template <typename T>
HashTable<T>::HashTable() : m_tableSize(10), m_table(10), m_hashFunction(new FirstHashFunction()) {}

template <typename T>
HashTable<T>::HashTable(const HashTable& other) : m_tableSize(other.m_tableSize), m_table(other.m_table), m_hashFunction(other.m_hashFunction->clone()) {}

template <typename T>
HashTable<T>::HashTable(HashFunction* hashFunc, int size) : m_tableSize(size), m_table(size), m_hashFunction(hashFunc->clone()) {}

template <typename T>
HashTable<T>::~HashTable() {
    delete m_hashFunction;
}

template <typename T>
void HashTable<T>::print() const {
    for (int i = 0; i < m_tableSize; ++i) {
        std::cout << i << ": ";
        for (const auto& node : m_table[i]) {
            std::cout << "(" << node.m_key << ", " << node.m_value << ") ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void HashTable<T>::insert(int key, const T& value) {
    if (contains(key)) {
        std::cerr << "Error: Key " << key << " already exists in the table." << std::endl;
        return;
    }

    int index = m_hashFunction->hash(key, m_tableSize);
    m_table[index].push_back(Node(key, value));
}

template <typename T>
bool HashTable<T>::contains(const int key) const {
    int index = m_hashFunction->hash(key, m_tableSize);
    for (const auto& node : m_table[index]) {
        if (node.m_key == key) {
            return true;
        }
    }
    return false;
}

template <typename T>
void HashTable<T>::resize(int newSize) {
    std::vector<std::list<Node>> newTable(newSize);
    for (const auto& list : m_table) {
        for (const auto& node : list) {
            int index = m_hashFunction->hash(node.m_key, newSize);
            newTable[index].push_back(node);
        }
    }
    m_table = std::move(newTable);
    m_tableSize = newSize;
}

template <typename T>
void HashTable<T>::clear() {
    for (auto& list : m_table) {
        list.clear();
    }
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable& other) {
    if (this != &other) {
        delete m_hashFunction;
        m_tableSize = other.m_tableSize;
        m_table = other.m_table;
        m_hashFunction = other.m_hashFunction->clone();
    }
    return *this;
}

template <typename T>
bool HashTable<T>::erase(int key) {
    int index = m_hashFunction->hash(key, m_tableSize);

    for (auto it = m_table[index].begin(); it != m_table[index].end(); ++it) {
        if (it->m_key == key) {
            m_table[index].erase(it);
            return true;
        }
    }
    return false;
}

template <typename T>
T& HashTable<T>::operator[](int key) {
    int index = m_hashFunction->hash(key, m_tableSize);

    for (auto& node : m_table[index]) {
        if (node.m_key == key) {
            return node.m_value;
        }
    }

    
    insert(key, T{});


    return m_table[index].back().m_value;
}

template <typename T>
void HashTable<T>::setHashFunction(HashFunction* newHashFunction) {
    
    auto oldTable = m_table;
    int oldSize = m_tableSize;

    
    delete m_hashFunction;  
    m_hashFunction = newHashFunction->clone();
    m_table.clear();
    m_tableSize = oldSize;  
    m_table.resize(m_tableSize); 

    
    for (const auto& list : oldTable) {
        for (const auto& node : list) {
            insert(node.m_key, node.m_value);
        }
    }
}