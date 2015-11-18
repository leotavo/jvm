Compilação:
$ gcc -std=c99 *.c -o jvm

Execução:
Linux
$ ./jvm arquivo.class [args...]
Windows
$ jvm.exe arquivo.class [args...]
args = array de strings, argumento do método main da classe de entrada. (opcional)

Links úteis (Quem tiver algum link útil, coloque aqui):

https://docs.oracle.com/javase/specs/jvms/se6/html/VMSpecTOC.doc.html (Especificação da Oracle)
Item 2.17 - Execução da JVM
Capítulo 3 - Estrutura da JVM
Capítulo 4 - Formato classfile
Capítulo 5 - Loading, Linking e Initializing (JVM)
Capítulo 6 - Conjunto de Instruções da JVM
Capítulo 9 - Mnemônicos dos Opcodes da JVM

http://blog.jamesdbloom.com/JVMInternals.html (arquitetura interna da JVM)
http://blog.jamesdbloom.com/JavaCodeToByteCode_PartOne.html (relação entre código Java e Bytecodes)
https://www.artima.com/insidejvm/ed2/index.html (Inside the Java Virtual Machine by Bill Venners)
http://mentebinaria.com.br/zine/edicoes/1/ClassInjection.txt (explicações em portugues sobre o formato classfile)
http://homepages.inf.ed.ac.uk/kwxm/JVM/codeByNo.html (opcodes por número)