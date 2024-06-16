#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

// interface of the hash function
class HashFunction {
public:
    virtual ~HashFunction() = default;
    virtual int hash(const int key, const int tableSize) const = 0;
    virtual HashFunction* clone() const = 0;
};


class FirstHashFunction : public HashFunction {
public:
    ~FirstHashFunction() override = default;

    int hash(const int key, const int tableSize) const override {
        int h = key % tableSize;
        return (h + c + d) % tableSize;
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

    int hash(const int key, const int tableSize) const override {
        double a = (1 - std::sqrt(5)) / 2;
        int h = key % tableSize;
        return static_cast<int>(std::floor(h * a * tableSize)) % tableSize;
    }

    HashFunction* clone() const override {
        return new SecondHashFunction(*this);
    }
};

class ThirdHashFunction : public HashFunction {
public:
    ~ThirdHashFunction() override = default;

    int hash(const int key, const int tableSize) const override {
        int h = key % tableSize;
        return (h + i * (1 + key % (tableSize - 2))) % tableSize;
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
        int key;
        T value;
        Node(int key, const T& value) : key(key), value(value) {}
    };

    int tableSize;
    std::vector<std::list<Node>> table;
    HashFunction* hashFunction;



};

