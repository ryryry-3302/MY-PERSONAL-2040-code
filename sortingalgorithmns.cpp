
#include <iostream>
using namespace std;
#define SPLITSTR "Splitting: "
#define INTOSTR "Into :"
#include <LinkedList.h>
#define MERGESTR "Merging: "

int bubbleSort(int* arr, int size) {
    int swaps = 0;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
    return swaps;
}

void insertionSort(int* arr, int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int* arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
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
    
    


}


void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1; 

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quickSort(int arr[], int low, int high) {
    if (low < high) {        
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

