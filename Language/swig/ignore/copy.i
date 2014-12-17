
%module drawing


%{
#include "Copy.h";
%}

%ignore Copy(const Copy & other);
%include "Copy.h";

