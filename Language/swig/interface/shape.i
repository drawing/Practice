
%module(directors="1") drawing

%feature("director") Shape;

%{
#include "include/shape.h";
%}

%include "include/shape.h";

