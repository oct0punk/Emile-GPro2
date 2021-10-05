#include "pch.h"
#include "LinkedList.h"

void LinkedList::test()
{
	LinkedList* list = CreateLinkedList(0);
	list->RemoveFirst();

	list->Print();

}
