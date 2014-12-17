
%module drawing


%{
#include "shape.h";
%}

%include "std_string.i"
%include "std_vector.i"

%template(VecInt) std::vector<int>;
%include "shape.h";

