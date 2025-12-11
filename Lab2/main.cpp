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

    Node() : Data(), pNext(nullptr), pPrev(nullptr) {}
    Node(const Employee& E) : Data(E), pNext(nullptr), pPrev(nullptr) {}

    ~Node() {  cout << "Deleting Node with ID: " << Data.ID << endl;  }
};

class DLL
{
protected:
    Node* pStart;
    Node* pLast;

public:
    DLL() : pStart(nullptr), pLast(nullptr) {}
    DLL(const DLL& other) : pStart(nullptr), pLast(nullptr)
    {
        Node* cur = other.pStart;
        while (cur)
        {
            Node* pNew = new Node(cur->Data);
            AddNode(pNew);
            cur = cur->pNext;
        }
    }

    DLL& operator=(const DLL& other)
    {
        if (this == &other) return *this;
        FreeList();
        Node* cur = other.pStart;
        while (cur)
        {
            Node* pNew = new Node(cur->Data);
            AddNode(pNew);
            cur = cur->pNext;
        }
        return *this;
    }

    virtual void AddNode(Node* pNew)
    {
        if (pNew == nullptr) return;
        pNew->pNext = pNew->pPrev = nullptr;

        if (pStart == nullptr)
        {
            pStart = pLast = pNew;
        }
        else
        {
            pLast->pNext = pNew;
            pNew->pPrev = pLast;
            pLast = pNew;
        }
    }

    virtual bool DeleteNode(int ID)
    {
        Node* pDel = SearchList(ID);
        if (pDel == nullptr) return false;

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

    virtual Node* SearchList(int ID)
    {
        Node* cur = pStart;
        while (cur != nullptr)
        {
            if (cur->Data.ID == ID) return cur;
            cur = cur->pNext;
        }
        return nullptr;
    }

    virtual bool DisplayNode(int ID)
    {
        Node* p = SearchList(ID);
        if (p == nullptr) return false;
        cout << "ID = " << p->Data.ID << endl;
        cout << "Name: " << p->Data.Name << endl;
        return true;
    }

    virtual void DisplayALL()
    {
        Node* cur = pStart;
        cout << "-------------------------------\n";
        while (cur != nullptr)
        {
            cout << "ID = " << cur->Data.ID << endl;
            cout << "Name: " << cur->Data.Name << endl;
            cout << "-------------------------------\n";
            cur = cur->pNext;
        }
    }

    virtual int NodeNumber()
    {
        int cnt = 0;
        Node* cur = pStart;
        while (cur != nullptr)
        {
            cnt++;
            cur = cur->pNext;
        }
        return cnt;
    }

    virtual Node* operator[](int index) 
    {
        if (index < 0) return nullptr;
        Node* cur = pStart;
        int i = 1;
        while (cur != nullptr && i < index)
        {
            cur = cur->pNext;
            i++;
        }
        return cur;
    }

    virtual void FreeList()
    {
        Node* cur = pStart;
        while (cur != nullptr)
        {
            Node* tmp = cur;
            cur = cur->pNext;
            delete tmp;
        }
        pStart = pLast = nullptr;
    }

    virtual ~DLL()
    {
        FreeList();
    }
};

class StackDLL : public DLL
{
public:
    void Push(Node* pNew)
    {
        if (!pNew) return;
        pNew->pNext = pStart;
        pNew->pPrev = nullptr;
        if (pStart) pStart->pPrev = pNew;
        pStart = pNew;
        if (!pLast) pLast = pNew;
    }

    Node* Pop()
    {
        if (!pStart) return nullptr;
        Node* temp = pStart;
        pStart = pStart->pNext;
        if (pStart) pStart->pPrev = nullptr;
        else pLast = nullptr;
        temp->pNext = nullptr;
        temp->pPrev = nullptr;
        return temp;
    }

    Node* Peek()
    {
        DisplayNode(0);
        return pStart;
    }
};

class QueueDLL : public DLL
{
public:
    void EnQ(Node* pNew)
    {
        AddNode(pNew);
    }

    Node* DeQ()
    {
        if (!pStart) return nullptr;
        Node* temp = pStart;
        pStart = pStart->pNext;
        if (pStart) pStart->pPrev = nullptr;
        else pLast = nullptr;
        temp->pNext = nullptr;
        temp->pPrev = nullptr;
        return temp;
    }

    Node* Peek()
    {
        return pStart;
    }
};

int main() {
    DLL L;
    int id;
    string name;

    for(int i =0 ; i<3 ; i++) {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.get();
        getline(cin, name);
        L.AddNode(new Node(Employee(id, name)));
    }

    L.DisplayALL();

    cout << "Search 5:\n";
    L.DisplayNode(5);

    cout << "Delete 1\n";
    L.DeleteNode(1);
    L.DisplayALL();

    cout << "Copy Constructor Test\n";
    DLL L2 = L;
    L2.DisplayALL();

    cout << "Assignment Operator Test\n";
    DLL L3;
    L3 = L;
    L3.DisplayALL();

    StackDLL S;
    S.Push(new Node(Employee(1,"A")));
    S.Push(new Node(Employee(2,"B")));
    S.Push(new Node(Employee(3,"C")));

    cout << "Stack Display Top to Bottom:\n";
    S.DisplayALL();

    Node* p = S.Pop();
    cout << "Popped: " << p->Data.ID << " - " << p->Data.Name << endl;
    delete p;

    cout << "Stack After Pop:\n";
    S.DisplayALL();

    S.Peek();

    QueueDLL Q;
    Q.EnQ(new Node(Employee(10,"X")));
    Q.EnQ(new Node(Employee(20,"Y")));
    Q.EnQ(new Node(Employee(30,"Z")));

    cout << "Queue Display Front to Back:\n";
    Q.DisplayALL();

    Node* q = Q.DeQ();
    cout << "Dequeued: " << q->Data.ID << " - " << q->Data.Name << endl;
    delete q;

    cout << "Queue After DeQ:\n";
    Q.DisplayALL();


    return 0;
}
