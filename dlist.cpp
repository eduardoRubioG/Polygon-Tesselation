//********************************************
//I M P L E M E N T A T I O N . F I L E
//********************************************
#include <cstddef>
#include <iostream>
using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};

template <class ItemType>		
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}//end constructor --

template <class ItemType>
DList<ItemType>::~DList   ()		
{
	// Post: List is empty; All items have been deallocated.
}//end destructor --

template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    // Post: List is empty; all items have been deallocated.
    NodeType<ItemType>* tmp = new NodeType<ItemType>;
    tmp = head;
    
    while(head -> next != NULL)
    {
        head = head -> next;
        delete tmp;
        tmp = head;
    }
    
    head = head -> next;
    delete head;
}//end makeEmpty() --

template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found
    NodeType<ItemType>* finder = new NodeType<ItemType>;
    finder = head;
    
    //Scenario 1.) The list is empty; return false
    if(head == NULL)
        return false;
    //Scenario 3.) The head contains the item
    else if(head -> info == item)
        return true;
    //Scenario 3.) The last node contains the item
    else if(last() -> info == item)
        return true;
    //Scenario 4.) The finder pointer will
    //  iterate through the whole list until the end is reached
    else
    {
        while(finder -> next != NULL)
        {
            if(finder -> info == item)
                return true;
            finder = finder -> next;
        }
        return false;
    }
    
}//end inList() -- 

template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{
	// Post : function returns true if list is empty, false otherwise
	if(head == NULL)
        return true;
    else
        return false;
}//end isEmpty() --

template <class ItemType>
void DList<ItemType>::print() const	
{
	// Pre  : List is not empty 
	// Post : Items in List have been printed to screen
    //Make a temporary pointer to move around for printing so you don't lose
    //  the head pointer's place
    NodeType<ItemType>* printPointer = new NodeType<ItemType>;
    printPointer = head;
        cout << "\nYour List\n: " << endl; 
        int counter = 0;
        //1.) The list is longer than 1 node, so we print all except the last
        while (printPointer -> next != NULL)
        {
            counter++;
            cout << counter << ".) " << printPointer -> info << endl;
            printPointer = printPointer -> next;
        }
        //2.) If the list only has one node this if statement will be activated
        //  or if step 1.) was activated this if statement will also be activated to
        //  print the last element in the list 
        if(printPointer -> next == NULL)
        {
            counter ++;
            cout  << counter << ".) " << printPointer -> info << endl;
        }
}//end print() --
	
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 
NodeType<ItemType>* newNode = new NodeType<ItemType>;
newNode -> info = item; 
newNode -> back = NULL;
    //If item entered has not already been entered  in the list, then do
    //  insert into the list
            if(head != NULL)
            {                                                                                           
                head -> back = newNode;
                newNode -> next = head;
            }
            else
            {
                newNode -> next = NULL;
            }
            head = newNode;
            length++;
}//end insertHead(item) --

template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link
    NodeType<ItemType>* newNode = new NodeType<ItemType>;
    newNode -> info = item;

    if(inList(item) == false)
    {
        //Scenario 1.) If the list is not empty;
        //  Send the tmp node to the last node
        if(head != NULL)
        {
            NodeType<ItemType>* tmp = new NodeType<ItemType>;
            tmp = head;
            while (tmp -> next != NULL)
                tmp = tmp -> next;
            tmp -> next = newNode;
            newNode -> back = tmp;
            newNode -> next = NULL;
            length++;
        }
        //Scenario 2.) If the list is empty
        else
        {
            head = newNode;
            newNode -> next = NULL;
            newNode -> back = NULL;
            length++;
        }
    }
}//end appendTail() --

template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list
    return length;
}//end lengthIs() --

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list
    //Temporary pointer to move around instead of changing the head pointer
    NodeType<ItemType>* lastPointer = new NodeType<ItemType>;
    lastPointer = head;
    
    //Scenario 1.) List is empty; return null
    if(head == NULL)
    {
        return NULL;
    }
    
    //Scenario 2.) List is NOT empty; Move lastPointer to the last node in list
    else
    {
        while(lastPointer -> next != NULL)
        {
                lastPointer = lastPointer -> next;
        }
        return lastPointer; 
    }
}//end last() --

template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)
{
    //  Pre :  item to be deleted is passed in via parameter
    // Post :  item is deleted if it exists in list
    deleteLocation(location(item));
    
}//End of deleteItem()--

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const
{
    //  Pre : item to be located is passed in via parameter
    // Post : function returns address of item being searched for --
    //        if not found, NULL is returned
    NodeType<ItemType>* tmp = new NodeType<ItemType>;
    tmp = head;
    
    //Scenario 1.) List is empty; return null
    if(head == NULL)
        return NULL;
    
    //Scenario 2.) List is not empty; iterate through list
    //  and find  location where item is found
    //2a.) Check to see if the head node is equal to the item
    if(head -> info == item)
        return head;
    //2b.) Check the rest of the list
    else
    {
        while(tmp -> next != NULL)
        {
            //If the item is in the list, return its address
            if(tmp -> info == item)
                return tmp;
            //Otherwise, keep iterating
            else
                tmp = tmp -> next;
        }
    }
    
    //Special Case: Item is found at the last node of the list
    if(last() -> info == item)
        return last();
    
    //2c.) If the item was not found in the list...
    return NULL;
}//end location() --

template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
    
    //Scenario 1.) There's only one item
    if((delPtr -> next == NULL) && (delPtr -> back == NULL))
        head = NULL;
    //Scenario 2.) More than 2 nodes and it's the tail
    else if(delPtr -> next == NULL)
        delPtr -> back -> next = NULL;
    //Scenario 3.) More then 2 nodes and it's the head
    else if(delPtr -> back == NULL)
    {
        delPtr -> next -> back = NULL;
        head = delPtr -> next;
    }
    //Scenario 4.) More than 2 nodes and it's in the middle
    else
    {
        delPtr -> next -> back = delPtr -> back;
        delPtr -> back -> next = delPtr -> next;
    }
    
    //End: Deallocate the pointer and decrease the length variable
    delete delPtr;
    length--;
}//end deleteLocation() --

template<class ItemType>
void DList<ItemType>:: accessItem(ItemType item) 
{
    findAndMove(item); 
}
template<class ItemType>
void DList<ItemType>:: findAndMove(ItemType item) 
{
    //Function checks to see if item is in list
    //  if item is in list then it will be moved
    //  to the front
        deleteItem(item);
        insertHead(item);
}

template<class ItemType>
void DList<ItemType>:: sort()
{
    //This is a bubble sort.
    NodeType<ItemType>* sort_lead = new NodeType<ItemType>;
    NodeType<ItemType>* sort_trail = new NodeType<ItemType>;
    sort_trail = head;
    sort_lead = head -> next;
    
    for(int x = 0; x < lengthIs(); x++)
    {
        sort_trail = head;
        sort_lead = head -> next;
            while(sort_lead -> next != NULL)
            {
                if(sort_trail -> info > sort_lead -> info)
                    swapInfo(sort_lead, sort_trail);
                
                sort_lead = sort_lead -> next;
                sort_trail = sort_trail -> next;
            }
    }
}

template<class ItemType>
void DList<ItemType>:: swapInfo(NodeType<ItemType> *p1, NodeType<ItemType> *p2)
{
    int tmp;
    tmp = p1 -> info;
    p1 -> info = p2 -> info;
    p2 -> info = tmp;
}



















