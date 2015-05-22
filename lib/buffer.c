#include "buffer.h"

/******************
 * 		          *
 *	   Buffer     *
 *                *
 *	Implementação *
 *                *
 ******************/

int acessos = 0;

Buffer* newBuffer(char* FILE_NAME, int ARRAY_SIZE){
	Buffer* BUFFER = (Buffer*) malloc (sizeof (Buffer) );
	BUFFER->ARRAY = (char*) malloc (sizeof (char) * ARRAY_SIZE);
	BUFFER->ARRAY_SIZE = ARRAY_SIZE;
	BUFFER->FILE_NAME = FILE_NAME;
	BUFFER->FILE_SIZE = fileSize(BUFFER, sizeof (char) );
	BUFFER->BEGIN_SEEK = BUFFER->END_SEEK = BUFFER->N_RECHARGE = BUFFER->CHANGE = 0;
	return BUFFER;
}

void destroyBuffer(Buffer* buffer){
    free(buffer->ARRAY);
    free(buffer);
}

void fileCreate(const char* FILE_NAME){
	FILE* arquivo = fopen(FILE_NAME,"wb+");
	fclose(arquivo);
}

int fileSize(Buffer* buffer, int UNIT){
	FILE* arquivo;
	arquivo = fopen(buffer->FILE_NAME, "rb+");
	fseek(arquivo, 0, SEEK_END);
	int _size = ftell(arquivo);
	fclose(arquivo);
	return _size/UNIT;
}

void saveBuffer(Buffer* buffer){
	FILE* arquivo = fopen(buffer->FILE_NAME, "rb+");
	fseek(arquivo, buffer->BEGIN_SEEK * sizeof(char), SEEK_SET);
	fwrite(buffer->ARRAY, sizeof(char), buffer->N_RECHARGE, arquivo);
	fclose(arquivo);
	buffer->CHANGE = 0;
	acessos++;
}

void loadBuffer(Buffer* buffer){
	if(buffer->END_SEEK < buffer->FILE_SIZE){
		FILE* arquivo = fopen(buffer->FILE_NAME, "rb+");
		fseek(arquivo, buffer->END_SEEK * sizeof(char), SEEK_SET);
		fread(buffer->ARRAY, sizeof(char), buffer->ARRAY_SIZE, arquivo);
		fclose(arquivo);
		buffer->BEGIN_SEEK = buffer->END_SEEK;
		buffer->END_SEEK = buffer->BEGIN_SEEK + buffer->ARRAY_SIZE < buffer->FILE_SIZE ? buffer->BEGIN_SEEK + buffer->ARRAY_SIZE : buffer->FILE_SIZE;
	}
	else
        buffer->BEGIN_SEEK = buffer->END_SEEK;
    buffer->N_RECHARGE = buffer->END_SEEK - buffer->BEGIN_SEEK;
    acessos++;
}

void swapBuffer(Buffer* buffer, int index1, int index2){
	int aux;
	aux = getElement(buffer,index1);
	setElement(buffer,index1,getElement(buffer,index2));
	setElement(buffer,index2,aux);
}

int getBuffer(Buffer* buffer, int INDEX_FILE){
    if(inBuffer(buffer,INDEX_FILE))
        return buffer->ARRAY[INDEX_FILE - buffer->BEGIN_SEEK];
    else if(buffer->FILE_SIZE <= INDEX_FILE){
        //printf("\nacessou posicao inexistente: %d/%d\n", INDEX_FILE, buffer->FILE_SIZE-1);
        return EOF;
    }
    else{
        if(buffer->CHANGE)
            saveBuffer(buffer);
        if(INDEX_FILE + buffer->ARRAY_SIZE < buffer->FILE_SIZE)
            loadBufferbyPos(buffer,INDEX_FILE);
        else if (buffer->FILE_SIZE - buffer->ARRAY_SIZE >= 0)
            loadBufferbyPos(buffer, buffer->FILE_SIZE - buffer->ARRAY_SIZE);
        else
            loadBufferbyPos(buffer,0);
        return getBuffer(buffer,INDEX_FILE);
    }
}

int setBuffer(Buffer* buffer, int INDEX_FILE, int ELEMENT){
    if(inBuffer(buffer,INDEX_FILE)){
        buffer->ARRAY[INDEX_FILE - buffer->BEGIN_SEEK] = ELEMENT;
        buffer->CHANGE = 1;
    }
    else if(buffer->FILE_SIZE <= INDEX_FILE){
       	//printf("\nacessou posicao inexistente: %d/%d\n",INDEX_FILE,buffer->FILE_SIZE-1);
       	return EOF;
    }
    else{
        if(buffer->CHANGE)
            saveBuffer(buffer);
        if(INDEX_FILE + buffer->ARRAY_SIZE < buffer->FILE_SIZE)
            loadBufferbyPos(buffer,INDEX_FILE);
        else if (buffer->FILE_SIZE - buffer->ARRAY_SIZE >= 0)
            loadBufferbyPos(buffer, buffer->FILE_SIZE - buffer->ARRAY_SIZE);
        else
            loadBufferbyPos(buffer,0);
        setBuffer(buffer,INDEX_FILE, ELEMENT);
    }
	return 1;
}

int getElement(Buffer* buffer, int index){
	if(inBuffer(buffer,index))
        return getBuffer(buffer,index);
	acessos++;
	FILE* arquivo = fopen(buffer->FILE_NAME,"rw+");
	fseek(arquivo,index * sizeof(char),SEEK_SET);
	char elemento;
	fread(&elemento,sizeof(char),1,arquivo);
	fclose(arquivo);
	return (int)elemento;
}

void setElement(Buffer* buffer, int index, int elemento){
    if(inBuffer(buffer,index)){
        setBuffer(buffer,index,elemento);
        return;
    }
	acessos++;
	FILE* arquivo = fopen(buffer->FILE_NAME,"rw+");
	fseek(arquivo, index * sizeof(char), SEEK_SET);
	fwrite(&elemento,sizeof(char),1,arquivo);
	fclose(arquivo);
}

void loadBufferbyPos(Buffer* buffer, int index){
    setbeginPos(buffer,index);
    loadBuffer(buffer);
}

void setbeginPos(Buffer* buffer, int index){
    buffer->BEGIN_SEEK = buffer->END_SEEK = index;
}

int inBuffer(Buffer* buffer, int INDEX_FILE){return buffer->BEGIN_SEEK <= INDEX_FILE && buffer->END_SEEK > INDEX_FILE ? 1 : 0;}

void printBuffer(Buffer* buffer){
    int i;
    for(i = 0; i < buffer->N_RECHARGE; ++i)
        printf(" %c", buffer->ARRAY[i]);
    printf("\nTamanho do buffer: %d",buffer->ARRAY_SIZE);
    printf("\nNome do arquivo: %s",buffer->FILE_NAME);
    printf("\nTamanho do arquivo: %d",buffer->FILE_SIZE);
    printf("\nInicio da procura: %d",buffer->BEGIN_SEEK);
    printf("\nFim da procura: %d",buffer->END_SEEK);
    printf("\nQuantidade capturada: %d\n\n",buffer->N_RECHARGE);
}

void printFile(Buffer* buffer){
    int i;
    putchar('\n');
    for(i = 0; i < buffer->FILE_SIZE; ++i)
        printf("%c", getBuffer(buffer,i));
    putchar('\n');
}

void printacesso(){
        printf("\n\nAcessos: %d\n\n", acessos);
}
