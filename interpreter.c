// interpreter.c

#include	"interpreter.h"
#include	"classreader.h"
#include	"opcode.h"
#include	<stdlib.h>
#include	<string.h>


/*	ARQUIVOS DE TESTE
nop_
	nao definido
Tconst e Tstore
	Exemplos/Tconst_Tstore.class
Tipush
	Exemplos/Tipush.class
ldc_
	Exemplos/ldc_class
*/

int	isWide = 0;

//Chapter 7. Opcode Mnemonics by Opcode
//https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-7.html

// 2.11. Instruction Set Summary
// https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-2.html#jvms-2.11

//6.5. Instructions => AKI TEM UMA EXPLICAÇÃO DETALHADA DE CADA INSTRUÇÃO
//https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5

/*==========================================*/
//	INTERPRETADOR
void	interpreter(METHOD_DATA	* method, THREAD * thread, JVM * jvm){
	thread->program_counter = method->bytecodes;
	printf("PC\tOPCODE");
	while(thread->program_counter < (method->bytecodes + method->code_length)){	// enquanto houver instruções
		printf("\n%" PRIu8 "\t%s", thread->program_counter - method->bytecodes, opcodes[* thread->program_counter]);
		func[* thread->program_counter](method, thread, jvm);
		// OBS: PROGRAM_COUNTER DEVE SER MODIFICADO AO EXECUTAR CADA INSTRUÇÃO, DE ACORDO COM A QUANTIDADE DE OPERANDOS.
	}
}

void	printStack(THREAD * thread){
	printf("Topo = %" PRIu32 "; 0x%" PRIX32, ((thread->jvm_stack)->operand_stack)->value, ((thread->jvm_stack)->operand_stack)->value);
}

/*==========================================*/
//	INSTRUÇÕES

// nop		0x00
// Não faz nada.
void	nop_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.nop*/
	thread->program_counter++;
}

/*	INSTRUÇÕES QUE CARREGAM VALORES NA PILHA	*/
// Tconst	0x01 a 0x0F
//	Carregam constantes na pilha de operandos.
void	Tconst(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.aconst_null*/	// Tconst_Tstore.class
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iconst_i*/	// Tconst_Tstore.class
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lconst_l*/	// Tconst_Tstore.class
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fconst_f*/	// Tconst_Tstore.class
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dconst_d*/	// Tconst_Tstore.class
	OPERAND		* operand = (OPERAND *) malloc(sizeof(OPERAND));
	u4		* value = (u4*) malloc(sizeof(u4));
	float		f = 0.0;
	switch(*thread->program_counter){
		case aconst_null:
		case iconst_m1:
		case iconst_0:
		case iconst_1:
		case iconst_2:
		case iconst_3:
		case iconst_4:
		case iconst_5:
			if(*thread->program_counter == aconst_null){
				value = NULL;
			}
			else if(*thread->program_counter == iconst_m1){
				*value = -1;
			}
			else if(*thread->program_counter == iconst_0){
				*value = 0;
			}
			else if(*thread->program_counter == iconst_1){
				*value = 1;
			}
			else if(*thread->program_counter == iconst_2){
				*value = 2;
			}
			else if(*thread->program_counter == iconst_3){
				*value = 3;
			}
			else if(*thread->program_counter == iconst_4){
				*value = 4;
			}
			else if(*thread->program_counter == iconst_5){
				*value = 5;
			}
			
			if(!value){
				operand->value = (u4) value;
			}
			else{
				operand->value = *value;
			}
/*			printf("value = %" PRIX32 "\n", operand->value);*/

			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			
			break;
		case lconst_0:
		case lconst_1:
				*value = 0;
			if(*thread->program_counter == lconst_1){
				*value = 1;
			}
			operand->value = 0;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			break;
		case fconst_0:
		case fconst_1:
		case fconst_2:
			if(*thread->program_counter == fconst_1){
				f = 1.0;
			}
			else if(*thread->program_counter == fconst_2){
				f = 2.0;
			}
			memcpy(value, &f, sizeof(u4));

			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			break;
		case dconst_0:
		case dconst_1:
			*value = 0x00000000;
			if(*thread->program_counter == dconst_1){
				*value = 0x3FF00000;
			}

			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			*value = 0x00000000;

			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			break;
	}
	thread->program_counter++;
/*	free(operand);*/
	free(value);
}

