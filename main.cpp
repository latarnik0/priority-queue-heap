#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Element{
    int id;
    int priority;
};
struct PriorityQueueHeap{
    std::vector<Element> heap;
    std::unordered_map<int, int> pos;

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

            // hashmap update
            pos[heap[index].id] = index;
            pos[heap[maxIndex].id] = maxIndex;
            
            restoreOrderPop(maxIndex);
        }
    }

    void restoreOrderPush(int index){
        while(index > 0 && heap[index].priority > heap[parent(index)].priority){
            std::swap(heap[index], heap[parent(index)]);
            
            // hashmap update
            pos[heap[index].id] = index;
            pos[heap[parent(index)].id] = parent(index);
            
            index = parent(index);
        }
    }

    void pop(){
        if(heap.empty()){
            throw std::out_of_range("Queue is empty");
        }
        // hashmap update
        pos.erase(heap[0].id);

        heap[0] = heap.back();
        heap.pop_back();

        if(!heap.empty()){
            // hashmap update
            pos[heap[0].id] = 0;

            restoreOrderPop(0);
        }
    }

    void push(int newId, int newPriority){
        if(pos.find(newId) != pos.end()){
            throw std::invalid_argument("Element already exists");
        }

        Element newElement = {newId, newPriority};
        heap.push_back(newElement);

        // hashmap update
        pos[newId] = heap.size() - 1;

        restoreOrderPush(heap.size()-1);
    }

    Element peek(){
        if(heap.empty()){
            throw std::out_of_range("Queue is empty");
        }
        return heap.front();
    }

    void changePriority(int targetID, int newPriority){
        auto it = pos.find(targetID);

        if(it == pos.end()){ 
            throw std::out_of_range("Element does not exist");
        }
        
        int index = it->second;
        
        int prevPriority = heap[index].priority;
        heap[index].priority = newPriority;

        if(prevPriority > newPriority){
            restoreOrderPop(index);
        }
        else if(prevPriority < newPriority){
            restoreOrderPush(index);
        }
        else return;
    }

    void prnt(){
        for(int i=0; i<heap.size(); ++i){
            std::cout<<"ID: "<<heap[i].id<<std::endl;
            std::cout<<"Priority: "<<heap[i].priority<<std::endl;
            std::cout<<"---------------"<<std::endl;
        }
    }
};

int main(){

}