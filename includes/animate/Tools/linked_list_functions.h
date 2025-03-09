#ifndef BARKESHLI__LINKED_LIST_FUNCTIONS_H__
#define BARKESHLI__LINKED_LIST_FUNCTIONS_H__

#include <iostream>
#include <iomanip>
#include "node.h"
#include <cassert>
using namespace std;











//I
template <typename T>
node<T> *insert_head(node<T> *&head_ptr, const T &item){
  //1. create a new crate
  node<T> *temp = new node<T>(item);
  // 2. point him to where headptr is pointing to.
  temp->_next = head_ptr;
  // 3. point headptr to this new guy
  head_ptr = temp;
  return head_ptr;
}



//I
template<typename T>
void print_list(node<T> *head_ptr){
  node<T> *walker = head_ptr;
  while (walker!=nullptr){
    //if you are here, walker is not nullptr:
    cout << *walker;
    walker = walker->_next;
  }
  cout << "|||" << endl;
}





//I C
    //ptr to previous node
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this){
        node<ITEM_TYPE>* walker = head;
        if(prev_to_this == walker)
            return nullptr;

        while(walker != nullptr){
            if(walker->_next == prev_to_this)
                return walker;
            walker = walker->_next;
        }
        assert(false);
        return nullptr;
    }






//I C
    //Linked List General Functions:
    template <typename ITEM_TYPE>
    void _print_list(node<ITEM_TYPE>* head){
        print_list<ITEM_TYPE>(head);
    }
    
//I C
        template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this){
        return insert_head<ITEM_TYPE>(head, insert_this);
    }

    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_head(node<ITEM_TYPE> *&head){
        assert(head != nullptr);
        ITEM_TYPE save = head->_item;
        node<ITEM_TYPE>* saveNext = head->_next;
        delete head;
        head = saveNext;
        return save;
    }


//I C
    //recursive fun! :)
    template <typename ITEM_TYPE>
    void _print_list_backwards(node<ITEM_TYPE> *head){
        node<ITEM_TYPE>* walker = head;
        node<ITEM_TYPE>* reversed = nullptr;
        while(walker != nullptr){
            reversed = _insert_head<ITEM_TYPE>(reversed, walker->_item);
            walker = walker->_next;
        }
        _print_list<ITEM_TYPE>(reversed);
    }

//I C
    //return ptr to key or NULL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key){
        node<ITEM_TYPE>* walker = head;
        while(walker != nullptr){
            if(walker->_item == key)
                return walker;
            walker = walker->_next;
        }
        return nullptr;
    }

//I C
    //insert after ptr
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this){
        if(after_this == nullptr)            
            return _insert_head<ITEM_TYPE>(head, insert_this);
        
        node<ITEM_TYPE>* oldNext = after_this->_next;
        node<ITEM_TYPE>* insert_ptr = new node<ITEM_TYPE>(insert_this, oldNext);
        after_this->_next = insert_ptr;
        return insert_ptr;
    }

//I C
    //insert before ptr
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this){
        //--------------------------------------------------------------
        node<ITEM_TYPE>* prevPtr = _previous_node<ITEM_TYPE>(head, before_this);
        //--------------------------------------------------------------
        if(prevPtr == nullptr)                                    //in case if the iMarker is the first node                              //why dont you use insert head! ): ): ):
            return insert_head<ITEM_TYPE>(head, insert_this);

        prevPtr->_next = new node<ITEM_TYPE>(insert_this, before_this);
        return prevPtr->_next;
    }


//I C Q: delete what if nullptr
    //delete, return item
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this){
        assert(delete_this != nullptr);
        node<ITEM_TYPE>* prevPtr = _previous_node<ITEM_TYPE>(head, delete_this);
        //if deleteing the nullptr node

        //if deleteing the head node
        if(prevPtr == nullptr){
            head = delete_this->_next;
        }
        else{
            prevPtr->_next = delete_this->_next;
        }
        ITEM_TYPE save = delete_this->_item;
        delete delete_this;
        return save;
    }


//I C
    //duplicate the list...
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
        node<ITEM_TYPE>* rethead = nullptr;

        if(head != nullptr){
            node<ITEM_TYPE>* walker1 = head;
            node<ITEM_TYPE>* walker2 = new node<ITEM_TYPE>(walker1->_item);
            rethead = walker2;

            while(walker1->_next != nullptr){
                walker2->_next = new node<ITEM_TYPE>;
                walker2 = walker2->_next;
                walker1 = walker1->_next;
                walker2->_item = walker1->_item;
            }
        }
        return rethead;
    }


//I C
    //duplicate list and return the last node of the copy
    template <typename ITEM_TYPE>
    node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE>* &dest, node<ITEM_TYPE> *src){
        node<ITEM_TYPE>* rethead = nullptr;
        node<ITEM_TYPE>* walker2 = nullptr;

        if(src != nullptr){
            node<ITEM_TYPE>* walker1 = src;
            walker2 = new node<ITEM_TYPE>(walker1->_item);
            rethead = walker2;

            while(walker1->_next != nullptr){
                walker2->_next = new node<ITEM_TYPE>;
                walker2 = walker2->_next;
                walker1 = walker1->_next;
                walker2->_item = walker1->_item;
            }
        }
        dest = rethead;
        return walker2;
    }


//I  C
    //delete all the nodes
    template <typename ITEM_TYPE>
    void _clear_list(node<ITEM_TYPE>*& head){
        while(head != nullptr){
            node<ITEM_TYPE>* temp = head->_next;
            delete head;
            head = temp;
        }
    }

//I C
    //_item at this position
    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
        node<ITEM_TYPE>* walker = head;
        int current = 0;
        while(walker != nullptr){
            if(current == pos)
                break;
            walker = walker->_next;
            current++;
        }
        assert(walker != nullptr);
        return walker->_item;
    }

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //      Sorted List Routines. order: 0: ascending, order: other: descending
    //                              Assume a Sorted List
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


//I  C
    //node after which this item goes order: 0 ascending
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending=true){
        node<ITEM_TYPE>* walker = head;

        if(walker == nullptr)
            return nullptr;
        
        if(((walker->_item >= item) && (ascending == true)) ||              //insert head
            ((walker->_item <= item) && (ascending == false)))             //
                return nullptr;

        while(walker->_next != nullptr){
            if((((walker->_next)->_item >= item) && (ascending == true)) ||
                (((walker->_next)->_item <= item) && (ascending == false))){
                break;
            }
            walker = walker->_next;
        }
        return walker;
    }











//I  C
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending = true){
        node<ITEM_TYPE>* insertPt = _where_this_goes<ITEM_TYPE>(head, item, ascending);
        return _insert_after<ITEM_TYPE>(head, insertPt, item);
    }

    //I  C
    //insert or add if a dup
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true){
        node<ITEM_TYPE>* insertPt = _where_this_goes<ITEM_TYPE>(head, item, ascending);
        node<ITEM_TYPE>* walker1 = insertPt->_next;
        ITEM_TYPE total = item;

        while(walker1->_item == item){
            total += item;
            _delete_node<ITEM_TYPE>(head, walker1);
            walker1 = insertPt->_next;
        }

        return _insert_after<ITEM_TYPE>(head, insertPt, total);
    }

    
    //Last Node in the list
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
        return _previous_node(head, nullptr);
    }            //never use this function.






//remove head
//delete if null ptr resolved
//check all dynamic mem
//last node f'n
//insert sorted edge case
//WTG no use previous












#endif // BARKESHLI__LINKED_LIST_FUNCTIONS_H__
