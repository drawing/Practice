
java:
	mkdir -p com/tencent/shape/
	swig -c++ -java -package com.tencent.shape -outdir com/tencent/shape/ shape.i

lib:java
	g++ -c src/shape.cpp -Iinclude
	g++ -c shape_wrap.cxx -I/Library/Java//JavaVirtualMachines/jdk1.8.0_25.jdk/Contents/Home/include -I/Library/Java//JavaVirtualMachines/jdk1.8.0_25.jdk/Contents/Home/include/darwin/
	g++ -shared shape.o shape_wrap.o -o libdrawing.so

test:lib
	mkdir jar
	javac -d jar/ -sourcepath . com/tencent/shape/*.java
	jar cf drawing.jar -C jar/ .
	javac -classpath drawing.jar main.java

clean:
	rm -rf com
	rm -rf jar
	rm -f shape_wrap.cxx
	rm -f shape_wrap.h
	rm -f *.o
	rm -f *.so
	rm -f *.jar
	rm -f *.class
