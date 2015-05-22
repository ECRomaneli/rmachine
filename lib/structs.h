typedef struct _Buffer{
	char* ARRAY;     // Vetor onde será armazenado o buffer
	int ARRAY_SIZE;	 // Tamanho do buffer
	char* FILE_NAME; // Nome do arquivo associado ao buffer
	int FILE_SIZE;	 // Tamanho do arquivo associado ao buffer
	int BEGIN_SEEK;  // Inicio da última procura
	int END_SEEK;	 // Fim da última procura
	int N_RECHARGE;	 // Quantidade recuperada na última procura
	int CHANGE;    	 // Mostra se houve mudança desde a última recarga
}Buffer;

typedef struct _Instruction{
	int LINE;       // Linha da instrução
	char* OPERATION;// Operação
	char REGISTER;  // Registrador Utilizado
	int JUMP1;      // Desvio Incondicional e Condicional no caso "Verdadeiro"
	int JUMP2;      // Desvio Condicional no caso "Falso"
}Instruction;
