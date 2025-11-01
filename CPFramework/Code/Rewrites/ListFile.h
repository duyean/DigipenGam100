#pragma once
#ifndef _Dynamic_Array_
#define _Dynamic_Array_

#include<stddef.h>

typedef struct List{
	void** items;
	size_t size;
	size_t capacity;
}List;

List* ListCreate(size_t initial_capacity);
void ListDestroy(List* list);
void ListAdd(List* list, void* item);
void* ListGet(List* list, size_t index);
static void ResizeIfNeeded(List* list);
void ListRemoveAt(List* list, size_t index);

#endif