#include <vector>
#include <iostream>
#include <algorithm>

struct PriorityQueueHeap{
    std::vector<int> arr;

    int parent(int i){ return (i-1)/2; }
    int leftChild(int i){ return 2*i + 1; }
    int rightChild(int i){ return 2*i + 2; }
    int getSize(){ return arr.size(); }

    void push(int priority){
        
    }
    void pop(){

    }

    int peek(){
        if(arr.empty()){
            throw std::out_of_range("Queue is empty");
        }
        return arr.front();
    }

};

int main(){

}