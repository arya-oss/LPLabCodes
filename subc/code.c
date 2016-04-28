#include "stdio.h"

void main() {
	int a,b,c,d;
	a = 10;
	c = 5;
	if (a == c) {
		d = 20;
	} else {
		d = 10;
	}
	b = 0;
	while(b != d) {
		a = a+c;
		b = b+1;
	}
	
}
