

#include <iostream>
using namespace std;

#define SPLITSTR "Splitting: "
#define INTOSTR "Into :"
#define MERGESTR "Merging: "


class ListNode {

private:
    int _item;
    ListNode* _next;

public:
    ListNode( int );        // Constructs the list node with parameter
    void printItem();       // Prints the item

    friend class List;
};

class List {

private:
    ListNode* _head;
    int _size;

public:
    List();                             // Constructs an empty list
    ~List();                            // Destructs a list

    void insertHead( int );             // Inserts the new value into the linked list
    int getHeadItem();                  // Retrieves the value in the head node
    int removeHead();                   // Removes the head node and returns the value removed

    void bubbleSort();            // TODO: Implement bubble sort
    void mergeSort();                   // Calls the recursive merge sort function

    void split( List* );                // TODO: Splits the linked lists into two halves
    void merge( List* );                // TODO: Merge two linked lists in ascending order

    void print();                 // Prints all items of the linked lists.
};








/*
 * LISTNODE CONSTRUCTUORS AND FUNCTIONS
 */
ListNode::ListNode(int item) {
    _item = item;
    _next = NULL;
}

void ListNode::printItem() {
    cout << _item;
}


/*
 * LIST CONSTRUCTORS AND FUNCTIONS
 */
List::List() {
    _head = NULL;
    _size = 0;
}

List::~List() {
    while (_head) {
        removeHead();
    }
}

void List::insertHead(int item) {
    ListNode* newNode = new ListNode(item);
    newNode->_next = _head;
    _head = newNode;
    _size++;
}

int List::getHeadItem() {
    return _head->_item;
}

int List::removeHead() {
    int item = -32768;  
    ListNode* temp;

    if (_head) {
        temp = _head;
        item = getHeadItem();
        _head = _head->_next;
        delete temp;
        _size--;
    }

    return item;
}

void List::bubbleSort() {

    // TODO: Implement bubble sort on this implementation of single linked list.
    //       Print the linked list after every pass in the outer iteration
    //       using print(false) function in List class if parameter is true.
    //       The list should be sorted in ascending order.

    // ENTER YOUR ANSWER BELOW.
    int notsorted = 1;
    ListNode* current = _head; 
    while (notsorted) {
        ListNode* currentnode = _head;
        int countofswap = 0;
        while(currentnode->_next){
            
            if (currentnode->_item > currentnode->_next->_item)
            {   
                countofswap += 1;
                int temp = currentnode->_item;
                currentnode->_item = currentnode->_next->_item;
                currentnode = currentnode->_next;
                currentnode->_item = temp;
                /* code */
            }
            else{
                currentnode = currentnode->_next;
            }
            if(countofswap == 0 && !currentnode->_next){
                notsorted=0;
            }
            
        }
        if(notsorted){
            
        print();
        }
    }

    // ENTER YOUR ANSWER ABOVE.
}


void List::mergeSort() {

    // modify this function
    // 
    // each time you split a list
    List* otherlist = new List();

    if(_size>1){
    cout << SPLITSTR;
    // original unsplitted list print
    print();
    cout << INTOSTR << endl;
    // original splitted list print (but it's halved)
    
    
    split(otherlist);
    print();
    otherlist->print();
    // the other splitted list print
    mergeSort();
    otherlist->mergeSort();
    }
    if(otherlist->_size){
    // after you sorted the two lists
    cout << MERGESTR << endl;
    // original splitted list print (but it's halved)
    print();
    // the other splitted list print
    otherlist->print();
    // after you merged the above two sorted lists
    merge(otherlist);
    
    cout << INTOSTR;
    // print the merged sorted single list
    print();
    }
}


void List::split(List* otherList) {
    // TODO: Implement splitting of the current list.
    //       The first half of the list will be pointed by itself.
    //       The second half of the list will be pointed by otherList.
    //       It is guaranteed that the original list will have more than one node.
    //
    //       No need to print within split()
    
    // ENTER YOUR ANSWER BELOW.
    ListNode * slownode = _head;
    ListNode * fastnode = _head->_next;
    while(fastnode->_next && fastnode->_next->_next){
        slownode= slownode->_next;
        fastnode= fastnode->_next->_next;       
    }
    fastnode = slownode->_next;
    otherList->_head =fastnode;
    otherList->_size = _size/2 + _size %2;
    slownode->_next = NULL;
    _size = _size/2;


   // ENTER YOUR ANSWER ABOVE.
}

void List::merge(List* otherList) {
    // TODO: Implement merging of current list and otherList.
    //       The otherList should be empty after merging.
    //       It is guaranteed that both lists are non-empty.
    //
    //       No need to print within merge()
    // ENTER YOUR ANSWER BELOW.
    List* newmerge = new List();
    while(otherList->_size && this->_size){
        if(getHeadItem() > otherList->getHeadItem()){
            newmerge->insertHead(otherList->getHeadItem());
            otherList->removeHead();
        }
        else{
            newmerge->insertHead(getHeadItem());
            removeHead();
        }
        
    }
    while (otherList->_size)
    {
        newmerge->insertHead(otherList->getHeadItem());
        otherList->removeHead();
    }
    while (_size)
    {
        newmerge->insertHead(getHeadItem());
        removeHead();
    }
    while(newmerge->_size){
        insertHead(newmerge->getHeadItem());
        newmerge->removeHead();
    }
    
    



    // ENTER YOUR ANSWER ABOVE.
}

void List::print() {

    ListNode* curr = _head;

    while (curr) {
        cout << curr->_item;
        cout << " ";
        curr = curr->_next;
    }

    cout << endl;
}




