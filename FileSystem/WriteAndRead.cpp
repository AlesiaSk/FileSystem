#include <iostream>
#include <fstream>
#include<conio.h>
#include<stdio.h>
#include<string>

using namespace std;

struct segment {
	unsigned long int address;
	char rools[2];
	int size;
};

struct element {
	segment block;
	element *next;
	element *previous;
};

void addInEnd(element **end, segment f, element **begin) {
	element *temp = new element;
	(*temp).previous = *end;
	(*temp).next = NULL;
	if (*end != NULL) {
		(**end).next = temp;
	}
	*end = temp;
	(*temp).block = f;
	if (*begin == NULL) {
		*begin = *end;
	}
}

void create(element **begin, element **end) {
	*begin = NULL;
	*end = NULL;
}


void deleteSegment(element **begin, element **end, segment delsegment) {
	segment g;
	element *iterator;
	iterator = *begin;
	while (iterator != NULL) {
		g = (*iterator).block;
		if (g.address == delsegment.address) {

			if ((*iterator).previous == NULL) {
				*begin = (**begin).next;
			}
			else
			{
				(*(*iterator).previous).next = (*iterator).next;
			}
			if ((*iterator).next == NULL) {
				*end = (**end).previous;
			}
			else {
				(*(*iterator).next).previous = (*iterator).previous;
			}
		}

		iterator = (*iterator).next;

	}
}