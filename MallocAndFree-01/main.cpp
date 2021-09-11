#include <stdlib.h>
#include <stdio.h>

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// Memory Relative Knowledge
/// 
/// 1. Exception-Safe - If you acquire some resources, you have to prepare a bullet-proof way 
///		to return all the resources back.
/// 
///		1.1 Never let any exceptions throw from ctors(constructors) or dtors(destructors).
///
/// 2. Thread-Safe - You should not use any static non-const variables.
/// 
///		2.1 Do not use non-const global variable and non-const static variables.
/// 
/// 3. Use namespace smartly - Use it properly to avoid remember hundreds of thousands of functions or class.
///		It will help you keep you code clean and easy to use.
/// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MallocAndFree(size_t size)
{
	// 0. Check if size is valid.
	if (size == 0)
	{
		printf("You can not set the size to 0!\n");
		::SetLastError(ERROR_INVALID_PARAMETER);
		return;
	}

	// 1. Allocate the memory.
	int* ptr = (int*)malloc(sizeof(int) * size);

	// 2. Check if the memory allocated successfully.
	if (!ptr)
	{
		printf("Failed to allocate memory!\n");
		return;
	}

	printf("Memory allocate successfully!\n");

	// 3. Use the memory.
	// Notice that this is not Exception-Safe code, because if an exception had been throw in here,
	// it will cause memory LEAK. The free() will not be called.
	for (int i = 0; i < (int)size; i++)
	{
		ptr[i] = i;
		printf("%d\n", ptr[i]);
	}

	// 4. Release the memory!
	free(ptr);
}

int main()
{
	size_t maxT = 0xffffffff;

	//MallocAndFree(0);      // accept. but actual malloc didn't do anything, it will return a nullptr or NULL.
	MallocAndFree(10);
	//MallocAndFree(maxT); // print "Failed to allocate memory!"
}