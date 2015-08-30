export PATH=~/llvm_dev/build/bin:$PATH

clang -cc1 -internal-isystem ~/llvm_dev/build/lib/clang/3.8.0/include -nostdsysteminc -triple i686-unknown-unknown -emit-llvm -x c ~/llvm_dev/llvm/tools/clang/test/CodeGen/builtins-overflow.c -o test.ll
cat test.ll | FileCheck ~/llvm_dev/llvm/tools/clang/test/CodeGen/builtins-overflow.c

clang -cc1 -Wall -Wno-unused -Werror -fsyntax-only -verify ~/llvm_dev/llvm/tools/clang/test/CodeGen/builtins-overflow-error.c
