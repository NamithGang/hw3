#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> list;
  int m_;
  PComparator c_;


};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  m_ = m;
  c_ = c;
}
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  list.push_back(item);

  //heapify
  int index = list.size()-1;
  while(index > 0){
    T& current = list[index];
    T& parent = list[(index-1)/m_];
    if(c_(current, parent)){
      std::swap(current, parent);
      index = (index-1)/m_;
    } else {
      break;
    }
  }
}
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return list.empty();
}
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return list.size();
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return list[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  std::swap(list[0], list[list.size()-1]);
  list.pop_back();

  if (!empty()) {
    int index = 0;
    while (true) {
      int smallest = index;
      for (int i = 1; i <= m_; ++i) {
        int childIndex = m_ * index + i;
        if (childIndex < list.size() && c_(list[childIndex], list[smallest])) {
          smallest = childIndex;
        }
      }

      if (smallest != index) {
        std::swap(list[index], list[smallest]);
        index = smallest;
      } else {
        break;
      }
    }
  }
}



#endif

