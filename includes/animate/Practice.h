#ifndef PRACTICE_H
#define PRACTICE_H



#include "node.h"



template <class T>
node<T>* revertK(node<T>* head, int k){
    node<T>* w1(head), w2(nullptr), w3(nullptr);
    node<T>* initial(head), final;
    bool first, stop;
    (head) ? w2 = w1->_next : return nullptr;
    (w2) ? w3 = w2->_next : return head;

    while(true){
        for(int i = 0; i < k-1; i++){
            w2->_next = w1;
            if(!w3){
                stop = true;
                breakl;
            }

            w1 = w2;
            w2 = w3;
            w3 = w3->next;
        }

        if(first && !stop){
            
        }
    }

}
















#endif