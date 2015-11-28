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


SITUAÇÃO ATUAL:
Loading: 
- le o arquivo .class principal, e armazena no tipo classfile;
- cria o class_data dentro da method_area, armazenando as informações do classfile;
- cria uma instância da classe principal, e armazena no heap;
- cria variáveis de classe (static fields) e variáveis de instância;
- verifica erros estruturais no classfile (ausência ou extra bytes, versão suportada)
=> o que falta: 
- Herança (herdar campos e metodos de superclasses) => FAZER EM TEMPO DE EXECUÇÃO, NA CHAMADA DE INSTRUCOES QUE REQUEIRAM FIELDS OU METODOS
- inicializar fields com constant_value; = FAZER EM TEMPO DE EXECUÇÃO

LinkingVerification:
- verifica erros semânticos no classfile (índices para constantpool, descritores corretos, access_flags, atributos corretos)
- verifica se superclasse final não é herdada; (TESTAR)
- verifica se método final não é sobrecarregado; (TESTAR)
- verifica se toda classe (exceto Object) possui uma superclasse
=> o que falta:
- verificar outras regras da linguagem java que possam estar sendo violadas no classfile.
- bytecodeVerifier: // FAZER EM TEMPO DE EXECUÇÃO
-- verificar se as instruções da JVM estao coerentes quanto aos operandos, pilha, vetor de variaveis locais, etc.
-- verificar inicialização de variaveis locais;
-- atribuição de valores à fields
-- metodo invocado com o correto numero e tipo de argumentos;

Initialization: 
- inicializa a superclasse direta;
- executa o método construtor da classe; // IGNORAR O METODO <INIT> de java/lang/Object

Interpreter:
- começa a executar o método main da classe principal

LinkingResolution
- resolve referências simbólicas durante a execução do interpretador





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
