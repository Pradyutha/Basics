#include <iostream>
#include <queue>
#include <vector>

struct Node
{
    int Data;
    int Height;
    Node* Left;
    Node* Right;
    Node(int data)
    {
        Data = data;
        Height = 0;
        Left = Right = NULL;
    }
};

class AVLTree
{
  public:

    AVLTree();

    ~AVLTree();

    bool Insert(int data);

    bool Delete(int data);

    void PrintInOrder();

    void PrintLevelOrder();
    
    void PrintLevelOrder(Node* Root);

    int GetHeight(Node* Root); 

  private: 

    Node* InsertNode(Node* Root, int data);

    Node* DeleteNode(Node* Root, int data);

    

    int GetBalance(Node* Root);

    void PrintInOrder(Node* Root);

    void PrintPreOrder(Node* Root);

    void PrintPostOrder(Node* Root);

    Node* RotateRight(Node* Root);

    Node* RotateLeft(Node* Root);

    Node* BalanceTree(Node* Root);

    Node* mRoot;


}; // class AVL Tree

// Recursive for understanding
void AVLTree::PrintInOrder(Node *Root)
{
    if(Root == NULL)
    {
        return;
    }

    PrintInOrder(Root->Left);
    std::cout << " " << Root->Data << std::endl;
    PrintInOrder(Root->Right);
    

} // PrintInOrder

void AVLTree::PrintLevelOrder(Node* Root)
{
    if(Root == NULL)
    {
        return;
    }

    std::vector< std::vector<int> > Matrix;
    Matrix.resize(Root->Height);

    std::queue< Node* > Q;

    Q.push(Root); // Push Root; Push_back if list

    while(!Q.empty())
    {
        Node* temp = Q.front();
        Q.pop();

        std::cout << " " << temp->Data <<  " H : " << temp->Height << std::endl;
        //Matrix.at(temp->Height).push_back(temp->Data);

        if(temp->Left)
          Q.push(temp->Left);

        if(temp->Right)
          Q.push(temp->Right);
    }
} // PrintLevelOrder

void AVLTree::PrintLevelOrder()
{
    PrintLevelOrder(mRoot);
} // PrintLevelOrder

void AVLTree::PrintInOrder()
{
    PrintInOrder(mRoot);
}

AVLTree::AVLTree()
{
    mRoot = NULL;
} // Ctor

bool AVLTree::Insert(int data)
{
    mRoot = InsertNode(mRoot, data);
    return true;
}

int AVLTree::GetHeight(Node* Root)
{
    if(Root == NULL)
        return 0;

    int height_left = GetHeight(Root->Left);
    int height_right = GetHeight(Root->Right);

    return (1 + (height_left > height_right ? height_left : height_right));
} // GetHeight

int AVLTree::GetBalance(Node* Root)
{
    if(Root == NULL)
        return 0;

    return (GetHeight(Root->Left) - GetHeight(Root->Right));

} // GetBalance

Node* AVLTree::InsertNode(Node* Root, int data)
{
    if(Root == NULL)
    {
        Node* temp = new Node(data);
        Root = temp;
    }

    if(data < Root->Data)
    {
        Root->Left = InsertNode(Root->Left, data);
    }
    else if(data > Root->Data)
    {
        Root->Right = InsertNode(Root->Right, data);
    }

    Root->Height = GetHeight(Root);
    //std::cout << "Height " << Root->Height << std::endl;
    Root = BalanceTree(Root);
    return Root;
} // InsertNode

Node* AVLTree::RotateRight(Node* Y)
{
    Node* X = Y->Left;
    Node* T2 = X->Right;

    X->Right = Y;
    Y->Left = T2;

    X->Height = GetHeight(X);
    Y->Height = GetHeight(Y);

    return X;
} // RotateRight

Node* AVLTree::RotateLeft(Node* X)
{
    Node* Y = X->Right;
    Node * T2 = Y->Left;

    Y->Left = X;
    X->Right = T2;

    Y->Height = GetHeight(Y);
    X->Height = GetHeight(X);

    return Y;

} // RotateLeft

Node* AVLTree::BalanceTree(Node* Root)
{
    if(Root == NULL)
    {
        return NULL;
    }

    int Balance = GetBalance(Root);
    int Left_Balance = GetBalance(Root->Left);
    int Right_Balance = GetBalance(Root->Right);

//    std::cout << "Data : " << Root->Data << " Balance " << Balance << " L " << Left_Balance << " R " << Right_Balance << std::endl;;

    // 4 Scenarios
    
    // Case 1 : LEFT LEFT!
    if((Balance > 1) &&
      (Left_Balance >= 0))
    {
        Root = RotateRight(Root);
    }

    // Case 2 : LEFT RIGHT!
    if((Balance > 1) &&
       (Left_Balance < 0))
    {
        Root->Left = RotateLeft(Root->Left);
        Root = RotateRight(Root);
    }

    // Case 3 : RIGHT RIGHT!
    if((Balance < -1) && 
       (Right_Balance <= 0))
    {
        Root = RotateLeft(Root);
    }

    // Case 4: RIGHT LEFT
    if((Balance < -1) &&
       (Right_Balance > 0))
    {
        Root->Right = RotateRight(Root->Right);
        Root = RotateLeft(Root);
    }
    return Root;
}

int main(int argc, char* argv[])
{
    AVLTree* Tree = new AVLTree();
    for(int i = 0; i < 15; i++)
    {
        int data = rand() % 100;
        std::cout << "Inserting " << data << std::endl;
        Tree->Insert(data);
    }
    Tree->PrintLevelOrder();
    std::cout << "In Order : " << std::endl;
    Tree->PrintInOrder();

    return 0; 
}