// Tipush	0x10 e 0x11
//	carregam inteiros com sinal (short ou byte) na pilha
void	Tipush(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.bipush*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.sipush*/
	OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));
	u4 *value = (u4*) malloc(sizeof(u4));
	u1 high;
	u1 low;
	s1 aux1;
	s2 aux2;
	switch(*thread->program_counter){
		case bipush:
			thread->program_counter++;
			aux1 = (s1) *(thread->program_counter);
			*value = (u4) aux1;
			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case sipush:
			thread->program_counter++;
			high = *(thread->program_counter);
			thread->program_counter++;
			low = *(thread->program_counter);
			aux2 = high;
			aux2 <<= 8;
			aux2 |= low;
			*value = (u4) aux2;
			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			thread->program_counter++;
			break;
	}
/*	free(operand);*/
	free(value);
}

// ldc_		0x12 a 0x14
//	carregam constantes single (int, float, literal string) ou double word (long, double) na pilha
//	tem como argumento um indice de 8 ou 16 bits da constant pool
void	ldc_(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldc*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldc_w*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ldc2_w*/
	OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));
	u4 *value = (u4*) malloc(sizeof(u4));
	u1 high, low;
	u2 string_index, index;
	cp_info	* cp, * cp_aux;
	char * string;
	float f;
	switch(*thread->program_counter)
	{
	case ldc:
	case ldc_w:
	case ldc2_w:
		if(*thread->program_counter == ldc){
			thread->program_counter++;
			index = (u2) *(thread->program_counter);
		}else if(*thread->program_counter == ldc_w || *thread->program_counter == ldc2_w){
			thread->program_counter++;
			high = *(thread->program_counter);
			thread->program_counter++;
			low = *(thread->program_counter);

			index = high;
			index <<= 8;
			index |= low;
		}
		cp = (thread->jvm_stack)->current_constant_pool + index - 1;
		switch(cp->tag)
		{
			case (CONSTANT_Integer):
			case (CONSTANT_Float):
				*value = cp->u.Integer_Float.bytes;
				operand->value = *value;
				operand->prox = (thread->jvm_stack)->operand_stack;
				(thread->jvm_stack)->operand_stack = operand;
				break;
			case (CONSTANT_String):
				cp_aux = (thread->jvm_stack)->current_constant_pool + cp->u.String.string_index - 1;
				string = (char *) cp_aux->u.Utf8.bytes;
				string[cp_aux->u.Utf8.length] = '\0';
				*value = (u4) string;
				operand->value = *value;
				operand->prox = (thread->jvm_stack)->operand_stack;
				(thread->jvm_stack)->operand_stack = operand;
				break;
			case (CONSTANT_Long):
			case (CONSTANT_Double):
				*value = cp->u.Long_Double.high_bytes;
				operand->value = *value;
				operand->prox = (thread->jvm_stack)->operand_stack;
				(thread->jvm_stack)->operand_stack = operand;

				*value = cp->u.Long_Double.low_bytes;
				operand->value = *value;
				operand->prox = (thread->jvm_stack)->operand_stack;
				(thread->jvm_stack)->operand_stack = operand;

				break;
			default:
				printf("Indice invalido.\n");
				exit(1);
				break;
		}
		thread->program_counter++;
		break;
	}
