
> Implementation using LinkedList

```
class Node{
    public:
        int data;
        Node *next;
        Node(int val){
            this->data = val;
            this->next = nullptr
        }
};

class Stack{
    Node *top;
    Stack(){
        this->top = nullptr;
    }

    bool isEmpty(){
        return top == nullptr;
    }

    void push(int data){
        Node *new_node = new Node(data);
        if(!new_node) cout<<"stack overflow"<<endl;

        new_node->next = top;
        top = new_node;
    }

    void pop(){
        if(this->isEmpty()) cout<<"stack underflow"<<endl;
        else {
            Node *tmp = top;
            top = top->next;
            delete tmp;
        }
    }

    int peek(){
        if(!isEmpty) return top->data;
        else {
            cout<<"Stack is empty "<<endl;
            return INT_MIN;
        }
    }
};
```
