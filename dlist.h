//**************************************
//H E A D E R . F I L E
//**************************************

using namespace std;

template <class ItemType>
struct NodeType;

template <class ItemType>
class DList 
{
public :
    DList ();		// Constructor
    ~DList   ();  	// Destructor	

    // Public Operations
    void accessItem(ItemType item);
    void makeEmpty ();
    void deleteItem (ItemType item);
    bool inList (ItemType item) const;	
    bool isEmpty () const;  
    void print() const; 
    void insertHead (ItemType item); 
    void appendTail (ItemType item); 
    int lengthIs() const;
    void sort(); 
    

private :
    // Private Attributes of a DList Object 
    NodeType<ItemType>* head;
    int length;

    // Functions Called Solely By Public Functions, Not The Client 
    NodeType<ItemType>* location(ItemType item) const;
    NodeType<ItemType>* last() const;
    void swapInfo(NodeType<ItemType>* p1, NodeType<ItemType>* p2); 
    void deleteLocation (NodeType<ItemType>* delPtr);
    void findAndMove(ItemType item);
};

//Notice the header at the bottom of the file 
#include "dlist.cpp"
