/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;

    //return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return 2 * currentIdx;

    //return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.

    return 2 * currentIdx + 1;

    //return 2 * currentIdx + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.

    return currentIdx/ 2;

    //return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child

    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    if (rightChild(currentIdx) >= _elems.size()) return leftChild(currentIdx);

    if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)])) {
        
        return leftChild(currentIdx);
    }
    else return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
    if (hasAChild(currentIdx)) {
        size_t max_priority_child = maxPriorityChild(currentIdx);

        if (higherPriority(_elems[max_priority_child], _elems[currentIdx])) {

            std::swap(_elems[currentIdx], _elems[max_priority_child]);
            heapifyDown(max_priority_child);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    // we start at index 1 so we need to offset heap
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.
    _elems = elems;

    // if 1-indexed;
    _elems.push_back(_elems[0]);

    //for (size_t i = parent(_elems.size() - 1); i >= root(); --i)
    //comparing under 0, always use signed int to make logics, unsigned will never go below 0
    for (int i = parent(_elems.size() - 1); i >= (int)root(); --i){
        
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority

    T val = peek();
    std::swap(_elems[root()], _elems.back());
    _elems.pop_back();
    heapifyDown(root());
    return val;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority

    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.size() == root(); 
    //root()=0 for 0 index heap, 1 for 1 indexed heap
}
