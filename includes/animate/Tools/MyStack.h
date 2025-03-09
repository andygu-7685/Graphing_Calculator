#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>
#include <cassert>

#include "linked_list_functions.h"
#include "node.h"
using namespace std;








template <typename T>
class Stack{
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

        T* operator ->(){                       //member access operator
            assert(_ptr);
            return &(_ptr->_item);
        }

        const T& operator *()const{
            assert(_ptr);
            return _ptr->_item;
        }                        //dereference operator

        const T* operator ->()const{                       //member access operator
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
    Stack(){
        _top = nullptr;
        _size = 0;
    }
//I
    Stack(const Stack<T>& copyMe){
        _top = _copy_list<T>(copyMe._top);
        _size = copyMe._size;
    }
//I
    ~Stack(){
        _clear_list<T>(_top);
    }

//I
    Stack<T>& operator=(const Stack<T>& RHS){
        _clear_list<T>(_top);
        _top = _copy_list<T>(RHS._top);
        _size = RHS._size;
    }

//I
    T top(){ 
        assert(!empty());
        return _top->_item; 
    }
//I
    bool empty(){ return _top == nullptr; }
//I
    void push(T item){
        _size++;
        _top = _insert_head<T>(_top, item);
    }
//I
    T pop(){
        assert(!empty());
        _size--;
        return _delete_head<T>(_top);
    }

    //template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        node<T> *walker = printMe._top;
        while (walker!=nullptr){
            //if you are here, walker is not nullptr:
            outs << *walker;
            walker = walker->_next;
        }
        outs << "|||" << endl;
        return outs;
    }
//I
    Iterator begin() const{ return Iterator(_top); }              //Iterator to the head node
//I
    Iterator end() const{ return Iterator(nullptr); }                //Iterator to NULL
//I
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};














#endif