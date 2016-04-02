
%include <std_string.i>

%{
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
%}

%rename(SockAddr) sockaddr_in;

struct in_addr {
        uint32_t s_addr;
};

struct sockaddr_in {
        uint16_t sin_port;
        struct in_addr sin_addr;
};

%extend sockaddr_in {
        std::string String() {
                char res[255] = {};
                const char * ret = inet_ntop(AF_INET, &$self->sin_addr.s_addr, res, sizeof(res));
                if (ret == NULL) {
                        return "";
                }
                sprintf(res, "%s:%u", res, ntohs($self->sin_port));
                return res;
        }
        void Assign(const std::string & addr) {
                sockaddr_in res;
                char buf[255] = {};
                uint32_t port = 0;
                sscanf(addr.c_str(), "%[^:]:%u", buf, &port);
                $self->sin_family = AF_INET;
                $self->sin_addr.s_addr = inet_addr(buf);
                $self->sin_port = htons(uint16_t(port));
        }
};

