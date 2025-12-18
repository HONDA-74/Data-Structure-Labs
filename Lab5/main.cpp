#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <queue>
#include <stdexcept>

using namespace std;

struct Employee
{
    int id;
    string name;
    string department;
    double salary;

    Employee() {}

    Employee(int _id, string _name, string _dept, double _salary)
    {
        id = _id;
        name = _name;
        department = _dept;
        salary = _salary;
    }
};

template<class KeyType, class ValueType>
class MapEntry
{
    KeyType key;
    ValueType value;

public:
    MapEntry(KeyType k, ValueType v) : key(k), value(v) {}

    KeyType GetKey() const { return key; }
    ValueType GetValue() const { return value; }
};


template<class KeyType, class ValueType>
class HashTable
{
    vector<list<MapEntry<KeyType, ValueType>>> theLists;
    int currentSize;

public:
    explicit HashTable(int size = 100) : theLists(size), currentSize(0) {}

    bool Contains(const KeyType& x) const
    {
        int index = MyHashFunction(x);
        const auto& bucket = theLists[index];

        for (const auto& entry : bucket)
        {
            if (entry.GetKey() == x)
                return true;
        }
        return false;
    }

    bool Insert(const KeyType& key, const ValueType& value)
    {
        if (Contains(key)) return false;

        int index = MyHashFunction(key);
        theLists[index].push_back(MapEntry<KeyType, ValueType>(key, value));
        currentSize++;

        return true;
    }

    bool Remove(const KeyType& key)
    {
        int index = MyHashFunction(key);
        auto& bucket = theLists[index];

        for (auto itr = bucket.begin(); itr != bucket.end(); ++itr)
        {
            if (itr->GetKey() == key)
            {
                bucket.erase(itr);
                currentSize--;
                return true;
            }
        }
        return false;
    }

    ValueType LookUP(const KeyType& key) const
    {
        int index = MyHashFunction(key);
        const auto& bucket = theLists[index];

        for (const auto& entry : bucket)
        {
            if (entry.GetKey() == key)
                return entry.GetValue();
        }

        throw runtime_error("Key not found");
    }

    void MakeEmpty()
    {
        for (auto& lst : theLists)
            lst.clear();

        currentSize = 0;
    }

    void Rehash()
    {
    vector<list<MapEntry<KeyType, ValueType>>> oldLists = theLists;

    theLists.clear();
    theLists.resize(oldLists.size() * 2);

    currentSize = 0;

    for (auto& bucket : oldLists)
    {
        for (auto& entry : bucket)
        {
            Insert(entry.GetKey(), entry.GetValue());
        }
    }

    }

protected:
    int MyHashFunction(const KeyType& x) const
    {
        hash<KeyType> hashFunc;
        return hashFunc(x) % theLists.size();
    }
};

int main()
{
    HashTable<int, Employee> table;

    Employee emp1(1, "Ahmed", "IT", 5000);
    Employee emp2(2, "Mohamed", "HR", 6000);
    Employee emp3(3, "Ali", "Finance", 5500);
    Employee emp4(101, "Sara", "IT", 6200);

    table.Insert(1, emp1);
    table.Insert(2, emp2);
    table.Insert(3, emp3);
    table.Insert(101, emp4);
    table.Insert(2, emp2) ? cout << "Inserted\n" : cout << "Not Inserted\n";

    table.Contains(101) ? cout << "Found\n" : cout << "Not Found\n";

    Employee e = table.LookUP(2);

    cout << e.id << " "
         << e.name << " "
         << e.department << " "
         << e.salary << endl;

    table.Remove(1);

    return 0;
}