/*	free(operand);*/
	free(value);
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
	OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));
	
	u2 index;
	u4 *value = (u4*) malloc(sizeof(u4));
	switch(*thread->program_counter){
		case iload:
		case lload:
		case fload:
		case dload:
		case aload:
			index = (u2) *(thread->program_counter + 1);
			if (isWide){
				index = index << 8;
				thread->program_counter++;
				index = index | *(thread->program_counter);
				isWide = 0;
			}
			*value = (thread->jvm_stack)->local_variables[index];
	
			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
	
			if(*thread->program_counter == lload || *thread->program_counter == dload){
				*value = (thread->jvm_stack)->local_variables[index + 1];
	
				operand->value = *value;
				operand->prox = (thread->jvm_stack)->operand_stack;
				(thread->jvm_stack)->operand_stack = operand;
			}
	
			thread->program_counter++;
			break;
		case iload_0:
		case iload_1:
		case iload_2:
		case iload_3:
		case fload_0:
		case fload_1:
		case fload_2:
		case fload_3:
		case aload_0:
		case aload_1:
		case aload_2:
		case aload_3:
			if(*thread->program_counter == iload_0 || 
			*thread->program_counter == fload_0 || 
			*thread->program_counter == aload_0){
				index = 0;
			}
			else if(*thread->program_counter == iload_1 ||
			*thread->program_counter == fload_1 ||
			*thread->program_counter == aload_1){
				index = 1;
			}
			else if(*thread->program_counter == iload_2 ||
			*thread->program_counter == fload_2 ||
			*thread->program_counter == aload_2){
				index = 2;
			}
			else if(*thread->program_counter == iload_3 ||
			*thread->program_counter == fload_3 ||
			*thread->program_counter == aload_3){
				index = 3;
			}
			*value = (thread->jvm_stack)->local_variables[index];
			
			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			
			
			thread->program_counter++;
			break;
		case lload_0:
		case lload_1:
		case lload_2:
		case lload_3:
		case dload_0:
		case dload_1:
		case dload_2:
		case dload_3:
			if(*thread->program_counter == lload_0 ||
			 *thread->program_counter == dload_0){
				index = 0;
			}
			else if(*thread->program_counter == lload_1 ||
			 *thread->program_counter == dload_1){
				index = 1;
			}
			else if(*thread->program_counter == lload_2 ||
			 *thread->program_counter == dload_2){
				index = 2;
			}
			else if(*thread->program_counter == lload_3 ||
			 *thread->program_counter == dload_3){
				index = 3;
			}
			*value = (thread->jvm_stack)->local_variables[index];

			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			*value = (thread->jvm_stack)->local_variables[index + 1];

			operand->value = *value;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			thread->program_counter++;
			break;
	}
