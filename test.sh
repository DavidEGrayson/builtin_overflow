~/llvm_dev/build/bin/clang -cc1 -internal-isystem ~/llvm_dev/build/lib/clang/3.8.0/include -nostdsysteminc -triple i686-unknown-unknown -emit-llvm -x c ~/llvm_dev/llvm/tools/clang/test/CodeGen/builtins-overflow.c -o test.ll
cat test.ll | ~/llvm_dev/build/bin/FileCheck ~/llvm_dev/llvm/tools/clang/test/CodeGen/builtins-overflow.c
