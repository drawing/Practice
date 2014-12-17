
%module modname


%{
#include "Name.h";
%}

%rename("%(lowercamelcase)s", %$isfunction) "";

%include "Name.h";

