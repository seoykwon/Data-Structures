#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 100; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 100; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}



TEST_CASE("Stack::push pop alterations","[weight=1][part=queue]"){
    Stack<int> intStack;
    vector<int> result;
    //vector<int> expected = {0,0, 1, 1};
    vector<int> expected = {0,0,1,1,2,2,3,3,2,2,1,1,0,0};
   
    
    intStack.push(0);
    intStack.push(0);
    result.push_back(intStack.pop());
    result.push_back(intStack.pop());

    intStack.push(1);
    intStack.push(1);
    result.push_back(intStack.pop());
    result.push_back(intStack.pop());

    intStack.push(2);
    intStack.push(2);
    result.push_back(intStack.pop());
    result.push_back(intStack.pop());

    intStack.push(3);
    intStack.push(3);
    result.push_back(intStack.pop());
    result.push_back(intStack.pop());

    intStack.push(2);
    result.push_back(intStack.pop());
    intStack.push(2);
    result.push_back(intStack.pop());
    

    intStack.push(1);
    result.push_back(intStack.pop());
    intStack.push(1);
    result.push_back(intStack.pop());

    intStack.push(0);
    result.push_back(intStack.pop());
    intStack.push(0);
    result.push_back(intStack.pop());

    REQUIRE( result == expected);
}

TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}

TEST_CASE("dequeue::popR","[weight=1][part=dequeue]"){ //not done
    Deque <int> intDeque;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i >= 1; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intDeque.pushR(i);
    }
    while (!intDeque.isEmpty()) {
        result.push_back(intDeque.popR());
    }
    REQUIRE( result == expected);
}

TEST_CASE("dequeue:: PopL","[weight=1][part=dequeue]"){ //not done
    Deque <int> intDeque;
    vector<int> result;
    vector<int> expected;
    int count = 0;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intDeque.pushR(i);
    }
    while (!intDeque.isEmpty()) {
        result.push_back(intDeque.popL());
        
    }
    REQUIRE( result == expected);
}

TEST_CASE("dequeue:: peekR ","[weight=1][part=dequeue]"){ //not done
    Deque <int> intDeque;
    vector<int> result;
    vector<int> expected;
    int count = 0;
    
    expected.push_back(10);

    for (int i = 1; i <= 10; i++) {
        intDeque.pushR(i);
    }
    result.push_back(intDeque.peekR());
        
    REQUIRE( result == expected);
}

TEST_CASE("dequeue:: push PopR Alternate","[weight=1][part=dequeue]"){ //not done
    Deque <int> intDeque;
    vector<int> result;
    vector<int> expected = {0,0,1,1,3,2,3,2,2,2,1,1,0,0};
    int count = 0;

    
    intDeque.pushR(0);
    intDeque.pushR(0);
    result.push_back(intDeque.popR());
    result.push_back(intDeque.popL());

    intDeque.pushR(1);
    result.push_back(intDeque.popR());
    intDeque.pushR(1);
    result.push_back(intDeque.popL());

    intDeque.pushR(2);
    intDeque.pushR(2);
    intDeque.pushR(3);
    intDeque.pushR(3);
    result.push_back(intDeque.popR());
    result.push_back(intDeque.popL());
    result.push_back(intDeque.popR());
    result.push_back(intDeque.popL());

    intDeque.pushR(2);
    result.push_back(intDeque.popR());
    intDeque.pushR(2);
    result.push_back(intDeque.popR());
    

    intDeque.pushR(1);
    result.push_back(intDeque.popR());
    intDeque.pushR(1);
    result.push_back(intDeque.popR());

    intDeque.pushR(0);
    result.push_back(intDeque.popR());
    intDeque.pushR(0);
    result.push_back(intDeque.popR());
        
    REQUIRE( result == expected);
}




