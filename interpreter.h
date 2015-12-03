// interpreter.h

#ifndef	INTERPRETER_H
#define	INTERPRETER_H

#include	"jvm.h"

//Chapter 7. Opcode Mnemonics by Opcode
//https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-7.html

// 2.11. Instruction Set Summary
// https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-2.html#jvms-2.11

//6.5. Instructions => AKI TEM UMA EXPLICAÇÃO DETALHADA DE CADA INSTRUÇÃO
//https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5


// TIPO DE PONTEIRO PRA FUNÇÃO QUE VAI EXECUTAR A RESPECTIVA INSTRUÇÃO DA JVM
typedef 	void (*INSTRUCTION)(METHOD_DATA *, THREAD *, JVM *);

// ARRAY DE PONTEIROS PRA FUNÇÕES
extern	INSTRUCTION	func[];

// INTERPRETADOR DE BYTECODES
void	interpreter(METHOD_DATA	*, THREAD *, JVM * jvm);

void	printStack(THREAD *);

/*==========================================*/
//	INSTRUÇÕES

// nop		0x00
// Não faz nada.
void	nop_(METHOD_DATA *, THREAD *, JVM *);

/*	INSTRUÇÕES QUE CARREGAM VALORES NA PILHA	*/

// Tconst	0x01 a 0x0F
//	Carregam constantes na pilha de operandos.
void	Tconst(METHOD_DATA *, THREAD *, JVM *);

// Tipush	0x10 e 0x11
//	carregam inteiros com sinal (short ou byte) na pilha
void	Tipush(METHOD_DATA *, THREAD *, JVM *);

// ldc_		0x12 a 0x14
//	carregam constantes single (int, float, literal string) ou double word (long, double) na pilha
//	tem como argumento um indice de 8 ou 16 bits da constant pool
void	ldc_(METHOD_DATA *, THREAD *, JVM *);

// Tload	0x15 a 0x2D
//	carregam na pilha valores do vetor de variaveis locais
void	Tload(METHOD_DATA *, THREAD *, JVM *);

// Taload	0x2E a 0x35
//	carregam na pilha valores de arrays referenciados do vetor.
void	Taload(METHOD_DATA *, THREAD *, JVM *);

/*	INSTRUÇÕES QUE ARMAZENAM VALORES NO VETOR DE VARIAVEIS LOCAIS	*/

// Tstore	0x36 a 0x4E
// grava valores do topo da pilha no vetor de variaveis locais ou em arrays referenciados no vetor.
void	Tstore(METHOD_DATA *, THREAD *, JVM *);

// Tastore	0x4F a 0x56
// grava valores do topo da pilha em arrays referenciados no vetor de variaveis locais.
void	Tastore(METHOD_DATA *, THREAD *, JVM *);

/*	MANIPULAÇÃO DA PILHA	*/

// handleStack	0x57 a 0x5F
// instruções de manipulação da pilha (descarte, duplicação, troca de valores)
void	handleStack(METHOD_DATA *, THREAD *, JVM *);

/*	INSTRUÇÕES ARITMETICAS	*/

// Tadd		0x60 a 0x63
//	instruções de adição
void	Tadd(METHOD_DATA *, THREAD *, JVM *);

// Tsub		0x64 a 0x67
//	instruções de subtração
void	Tsub(METHOD_DATA *, THREAD *, JVM *);

// Tmul		0x68 a 0x6B
//	instruções de multiplicação
void	Tmul(METHOD_DATA *, THREAD *, JVM *);

// Tdiv		0x6C a 0x6F
//	instrucoes de divisão
void	Tdiv(METHOD_DATA *, THREAD *, JVM *);

// Trem		0x70 a 0x73
//	instruções de resto
void	Trem(METHOD_DATA *, THREAD *, JVM *);

/*	INSTRUÇÕES BIT A BIT	*/
// Tneg		0x74 a 0x77
//	Instruções de Negação
void	Tneg(METHOD_DATA *, THREAD *, JVM *);

// Tshl		0x78 e 0x79
//	Instruções de Deslocamento à Esquerda
void	Tshl(METHOD_DATA *, THREAD *, JVM *);

// Tshr		0x7A e 0x7B
//	Instruções de Deslocamento à Direita
void	Tshr(METHOD_DATA *, THREAD *, JVM *);

// Tushr	0x7C e 0x7D
//	Instruções de Deslocamento à Direita, sem sinal
void	Tushr(METHOD_DATA *, THREAD *, JVM *);

