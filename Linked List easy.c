
#include <stdexcept>

int List::head() {
  // Check if the list is empty
  if (m_size > 0) {
    return m_head->element;
  } else {
    // Throw an std::out_of_range exception for an empty list
    throw std::out_of_range("List is empty");
  }
}

// Checks whether the container is empty
bool List::empty() const {
  // TODO: Implement this method
  if (m_size > 0){
    return false;
  }
  else{
    return true;
  }
  
}

// Returns the number of elements
size_t List::size() const {
  // TODO: Implement this method
  return m_size;
}

// Inserts an element to the head
void List::push_head(int element) {
  // TODO: Implement this method
  Node* newNode = new Node(element);
  Node* temp = m_head;
  m_head = newNode;
  m_head->next = temp;
  m_size = m_size + 1;
  return;  
}

// Removes the head element
int List::pop_head() {
  // TODO: Implement this method
  if (m_size < 1)
  {
    // Throw an std::out_of_range exception for an empty list
    throw std::out_of_range("List is empty");
  }
  
  Node* temp = m_head;
  int value = m_head->element;
  m_head = m_head->next;
  m_size -= 1;
  delete temp;
  return value;
}

// Checks whether the container contains the specified element
bool List::contains(int element) const {
    if (m_size <= 0){
      return false;
    }
      Node *current = m_head;

    // Traverse the list
    while (current != nullptr) {
        // Check if the current node contains the specified element
        if (current->element == element) {
            return true;
        }

        // Move to the next node
        current = current->next;
    }

    // Element not found in the list
    return false;
}

// Returns a std::string equivalent of the container
std::string List::to_string() const {
  // TODO: Implement this method
  if (m_size < 1){
    return "{}";
  }

  std::string text = "{";
  Node *current = m_head;
  while (current->next != nullptr)
  {
    text += std::to_string(current->element)+", "; ///add, and }
    current= current->next;
  }
  text += std::to_string(current->element);
  text += "}";
  return text;
}
