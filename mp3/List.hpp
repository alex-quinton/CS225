/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */

template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  //std::cout << "began deletion" << std::endl;
  
    ListNode* old_head_next;
  while (head_ != nullptr)
  {
      old_head_next = head_ -> next;
      delete head_;
      head_ = old_head_next;
  }

  length_ = 0;
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  delete this;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if (head_ != nullptr)
  {
      head_ -> prev = new ListNode(ndata);
      head_ -> prev -> next = head_;
      head_ = head_ -> prev;
      //std::cout << head_ -> data << std::endl;
  } else
  {
      head_ = new ListNode(ndata);
      tail_ = head_;
  }

  length_ ++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if (head_ != nullptr)
  {
      tail_ -> next = new ListNode(ndata);
      tail_ -> next -> prev = tail_;
      tail_ = tail_ -> next;
  } else 
  {
      head_ = new ListNode(ndata);
      tail_ = head_;
  }

  length_++;
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
  /// @todo Graded in MP3.1

  if (startPoint == nullptr || endPoint == nullptr || startPoint -> next == nullptr || endPoint -> prev == nullptr)
  {
      return;
  }

  ListNode* old_startPoint = startPoint;
  ListNode* old_endPoint = endPoint;
  ListNode* start_iter = startPoint;
  ListNode* end_iter = endPoint;


  startPoint = old_endPoint;
  endPoint = old_startPoint;

  if (start_iter -> next == end_iter)
  {
      //std::cout << "small list" << std::endl;

      start_iter -> prev = end_iter;
      start_iter -> next = end_iter -> next;
      end_iter -> next = start_iter;
      end_iter -> prev = start_iter -> prev;

      ListNode* old_start_iter = start_iter;

      startPoint = end_iter;
      endPoint = start_iter;
      return;
  }

  // Declare necessary temporary pointers
  ListNode *old_start_iter_next;
  ListNode *old_start_iter_prev;
  ListNode* temp_start_iter;

  while (start_iter != nullptr && start_iter -> next != end_iter && start_iter != end_iter)
  {
      // Swap pointers of adjacent nodes
      start_iter -> next -> prev = end_iter;
      end_iter -> prev -> next = start_iter;

      if (start_iter -> prev != nullptr)
      {
          start_iter -> prev -> next = end_iter;
      }
      
      if (end_iter -> next != nullptr)
      {
          end_iter -> next -> prev = start_iter;
      }

      // Declaring temp pointers
      old_start_iter_next = start_iter -> next;
      old_start_iter_prev = start_iter -> prev;

      // Swap pointers in edge nodes
      start_iter -> next = end_iter -> next;
      start_iter -> prev = end_iter -> prev;
      end_iter -> next = old_start_iter_next;
      end_iter -> prev = old_start_iter_prev;

      // Swap iter pointers
      temp_start_iter = start_iter;
      start_iter = end_iter;
      end_iter = temp_start_iter;

      // Advance for next iteration
      start_iter = start_iter -> next;
      end_iter = end_iter -> prev;
      //std::cout << "start_iter now at: " << start_iter -> data << std::endl;
      //std::cout << "end_iter now at: " << end_iter -> data << std::endl;

      //print(std::cout);
      //std::cout << std::endl;
      //std::cout << "next step" << std::endl;
  }

  //if (start_iter == nullptr) std::cout << "start_iter is nullptr" << std::endl;

  if (start_iter != nullptr && start_iter -> next == end_iter)
  {
      //print(std::cout);
      //std::cout << "entered special case" << std::endl;
      if (start_iter -> prev != nullptr)
      {
          start_iter -> prev -> next = end_iter;
      }
      
      if (end_iter -> next != nullptr)
      {
          end_iter -> next -> prev = start_iter;
      }
      start_iter -> prev = end_iter;
      start_iter -> next = end_iter -> next;
      end_iter -> next = start_iter;
      end_iter -> prev = start_iter -> prev;

      ListNode* old_start_iter = start_iter;

      start_iter = end_iter;
      end_iter = old_start_iter;
      return;
  }

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode* reverse_begin = head_;
  ListNode* reverse_end = head_;

  while (reverse_begin -> next != nullptr)
  {
      for (int i = 0; i < n - 1 && reverse_end -> next != nullptr; i++)
      {
        reverse_end = reverse_end -> next;
      //  std::cout << reverse_end -> data << std::endl;
      }

      //std::cout << "before reversal reverse_begin = " << reverse_begin -> data << std::endl;
      //std::cout << "before reversal reverse_end = " << reverse_end -> data << std::endl;
      reverse(reverse_begin, reverse_end);
      //std::cout << "after reversal reverse_begin = " << reverse_begin -> data << std::endl;
      //std::cout << "after reversal reverse_end = " << reverse_end -> data << std::endl;

      if (reverse_begin -> prev == nullptr)
      {
          head_ = reverse_begin;
      }
      reverse_begin = reverse_end -> next;
      reverse_end = reverse_end -> next;

      if (reverse_begin == nullptr)
      {
          return;
      }
  }
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
  /// @todo Graded in MP3.1

  ListNode* cur = head_;
  ListNode* old_cur_next = cur -> next;
  int step = 0;

  while (cur != tail_ && cur != nullptr)
  {
    if (step % 2 == 0)
    {
        step ++;
        cur = cur -> next;
        continue;
    }

    old_cur_next = cur -> next;
    // We know cur cannot be the head or the tail
    cur -> prev -> next = cur -> next;
    cur -> next -> prev = cur -> prev;
    cur -> next = nullptr;
    cur -> prev = tail_;
    tail_ -> next = cur;
    tail_ = cur;
    
    cur = old_cur_next;
    step++;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2

  ListNode* new_list = start;
  for (int i = 0; i < splitPoint; i++)
  {
      if (new_list != nullptr)
      {
          new_list = new_list -> next;
      }
  }

  if(new_list == nullptr)
  {
      return new_list;
  }

  new_list -> prev -> next = nullptr;
  return new_list;
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
  /// @todo Graded in MP3.2

  // null checks
  if (first == NULL) return second;
  if(second == NULL) return first;

  // pointers used to store answer/fill answer
  ListNode* result = NULL;
  ListNode* result_iter = result;

  while(first != NULL && second != NULL)
  {
      // IMPORTANT::::: ONLY ADD ONE ELEMENT AT A TIME!!
      // save these to we can reset pointers after we're done moving them
      ListNode* o_first = first;
      ListNode* o_second = second;
      ListNode* o_first_next = first -> next;
      ListNode* o_second_next = second -> next;

      if(first -> data < second -> data)
      {
        first -> prev = result_iter;
        first -> next = NULL;

        if (result == NULL)
        {
          result = first;
          result_iter = first;
        }else
        {
          result_iter -> next = first;
          result_iter = result_iter -> next;
        }
      first = o_first_next;

      } else
      {
        second -> prev = result_iter;
        second -> next = NULL;
        if (result == NULL)
        {
          result = second;
          result_iter = second;
        }else
        {
          result_iter -> next = second;
          result_iter = result_iter -> next;
        }
        second = o_second_next;
      }



      // print statement to show us how many elements come after result_iter
      //int num = -1;
      //ListNode* temp = result_iter;
      //while(temp != NULL)
      //{
      //    num++;
      //    temp = temp -> next;
      //}
      //std::cout << "num elements after result_iter: " << num << std::endl; 

  }

  if (first != NULL)
  {
      result_iter -> next = first;
  } else
  {
      result_iter -> next = second;
  }
  return result;

 // // repeatedly read the head of the second list and place it into the first
 // while (second != nullptr)
 // {

 //           //std::cout << second -> data << std::endl;
 //   ListNode* o_second_next = second -> next;

 //   //special case when second belongs in the front of first
 //   if (second -> data < first -> data  )
 //   {
 //       first -> prev = second;
 //       second -> next = first;
 //       if (o_second_next != NULL)
 //       {
 //           o_second_next -> prev = NULL;
 //       }
 //   }else
 //   {
 //       // iterate to the element that belongs before the element being merged
 //       ListNode* iter = first;
 //       while((iter -> next) != nullptr && iter -> next -> data < second -> data)
 //       {
 //           if (iter -> next == iter) std::cout << iter -> data << std::endl;
 //           iter = iter -> next;
 //       }

 //       // pointer jazz
 //       if (second -> next != nullptr)
 //       {
 //           second -> next -> prev = nullptr;
 //       }
 //       second -> next = iter -> next;
 //       if (iter -> next != nullptr)
 //       {
 //           iter -> next -> prev = second;
 //       }
 //       iter -> next = second;
 //       second -> prev = iter;
 //   } 

 //   second = o_second_next;
 // }

 // return first;
}//

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  if(start -> next == NULL)
  {
      return start;
  }

  ListNode* list2 = split(start, chainLength/2);
  start = mergesort(start, chainLength/2);
  if (chainLength % 2 == 0)
  {
      list2 = mergesort(list2, chainLength/2);
  } else
  {
      list2 = mergesort(list2, chainLength/2 + 1);
  }
  start = merge(start, list2);

  //ListNode* iter = start;
  //while(iter != NULL)
  //{
  //    std::cout << iter -> data << ", ";
  //    iter = iter -> next;
  //}
  //std::cout << std::endl;
  
  return start;
  //return merge(start, list2);
}
