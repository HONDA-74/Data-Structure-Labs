#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Employee
{
    int ID;
    string Name;

    Employee() : ID(0), Name("") {}
    Employee(int id, const string& name) : ID(id), Name(name) {}
};

struct Node
{
    Employee Data;
    Node* pLeft;
    Node* pRight;
    int Height;

    Node(const Employee& emp)
        : Data(emp), pLeft(nullptr), pRight(nullptr), Height(1) {}
};

class BST
{
private:

    void deleteNode(Node*& pRoot )
    {
        Node *delNode = pRoot;
        if (pRoot->pLeft == nullptr && pRoot->pRight == nullptr)
        {
            pRoot = nullptr;
            delete delNode;
            rebalance(pRoot);
        }
        else if (pRoot->pLeft == nullptr)
        {
            pRoot = pRoot->pRight;
            delete delNode;
            rebalance(pRoot);
        }
        else if (pRoot->pRight == nullptr)
        {
            pRoot = pRoot->pLeft;
            delete delNode;
            rebalance(pRoot);
        }
        else
        {
            Node* max = getMax(pRoot->pLeft);
            pRoot->Data = max->Data;
            Delete(pRoot->pLeft, max->Data.ID);
            rebalance(pRoot);
        }
    }

    Node* getMax(Node* pRoot)
    {
        Node* current = pRoot;
        while (current->pRight != nullptr)
        {
            current = current->pRight;
        }
        return current;
    }

    void rotateLeft(Node*& pRoot)
    {
        Node* newRoot = pRoot->pRight;
        pRoot->pRight = newRoot->pLeft;
        newRoot->pLeft = pRoot;

        // Update heights
        pRoot->Height = 1 + max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));
        newRoot->Height = 1 + max(getHeight(newRoot->pLeft), getHeight(newRoot->pRight));

        pRoot = newRoot;
    }

    void rotateRight(Node*& pRoot)
    {
        Node* newRoot = pRoot->pLeft;
        pRoot->pLeft = newRoot->pRight;
        newRoot->pRight = pRoot;

        // Update heights
        pRoot->Height = 1 + max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));
        newRoot->Height = 1 + max(getHeight(newRoot->pLeft), getHeight(newRoot->pRight));

        pRoot = newRoot;
    }

    int getHeight(Node* pNode)
    {
        return pNode ? pNode->Height : 0;
    }

    int getBalanceFactor(Node* pNode)
    {
        if (!pNode)
            return 0;
        return getHeight(pNode->pLeft) - getHeight(pNode->pRight);
    }

    void rebalance(Node*& pRoot)
    {
        int balanceFactor = getBalanceFactor(pRoot);
        if (balanceFactor > 1)
        {
            if (getBalanceFactor(pRoot->pLeft) < 0)
            {
                rotateLeft(pRoot->pLeft);
            }
            rotateRight(pRoot);
            cout << "rebalance" << endl;
        }
        else if (balanceFactor < -1)
        {
            if (getBalanceFactor(pRoot->pRight) > 0)
            {
                rotateRight(pRoot->pRight);
            }
            rotateLeft(pRoot);
            cout << "rebalance" << endl;
        }
    }

    void FreeTree(Node* pNode) {
    if (!pNode) return;
    FreeTree(pNode->pLeft);
    FreeTree(pNode->pRight);
    cout << "Node with ID " << pNode->Data.ID << " deleted." << endl;
    delete pNode;
    }

