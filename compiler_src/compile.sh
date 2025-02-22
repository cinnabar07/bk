gcc -fwhole-program -static-pie -flto=auto -s -O3 -Wl,-z,relro,-z,now -o compiler $(find | grep '\.c' | grep -v 'lex\.yy\.c' | xargs) -lfl
