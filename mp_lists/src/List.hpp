/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return head_;
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return tail_->next;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  if(head_==NULL)return;
  else{
    ListNode* iterator = tail_;
    while(iterator!=NULL){
      ListNode* temp = iterator;
      iterator = iterator->prev;
      delete temp;
    }
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;
  

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  if(start==NULL)return NULL;
  if(splitPoint==0)return start;
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if(curr == NULL)return NULL;
  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  ListNode* curr = head_;
  ListNode* last = tail_;
  int count=0;
  if(curr ==NULL || curr==last)return;
  while(curr->next != last){
    if(curr == head_ || count%2==0){
      curr = curr->next;
      count++;
    }
    else{
      ListNode* temp = curr->next;
      curr->prev->next = curr->next;
      curr->next->prev = curr->prev;
      last->next = curr;
      curr->prev = last;
      curr->next = NULL;
      curr = temp;
      last = last->next;
      count++;
    }
  }
  ListNode* temp = curr->next;
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  last->next = curr;
  curr->prev = last;
  curr->next = NULL;
  curr = temp;
  last = last->next;
  tail_ = last;
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2

    if(startPoint==NULL || endPoint==NULL)return;
    if(startPoint==endPoint)return;

    bool change_head = false;
    bool change_tail = false;
    if(startPoint->prev==NULL){
      change_head = true;
    }
    if(endPoint->next==NULL){
      change_tail = true;
    }

    ListNode* current = startPoint;
    ListNode* stop = endPoint->next;

    int count=0;
    ListNode* start;
    ListNode* end;

    while(current!=stop){
      ListNode* pre = current->prev;
      current->prev = current->next;
      current->next = pre;
      if(count==0){
        start = current;
      }
      else{
        end = current;
      }
      count++;
      current = current->prev;
    }

    ListNode* front = end->prev;
    end->prev = start->next;
    start->next = front;
    if(start->next!=NULL){
      start->next->prev = start;
    }
    if(end->prev!=NULL){
      end->prev->next = end;
    }
    if(change_head){
      head_=end;
    }
    if(change_tail){
      tail_ = start;
    }
    startPoint = end;
    endPoint = start;


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  if(head_==NULL)return;
  ListNode* iterator = head_;
  ListNode* end = head_;
  int count=1;
  while(end->next!=NULL){
    if(count==n){
      count=0;
      ListNode* temp = end->next;
      reverse(iterator, end);
      iterator = temp;
      end=temp;
    }
    else{
      end = end->next;
    }
    count++;
  }
  if(count!=1){
    reverse(iterator, end);
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  if(first ==NULL)return second;
  if(second == NULL)return first;
  ListNode* head = first;
  while(second !=NULL){
    if(second->data<first->data){
      if(first->prev==NULL){
        head = second;
        ListNode* next_sec = second->next;
        second->next = first;
        first->prev = second;
        second = next_sec;
      }
      else{
        ListNode* next_sec = second->next;
        first->prev->next = second;
        second->prev = first->prev;
        second->next = first;
        first->prev = second;
        second = next_sec;
      }
    }
    else{
      if(first->next==NULL){
        first->next = second;
        second->prev = first;
        break;
      }
      else{
        first = first->next;
      }
    }
  }
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if(chainLength==1)return start;
  if(chainLength==2){
    if(start->data>start->next->data){
      ListNode* second = start->next;
      second->prev = NULL;
      second->next = start;
      start->prev = second;
      start->next = NULL;
      return second;
    }
    return start;
  }
  else{
    ListNode* firsthalf = start;
    ListNode* sechalf = start;
    for(int i=0;i<chainLength/2;i++){
      sechalf = sechalf->next;
    }
    sechalf->prev->next = NULL;
    sechalf->prev = NULL;
    firsthalf = mergesort(firsthalf, chainLength/2);
    sechalf = mergesort(sechalf, (chainLength+1)/2);
    return merge(firsthalf, sechalf);
  }
}
