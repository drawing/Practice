
%module(directors="1") drawing

%feature("director") Shape;

%{
#include "include/shape.h"
%}

%feature("director:except") {
        jthrowable $error = jenv->ExceptionOccurred();
        if ($error) {
                jenv->ExceptionDescribe();
                jenv->ExceptionClear();
                printf("ERROR: %s:%u catch a java exception\n", __FILE__, __LINE__);
        }
}

%include "std_string.i"

%include "include/shape.h";

