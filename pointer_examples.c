
#include <stdio.h>
#include <stdlib.h>

/*pointer magic*/
int main()
{

	int matSize = 2;
	char * ptr = malloc (sizeof(int)*4); //malloc aloca em bytes


	int (*mat)[matSize]; //vetores bi-dimiensionais um dos tamanhos é, obrigatóriamente, fixo

	mat = (int (*)[matSize]) ptr;

	mat[0][1] = 10; //igual à *(ptr + sizeof(int)*1)

	if(*(ptr + sizeof(int)*1) == mat[0][1]){
		printf("conteúdo de ptr += sizeof(int)*1 é igual a mat[0][1]\n");
		printf("%d %d\n", mat[0][1], *(ptr + sizeof(int)*1));
	}
	
	ptr += sizeof(int)*2; //igual à mat[1][0]
	*ptr = 2;
	if(*ptr == mat[1][0]){
		printf("conteúdo de ptr += sizeof(int)*2 é igual a mat[1][0]\n");
		printf("%d %d\n", mat[1][0], *ptr);
	}

	return 0;
}
