#include "ListFile.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

List* listCreate(size_t initialCapacity)
{
	List* list = (List*)malloc(sizeof(List));
	if (!list) return NULL;

	list->size = 0;
	if (initialCapacity > 0)
	{
		list->capacity = initialCapacity;
	}
	else
	{
		list->capacity = 1;
	}
	list->items = (void**)calloc(list->capacity, sizeof(void*));
	if (!list->items)
	{
		free(list);
		return NULL;
	}
	return list;
}

void listDestroy(List* list)
{
	if (list)
	{
		free(list->items);
		free(list);
	}
}

void resize_if_needed(List* list)
{
	if (list->size == list->capacity)
	{
		list->capacity *= 2;
		void** new_items = (void**)realloc(list->items, list->capacity * sizeof(void*));
		if (new_items)
		{
			list->items = new_items;
		}
		else
		{
			fprintf(stderr, "Error: Memory could not be reallocated .\n");
		}

	}
}

void listAdd(List* list, void* item)
{
	resize_if_needed(list);
	list->items[list->size++] = item;
}

void* listGet(List* list, size_t index)
{
	if (index >= list->size)
	{
		fprintf(stderr, "Error: Index out of bounds. \n");
		return NULL;
	}
	return list->items[index];
}

void listRemoveAt(List* list, size_t index)
{
	if (index >= list->size)
	{
		return;
	}
	for (size_t i = index; i < list->size - 1; i++)
	{
		list->items[i] = list->items[i + 1];
	}
	list->size--;
}