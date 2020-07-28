#include <stdio.h>

int main(){
	int a = 1,b = 2,c = 0;

	printf("%d %d\n",a,b);

	asm volatile(
		"movl %1,%0\n"
		: "=r"(b)
		: "r"(a)
	);

	printf("%d %d\n",a,b);

	return 0;
}
