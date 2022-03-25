/*
Project and realise a template of a container class, that represents an abstract data type of dual linked list.
This class should contain random access iterator and have the following interface:
Constructor
Destructor
Operator=
Iterators:
begin           return iterator to beginning
end             return iterator to end
rbegin          return reverse iterator to reverse beginning
rend            return reverse iterator to reverse end
Capacity:
empty           test whether container is empty
size            return size
Element access:
front           access first element
back            access last element
Modifiers:
assign          assign new content to container
push_front      insert element at beginning
pop_front       delete first element
push_back       add element at the end
pop_back        delete last element
insert          insert element x at index idx
erase           erase element
swap            swap content
resize          change size
clear           clear
Operations:     
reverse         reverse the order of elements

It is forbidden to use std::iterator.
Demonstrate work of the implemented methods in the main function.
*/
#include <iostream>

template <class T>
class DoubleLinkedList {

    // struct Node is substruct of class DoubleLinkedList
    struct Node {
        Node* prev;
        Node* next;
        T value;
        Node(const T& value, Node* next = nullptr, Node* prev = nullptr) :
            value(value), prev(prev), next(next) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int n_size = 0;

    constexpr void checkEmpty() {
        if (empty()) throw "List is empty";
    }

    template<class U>
    void mySwap(U& u1, U& u2) {
        U tmp(u2);
        u2 = u1;
        u1 = tmp;
    }

public:

    class iterator {
        Node* ptr;
    public:
        iterator(Node* ptr) :ptr(ptr) {}

        T& operator*() { return ptr->value; }
        T* operator->() { return &ptr->value; }
        // Prefix increment & decrement
        iterator& operator++() { ptr = ptr->next; return *this; }
        iterator& operator--() { ptr = ptr->prev; return *this; }
        // Postfix increment & decrement
        iterator operator++(int) { iterator tmp(*this); ++(*this); return tmp; }
        iterator operator--(int) { iterator tmp(*this); --(*this); return tmp; }

        iterator& operator+=(int n) {
            for (; n > 0; n--, ++(*this));
            return *this;
        }
        iterator& operator-=(int n) {
            for (; n > 0; n--, --(*this));
            return *this;
        }
        iterator operator-(const iterator it2) {
            int distance = 0;
            while (it2 != *this) { ++it2; distance++; };
            return distance;
        }
        bool operator<(const iterator& it) {
            return (it - *this) > 0;
        }
        bool operator>(const iterator& it) {
            return (*this - it) > 0;
        }
        bool operator>=(const iterator& it) {
            return !(*this < it);
        }
        bool operator<=(const iterator& it) {
            return !(*this > it);
        }
        T& operator[](int n) {
            return *(*this + n);
        }

        friend iterator operator+(iterator it, int n) {
            return it += n;
        }
        friend iterator operator+(int n, iterator& it1) {
            return it1 + n;
        }
        friend iterator operator-(iterator it, int n) {
            return it -= n;
        }
        friend iterator operator-(int n, iterator& it1) {
            return it1 - n;
        }

        bool operator==(const iterator& a) { return ptr == a.ptr; };
        bool operator!=(const iterator& a) { return ptr != a.ptr; };
    };

    // Reverse iterator
    class riterator  {
        Node* ptr;
    public:
        riterator(Node* ptr) :ptr(ptr) {}

        T& operator*() { return ptr->value; }
        T* operator->() { return &ptr->value; }
        // Prefix increment & decrement
        riterator& operator++() { ptr = ptr->prev; return *this; }
        riterator& operator--() { ptr = ptr->next; return *this; }
        // Postfix increment & decrement
        riterator operator++(int) { riterator tmp(*this); ++(*this); return tmp; }
        riterator operator--(int) { riterator tmp(*this); --(*this); return tmp; }

        riterator& operator+=(int n) {
            for (; n > 0; n--, ++(*this));
            return *this;
        }
        riterator& operator-=(int n) {
            for (; n > 0; n--, --(*this));
            return *this;
        }
        riterator operator-(const riterator it2) {
            int distance = 0;
            while (it2 != *this) { ++it2; distance++; };
            return distance;
        }
        bool operator<(const riterator& it) {
            return (it - *this) > 0;
        }
        bool operator>(const riterator& it) {
            return (*this - it) > 0;
        }
        bool operator>=(const riterator& it) {
            return !(*this < it);
        }
        bool operator<=(const riterator& it) {
            return !(*this > it);
        }
        T& operator[](int n) {
            return *(*this + n);
        }

        friend riterator operator+(riterator it, int n) {
            return it += n;
        }
        friend riterator operator+(int n, riterator& it1) {
            return it1 + n;
        }
        friend riterator operator-(riterator it, int n) {
            return it -= n;
        }
        friend riterator operator-(int n, riterator& it1) {
            return it1 - n;
        }

        bool operator==(const riterator& a) { return ptr == a.ptr; };
        bool operator!=(const riterator& a) { return ptr != a.ptr; };
    };

    // Constructor
    DoubleLinkedList() {}
    DoubleLinkedList(const DoubleLinkedList& dll) {
        Node* p = dll.head;
        while (p) {
            push_back(p->value);
            p = p->next;
        }
    }
    // Iterators
    iterator begin() {
        return head;
    }
    iterator end() {
        return nullptr;
    }

    riterator rbegin() {
        return tail;
    }
    riterator rend() {
        return nullptr;
    }

