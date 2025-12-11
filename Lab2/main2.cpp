#include <iostream>
#include <string>
using namespace std;

struct Employee
{
    int ID;
    string Name;

    Employee() : ID(0), Name("") {}
    Employee(int id, const string& name) : ID(id), Name(name) {}
};

class Node
{
public:
    Employee Data;
    Node* pNext;
    Node* pPrev;

    Node() : pNext(nullptr), pPrev(nullptr) {}
    Node(const Employee& E) : Data(E), pNext(nullptr), pPrev(nullptr) {}

    ~Node() { cout << "Deleting Node with ID: " << Data.ID << endl; }
};

class SortedDLL
{
protected:
    Node* pStart;
    Node* pLast;

public:
    SortedDLL() : pStart(nullptr), pLast(nullptr) {}

    SortedDLL(const SortedDLL& other) : pStart(nullptr), pLast(nullptr)
    {
        Node* cur = other.pStart;
        while (cur)
        {
            InsertNode(new Node(cur->Data));
            cur = cur->pNext;
        }
    }

    SortedDLL& operator=(const SortedDLL& other)
    {
        if (this == &other) return *this;
        FreeList();
        Node* cur = other.pStart;
        while (cur)
        {
            InsertNode(new Node(cur->Data));
            cur = cur->pNext;
        }
        return *this;
    }

    void InsertNode(Node* pNew)
    {
        if (!pNew) return;
        pNew->pNext = pNew->pPrev = nullptr;

        if (!pStart)
        {
            pStart = pLast = pNew;
            return;
        }

        Node* cur = pStart;
        while (cur && cur->Data.ID < pNew->Data.ID)
            cur = cur->pNext;

        if (cur == pStart)
        {
            pNew->pNext = pStart;
            pStart->pPrev = pNew;
            pStart = pNew;
        }
        else if (!cur)
        {
            pLast->pNext = pNew;
            pNew->pPrev = pLast;
            pLast = pNew;
        }
        else
        {
            pNew->pNext = cur; // next of new is current
            pNew->pPrev = cur->pPrev; // prev of new is prev of current
            cur->pPrev->pNext = pNew; // next of prev of current is new
            cur->pPrev = pNew; // prev of current is new
        }
    }

    bool DeleteNode(int ID)
    {
        Node* pDel = SearchList(ID);
        if (!pDel) return false;

        if (pStart == pLast)
        {
            pStart = pLast = nullptr;
        }
        else if (pDel == pStart)
        {
            pStart = pStart->pNext;
            if (pStart) pStart->pPrev = nullptr;
        }
        else if (pDel == pLast)
        {
            pLast = pLast->pPrev;
            if (pLast) pLast->pNext = nullptr;
        }
        else
        {
            pDel->pPrev->pNext = pDel->pNext;
            pDel->pNext->pPrev = pDel->pPrev;
        }

        delete pDel;
        return true;
    }

    Node* SearchList(int ID)
    {
        Node* cur = pStart;
        while (cur)
        {
            if (cur->Data.ID == ID) return cur;
            cur = cur->pNext;
        }
        return nullptr;
    }

    bool DisplayNode(int ID)
    {
        Node* p = SearchList(ID);
        if (!p) return false;
        cout << "ID = " << p->Data.ID << endl;
        cout << "Name: " << p->Data.Name << endl;
        return true;
    }

    void DisplayALL()
    {
        Node* cur = pStart;
        cout << "-------------------------------\n";
        while (cur)
        {
            cout << "ID = " << cur->Data.ID << endl;
            cout << "Name: " << cur->Data.Name << endl;
            cout << "-------------------------------\n";
            cur = cur->pNext;
        }
    }

    int NodeNumber()
    {
        int cnt = 0;
        Node* cur = pStart;
        while (cur)
        {
            cnt++;
            cur = cur->pNext;
        }
        return cnt;
    }

    Node* operator[](int index)
    {
        if (index < 0) return nullptr;
        Node* cur = pStart;
        int i = 0;
        while (cur && i < index)
        {
            cur = cur->pNext;
            i++;
        }
        return cur;
    }

    void FreeList()
    {
        Node* cur = pStart;
        while (cur)
        {
            Node* tmp = cur;
            cur = cur->pNext;
            delete tmp;
        }
        pStart = pLast = nullptr;
    }

    ~SortedDLL()
    {
        FreeList();
    }
};

int main()
{
    SortedDLL L;
    int id;
    string name;

    for (int i = 0; i < 3; i++)
    {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        if (cin.peek() == '\n') cin.get();
        getline(cin, name);

        L.InsertNode(new Node(Employee(id, name)));
    }

    L.DisplayALL();

    cout << "Search 5:\n";
    L.DisplayNode(5);

    cout << "Delete 1\n";
    L.DeleteNode(1);
    L.DisplayALL();

    cout << "Copy Constructor Test\n";
    SortedDLL L2 = L;
    L2.DisplayALL();

    cout << "Assignment Operator Test\n";
    SortedDLL L3;
    L3 = L;
    L3.DisplayALL();

    return 0;
}
