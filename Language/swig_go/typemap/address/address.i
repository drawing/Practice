
%module address

/* %go_import("net") */

%{
#include <sys/socket.h>
#include <netinet/in.h>
#include "address.h"

%}

%typemap(gotype) struct sockaddr_in "string"

%typemap(out) struct sockaddr_in {
        /* $result = net.Addr{$1}; */
        $result.p = "192.168.1.1:80";
        $result.n = 14;
}

%typemap(in) struct sockaddr_in {
        $1.sin_family = AF_INET;
        $1.sin_addr.s_addr = inet_addr("192.168.1.1");
}

%include "address.h";

