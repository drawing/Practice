
set -x

export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64/

swig -java -c++ tools.i

g++ -c -fPIC tools.cc tools_wrap.cxx -I$JAVA_HOME/include
gcc -shared tools.o tools_wrap.o -o libtest.so

javac main.java

# java main

