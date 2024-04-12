#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <string>

template <typename T> struct Node {
  T element;
  Node<T> *next;

  Node(T element) : element{element}, next{nullptr} {}
  Node(T element, Node<T> *next) : element{element}, next{next} {}
};

template <typename T> class List {
private:
  size_t m_size;
  Node<T> *m_head;


  // Feel free to add helper functions here, if necessary
  std::string convertToString(const std::string& str) const {
    return "\"" + str + "\"";
  }

  template<typename U>
  std::string convertToString(const U& value) const {
      return std::to_string(value);
  }

public:
  // Constructs an empty container
  List() : m_size{0}, m_head{nullptr} {}

  // Constructs the container with the contents of the initializer list
  List(std::initializer_list<T> init_list) : m_size{0}, m_head{nullptr} {
    auto it = init_list.end();
    while (--it != init_list.begin()) {
      push_head(*it);
    }
    push_head(*it);
  }
  std::string to_string_custom(const char& value) {
    return "'" + std::string(1, value) + "'";
  }

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.

  // Destructor
  ~List() {
    // TODO: (Optional) Implement this method
  }

  // Copy constructor
  List(const List<T> &other) {
    // TODO: (Optional) Implement this method
  }

  // Copy assignment
  List<T> &operator=(const List<T> &other) {
    // TODO: (Optional) Implement this method
  }

  // Returns the contents of the head node
  const T& head() {
    if (m_size <= 0) {
      throw std::out_of_range("List is empty");
    }
    return m_head->element;
  }

  // Checks whether the container is empty
  bool empty() const { return m_size == 0; }

  // Returns the number of elements
  size_t size() const { return m_size; }

  // Inserts an element to the head
  void push_head(const T& element) {
    Node<T> *node = new Node<T>{element, m_head};
    m_head = node;
    m_size++;
  }

  // Removes the head element
  void pop_head() {
    if (m_size <= 0) {
      throw std::out_of_range("List is empty");
    }
    Node<T> *node = m_head;
    m_head = m_head->next;
    delete node;
    m_size--;
  }

  // Checks whether the container contains the specified element
  bool contains(const T& element) const {
    // TODO: Implement this method
    //if (m_size <= 0){return false;}
   // else{
      Node<T>* current = m_head;
      while(current != nullptr){
        if(current->element == element)
          return true;
        else
          current = current->next;
      }
      return false;
   // }
    
  }

  // Extracts the maximum element from the container
  T extract_max() {
    // TODO: Implement this method
    if (m_size > 0){
      T max = m_head->element;
      Node<T>* current = m_head;
      while (current != nullptr)
      {
        if (max< current->element){
          max = current->element;
        }
        current = current->next;
      }
      return max;
    }
    else
    throw std::out_of_range("Cannot extract max from empty list");
  }

  // Reverse the container
 void reverse() {
    // TODO: Implement this method
    if (m_head == nullptr || m_head->next == nullptr) {
        
        return;
    }
    Node<T>* tempnext = m_head->next;
    Node<T>* current = m_head;
    current->next = nullptr;
    while (tempnext != nullptr)
    {
      Node<T>* nextNode = tempnext->next;
      tempnext->next = current;
      current = tempnext;
      tempnext = nextNode;

    }
    m_head = current; 

  }

  // Returns a std::string equivalent of the container
 std::string to_string() const {
    if (m_head == nullptr) {
        return "{}";
    }

    std::string result = "{";
    Node<T>* current = m_head;

    while (current != nullptr) {
        result += convertToString(current->element);

        if (current->next != nullptr) {
            result += ", ";
        }

        current = current->next;
    }

    result += "}";
    return result;
}

};

#endif
