
%module test

%{
extern int TestFunction(int a, int b);
%}


%exception {
        try {
                $action
        }
        catch (...) {
                printf("catch exception:%s\n", "$fulldecl");
                SWIG_JavaThrowException(jenv, SWIG_JavaUnknownError, "catch exception");
        }
}

extern int TestFunction(int a, int b);

