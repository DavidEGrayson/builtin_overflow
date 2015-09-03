export PATH=~/llvm_dev/build/bin:$PATH
S=~/llvm_dev/llvm-svn/tools/clang

clang -cc1 -internal-isystem ~/llvm_dev/build/lib/clang/3.8.0/include -nostdsysteminc -triple i686-unknown-unknown -emit-llvm -x c $S/test/CodeGen/builtins-overflow.c -o test.ll
cat test.ll | FileCheck $S/test/CodeGen/builtins-overflow.c

clang -cc1 -Wall -Wno-unused -Werror -fsyntax-only -verify $S/test/CodeGen/builtins-overflow-error.c

clang test.c -o test && ./test
