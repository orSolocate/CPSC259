/*
 File:              linkedlist.c
 Purpose:           Implements the linked list functions whose prototypes
					are declared in the linked_list.h header file
 Author:			Jingwei Xiong and Or Bahari
 Student #s:		41724148 and 51277200
 CS Accounts:		r8u9a and iok2b
 Date:				2018-10-14
 */

 /* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/******************************************************************
 PLEASE EDIT THIS FILE

 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/

 /*
  Main function drives the program.  Every C program must have one
  main function.  A project will not compile without one.

  In our program, the main function does nothing.  That's because
  our program doesn't do anything.  We're just implementing a linked
  list and testing it using our unit tests.

  PRE:    NULL (no pre-conditions)
  POST:	 NULL (no side-effects)
  RETURN: IF the program exits correctly
		  THEN 0 ELSE 1
  */
int main(void)
{
	struct airplane test_airplane = { 100, "Vancouver", "Toronto", 1, 900, 36000, 350 };
	struct node * test_list = create_linked_list();
	test_list = prepend_node(test_list, create_node(test_airplane));
	test_list = remove_from_list(test_list, "Toronto");
	/* The system command forces the system to pause */
	system("pause");
	return 0;
}

/*
 Returns a pointer to a new, empty linked list of struct node.
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a new, empty linked list of struct node (NULL)
 */
struct node * create_linked_list()
{
	struct node* empty;
	//empty = (struct node*) malloc(sizeof(struct node));
	empty = NULL;
	return empty;
};

/*
 Returns a dynamically allocated struct node that contains the specified
 struct airplane.  The node's next pointer doesn't point to anything
 e.g., it is equal to NULL.
 PARAM:     plane, a struct airplane
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a dynamically allocated struct node a) that contains
			the specified struct airplane, and b) whose next pointer points to NULL
 */
struct node * create_node(struct airplane plane)
{
	// Insert your code here
	struct node *empty = (struct node*) malloc(sizeof(struct node));
	empty->plane = plane;
	empty->next = NULL;
	return empty;

}

/*
 Prepends a struct node passed as a parameter to the list passed as a
 parameter, and returns a pointer to the result.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     new_node is a pointer to a struct node
 PRE:       new_mode is not null
 POST:      The specified struct node is added to the beginning of the list
			and its next pointer points to the node that used to be first
 RETURN:    A pointer to a linked list which contains all of the nodes
			of the list passed as a parameter, plus a prepended node
 */
struct node * prepend_node(struct node * list, struct node * new_node)
{
	new_node->next = list;
	list = new_node;
	return list;
}

/*
 Deletes the first struct node in the specified list, and returns a pointer to
 the shortened list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL
 POST:      The list passed as a parameter has one fewer node, and the dynamically
			allocated memory which contained that removed node has been freed
 RETURN:    IF the list is empty
			THEN NULL
			ELSE a pointer to the shortened list
 */
struct node * delete_node(struct node * list)
{
	if (list == NULL) {
		return NULL;
	}
	else {
		struct node *dummy = list;
		list = list->next;
		free(dummy);
		return list;
	}
}

/*
 Returns the number of nodes in the specified linked list of struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    The length of the specified list, an int
 */
int get_length(struct node * list)
{
	int i = 0;
	struct node *list_1 = list;
	while (list_1 != NULL) {
		i++;
		list_1 = list_1->next;
	}
	return i;

}

/*
 Deletes an entire list.  This function iterates along a list and deallocates the
 memory containing each struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The memory containing all of the nodes in the list has been freed
 RETURN:    an empty list (NULL)
 */
struct node * delete_list(struct node * list)
{

	while (list != NULL) {

		list = delete_node(list);
	}
	return list;

}

