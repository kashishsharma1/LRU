#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

//node to store the data(linked list)
class Node{
    public:
        string key;
        int value;
        Node(string key,int value){
            this ->key = key;
            this -> value = value;
        }
};

class LRUCache{
    public:
    int maxSize;
    list<Node> l;
    unordered_map<string,list<Node>::iterator>  m;

    LRUCache(int maxSize){
        this -> maxSize = maxSize > 1 ? maxSize : 1;
    }

    void insertKeyValue(string key, int value){
        if(m.count(key) != 0){
            auto it = m[key];
            it -> value = value;
        }
        else{
            if(l.size() == maxSize){
                Node last = l.back();
                m.erase(last.key);
                l.pop_back();
            }

            Node n(key,value);
            l.push_front(n);
            m[key] = l.begin();
        }

    }

    int* getValue(string key){
        if(m.count(key) != 0){
            auto it = m[key];

            int value = it -> value;
            l.push_front(*it);
            l.erase(it);
            m[key] = l.begin();
            return &l.begin() -> value;
        }
        return NULL;
    }

    string mostRecentKey(){
        return l.front().key;
    }
};

int main(){

    LRUCache lru(3);
    lru.insertKeyValue("mango",10);
    lru.insertKeyValue("apple",20);
    lru.insertKeyValue("guava",30);
    cout<<lru.mostRecentKey()<<endl;

    lru.insertKeyValue("orange",40);
    cout<<lru.mostRecentKey()<<endl;

    int *orders = lru.getValue("orange");
    if(orders != NULL){
        cout<<"Order of Orange  "<<*orders<<endl;
    }

    lru.insertKeyValue("pear",20);
    if(lru.getValue("apple") == NULL){
        cout<<"apple doesn't exist";
    }
    if(lru.getValue("guava") == NULL){
        cout<<"apple doesn't exist";
    }
    if(lru.getValue("pear") == NULL){
        cout<<"apple doesn't exist";
    }
    if(lru.getValue("orange") == NULL){
        cout<<"apple doesn't exist";
    }
    return 0;
}
