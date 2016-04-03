
/**
 * swig -java tools.i
 *
 * gcc -c tools.c tools_wrap.c  -I/Library/Java//JavaVirtualMachines/jdk1.8.0_25.jdk/Contents/Home/include -I/Library/Java//JavaVirtualMachines/jdk1.8.0_25.jdk/Contents/Home/include/darwin/
 *
 * gcc -shared tools.o tools_wrap.o -o libtest.so
 *
 * javac main.java
 *
 * java main
 *
 */

int TestFunction(int a, int b) {
	return *(int*)a;
}

