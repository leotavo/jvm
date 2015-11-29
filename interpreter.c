// interpreter.c

#include	"interpreter.h"
#include	"opcode.h"
#include	<stdlib.h>

/*==========================================*/
//	INTERPRETADOR
void	interpreter(METHOD_DATA	* method, THREAD * thread, JVM * jvm){
	thread->program_counter = method->bytecodes;
	while(thread->program_counter){	// enquanto houver instruções
		func[* thread->program_counter](method, thread, jvm);
		// OBS: PROGRAM_COUNTER DEVE SER MODIFICADO AO EXECUTAR CADA INSTRUÇÃO, DE ACORDO COM A QUANTIDADE DE OPERANDOS.
	}
}
/*==========================================*/
//	INSTRUÇÕES

// nop		0x00
// Não faz nada.
void	nop_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.nop*/
}

/*	INSTRUÇÕES QUE CARREGAM VALORES NA PILHA	*/
// Tconst	0x01 a 0x0F
//	Carregam constantes na pilha de operandos.
void	Tconst(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.aconst_null*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iconst_i*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lconst_l*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fconst_f*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dconst_d*/
}

// Tipush	0x10 e 0x11
//	carregam inteiros com sinal (short ou byte) na pilha
void	Tipush(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.bipush*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.sipush*/
}

// ldc_		0x12 a 0x14
//	carregam constantes single (int, float, literal string) ou double word (long, double) na pilha
//	tem como argumento um indice de 8 ou 16 bits da constant pool
void	ldc_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldc*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldc_w*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldc2_w*/
}

// Tload	0x15 a 0x2D
//	carregam na pilha valores do vetor de variaveis locais
void	Tload(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.aload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iload_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lload_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fload_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dload_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.aload_n*/
}

// Taload	0x2E a 0x35
//	carregam na pilha valores de arrays referenciados do vetor.
void	Taload(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iaload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.laload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.faload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.daload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.aaload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.baload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.caload*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.saload*/
}

/*	INSTRUÇÕES QUE ARMAZENAM VALORES NO VETOR DE VARIAVEIS LOCAIS	*/

// Tstore	0x36 a 0x4E
// grava valores do topo da pilha no vetor de variaveis locais ou em arrays referenciados no vetor.
void	Tstore(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.istore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lstore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fstore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dstore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.astore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.istore_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lstore_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fstore_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dstore_n*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.astore_n*/
}

// Tastore	0x4F a 0x56
// grava valores do topo da pilha em arrays referenciados no vetor de variaveis locais.
void	Tastore(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iastore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lastore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fastore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dastore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.aastore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.bastore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.castore*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.sastore*/
}

/*	MANIPULAÇÃO DA PILHA	*/

// handleStack	0x57 a 0x5F
// instruções de manipulação da pilha (descarte, duplicação, troca de valores)
void	handleStack(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.pop*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.pop2*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dup*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dup_x1*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dup_x2*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dup2*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dup2_x1*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dup2_x2*/
}

/*	INSTRUÇÕES ARITMETICAS	*/

// Tadd		0x60 a 0x63
//	instruções de adição
void	Tadd(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iadd*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ladd*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fadd*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dadd*/
}

// Tsub		0x64 a 0x67
//	instruções de subtração
void	Tsub(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.isub*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lsub*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fsub*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dsub*/
}

// Tmul		0x68 a 0x6B
//	instruções de multiplicação
void	Tmul(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.imul*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lmul*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fmul*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dmul*/
}

// Tdiv		0x6C a 0x6F
//	instrucoes de divisão
void	Tdiv(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.idiv*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldiv*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fdiv*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ddiv*/
}

// Trem		0x70 a 0x73
//	instruções de resto
void	Trem(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.irem*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lrem*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.frem*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.drem*/
}

/*	INSTRUÇÕES BIT A BIT	*/
// Tneg		0x74 a 0x77
//	Instruções de Negação
void	Tneg(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ineg*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lneg*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fneg*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dneg*/
}

// Tshl		0x78 e 0x79
//	Instruções de Deslocamento à Esquerda
void	Tshl(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ishl*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lshl*/
}

// Tshr		0x7A e 0x7B
//	Instruções de Deslocamento à Direita
void	Tshr(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ishr*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lshr*/
}

// Tushr	0x7C e 0x7D
//	Instruções de Deslocamento à Direita, sem sinal
void	Tushr(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iushr*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lushr*/
}

// Tand		0x7E e 0x7F
//	Instruções And bit a bit
void	Tand(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iand*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.land*/
}

// Tor		0x80 e 0x81
//	Instruções Or bit a bit
void	Tor(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ior*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lor*/
}

