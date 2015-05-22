#include"libs.h"

/******************
 * 		          *
 *	   Buffer     *
 *                *
 ******************/

//newBuffer
// Vincula o nome do arquivo ao buffer e aloca a mem�ria especificada
// no vetor.
// Entrada: Nome do arquivo, tamanho do buffer
// Sa�da:	Ponteiro para buffer alocado
Buffer* newBuffer(char*, int);

//destroyBuffer
// Remove o vetor e o buffer da mem�ria.
// Entrada: Ponteiro para buffer a ser destruido
void destroyBuffer(Buffer*);

//fileSize
// Retorna tamanho do arquivo associado ao buffer de acordo com unidade
// especificada.
// Entrada: Buffer, unidade
// Sa�da: tamanho do arquivo
int fileSize(Buffer*,int);

//saveBuffer
// Salva o buffer especificado na posi��o do arquivo de onde foi
// recuperado.
// Entrada: Ponteiro para buffer a ser salvo
void saveBuffer(Buffer*);

//loadBuffer
// Carrega o buffer a partir da posi��o final do �ltimo carregamento.
// Entrada: Ponteiro para buffer a ser carregado
void loadBuffer(Buffer*);

//loadBufferbyPos
// Carrega o buffer a partira da posi��o especificada.
// Entrada: Ponteiro para buffer a ser carregado
void loadBufferbyPos(Buffer*, int);

//getBuffer
// Respons�vel por manter a abstra��o do carregamento do buffer, se ne-
// cess�rio recarrega o buffer e/ou retorna o elemento especificado.
// Entrada: Buffer, index do elemento no "arquivo"
// Sa�da: Elemento na posi��o indicada
int getBuffer(Buffer*,int);

//setBuffer
// Respons�vel por manter a abstra��o do carregamento do buffer, se ne-
// cess�rio recarrega o buffer e/ou posiciona o elemento especificado.
// Entrada:Buffer, index do elemento no "arquivo", elemento
int setBuffer(Buffer*,int,int);

//getElement
// Retorna elemento na posi��o especificada, caso n�o esteja no
// buffer, realiza uma busca independente e retorna o elemento.
// Entrada: Buffer, index do elemento no "arquivo"
// Sa�da: Elemento na posi��o indicada
int getElement(Buffer*,int);

//setElement
// Posiciona o elemento especificado no index tamb�m especificado,
// caso n�o esteja no buffer, realiza uma busca independente no arquivo.
// Entrada: Buffer, index do elemento no "arquivo", elemento
void setElement(Buffer*,int,int);

//setbeginPos
// Coloca a posi��o do BEGIN e END SEEK onde foi especificado.
// Entrada: Index do "arquivo"
void setbeginPos(Buffer*, int);

//inBuffer
// Retorna se o index especificado encontra-se carregado no buffer.
// Entrada: Index do elemento no "arquivo"
// Sa�da: 1 para <SIM> e 2 para <N�O>
int inBuffer(Buffer*,int);

//swapBuffer
// Alterna elementos dentro do arquivo, podendo ser:
// 		intraBuffer: troca interna no buffer;
//		partialextraBuffer: troca entre buffer e arquivo;
//		extraBuffer: troca entre elementos fora do buffer.
// Entrada: Buffer, index do 1� elemento, index do 2� elemento
void swapBuffer(Buffer*,int,int);

//printBuffer
// Exibe os elementos no buffer seguidos dos dados de seus campos.
// Entrada: Buffer
void printBuffer(Buffer*);

//printFile
// Imprime todos os elementos do arquivo vinculado ao buffer.
// Entrada: Buffer
void printFile(Buffer*);
