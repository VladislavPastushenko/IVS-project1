//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     VLADISLAV PASTUSHENKO <xpastu04@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author VLADISLAV PASTUSHENKO xpastu04
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"


PriorityQueue::PriorityQueue()
{
    root = NULL;
}

PriorityQueue::~PriorityQueue()
{
    
    Element_t *current = GetHead();
    
    // Pass each element 
    while(current != NULL) {
        Element_t *tmp = current->pNext;
        delete current;
        current = tmp;
    }
}

void PriorityQueue::Insert(int value)
{
    Element_t *current = GetHead();
    Element_t *newElement = new Element_t();
    newElement->value = value;
    newElement->pNext = NULL;
    newElement->pPrev = NULL;
    
    // If there is no elements, new element is root 
    if (current == NULL) {
        root = newElement;
        return;
    }
    
    
    // Check the root without next elements 
    if (current->pNext == NULL && current->pPrev == NULL) {
        // If root value < value of new element -> put new element next after root. Else - new element is root
        if (current->value < newElement->value) {
            current->pNext = newElement;
            newElement->pPrev = current;
        } else {
            root = newElement;
            newElement->pNext = current;
            current->pPrev = newElement;
        }
        
        return;
    }
    
    // Check the root, which has next elements
    else if(current->pNext != NULL && current->pPrev == NULL) {
        // If root value > value of new element -> new element is root.
        if(current->value > newElement->value) {
            newElement->pNext = current;
            current->pPrev = newElement;
            root = newElement;
        } else {
            // Else if root value < value of new element -> check each next element, until find the one, which has value which is less than value of privious one. If found it - put it after privious and end the function   
            while(current->pNext != NULL) {   
                if (current->value >= newElement->value) {
                    newElement->pPrev = current->pPrev;
                    newElement->pNext = current;
                    current->pPrev->pNext = newElement;
                    current->pPrev = newElement;
                    return;
                }
                
                current = current->pNext;
            }
            
            // Compare value of new element with value of the last element.   
            if (current->value > newElement->value) {
                    newElement->pNext = current;
                    newElement->pPrev = current->pPrev;
                    current->pPrev->pNext = newElement;
                    current->pPrev = newElement;
                
            } else {
                newElement->pPrev = current;
                current->pNext = newElement;
            }
        }
    }
    
    return;
}

bool PriorityQueue::Remove(int value)
{   
    Element_t *element = Find(value);
    
    if (element != NULL){
        
        // If found element is root, wich doesn't have next elements
        if (element->pNext == NULL && element->pPrev == NULL) {
            root = NULL;
        }
        
        // If found element is root, wich has next elements
        else if(element->pNext != NULL && element->pPrev == NULL) {
            root = element->pNext;
            element->pNext->pPrev = element->pPrev;
        }
        
        // If found element isn't root, and isn't last
        else if(element->pNext != NULL && element->pPrev != NULL) {
            element->pNext->pPrev = element->pPrev;
            element->pPrev->pNext = element->pNext;
        }
        
        // If found element is last
        else if(element->pNext == NULL && element->pPrev != NULL) {
            element->pPrev->pNext = element->pNext;
        }
        
        delete element;
        
        return true;
    }
    
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *current = GetHead();
    
    // Pass each element 
    while (current != NULL) {
        
        // If value of current element is eaqual to found value - return current element
        if (current->value == value) 
            return current;
        current = current->pNext;
    }
    
    // Didn't find nothing
    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return root;
}

/*** Konec souboru tdd_code.cpp ***/
