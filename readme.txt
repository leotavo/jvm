MASTER ATUALIZADA. FAÇAM CLONE DELA ANTES DE FAZER CÒDIGO NOVO (01/12)
ESCREVAM NO README QUAL FUNCAO VCS ESTAO MEXENDO!!!

Corretude do interpretador:

( ) arrays simples; => Taload, Tastore, handleObject
( ) array length; => handleObject
( ) inteiros; => todas as instruções com byte, char, short, int
( ) floats; => todas as instruções com float
( ) desvios com cat 1; => jump, widejump, ifOP, if_icmOP, if_acmOP, ifnull
( ) recursao; => invoke
( ) metodos estaticos; => invoke
( ) operações de retorno; => Treturn
( ) operações lógicas com cat 1; => Tneg, Tand, Tor, Txor
( ) operações de deslocamento com cat 1; => Tshl, Tshr, Tushr
( ) operações de manipulação de pilha; => Tload, Taload, Tstore, Tastore, Tipush, ldc_, Tconst, accessField, handleStack
( ) iteracao e case => switch_
( ) arrays multidimensionais; => Taload, Tastore, handleObject
( ) arrays de referência; => Taload, Tastore, handleObject
( ) objetos; => handleObject
( ) métodos não estaticos; => invoke
( ) longs; => todas as instruções com long
( ) doubles; = todas as instruções com doubles
( ) operações aritmeticas de cat 2; => Tadd, Tsub, Tmul, Tdiv, Trem.
( ) operações de deslocamento de long; => Tshl, Tshr, Tushr
( ) system.out.println (int, float, string, booleano); => invokespecial
( ) conversao de e para cat 2; => i2T, l2T, f2T, d2T
( ) strings; => ????
( ) interfaces; => ????



(X) leitura do formato .class (30% do interpretador)

opcionais:
- Todas as demais instruções.
( ) threads;
( ) debugs; => breakpoint
( ) chamada às bibliotecas java;
( ) tratamento de exceções; => athrow, try_catch (tratamento de métodos)
( ) checagem dinâmica de tipos; => properties
( ) coletor de lixo; (monitoramento da heap)

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
Treturn => return OK
accessField => (LEO) getstatic e putstatic ok
invoke => (LEO) implementada a resolução e controle de acesso aos métodos.
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