public:
    Node* pRoot;

    BST() : pRoot(nullptr) {}

    ~BST() {
        FreeTree(pRoot);
    }

    void insertNode(Node*& pRoot, Node* pNew)
    {
        if (!pRoot)
        {
            pRoot = pNew ;
            return;
        }

        if (pNew->Data.ID < pRoot->Data.ID)
            insertNode(pRoot->pLeft, pNew);
        else if (pNew->Data.ID > pRoot->Data.ID)
            insertNode(pRoot->pRight, pNew);
        else
        {
            cout<< "Duplicate ID not allowed: " << pNew->Data.ID << endl;
            return;
        }

        pRoot->Height = 1 + max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));

        rebalance(pRoot);
    }

    void insertNode(Node* pRoot , Node* pLeaf , Node* pNew)
    {
        if (pLeaf == nullptr)
        {
            if(pRoot != nullptr)
            {
            if (pNew->Data.ID < pRoot->Data.ID)
                pRoot->pLeft = pNew;
            else if (pNew->Data.ID > pRoot->Data.ID)
                pRoot->pRight = pNew;
            else{
                cout<< "Duplicate ID not allowed: " << pNew->Data.ID << endl;
                return;
                }
            }
            else pRoot = pNew;
        }
        else if (pNew->Data.ID < pLeaf->Data.ID)
            insertNode(pLeaf, pLeaf->pLeft, pNew);
        else if (pNew->Data.ID > pLeaf->Data.ID)
            insertNode(pLeaf, pLeaf->pRight, pNew);
        else
            {
            cout<< "Duplicate ID not allowed: " << pNew->Data.ID << endl;
            return;
            }

        pLeaf->Height = 1 + max(getHeight(pLeaf->pLeft), getHeight(pLeaf->pRight));

        rebalance(pRoot);
    }

    void Delete(Node*& pRoot, int ID){
    if(!pRoot) return;

    if(ID < pRoot->Data.ID)
        Delete(pRoot->pLeft, ID);
    else if(ID > pRoot->Data.ID)
        Delete(pRoot->pRight, ID);
    else{
        deleteNode(pRoot);
    }

    if(pRoot)
        pRoot->Height = 1 + max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));
}

    Node* searchNode(Node* pRoot, int ID)
    {
        if (!pRoot || pRoot->Data.ID == ID)
            return pRoot;

        if (ID < pRoot->Data.ID)
            return searchNode(pRoot->pLeft, ID);
        else
            return searchNode(pRoot->pRight, ID);

    }

    void traverseTree(Node* pRoot)
    {
        if (pRoot)
        {
            traverseTree(pRoot->pLeft);
            cout << "ID: " << pRoot->Data.ID << ", Name: " << pRoot->Data.Name << endl;
            traverseTree(pRoot->pRight);
        }
    }

    int countNodes(Node* pRoot)
    {
        if (!pRoot)
            return 0;
        return 1 + countNodes(pRoot->pLeft) + countNodes(pRoot->pRight);
    }

    int CountLevels(Node* pRoot)
    {
        if (!pRoot)
            return 0;
        return 1 + max(CountLevels(pRoot->pLeft), CountLevels(pRoot->pRight));
    }

};

int main()
{
    BST T;

    T.insertNode(T.pRoot, new Node(Employee(8, "John Doe")));
    T.insertNode(T.pRoot, new Node(Employee(5, "Jane Doe")));
    T.insertNode(T.pRoot, new Node(Employee(12, "Bob Smith")));
    T.insertNode(T.pRoot, new Node(Employee(3, "Alice Johnson")));
    T.insertNode(T.pRoot, new Node(Employee(7, "Charlie Brown")));
    T.insertNode(T.pRoot, new Node(Employee(10, "Diana Prince")));
    T.insertNode(T.pRoot , new Node(Employee(2 , "AL;D")));
    T.insertNode(T.pRoot , new Node(Employee(1 , "kasjiod")));




    T.traverseTree(T.pRoot);

    cout << "==============================\n";
    T.Delete(T.pRoot, 3);
    cout << "\nAfter deletion:\n";
    T.traverseTree(T.pRoot);

    cout << "==============================\n";
    cout << "\nSearching for employee with ID 4:\n";
    Node* found = T.searchNode(T.pRoot, 4);
    if (found)
        cout << "Found employee with ID 4: " << found->Data.Name << endl;
    else
        cout << "Employee with ID 4 not found." << endl;

    cout << "==============================\n";
    cout << "\nNumber of nodes: " << T.countNodes(T.pRoot) << endl;
    cout << "Number of levels: " << T.CountLevels(T.pRoot) << endl;

    cout << "==============================\n";

    return 0;
}