/*	printStack(thread);*/
/*	free(operand);*/
	free(value);
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
	OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));
	thread->program_counter++;
	u2 index;
	index = (u1) *(thread->program_counter);
	u4 *value = (u4*) malloc(sizeof(u4));
	void *reference;
	u4 f;
	switch(*thread->program_counter){
		case iaload:
		case faload:
		case aaload:
		case baload:
		case caload:
		case saload:
			// get index from operand_stack
			index = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			(thread->jvm_stack)->operand_stack = operand;
			//get reference from operand_stack
			reference = (void *)(thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			(thread->jvm_stack)->operand_stack = operand;
			//push array element into the operand_stack;
			if(*thread->program_counter == iaload || *thread->program_counter == aaload){
				operand->value = ((u4 *)reference)[index];
			}
			else if(*thread->program_counter == faload){
				memcpy(&f, &((float *)reference)[index], sizeof(u4));
				operand->value = f;
			}
			else if(*thread->program_counter == caload || *thread->program_counter == saload){
				operand->value = (u4)(((u2 *)reference)[index]);
			}
			else if(*thread->program_counter == baload){
				operand->value = (u4)(((u1 *)reference)[index]);
			}
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			thread->program_counter++;
			break;

		case laload:
		case daload:
			// get index from operand_stack
			index = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			(thread->jvm_stack)->operand_stack = operand;
			//get reference from operand_stack
			reference = (void *)(thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			(thread->jvm_stack)->operand_stack = operand;
			//push array element into the operand_stack;
			operand->value = ((u4 *)reference)[index];
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			operand->value = ((u4 *)reference)[index + 1];
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			thread->program_counter++;
			break;
	}
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
	switch(*thread->program_counter){
		case	istore:
		case	lstore:
		case	fstore:
		case	dstore:
		case	astore:
			thread->program_counter += 2;
			break;
		case	istore_0:
		case	istore_1:
		case	istore_2:
		case	istore_3:
		case	lstore_0:
		case	lstore_1:
		case	lstore_2:
		case	lstore_3:
		case	fstore_0:
		case	fstore_1:
		case	fstore_2:
		case	fstore_3:
		case	dstore_0:
		case	dstore_1:
		case	dstore_2:
		case	dstore_3:
		case	astore_0:
		case	astore_1:
		case	astore_2:
		case	astore_3:
			thread->program_counter++;
			break;
		
	}
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
	thread->program_counter++;
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
	thread->program_counter++;
}

/*	INSTRUÇÕES ARITMETICAS	*/

// Tadd		0x60 a 0x63
//	instruções de adição
void	Tadd(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.iadd*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.ladd*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fadd*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dadd*/
	int32_t first_operand, second_operand;
	int64_t oper1, oper2, *aux3d;
	float *aux1f, *aux2f;
	double *aux1d, *aux2d;
	u4 value, aux1, aux2, *aux3f, aux4d, aux5d;
	OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));

	switch(*thread->program_counter) {
		// INSTRUÇÃO IADD
		case iadd:
			// Desempilha operando
			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			first_operand = (int32_t) value;
			// Desempilha operando
			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			second_operand = (int32_t) value;
			// Empilha soma
			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = first_operand + second_operand;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case ladd:

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux2 = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			oper1 = (signed)(int32_t) value;

			oper1 = oper1 << 32;
			oper1 |= aux2;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux2 = (signed)(int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			oper2 = (signed)(int32_t) value;

			oper2 = oper2 << 32;
			oper2 |= aux2;
			oper1 = oper2 + oper1;
			aux1 = oper1 >> 32;

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux1;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			aux1 = oper1 & 0xffffffff;

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux1;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case fadd:

			aux3f = malloc(sizeof(u4));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3f = (int32_t) value;

			aux1f = malloc(sizeof(float));
			memcpy(aux1f, aux3f, sizeof(u4));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3f = (int32_t) value;

			aux2f = malloc(sizeof(float));
			memcpy(aux2f, aux3f, sizeof(u4));

			*aux1f = *aux1f + *aux2f;
			memcpy(aux3f, aux1f, sizeof(u4));

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = *aux3f;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case dadd:

			aux3d = malloc(sizeof(int64_t));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux5d = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3d = (int32_t) value;

			*aux3d = *aux3d << 32;
			*aux3d |= aux5d;

			aux1d = malloc(sizeof(double));
			memcpy(aux1d, aux3d, sizeof(double));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux5d = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3d = (int32_t) value;

			*aux3d = *aux3d << 32;
			*aux3d |= aux5d;

			aux2d = malloc(sizeof(double));
			memcpy(aux2d, aux3d, sizeof(double));
			*aux1d = *aux1d + *aux2d;
			memcpy(aux3d, aux1d, sizeof(double));
			aux4d = *aux3d >> 32;

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux4d;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			aux4d = *aux3d & 0xffffffff;
			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux4d;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
	}
}

