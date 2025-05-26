#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "linked_list_functions.h"
#include "node.h"
using namespace std;




template <typename T>
class Queue
{
public:









    class Iterator{
    public:
        friend class List;                              //give access to list to access _ptr

        Iterator(){
            _ptr = nullptr;
        }                  //default ctor
        
        Iterator(node<T>* p){
            _ptr = p;
        }        //Point Iterator to where
        //...                        //  p is pointing to


        Iterator& operator =(const Iterator& rhs){
            if(this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }


        operator bool(){
            return _ptr != nullptr;
        }                                //casting operator: true if _ptr not NULL
                                                        //      this turned out to be a pain!


        T& operator *(){
            assert(_ptr);
            return _ptr->_item;
        }                        //dereference operator

        T operator ->(){                       //member access operator
            assert(_ptr);
            return &(_ptr->_item);
        }

        const T& operator *()const{
            assert(_ptr);
            return _ptr->_item;
        }                        //dereference operator

        const T operator ->()const{                       //member access operator
            assert(_ptr);
            return &(_ptr->_item);
        }

        

        bool is_null(){ return _ptr == nullptr; }                                 //true if _ptr is NULL

        friend bool operator ==(const Iterator& left, const Iterator& right){ //true if left == right
            if(left._ptr == right._ptr)
                return true;
            return false;
        }

        friend bool operator !=(const Iterator& left, const Iterator& right){ //true if left != right
            return !(left == right);
        }

        Iterator& operator++(){
            if (_ptr != nullptr)
                _ptr = _ptr->_next;
            return *this;
        }                         //member operator: ++it; or ++it = new_value

        friend Iterator operator++(Iterator& it, int unused){         //friend operator: it++
            Iterator temp = it;
            if (it._ptr != nullptr)
                it._ptr = it._ptr->_next; 
            return temp;
        }


    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };












//I
    Queue(){
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }

//I
    Queue(const Queue<T>& copyMe){
        _rear = _copy_list<T>(_front, copyMe._front);
        _size = copyMe._size;
    }

//I
    ~Queue(){
        //cout << "\nDestructor fired: \n";
        _clear_list<T>(_front);
    }

//I
    Queue& operator=(const Queue<T>& RHS){
        _clear_list<T>(_front);
        _rear = _copy_list<T>(_front, RHS._front);
        _size = RHS._size;
        return *this;
    }

//I
    bool empty(){ return _size == 0; }
    bool empty() const{ return _size == 0; }

//I
    T front(){ 
        assert(!empty());
        return _front->_item; 
    }


//I
    T back(){ 
        assert(!empty());
        return _rear->_item;
    }


//I
    void push(T item){
        _size++;
        //cout << "\npush fired: \n";
        _rear = _insert_after(_front, _rear, item);
    }


//I
    T pop(){
        assert(!empty());
        _size--;
        //cout << "\npop fired: \n";
        if(_front == _rear){
            _rear = nullptr;
            return _delete_head(_front);
        }
        return _delete_head(_front);
    }


//I
    Iterator begin() const{ return Iterator(_front); }           //Iterator to the head node
    Iterator end() const{ return Iterator(nullptr); }              //Iterator to NULL

    void print_pointers(){
    }
//I
    int size() const { return _size; }

    //template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<T>& printMe){
        node<T> *walker = printMe._front;
        while (walker != nullptr){
            //if you are here, walker is not nullptr:
            outs << *walker;
            walker = walker->_next;
        }
        outs << "|||" << endl;
        return outs;
    }

private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};


















#endif