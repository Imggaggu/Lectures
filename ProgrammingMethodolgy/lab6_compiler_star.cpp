#include <iostream>
using namespace std;

int main(){
    cout <<"hello"<<endl;
    for(int i=0; i<5; i++){
      for (int j=0; j<5-i;j++){cout <<" ";}
      cout<<"*";
      for (int j=0; j<i;j++){cout <<"**";}
      cout<<endl;
    }
}
void studentid(){
    cout << "학번..."<<endl;
};

/*

.LC0:
        .string "hello"
.LC1:
        .string " "
.LC2:
        .string "*"
.LC3:
        .string "**"
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     esi, OFFSET FLAT:.LC0
        mov     edi, OFFSET FLAT:std::cout
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)
        mov     esi, OFFSET FLAT:std::basic_ostream<char, std::char_traits<char>>& std::endl<char, std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&)
        mov     rdi, rax
        call    std::ostream::operator<<(std::ostream& (*)(std::ostream&))
        mov     DWORD PTR [rbp-4], 0
        jmp     .L2
.L7:
        mov     DWORD PTR [rbp-8], 0
        jmp     .L3
.L4:
        mov     esi, OFFSET FLAT:.LC1
        mov     edi, OFFSET FLAT:std::cout
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)
        add     DWORD PTR [rbp-8], 1
.L3:
        mov     eax, 5
        sub     eax, DWORD PTR [rbp-4]
        cmp     DWORD PTR [rbp-8], eax
        jl      .L4
        mov     esi, OFFSET FLAT:.LC2
        mov     edi, OFFSET FLAT:std::cout
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)
        mov     DWORD PTR [rbp-12], 0
        jmp     .L5
.L6:
        mov     esi, OFFSET FLAT:.LC3
        mov     edi, OFFSET FLAT:std::cout
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)
        add     DWORD PTR [rbp-12], 1
.L5:
        mov     eax, DWORD PTR [rbp-12]
        cmp     eax, DWORD PTR [rbp-4]
        jl      .L6
        mov     esi, OFFSET FLAT:std::basic_ostream<char, std::char_traits<char>>& std::endl<char, std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&)
        mov     edi, OFFSET FLAT:std::cout
        call    std::ostream::operator<<(std::ostream& (*)(std::ostream&))
        add     DWORD PTR [rbp-4], 1
.L2:
        cmp     DWORD PTR [rbp-4], 4
        jle     .L7
        mov     eax, 0
        leave
        ret
.LC4:
        .string "학번..."
studentid():
        push    rbp
        mov     rbp, rsp
        mov     esi, OFFSET FLAT:.LC4
        mov     edi, OFFSET FLAT:std::cout
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)
        mov     esi, OFFSET FLAT:std::basic_ostream<char, std::char_traits<char>>& std::endl<char, std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&)
        mov     rdi, rax
        call    std::ostream::operator<<(std::ostream& (*)(std::ostream&))
        nop
        pop     rbp
        ret
*/