// Tsub		0x64 a 0x67
//	instruções de subtração
void	Tsub(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.isub*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.lsub*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.fsub*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.dsub*/
	int32_t first_operand, second_operand;
	int64_t oper1, oper2, *aux3d;
	float *aux1f, *aux2f;
	double *aux1d, *aux2d;
	u4 value, aux1, aux2, *aux3f, aux4d, aux5d;
	OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));

	switch(*thread->program_counter) {
		// INSTRUÇÃO IADD
		case isub:
			// Desempilha operando
			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			first_operand = (int32_t) value;
			// Desempilha operando
			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			second_operand = (int32_t) value;
			// Empilha soma
			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = second_operand - first_operand;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case lsub:

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux2 = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			oper1 = (signed)(int32_t) value;

			oper1 = oper1 << 32;
			oper1 |= aux2;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux2 = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			oper2 = (signed)(int32_t) value;

			oper2 = oper2 << 32;
			oper2 |= aux2;
			oper1 = oper2 - oper1;
			aux1 = oper1 >> 32;

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux1;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			aux1 = oper1 & 0xffffffff;

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux1;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case fadd:

			aux3f = malloc(sizeof(u4));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3f = (int32_t) value;

			aux1f = malloc(sizeof(float));
			memcpy(aux1f, aux3f, sizeof(u4));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3f = (int32_t) value;

			aux2f = malloc(sizeof(float));
			memcpy(aux2f, aux3f, sizeof(u4));

			*aux1f = *aux2f - *aux1f;
			memcpy(aux3f, aux1f, sizeof(u4));

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = *aux3f;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
		case dadd:

			aux3d = malloc(sizeof(int64_t));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux5d = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3d = (int32_t) value;

			*aux3d = *aux3d << 32;
			*aux3d |= aux5d;

			aux1d = malloc(sizeof(double));
			memcpy(aux1d, aux3d, sizeof(double));

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			aux5d = (int32_t) value;

			value = (thread->jvm_stack)->operand_stack->value;
			(thread->jvm_stack)->operand_stack = (thread->jvm_stack)->operand_stack->prox;
			*aux3d = (int32_t) value;

			*aux3d = *aux3d << 32;
			*aux3d |= aux5d;

			aux2d = malloc(sizeof(double));
			memcpy(aux2d, aux3d, sizeof(double));
			*aux1d = *aux2d - *aux1d;
			memcpy(aux3d, aux1d, sizeof(double));
			aux4d = *aux3d >> 32;

			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux4d;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;

			aux4d = *aux3d & 0xffffffff;
			operand = (OPERAND *) malloc(sizeof(OPERAND));
			operand->value = aux4d;
			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
			thread->program_counter++;
			break;
	}

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
	thread->program_counter += 3;
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
	thread->program_counter += 3;
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
	thread->program_counter += 3;
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
	switch(* thread->program_counter){// PARA TESTAR O HELLOWORLD
		case	return_:;
			// retorna a execução ao método invocador;
			FRAME	*	aux = thread->jvm_stack;
			thread->jvm_stack = (thread->jvm_stack)->prox;
			free(aux->local_variables);
			if(aux->operand_stack){
				free(aux->operand_stack);
			}
			free(aux);
			break;
	}
	thread->program_counter += method->code_length;
}