// Tand		0x7E e 0x7F
//	Instruções And bit a bit
void	Tand(METHOD_DATA *, THREAD *, JVM *);

// Tor		0x80 e 0x81
//	Instruções Or bit a bit
void	Tor(METHOD_DATA *, THREAD *, JVM *);

// Txor		0x82 e 0x83
//	Instruções Xor bit a bit
void	Txor(METHOD_DATA *, THREAD *, JVM *);

/*	INCREMENTO	*/

// Tinc		0x84
//	Incremento de variável local
void	Tinc(METHOD_DATA *, THREAD *, JVM *);

/*	CONVERSÕES DE TIPOS	*/

// i2T		0x85 a 0x87; 0x91 a 0x93
//	Converte inteiro pra um outro tipo
void	i2T(METHOD_DATA *, THREAD *, JVM *);

// l2T		0x88 a 0x8A
//	Converte long pra um outro tipo
void	l2T(METHOD_DATA *, THREAD *, JVM *);

// f2T		0x8B a 0x8D
//	Converte float pra um outro tipo
void	f2T(METHOD_DATA *, THREAD *, JVM *);

// d2T		0x8E a 0x90
//	Converte double pra um outro tipo
void	d2T(METHOD_DATA *, THREAD *, JVM *);

/*	COMPARAÇÃO	*/

// Tcmp		0x94
//	comparação tipo integral (long)
void	Tcmp(METHOD_DATA *, THREAD *, JVM *);

// TcmpOP	0x95 a 0x98
//	comparação ponto flutuante
void	TcmpOP(METHOD_DATA *, THREAD *, JVM *);

// ifOP		0x99 a 0x9E
//	compara um valor inteiro com zero, e realiza um jump
void	ifOP(METHOD_DATA *, THREAD *, JVM *);

// if_icmOP	0x9F a 0xA4
//	compara dois valores inteiros, e realiza um jump
void	if_icmOP(METHOD_DATA *, THREAD *, JVM *);

// if_acmOP	0xA5 e 0xA6
//	compara dois valores do tipo reference.
void	if_acmOP(METHOD_DATA *, THREAD *, JVM *);

// jump		0xA7 a 0xA9
//	jumps incondicionais
void	jump(METHOD_DATA *, THREAD *, JVM *);

// switch_	0xAA e 0xAB
//	jump table
void	switch_(METHOD_DATA *, THREAD *, JVM *);

// Treturn	0xAC a 0xB1
//	retorna valor do metodo e retoma a execuçao do método invocador
void	Treturn(METHOD_DATA *, THREAD *, JVM *);

// accessField	0xB2 a 0xB5
//	manipula fields
void	accessField(METHOD_DATA *, THREAD *, JVM *);

// invoke	0xB6 a 0xBA
//	invocação de métodos
void	invoke(METHOD_DATA *, THREAD *, JVM *);

// handleObject	0xBB a 0xBE; 0xC5
//	criação e manipulação de objetos e arrays
void	handleObject(METHOD_DATA *, THREAD *, JVM *);

// athrow	0xBF
//	lançamento de exceções
void	athrow(METHOD_DATA *, THREAD *, JVM *);

// properties	0xC0 e 0xC1
//	checa propriedades de objetos
void	properties(METHOD_DATA *, THREAD *, JVM *);

// monitor	0xC2 e 0xC3
//	implementa monitores para objetos (multithreading)
void	monitor(METHOD_DATA *, THREAD *, JVM *);

// wide		0xC4
//	modifica tamanho de argumentos de certas instruções aritmeticas
void	wide_(METHOD_DATA *, THREAD *, JVM *);

// ifNull	0xC6 e 0xC7
//	verifica se uma referencia é ou não NULL, e realiza jump
void	ifNull(METHOD_DATA *, THREAD *, JVM *);

// widejump	0xC8 a 0xC9
//	jumps incondicionais de maior tamanho de offset
void	widejump(METHOD_DATA *, THREAD *, JVM *);

// breakpoint	0xCA
//	(opcode reservado) utilizado por debuggers para implementar breakpoints
void	breakpoint_(METHOD_DATA *, THREAD *, JVM *);

// nonDefined	0xCB a 0xFD
//	faixa de Opcodes não utilizada pela Oracle
void	nonDefined(METHOD_DATA *, THREAD *, JVM *);

// impdep	0xFE e 0xFF
//	(opcodes reservados) instruções que provêem backdoors para implementações específicas
void	impdep(METHOD_DATA *, THREAD *, JVM *);

#endif
