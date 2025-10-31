#pragma once
#ifndef _Dynamic_Array_
#define _Dynamic_Array_

#include<stddef.h>

typedef struct List{
	void** items;
	size_t size;
	size_t capacity;
}List;

List* listCreate(size_t initial_capacity);
void listDestroy(List* list);
void listAdd(List* list, void* item);
void* listGet(List* list, size_t index);
void listRemoveAt(List* list, size_t index);

#endif