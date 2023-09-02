/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){

/* YOUR CODE HERE! */
    data; //not sure if this is how you should do it
    n1 = 0; //front
    n2 = 0; //back

}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem) //finish
{
    /**
     * @todo Your code here!
     */
    data.push_back(newItem); 
    T lastItem = data[data.size() -1];
    swap(data[n2], lastItem);
    n2++;
    
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL() //pop front debug
{
    /**
     * @todo Your code here! 
     */
    
    
    T toRemove = data[n1];
    //swap(toRemove, data[n2]);
    //cout << toRemove << " ";
    //cout << data.capacity() << " ";
    //data.pop_back();
    //data.erase(data.begin()+n1);
    //int size = n2-n1;
    n1++;
    int size = n2-n1;
    int vecSpaceR = data.size() - n2;
    int vecSpaceL = n1;
    int vecSpaceTot = vecSpaceL + vecSpaceR;
    
    if (size <= vecSpaceTot) {
        //cout << n2 << " ";
        data.erase(data.begin() + n2, data.end());
        data.erase(data.begin(), data.begin()+n1);
        n2 = size;
        n1 = 0; 
        //return data[n1];      
    }

    /*if (size <= n1 - 1) {
        data.erase(data.begin(), data.begin()+n1);
        n2 = size;
        n1 = 0;
    }*/
    /*if (size < n1) {
        vector<T> temp;
        for (int i = 0; i < size; is++) {
            temp.push_back(data[n1+i]);
        }
        data.swap(temp);
    }*/
    return toRemove; // ./testStackQueue

}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR() //done
{
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    T toRemove = data[n2-1];
    //swap(data[n2-1], data.back());
    //data.pop_back();
    n2--;
    int size = n2 - n1;
    int vecSpaceR = data.size() - n2;
    int vecSpaceL = n1;
    int vecSpaceTot = vecSpaceL + vecSpaceR;

    
    if (size <= vecSpaceTot) {
        data.erase(data.begin() + n2, data.end());
        data.erase(data.begin(), data.begin()+n1);
        n2 = size;
        n1 = 0;          
    }
    
    return toRemove;
}
//

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL() //done
{
    /**
     * @todo Your code here! 
     */
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR() //done
{
    /**
     * @todo Your code here! 
     */
    return data[n2-1];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const //done
{
    /**
     * @todo Your code here! 
     */
    return data.empty();
}
