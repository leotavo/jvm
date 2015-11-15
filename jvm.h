

#include	<stdint.h>
#include	<stdbool.h>
#include	"classfile.h"

// Data Types
typedef		int8_t		BYTE;
typedef		int16_t		SHORT;
typedef		int32_t		INT;
typedef		int64_t		LONG; 		// ou usar dois campos de 32 bits como em cp_info?
typedef		uint16_t	CHAR;
typedef		uint32_t	FLOAT;
typedef		uint64_t	DOUBLE;  	// ou usar dois campos de 32 bits como em cp_info?
typedef		bool		BOOLEAN;
// REFERENCE
// RETURN_ADDRESS



typedef	struct locals{
	/* data */	// A DEFINIR
}LOCALS;

}

typedef		OPERAND		uint32_t;


typedef	struct stack_frame{			// um stack_frame é criado qdo um método é executado na JVM;
						// é adicionado à jvm_stack da Thread;
						// qdo o método é finalizado, o stack_frame é removido;
				
	LOCALS		*local_variable_array;	// o tamanho é determinado pelo campo 'max_locals' do atributo Code do método (classfile) ;
						// local_variable_array[0] = referência para a instância da classe do método (this);
						// local_variable_array[1..x] = parâmetros do método;
						// local_variable_array[(x+1)..(max_locals-1)] = variáveis locais do método;

	OPERAND		* operand_stack;	// o tamanho da pilha é determinado pelo campo 'max_stack' do atributo Code do método (classfile);
						// área de trabalho do método, onde são empilhados os operandos e os resultados de uma instrução;
						// cada item da pilha tem o tamanho fixo de 32 bits;
	
	cp_info		* constant_pool_ref;	// referência para o constant_pool da classe onde o método está sendo executado;
}STACK_FRAME;

typedef	JVM_INSTRUCTION	uint8_t;

typedef	struct native_stack{
	/* data */	// A DEFINIR
}NATIVE_STACK;

typedef	struct thread{
	JVM_INSTRUCTION	* pc_register;		// contém o endereço da próxima instrução da jvm a ser executada;
						// um por thread;
						
	STACK_FRAME	* jvm_stack;		// pilha de frames;
						// um por thread;
						
	NATIVE_STACK	* native_method_stack	// pilha para execução de código C/C++;
}THREAD;

typedef	struct heap{
	/* data */	// A DEFINIR		// guarda objetos ou instâncias;
}HEAP{

}

typedef	struct method_area{			// runtime_constant_pool; field and method information; static variable; method bytecode;
	/* data */	// A DEFINIR
}METHOD_AREA;

typedef	struct runtime_data_area{
	THREAD		* threads;	// array de threads;
	HEAP		heap;
	METHOD_AREA	method_area;
}RUNTIME_DATA_AREA;









