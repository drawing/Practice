
%module(directors="1") drawing

%feature("director") Shape;

%{
#include "include/shape.h";
%}

%include "std_string.i"

%include "include/shape.h";