/*
 Prints the data stored in a node.  For the struct airplane in the node,
 prints the fields on separate lines.  For each field, prints the field name
 and the field value.  For the pointer, prints "Link = NULL\n" if the pointer points
 to null, else prints "Link points to address xxx\n", where xxx is the pointer address
 in hexademical.
 If node_to_print is NULL, prints "The node is empty\n".
 PARAM:     node_to_print is a pointer to a (possibly null) struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about node_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_node(struct node * node_to_print)
{
	if (node_to_print == NULL) {
		printf("The node is empty\n");
		return;
	}
	else
	{
		printf("flight_number: %d\n", node_to_print->plane.flight_number);
		printf("city_origin: %s\n", node_to_print->plane.city_origin);
		printf("city_destination: %s\n", node_to_print->plane.city_destination);
		printf("priority: %d\n", node_to_print->plane.priority);
		printf("maximum_speed: %d\n", node_to_print->plane.maximum_speed_kph);
		printf("cruising_altitude: %d\n", node_to_print->plane.cruising_altitude);
		printf("capacity: %d\n", node_to_print->plane.capacity);
		if (node_to_print->next != NULL) {
			printf("Link points to address %h\n", node_to_print->next);
		}
		else {
			printf("Link = NULL\n");
			return;
		}
	}


}

/*
 Prints the data stored in all nodes in the specified list to print.
 For each node, prints the data inside the node the same way that it
 is printed by print_node.  If the list is empty, a suitable message
 is printed to standard output.
 PARAM:     node_to_print is a pointer to a (possibly empty) linked list of
			struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about list_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_list(struct node * list_to_print)
{

	struct node *list_1 = list_to_print;
	while (list_1 != NULL) {
		print_node(list_1);
		list_1 = list_1->next;
	}
	return;
}

/*
 Reverses a list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The order of the nodes in the list passed as a parameter has been
			reversed
 RETURN:    a list of struct node that is the reverse of the list passed as a
			parameter
 */
struct node * reverse(struct node * list)
{
	if (list == NULL) {
		return NULL;
	}
	int len = get_length(list);
	struct node *iter;
	struct node *new_list = list;
	while (new_list->next != NULL) { new_list = new_list->next; }
	while (len > 1)
	{
		iter = list;
		while (iter->next->next != NULL) { iter = iter->next; }
		iter->next->next = iter;
		iter->next = NULL;
		len--;
	}
	list = new_list;
	return list;
}

/*
 Removes every node from the list which contains an airplane destined for
 the city name passed in the second parameter.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     destination_city is a pointer to a null-terminated array of char
 PRE:       NULL (no pre-conditions)
 POST:      Any struct node in the list which contains an airplane struct
			destined for the destination_city is removed from the list, and
			the memory deallocated
 RETURN:    a list of struct node that does not contain any struct node that
			has an airplane destined for the destination_city
 */
struct node * remove_from_list(struct node * list, char * destination_city)
{
	struct node* dummy = list;
	//sanity check for list
	if (list == NULL)
	{
		return list;
	}
	//check the first destination
	while (strcmp(dummy->plane.city_destination, destination_city) == 0)
	{
		list = delete_node(dummy);
		dummy = list;
		if (list == NULL) { return list; }	// well that's in case this was the only element
	}
	//taking care of other destinations
	while (dummy->next != NULL) {
		if (strcmp(dummy->next->plane.city_destination, destination_city) == 0)
		{
			dummy->next = delete_node(dummy->next);
		}
		else
		{
			dummy = dummy->next;
		}
	}
	return list;
}

/*
 Returns a reference to the nth node (but does not remove it ) in the
 specified list.  If the list is too short, returns NULL.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list
			THEN a pointer to the nth node
			ELSE NULL
 */
struct node * retrieve_nth(struct node * list, int ordinality)
{
	struct node *dummy = list;
	int n = 0;
	if (list == NULL) { //return null is emply list
		return NULL;
	}
	if (ordinality > get_length(list)) {
		return NULL; //reutrn NULL is the ordinality is outside of the list
	}
	else {
		for (n = 0; n < ordinality - 1; n++) {
			dummy = dummy->next;
		}
		return dummy;
	}
}

/*
 Inserts the specified node into the specified list of nodes at the specified
 ordinality.  For example, if ordinality = 1, this is a simple prepend_node
 operation.  If ordinality = 3, then when this function is finished, the third
 node in the list will be the node_to_insert.  If the ordinality = the length
 of the list + 1, then the node_to_insert is appended to the end of the list.
 If the ordinality > 1 + length of the list, the function returns a pointer
 to the unchanged list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 PRE:       node_to_insert is NEVER a null (it is always a correct node pointer)
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list + 1
			THEN a pointer to the list which contains the node_to_insert in the
			correct location
			ELSE a pointer to the unchanged list
 */
struct node * insert_nth(struct node * list, struct node * node_to_insert, int ordinality)
{
	struct node *dummy3 = list;
	int i = 0;

	
		if (ordinality == 1) {
			if (list == NULL) {
				return node_to_insert;
			}
			else {
				node_to_insert->next = list;
				return node_to_insert;
			}
		}
	

	if (ordinality <= (get_length(list) + 1)) {
		for (i = 0; i < ordinality - 2; i++) {
			dummy3 = dummy3->next;
		}
		node_to_insert->next = dummy3->next;
		dummy3->next = node_to_insert;
		
	}
	return list;
}