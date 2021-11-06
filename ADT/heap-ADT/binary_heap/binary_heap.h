#ifndef INCLUDE_BINARYHEAP_H_
#define INCLUDE_BINARYHEAP_H_

#include <vector>
#include <iterator>
#include <cmath>

// Assume min heap
template <class T>
class BinaryHeap
{
 private:
  unsigned long heap_size_;
  std::vector<T> data_;
  // typedef typename std::vector<T>size_type heap_size_;
  void SiftUp(unsigned long node);
  void SiftDown(unsigned long node);

 public:
  BinaryHeap(unsigned long num_elements);
  BinaryHeap();
  ~BinaryHeap() {}

  // Misc Operations (using STL namimg).
  unsigned long count() { return heap_size_;}  // Get count of objects.
  void clear();                      // clear the object for reuse.
  
  template <class I>
  int Heapify(I start, I end);
  const T FindXtrma();
  const T ExtractXtrma();
  void Insert(const T& data);   // Insert(key)
  void Delete(unsigned long element);     // Delete(element)
  void IncreaseKey(unsigned long element, const T& change);
  void DecreaseKey(unsigned long element, const T& change);
  unsigned long get_size(){return(heap_size_);}
  /* void Merge(class &Heap); */
};

#endif  // INCLUDE_BINARYHEAP_H_