// accessField	0xB2 a 0xB5
//	manipula fields
void	accessField(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.getstatic*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.putstatic*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.getfield*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.putfield*/

	if((method->bytecodes + method->code_length - 2) <= thread->program_counter){
		puts("VerifyError: instrução sem a quantidade de argumentos correta.");
		exit(EXIT_FAILURE);
	}
	
	u1	indexbyte1 = *(thread->program_counter + 1);
	u1	indexbyte2 = *(thread->program_counter + 2);
	u2	index = (indexbyte1 << 8) | indexbyte2;
	printf("\t%" PRIu16, index);
	// RESOLUÇÃO DO FIELD
		// Nome da classe do field
	cp_info	* cp_aux = (thread->jvm_stack)->current_constant_pool;
	cp_aux = cp_aux + index - 1; // falta verificar se o indice está nos limites da constant pool
	cp_aux = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Ref.class_index - 1;
	cp_info	* cp_class_name = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Class.name_index - 1;
/*	printf("field_class_name: ");*/
/*	PrintConstantUtf8(cp_class_name, stdout);*/
	

		// nome do field
	cp_aux = (thread->jvm_stack)->current_constant_pool;
	cp_aux = cp_aux + index - 1;
	cp_aux = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Ref.name_and_type_index - 1;
	cp_info	* cp_field_name = (thread->jvm_stack)->current_constant_pool + cp_aux->u.NameAndType.name_index - 1;
/*	printf("\nfield_name: ");*/
/*	PrintConstantUtf8(cp_field_name, stdout);*/

		
		// descritor do field
	cp_info * cp_field_descriptor = (thread->jvm_stack)->current_constant_pool + cp_aux->u.NameAndType.descriptor_index - 1;
/*	printf("\nfield_descriptor: ");*/
/*	PrintConstantUtf8(cp_field_descriptor, stdout);*/
/*	puts("");*/
	
	// CONTROLE DE ACESSO
	u1	* backupPC = thread->program_counter;
	CLASS_DATA	* field_class = getClass(cp_class_name, jvm);
	if(!field_class){// se a classe do field não foi carregada
		char	* class_name = cp_class_name->u.Utf8.bytes;
		class_name[cp_class_name->u.Utf8.length] = '\0';
		puts("");
		classLoading(strcat(class_name, ".class"), &field_class, method->class_data, jvm);
		classLinking(field_class, jvm);
		classInitialization(field_class, jvm, thread);
		thread->program_counter = backupPC;
		printf("\nResume %s\n", opcodes[*thread->program_counter]);
	}
	else{
		if(field_class != method->class_data){// Se o Field não for da mesma classe
			// verifica se a classe do field é acessível pelo método corrente	
			if(!(field_class->modifiers & ACC_PUBLIC) &
			(field_class->classloader_reference != (method->class_data)->classloader_reference)){
				puts("IllegalAccessError: acesso indevido à classe ou interface.");
				exit(EXIT_FAILURE);
			}
		}
	}	

	VARIABLE	* var = getClassVariable(cp_field_name, field_class);
	
	if(!var){
		puts("NoSuchFieldError");
		exit(EXIT_FAILURE);
	}
	
	switch(* thread->program_counter){
		case	getstatic:;
			OPERAND	* operand = (OPERAND *) malloc(sizeof(OPERAND));
			switch((var->value).type){
				case	BYTE:
					operand->value = (s4) (var->value).u.Byte.byte;
					break;
				case	CHAR:
					operand->value = (u4) (var->value).u.Char.char_;
					break;
				case	FLOAT:
					operand->value = (u4) (var->value).u.Float.float_;
					break;
				case	INT:
					operand->value = (s4) (var->value).u.Integer.integer;
					break;
				case	REF_INST:
					operand->value = (u4) (var->value).u.ArrayReference.reference;
					break;
				case	SHORT:
					operand->value = (s4) (var->value).u.Short.short_;
					break;
				case	BOOLEAN:
					operand->value = (u4) (var->value).u.Boolean.boolean;
					break;
				case	REF_ARRAY:
					operand->value = (u4) (var->value).u.InstanceReference.reference;
					break;
				case	DOUBLE:
				case	LONG:;
					OPERAND	* operand2 = (OPERAND *) malloc(sizeof(OPERAND));
					if((var->value).type == DOUBLE){
						operand2->value = (u4) (var->value).u.Double.high_bytes;
						operand->value = (u4) (var->value).u.Double.low_bytes;				
					}
					else{
						operand2->value = (u4) (var->value).u.Long.high_bytes;
						operand->value = (u4) (var->value).u.Long.low_bytes;	
					}
					operand2->prox = (thread->jvm_stack)->operand_stack;
					(thread->jvm_stack)->operand_stack = operand;
					printf("value = %" PRIu32 "\n", ((thread->jvm_stack)->operand_stack)->value);
					break;
				default:
					puts("VerifyError: descritor de field inválido");
					exit(EXIT_FAILURE);
			}

			operand->prox = (thread->jvm_stack)->operand_stack;
			(thread->jvm_stack)->operand_stack = operand;
/*			printf("value = %" PRIu32 "\n", ((thread->jvm_stack)->operand_stack)->value);*/
			break;
		case	putstatic:
			switch((var->value).type){
				case	BYTE:
					(var->value).u.Byte.byte = (s1) popOperand(thread->jvm_stack);
					break;
				case	CHAR:
					(var->value).u.Char.char_ = (u1) popOperand(thread->jvm_stack);
					break;
				case	FLOAT:
					(var->value).u.Float.float_ = popOperand(thread->jvm_stack);
					break;
				case	INT:
					(var->value).u.Integer.integer = (s4) popOperand(thread->jvm_stack);
					break;
				case	REF_INST:
					(var->value).u.InstanceReference.reference = (OBJECT *) popOperand(thread->jvm_stack);
/*					printf("%p\n" , (var->value).u.ArrayReference.reference);	*/
					break;
				case	SHORT:
					(var->value).u.Short.short_ = (s2) popOperand(thread->jvm_stack);
					break;
				case	BOOLEAN:
					(var->value).u.Boolean.boolean = (u1) popOperand(thread->jvm_stack);
					break;
				case	REF_ARRAY:
					(var->value).u.ArrayReference.reference = (ARRAY *) popOperand(thread->jvm_stack);

					break;
				case	DOUBLE:
					(var->value).u.Double.high_bytes = popOperand(thread->jvm_stack);
					(var->value).u.Double.low_bytes = popOperand(thread->jvm_stack);
					break;
				case	LONG:
					(var->value).u.Long.high_bytes = popOperand(thread->jvm_stack);
					(var->value).u.Long.low_bytes = popOperand(thread->jvm_stack);
					break;
				default:
					puts("VerifyError: descritor de field inválido");
					exit(EXIT_FAILURE);
			}
			break;
		case	getfield:
			break;
		case	putfield:
			break;	
	}
	
	thread->program_counter += 3;
}

