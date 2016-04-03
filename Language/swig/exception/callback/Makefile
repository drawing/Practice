
java:
	mkdir -p com/tencent/shape/
	swig -c++ -java -package com.tencent.shape -outdir com/tencent/shape/ shape.i

lib:java
	g++ -fPIC -c src/shape.cpp -Iinclude
	g++ -fPIC -c shape_wrap.cxx -I/usr/lib/jvm/java-7-openjdk-amd64/include/
	g++ -shared shape.o shape_wrap.o -o libdrawing.so

test:lib
	mkdir jar
	javac -d jar/ -sourcepath . com/tencent/shape/*.java
	jar cf drawing.jar -C jar/ .
	javac -classpath drawing.jar main.java

run:clean test
	java -classpath drawing.jar:. main

clean:
	rm -rf com
	rm -rf jar
	rm -f shape_wrap.cxx
	rm -f shape_wrap.h
	rm -f *.o
	rm -f *.so
	rm -f *.jar
	rm -f *.class
	rm -f drawing_wrap.*