// Txor		0x82 e 0x83
//	Instruções Xor bit a bit
void	Txor(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ixor*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lxor*/
}

/*	INCREMENTO	*/

// Tinc		0x84
//	Incremento de variável local
void	Tinc(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iinc*/
}

/*	CONVERSÕES DE TIPOS	*/

// i2T		0x85 a 0x87; 0x91 a 0x93
//	Converte inteiro pra um outro tipo
void	i2T(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.i2l*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.i2f*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.i2d*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.i2b*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.i2c*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.i2s*/
}

// l2T		0x88 a 0x8A
//	Converte long pra um outro tipo
void	l2T(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.l2i*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.l2f*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.l2d*/
}

// f2T		0x8B a 0x8D
//	Converte float pra um outro tipo
void	f2T(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.f2i*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.f2l*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.f2d*/
}

// d2T		0x8E a 0x90
//	Converte double pra um outro tipo
void	d2T(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.d2i*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.d2l*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.d2f*/
}

/*	COMPARAÇÃO	*/

// Tcmp		0x94
//	comparação tipo integral (long)
void	Tcmp(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lcmp*/
}

// TcmpOP	0x95 a 0x98
//	comparação ponto flutuante
void	TcmpOP(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fcmpl*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fcmpg*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dcmpl*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dcmpg*/
}

// ifOP		0x99 a 0x9E
//	compara um valor inteiro com zero, e realiza um jump
void	ifOP(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifeq*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifne*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iflt*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifge*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifgt*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifle*/
}

// if_icmOP	0x9F a 0xA4
//	compara dois valores inteiros, e realiza um jump
void	if_icmOP(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_icmpeq*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_icmpne*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_icmplt*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_icmpge*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_icmpgt*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_icmple*/
}

// if_acmOP	0xA5 e 0xA6
//	compara dois valores do tipo reference.
void	if_acmOP(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_acmpeq*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.if_acmpne*/
}

// jump		0xA7 a 0xA9
//	jumps incondicionais
void	jump(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.goto*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.jsr*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ret*/
}

// switch_	0xAA e 0xAB
//	jump table
void	switch_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.tableswitch*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lookupswitch*/
}

// Treturn	0xAC a 0xB1
//	retorna valor do metodo e retoma a execuçao do método invocador
void	Treturn(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ireturn*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lreturn*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.freturn*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dreturn*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.areturn*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.return*/
}

// accessField	0xB2 a 0xB5
//	manipula fields
void	accessField(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.getstatic*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.putstatic*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.getfield*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.putfield*/
	puts("accessField");
}

// invoke	0xB6 a 0xBA
//	invocação de métodos
void	invoke(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokevirtual*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokespecial*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokestatic*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokeinterface*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokedynamic*/
}

// handleObject	0xBB a 0xBE; 0xC5
//	criação e manipulação de objetos e arrays
void	handleObject(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.new*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.newarray*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.anewarray*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.arraylength*/
}

// athrow	0xBF
//	lançamento de exceções
void	athrow_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.athrow*/
}

// properties	0xC0 e 0xC1
//	checa propriedades de objetos
void	properties(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.checkcast*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.instanceof*/
}

// monitor	0xC2 e 0xC3
//	implementa monitores para objetos (multithreading)
void	monitor(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.monitorenter*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.monitorexit*/
}

// wide		0xC4
//	modifica tamanho de argumentos de certas instruções aritmeticas
void	wide_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.wide*/
}

// ifNull	0xC6 e 0xC7
//	verifica se uma referencia é ou não NULL, e realiza jump
void	ifNull(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifnull*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ifnonnull*/
}

// widejump	0xC8 a 0xC9
//	jumps incondicionais de maior tamanho de offset
void	widejump(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.goto_w*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.jsr_w*/
}

// breakpoint	0xCA
//	(opcode reservado) utilizado por debuggers para implementar breakpoints
void	breakpoint_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.2*/
}

// nonDefined	0xCB a 0xFD
//	faixa de Opcodes não utilizada pela Oracle
void	nonDefined(METHOD_DATA * method, THREAD * thread, JVM * jvm){
	puts("Unknown jvm instruction.");
	exit(EXIT_FAILURE);
}

// impdep	0xFE e 0xFF
//	(opcodes reservados) instruções que provêem backdoors para implementações específicas
void	impdep(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.2*/
}