// invoke	0xB6 a 0xBA
//	invocação de métodos
void	invoke(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokevirtual*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokespecial*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokestatic*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokeinterface*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.invokedynamic*/

	u1	indexbyte1 = *(thread->program_counter + 1);
	u1	indexbyte2 = *(thread->program_counter + 2);
	u2	index = (indexbyte1 << 8) | indexbyte2;
	printf("\t%" PRIu16, index);
/*	https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-5.html#jvms-5.4.3.3*/
	// RESOLUÇÃO DO MÈTODO
	cp_info	* cp_aux = (thread->jvm_stack)->current_constant_pool;
	cp_aux = cp_aux + index - 1; // falta verificar se o indice está nos limites da constant pool
	cp_aux = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Ref.class_index - 1;

		// nome da classe do método
	cp_info	* cp_class_name = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Class.name_index - 1;
	printf("\ncp_class_name: ");
	PrintConstantUtf8(cp_class_name, stdout);
	puts("");
	
		// nome do método
	cp_aux = (thread->jvm_stack)->current_constant_pool;
	cp_aux = cp_aux + index - 1;
	cp_aux = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Ref.name_and_type_index - 1;
	cp_info * cp_method_name = (thread->jvm_stack)->current_constant_pool + cp_aux->u.NameAndType.name_index - 1;
	printf("cp_method_name: ");
	PrintConstantUtf8(cp_method_name, stdout);
	puts("");
	
		// descritor do método
	cp_aux = (thread->jvm_stack)->current_constant_pool;
	cp_aux = cp_aux + index - 1;
	cp_aux = (thread->jvm_stack)->current_constant_pool + cp_aux->u.Ref.name_and_type_index - 1;
	cp_info	* cp_method_descriptor = (thread->jvm_stack)->current_constant_pool + cp_aux->u.NameAndType.descriptor_index - 1;
	printf("cp_method_descriptor: ");
	PrintConstantUtf8(cp_method_descriptor, stdout);
	puts("");
	
	// CONTROLE DE ACESSO
/*	https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-5.html#jvms-5.4.4*/
	u1	* backupPC = thread->program_counter;
	CLASS_DATA	* method_class = getClass(cp_class_name, jvm);
	if(!method_class){// se a classe do método não foi carregada, mesmo package
		char	* class_name = cp_class_name->u.Utf8.bytes;
		class_name[cp_class_name->u.Utf8.length] = '\0';
		puts("");
		classLoading(strcat(class_name, ".class"), &method_class, method->class_data, jvm);
		classLinking(method_class, jvm);
		classInitialization(method_class, jvm, thread);
		thread->program_counter = backupPC;
		printf("\nResume %s\n", opcodes[*thread->program_counter]);
	}	
	
	char	* method_name = cp_method_name->u.Utf8.bytes;
	method_name[cp_method_name->u.Utf8.length] = '\0';
	
	METHOD_DATA	* invoked_method = getMethod(method_name, method_class);
	if(!(invoked_method->modifiers & ACC_PUBLIC)){// SE O MÉTODO NÃO É PUBLICO
		if(invoked_method->modifiers & ACC_PROTECTED){ // SE O MÉTODO É PROTECTED
			if(method->class_data != method_class){ // Se a classe do método invokado é diferente da classe método corrente
				if(!isSuperClass(method->class_data, method_class)){
				// Se a classe do método invokado é não é subclasse da classe método corrente 
					if((method->class_data)->classloader_reference != method_class->classloader_reference){
						if(!(invoked_method->modifiers & ACC_PRIVATE)){
							puts("IllegalAccessError");
							exit(EXIT_FAILURE);
						}
					}
				}
			}
			else if(1/*NOT restricao static*/){
				if(!(invoked_method->modifiers & ACC_PRIVATE)){
					puts("IllegalAccessError");
					exit(EXIT_FAILURE);
				}
			}
			
			
			// restriçao static
		
		}
		else if(!invoked_method->modifiers){// SE O MÉTODO É DEFAULT
			if((method->class_data)->classloader_reference != (method_class)->classloader_reference){
				if(!(invoked_method->modifiers & ACC_PRIVATE)){
					puts("IllegalAccessError");
					exit(EXIT_FAILURE);
				}
			}
		}
	}	


/*	if(!method_class){*/
/*		puts("\nNoSuchMethodError");*/
/*		exit(EXIT_FAILURE);*/
/*	}*/
	
/*	if(method_class->modifiers & ACC_INTERFACE){// se a classe do método for interface.*/
/*		puts("\nIncompatibleClassChangeError");*/
/*		exit(EXIT_FAILURE);*/
/*	}*/
	// faltando
	
	
	switch(* thread->program_counter){// PARA TESTAR O HELLOWORLD
		case	invokespecial:
			break;
		case	invokevirtual:
			break;
	}
	thread->program_counter += 3;
}

// handleObject	0xBB a 0xBE; 0xC5
//	criação e manipulação de objetos e arrays
void	handleObject(METHOD_DATA * method, THREAD * thread, JVM * jvm){
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.new*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.newarray*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.anewarray*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.arraylength*/
/*https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-6.html#jvms-6.5.multianewarray*/
	switch(* thread->program_counter){// PARA TESTAR O HELLOWORLD
		case	new:
		case	anewarray:
			thread->program_counter += 3;
			break;
		case	newarray:
			thread->program_counter += 2;
			break;
		case	arraylength:
			break;
		case	multianewarray:
			thread->program_counter += 4;
			break;
	}
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