    // Capacity
    constexpr bool empty() {
        return n_size == 0;
    }
    constexpr int size() {
        return n_size;
    }

    // Destructor
    ~DoubleLinkedList() {
        clear();
    }
    void operator=(const DoubleLinkedList& dll) {
        clear();
        Node* p = dll.head;
        while (p) {
            push_back(p->value);
            p = p->next;
        }
    }

    // Element access
    T front() {
        checkEmpty();
        return head->value;
    }
    T back() {
        checkEmpty();
        return tail->value;
    }
    // Modifiers
    void assign(const T* content, int n) {
        clear();
        for (; n > 0; n--)
            push_back(*content++);
    }

    void push_front(T x) {
        if (empty())  // list is empty
            tail = head = new Node(x);
        else {
            head->prev = new Node(x, head);
            head = head->prev;
        }

        n_size++;
    }
    void pop_front() {
        checkEmpty();
        if (n_size == 1) {
            delete head;
            tail = head = nullptr;
            n_size--;
            return;
        }

        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        n_size--;
    }
    void push_back(T x) {
        if (empty())
            tail = head = new Node(x);
        else
            tail = tail->next = new Node(x, nullptr, tail);

        n_size++;
    }
    void pop_back() {
        checkEmpty();
        if (n_size == 1) {
            delete tail;
            tail = head = nullptr;
            n_size--;
            return;
        }

        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        n_size--;
    }
    void insert(int idx, T x) {
        if (idx == 0) {
            push_front(x);
            return;
        }
        if ((idx > n_size) || (idx < 0)) {
            throw "Invalid index";
        }
        if (idx == n_size) {
            push_back(x);
            return;
        }

        Node* p = head;
        for (; idx > 1; idx--, p = p->next);

        // Put x between p and p->next
        p->next = p->next->prev = new Node(x, p->next, p);
        n_size++;
    }
    void erase(int idx) {
        if (idx == 0) {
            pop_front();
            return;
        }
        if ((idx >= n_size) || (idx < 0)) {
            throw "Invalid index";
        }
        if (idx == n_size - 1) {
            pop_back();
            return;
        }

        Node* p = head;
        for (; idx > 0; idx--, p = p->next);

        // Erase p
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        n_size--;
    }
    void swap(DoubleLinkedList& dll) {
        DoubleLinkedList::mySwap(head, dll.head);
        DoubleLinkedList::mySwap(tail, dll.tail);
        DoubleLinkedList::mySwap(n_size, dll.n_size);
    }
    void resize(int n) {
        while (n_size < n) push_back(T());
        while (n_size > n) pop_back();
    }
    void clear() {
        while (!empty()) pop_back();
    }
    // Operations
    void reverse() {
        Node* l = head, * r = tail;
        int l_index = 0, r_index = n_size - 1;
        while (l_index < r_index) {
            mySwap(l->value, r->value);
            l = l->next;
            r = r->prev;
            l_index++;
            r_index--;
        }
    }
};

template<class T>
std::ostream& operator<<(std::ostream& out, DoubleLinkedList<T>& l) {
    for (typename DoubleLinkedList<T>::iterator it = l.begin(); it != l.end(); ++it) {
        out << *it << ' ';
    }
    out << std::endl;
    return out;
}

int main()
{
    
    DoubleLinkedList<int> list1;
    list1.push_front(10);
    std::cout << "list after push_front(10): " << list1;
    list1.push_back(0);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    std::cout << "list after push_back(0,1,2,3): " << list1;

    list1.pop_back();
    std::cout << "list after pop_back(): " << list1;

    std::cout << "list empty = " << list1.empty() << "\n";
    std::cout << "list size = " << list1.size() << "\n";

    DoubleLinkedList<int> list;
    int numbers[] = { 2,23,4,9,5,6,7,8 };
    list.assign(numbers, sizeof(numbers) / sizeof(numbers[0]));
    std::cout << list;

    list.insert(2, 888);
    std::cout << "list after list.insert(2, 888): " << list;
    std::cout << "list size() = " << list.size() << "\n";

    list.erase(5);
    std::cout << "list after list.erase(5): " << list;
    list.erase(5);
    std::cout << "list after list.erase(5): " << list;

    list.resize(3);
    std::cout << "list after list.resize(3): " << list;
    std::cout << "list size() = " << list.size() << "\n";

    std::cout << std::endl;


    list.reverse();
    std::cout << "list after list.reverse() " << list << "\n";


    // list and list1 swap
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list: " << list << "\n";

    list.swap(list1);
    std::cout << "swap\n";

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list: " << list << "\n";




    // iterator test
    std::cout << "iterator test: " << "\n";
    for (DoubleLinkedList<int>::iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    std::cout << "iterator random access test: " << "\n";
    DoubleLinkedList<int>::iterator it = list.begin();
    for (int i = 0; i < list.size(); i++) {
        std::cout << it[i] << ' ';
    }
    std::cout << "\n\n";
    
    std::cout << "iterator random access test 2: " << "\n";
    for (int i = 0; i < list.size(); i++) {
        std::cout << *(it + i) << ' ';
    }

    std::cout << "\n\n";
    

    std::cout << "riterator test: " << "\n";
    for (DoubleLinkedList<int>::riterator it = list.rbegin(); it != list.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    list.clear();
    std::cout << "list after list.clear(): " << list;
    std::cout << "list size = " << list.size() << "\n";
    std::cout << "list empty = " << list.empty();
    
    return 0;
}