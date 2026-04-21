#include <vector>
#include <iostream>
#include <algorithm>

struct Element{
    int id;
    int priority;
};
struct PriorityQueueHeap{
    std::vector<Element> heap;

    int parent(int i){ return (i-1)/2; }
    int leftChild(int i){ return 2*i + 1; }
    int rightChild(int i){ return 2*i + 2; }
    int getSize(){ return heap.size(); }

    void restoreOrderPop(int index){
        int maxIndex = index;
        int l = leftChild(index);
        int r = rightChild(index);
        
        if(l < heap.size() && heap[l].priority > heap[maxIndex].priority){
            maxIndex = l;
        }
        if(r < heap.size() && heap[r].priority > heap[maxIndex].priority){
            maxIndex = r;
        }

        if(index != maxIndex){
            std::swap(heap[index], heap[maxIndex]);
            restoreOrderPop(maxIndex);
        }
    }

    void restoreOrderPush(int index){
        while(index > 0 && heap[index].priority > heap[parent(index)].priority){
            std::swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void pop(){
        if(heap.empty()){
            throw std::out_of_range("Queue is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        restoreOrderPop(0);
    }

    void push(Element newElement){
        heap.push_back(newElement);
        restoreOrderPush(heap.size()-1);
    }

    Element peek(){
        if(heap.empty()){
            throw std::out_of_range("Queue is empty");
        }
        return heap.front();
    }

    void changePriority(){

    }
};

int main(){

}