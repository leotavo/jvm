RECADOS: 


MASTER ATUALIZADA. FAÇAM CLONE DELA ANTES DE FAZER CÒDIGO NOVO (01/12)
ESCREVAM NO README QUAL FUNCAO VCS ESTAO MEXENDO!!!

SITUAÇÃO ATUAL:

Interpreter:
FALTA:
Tstore
Tastore
Tmul
Tdiv
Trem
Tneg
Tshl
Tshr
Tushr
Tand
Tor
Txor
Tinc
i2T
l2T
f2T
d2T
Tcmp
TcmpOP
ifOP
if_icmOP
if_acmOP
jump
switch_
Treturn
accessField => LEO
invoke
handleObject
athrow_
properties
monitor
ifnull
widejump
breakpoint
nonDefined
impdep


Loading: 
=> o que falta: 
- Herança (herdar campos e metodos de superclasses) => FAZER EM TEMPO DE EXECUÇÃO, NA CHAMADA DE INSTRUCOES QUE REQUEIRAM FIELDS OU METODOS
- inicializar fields com constant_value; = FAZER EM TEMPO DE EXECUÇÃO

LinkingVerification:
=> o que falta:
- verificar outras regras da linguagem java que possam estar sendo violadas no classfile.
- bytecodeVerifier: // FAZER EM TEMPO DE EXECUÇÃO
-- verificar se as instruções da JVM estao coerentes quanto aos operandos, pilha, vetor de variaveis locais, etc.
-- verificar inicialização de variaveis locais;
-- atribuição de valores à fields
-- metodo invocado com o correto numero e tipo de argumentos;


LinkingResolution
- resolve referências simbólicas durante a execução do interpretador


Compilação:
$ gcc -std=c99 *.c -o jvm

Execução:
Linux
$ ./jvm arquivo.class [args...]
Windows
$ jvm.exe arquivo.class [args...]
args = array de strings, argumento do método main da classe de entrada. (opcional)

Testes Prontos:
Linux
$ ./teste.sh


Links úteis (Quem tiver algum link útil, coloque aqui):

https://docs.oracle.com/javase/specs/jvms/se6/html/VMSpecTOC.doc.html (Especificação da Oracle)
Item 2.17 - Execução da JVM
Capítulo 3 - Estrutura da JVM
Capítulo 4 - Formato classfile
Capítulo 5 - Loading, Linking e Initializing (JVM)
Capítulo 6 - Conjunto de Instruções da JVM
Capítulo 9 - Mnemônicos dos Opcodes da JVM

http://www.cs.cornell.edu/courses/cs2112/2012sp/lectures/lec27-12sp.pdf
http://blog.jamesdbloom.com/JVMInternals.html (arquitetura interna da JVM)
http://blog.jamesdbloom.com/JavaCodeToByteCode_PartOne.html (relação entre código Java e Bytecodes)
https://www.artima.com/insidejvm/ed2/index.html (Inside the Java Virtual Machine by Bill Venners)
http://mentebinaria.com.br/zine/edicoes/1/ClassInjection.txt (explicações em portugues sobre o formato classfile)
http://homepages.inf.ed.ac.uk/kwxm/JVM/codeByNo.html (opcodes por número)