// ARRAY DE PONTEIROS PRA FUNÇÃO
INSTRUCTION	func[] = {
		// 0x00		nop
		nop_,
		
		// 0x01 a 0x0F	Tconst
		Tconst, Tconst, Tconst, Tconst, Tconst, Tconst, Tconst,Tconst,
		Tconst,	Tconst, Tconst, Tconst, Tconst, Tconst, Tconst,
		
		// 0x10 e 0x11	Tipush
		Tipush, Tipush,
		
		// 0x12 a 0x14	ldc_
		ldc_, ldc_, ldc_,
		
		// 0x15 a 0x2D	Tload
		Tload, Tload, Tload, Tload, Tload, Tload, Tload, Tload, Tload, Tload,
		Tload, Tload, Tload, Tload, Tload, Tload, Tload, Tload, Tload, Tload,
		Tload, Tload, Tload, Tload, Tload,
		
		// 0x2E a 0x35	Taload
		Taload, Taload, Taload, Taload, Taload, Taload, Taload, Taload,
		
		// 0x36 a 0x4E	Tstore
		Tstore, Tstore, Tstore, Tstore, Tstore, Tstore,	Tstore, Tstore, Tstore, Tstore,
		Tstore, Tstore, Tstore, Tstore, Tstore, Tstore,	Tstore, Tstore, Tstore, Tstore,
		Tstore, Tstore, Tstore, Tstore, Tstore, 
		
		// 0x4F a 0x56
		Tastore, Tastore, Tastore, Tastore, Tastore, Tastore, Tastore, Tastore,
		
		// 0x57 a 0x5F
		 handleStack, handleStack, handleStack, handleStack, handleStack, handleStack, handleStack, handleStack, handleStack,
		
		// 0x60 a 0x63
		Tadd, Tadd, Tadd, Tadd,
		
		// 0x64 a 0x67
		Tsub, Tsub, Tsub, Tsub,
		
		// 0x68 a 0x6N
		Tmul, Tmul, Tmul, Tmul,
		
		// 0x6C a 0x6F
		Tdiv, Tdiv, Tdiv, Tdiv,
		
		// 0x70 a 0x73
		Trem, Trem, Trem, Trem,
		
		// 0x74 a 0x77
		Tneg, Tneg, Tneg, Tneg,
		
		// 0x78 e 0x79
		Tshl, Tshl,
		
		// 0x7A e 0x7B
		Tshr, Tshr,
		
		// 0x7C e 0x7D
		Tushr, Tushr,
		
		// 0x7E e 0x7F
		Tand, Tand,
		
		// 0x80 e 0x81
		Tor, Tor,
		
		// 0x82 e 0x83
		Txor, Txor,
		
		// 0x84
		Tinc,
		
		// 0x85 a 0x87
		i2T, i2T, i2T,
		
		// 0x88 a 0x8A
		l2T, l2T, l2T,
		
		// 0x8B a 0x8D
		f2T, f2T, f2T,
		
		// 0x8E a 0x90
		d2T, d2T, d2T,
		
		// 0x91 a 0x93
		i2T, i2T, i2T,
		
		// 0x94
		Tcmp,
		
		// 0x95 a 0x98
		TcmpOP, TcmpOP, TcmpOP, TcmpOP,
		
		// 0x99 a 0x9E
		ifOP, ifOP, ifOP, ifOP, ifOP, ifOP,
		
		// 0x9F a 0xA4
		if_icmOP, if_icmOP, if_icmOP, if_icmOP, if_icmOP, if_icmOP,
		
		// 0xA5 e 0xA6
		if_acmOP, if_acmOP,
		
		// 0xA7, 0xA8, 0xA9
		jump, jump, jump,
		
		// 0xAA e 0xAB
		switch_, switch_,
		
		// 0xAC a 0xB1
		Treturn, Treturn, Treturn, Treturn, Treturn, Treturn,
		
		// 0xB2 a 0xB5
		accessField, accessField, accessField, accessField,
		
		// 0xB6 a 0xBA
		invoke, invoke, invoke, invoke, invoke,
		
		// 0xBB a 0xBE
		handleObject, handleObject, handleObject, handleObject,
		
		// 0xBF
		athrow_,
		
		// 0xC0 e 0xC1
		properties, properties,		
		
		// 0xC2 e 0xC3
		monitor, monitor,
 
		// 0xC4
		wide_,
		
		// 0xC5
		handleObject,
		
		// 0xC6 e 0xC7
		ifNull, ifNull,
		
		// 0xC8 a 0xC9
		widejump, widejump,

		// 0xCA
		breakpoint_,
		
		// 0xCB a 0xFD
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined,	nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined,	nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined, nonDefined, nonDefined, nonDefined,
		nonDefined, nonDefined,	nonDefined, nonDefined, nonDefined,
		nonDefined, 
		
		// 0xFE e 0xFF
		impdep, impdep
};




