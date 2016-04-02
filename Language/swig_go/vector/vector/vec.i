%module vector

%include <std_vector.i>


%{
#include <vector>
#include "vec.h"
%}

namespace std {
        %template(vectori) vector<int>;
};


%include "vec.h"

