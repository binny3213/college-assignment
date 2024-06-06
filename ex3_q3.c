// Course: Advanced C programming
// exercise 1, question 3
// file name: ex1_q3.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>

// --------------------------- //
//
//
// --------------------------- //

// structs and function declarations section:
typedef struct rectangle {
	int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;
}rectangle;

typedef struct recElement {
	rectangle Rect;
	struct recElement* next;
}recElement;

int validateRectangle(rectangle* rec);
rectangle scanRectangle();
recElement* createElement();
recElement* createRectList();
rectangle findSmallest(recElement* head);
void printRectangle(rectangle* rec);
void printList(recElement* head);
void freeList(recElement* head);

// --------------------------- //

int main()
{
	rectangle rec;
	recElement* head = NULL;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	head = createRectList();

	printf("\n\nRectangle list:\n");
	printList(head);

	rec = findSmallest(head);

	printf("\n\nFilling rectangle:\n");
	printRectangle(&rec);

	freeList(head);
	head = NULL;

	printf("\n\n");

	return 0;
}
// --------------------------- //


/// <summary>
/// Function gets an address of a rectangle and check validity.
/// </summary>
/// <param>Address of rectangle</param>
/// <returns>0- if rectangle is not valid, 1-if rectangle is a valid, 2-if rectangle is a point</returns>
int validateRectangle(rectangle* rec)
{
	// your code:
	if (rec->xTopSmall > rec->xButtomRight || rec->yTopSmall < rec->yButtomRight)
		return 0;
	else if ((rec->xButtomRight == rec->xTopSmall) && (rec->yButtomRight == rec->yTopSmall))
		return 2;
	else
		return 1;
}

// --------------------------- //



/// <summary>
/// Function scan a rectangle in the plane,
/// Used as auxiliary function for createElement.
/// </summary>
/// <param>None</param>
/// <returns>a newly scanned rectangle</returns>
rectangle scanRectangle()
{
	// your code:
	rectangle rec;
	static int i = 1;
	do
	{
		printf("Insert two points of corners of the rectangle %d: \n", i);
		printf("X top left corner: "); scanf_s("%d", &rec.xTopSmall);
		printf("Y top left corner: "); scanf_s("%d", &rec.yTopSmall);
		printf("X buttom right corner: "); scanf_s("%d", &rec.xButtomRight);
		printf("Y buttom right corner: "); scanf_s("%d", &rec.yButtomRight);

	} while (validateRectangle(&rec) == 0);
	i++;
	return rec;

}
// --------------------------- //


/// <summary>
/// Function allocate a new recElement.
/// Calls scanRectangle during the process. 
/// if the scanned rectangle is a point, returns NULL.
/// </summary>
/// <returns>New allocated recElement or NULL if rectangle is a point</returns>
recElement* createElement()
{
	// your code:
	recElement* element;

	element = (recElement*)calloc(1, sizeof(recElement));
	if (!element)
	{
		printf("No memory access!");
		return NULL;
	}
	else
	{
		element->Rect = scanRectangle();
		if (validateRectangle(&element->Rect) == 2)//its a point and not rectangle
			return NULL;
		else
		{
			element->next = NULL;
			return element;
		}
	}
}
// --------------------------- //


/// <summary>
/// Function creates a list of rectangles.
/// Calls function createElement in a loop.
/// Scan stops when createElement returns null.
/// </summary>
/// <param>None</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
recElement* createRectList()
{
	// your code:
	recElement* lst, * curr_rec;
	curr_rec = NULL;
	lst = createElement();
	curr_rec = lst;

	do
	{
		curr_rec->next = createElement();
		curr_rec = curr_rec->next;

	} while (curr_rec != NULL);

	return lst;
}
// --------------------------- //


/// <summary>
/// Function gets a list and returns the filling rectangle
/// </summary>
/// <param>recElement* head - the list of rectangles</param>
/// <returns>The filling rectangle. if the list is empty return rectangle with (0,0,0,0)</returns>
rectangle findSmallest(recElement* head)
{
	// your code:
	rectangle rec = head->Rect;
	head = head->next;

	while (head != NULL)
	{
		if (head->Rect.xTopSmall < rec.xTopSmall)
			rec.xTopSmall = head->Rect.xTopSmall;
		if (head->Rect.xButtomRight > rec.xButtomRight)
			rec.xButtomRight = head->Rect.xButtomRight;
		if (head->Rect.yTopSmall > rec.yTopSmall)
			rec.yTopSmall = head->Rect.yTopSmall;
		if (head->Rect.yButtomRight < rec.yButtomRight)
			rec.yButtomRight = head->Rect.yButtomRight;

		head = head->next;
	}
	return rec;

}
// --------------------------- //


/// <summary>
/// Function print rectangle cordinates on screen. (not drawing the rectangle!)
/// </summary>
/// <param>rectangle* rec - pointer to rectangle</param>
/// <returns>None</returns>
void printRectangle(rectangle* rec)
{
	// your code:
	printf("[(%d,%d)(%d,%d)]", rec->xTopSmall, rec->yTopSmall,
		rec->xButtomRight, rec->yButtomRight);
}
// --------------------------- //


/// <summary>
/// Function print list on screen.
/// </summary>
/// <param>recElement* head - list address</param>
/// <returns>None</returns>
void printList(recElement* head)
{
	// your code:
	while (head != NULL)
	{
		printRectangle(&head->Rect);
		printf("->");
		head = head->next;
	}
	printf("NULL\n");

}
// --------------------------- //


/// <summary>
/// Function free alocated memory of list 
/// </summary>
/// <param>recElement* head - pointer to head of the list</param>
/// <returns>None</returns>
void freeList(recElement* head)
{
	// your code:
	recElement* element = head;
	while (element != NULL)
	{
		head = head->next;
		free(element);
		element = NULL;
		element = head;
	}
}
// --------------------------- //
