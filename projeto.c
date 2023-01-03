#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define tam 3

void SOMA(int dimensao, int matriz1[dimensao][dimensao], int matriz2[dimensao][dimensao], int soma[dimensao][dimensao]){
  int l, c;


  for (l=0; l<dimensao; l++){
    for (c=0; c<dimensao; c++){
      soma[l][c] = matriz1[l][c] + matriz2[l][c];
    }
  }
}

void INVERSA(int linha_matriz, int coluna_matriz, int matriz_arquivo[linha_matriz][coluna_matriz], float identidade[linha_matriz][coluna_matriz]){
  float pivo = 0, aux = 0;
  int l, c, k;
  float matriz[linha_matriz][coluna_matriz];

  for (l=0; l<linha_matriz; l++){
    for (c=0; c<coluna_matriz; c++){
      if(l == c){
        identidade[l][c] = 1;
      }else{
        identidade[l][c] = 0;
      }
    }
  }

  for (l=0; l<linha_matriz; l++){
    for (c=0; c<coluna_matriz; c++){
      matriz[l][c] = matriz_arquivo[l][c];
    }
  }
  
for(c = 0; c < 3; c++){
    pivo = matriz[c][c];
    	for(k = 0; k < 3; k++){
		matriz[c][k] = (matriz[c][k])/(pivo); //L1 -> L1/pivo , L2 -> L2/pivo, L3 -> L3/pivo
		identidade[c][k] = (identidade[c][k])/(pivo); //Ex: 1 0 0 / pivo  , 0 1 0 / pivo,   0 0 1/ pivo
        }
    
	for(l = 0; l < 3; l++){
		if(l != c){
			aux = matriz[l][c];
           			for(k = 0; k < 3; k++){
			matriz[l][k] = (matriz[l][k]) - (aux*matriz[c][k]); //Ex: L2 -> L2 - ( 1"m" - L1) 
			identidade[l][k] = (identidade[l][k]) - (aux*identidade[c][k]);  
    			}
    		}
    	}  
}

}

void MULTIPLICACAO(int linhaMatriz1, int colunaMatriz1, int linhaMatriz2, int colunaMatriz2, int matriz1[linhaMatriz1][colunaMatriz1], int matriz2[linhaMatriz1][linhaMatriz2], 
  int multiplicacao[colunaMatriz1][linhaMatriz2]){

  int l,c,i;
  int aux = 0;

  for (l=0; l<linhaMatriz1 ; l++){
    for (c=0; c<colunaMatriz2; c++){
      multiplicacao[l][c] = 0;
      for(i=0; i<colunaMatriz1; i++){
        multiplicacao[l][c] += matriz1[l][i] * matriz2[i][c];
      }
    }
  }
}

int TRANSPOSTA (int linha1, int coluna1, int linha2, int coluna2, int matriz1[linha1][coluna1], int matriz2[linha2][coluna2], 
  int transposta1[coluna1][linha1], int transposta2[coluna2][linha2]){
  int l,c;

  for (l=0; l<linha1; l++){
    for (c=0; c<coluna1; c++){
      transposta1[c][l] = matriz1[l][c];
    }
  }
  for (l=0; l<linha2; l++){
    for (c=0; c<coluna2; c++){
      transposta2[c][l] = matriz2[l][c];
    }
  }
}

int main() {
  int matriz1[tam][tam], matriz2[tam][tam], l, c, escolha1, escolha;
  int dimensao;
  char nomedoarqv1[10], nomedoarqv[10];
  int linha_matriz1 = 0, coluna_matriz1 = 0, linha_matriz2 = 0, coluna_matriz2 = 0;
  int flagMatriz1 = 0, flagMatriz2 = 0;

  FILE*arqv_entrada;

  printf("\nDigite o nome do arquivo de entrada: ");
  scanf("%s", nomedoarqv1);


  if((arqv_entrada=fopen(nomedoarqv1,"r"))==NULL){
    printf("\nNao foi possivel abrir o arquivo");
  return 0;
  
  }
  while(!feof(arqv_entrada)){
    c = getc(arqv_entrada);
    if ( c == ' ')
    {
      coluna_matriz1++;
    }
    if ( c == '\n')
    {
      coluna_matriz1++;
      break;
    }
  }
  while(!feof(arqv_entrada)){
    c = getc(arqv_entrada);
    if(flagMatriz1 == 0){
      if (c == '\n')
      {
        linha_matriz1++;
        flagMatriz1 = 1;
      }else{
        flagMatriz1 = 0;
      }
    }else{
      if ( c == '\n')
      {
        linha_matriz1++;
        linha_matriz2++;
        break;
      }else{
        flagMatriz1 = 0;
      }
    }
  }
  while(!feof(arqv_entrada)){
    c = getc(arqv_entrada);
    if ( c == ' ')
    {
      coluna_matriz2++;
    }
    if ( c == '\n')
    {
      coluna_matriz2++;
      linha_matriz2++;
      break;
    }
  }
  while(!feof(arqv_entrada)){
    c = getc(arqv_entrada);
    if ( c == '\n')
    {
      linha_matriz2++;
    }
  }

  fclose(arqv_entrada);

  int matriz1_arquivo[linha_matriz1][coluna_matriz1], matriz2_arquivo[linha_matriz2][coluna_matriz2];

  if((arqv_entrada=fopen(nomedoarqv1,"r"))==NULL){
      printf("\nNao foi possivel abrir o arquivo");

  return 0;
  
  }

  FILE*arqv_saida;

  printf("\nDigite o nome do arquivo de saida: ");
  scanf("%s", nomedoarqv);

  if((arqv_saida=fopen(nomedoarqv,"w"))==NULL){
    printf("\nNao foi possivel abrir o arquivo");
    return 0;
  }

  for (l=0; l<linha_matriz1; l++){
    for (c=0; c<coluna_matriz1; c++){
      fscanf(arqv_entrada, "%d", &matriz1_arquivo[l][c]);
    }
  }
  for (l=0; l<linha_matriz2; l++){
    for (c=0; c<coluna_matriz2; c++){
      fscanf(arqv_entrada, "%d", &matriz2_arquivo[l][c]);
    }
  }
  

  // testa se a soma é possível
  if(linha_matriz1 == linha_matriz2 && coluna_matriz1 && coluna_matriz2){
    char texto1[500] = "Soma das matrizes:\n\n";
    int dimensao = linha_matriz1;
    int soma[dimensao][dimensao];
    SOMA(dimensao, matriz1_arquivo, matriz2_arquivo, soma);
    fprintf(arqv_saida, "%s", texto1);
    for (l=0; l<dimensao; l++){
      for (c=0; c<dimensao; c++){
        fprintf(arqv_saida,"%d ", soma[l][c]);
      }
        fprintf(arqv_saida,"\n");
    }
  }else{
    char texto1[500] = "Não foi possível realizar a operação SOMA!!\n\n";
    fprintf(arqv_saida, "%s", texto1);
  }
  
  if(coluna_matriz1 == linha_matriz2){
    char texto2[500] = "\nMultiplacaçao das matrizes:\n\n";
    int multiplicacao[linha_matriz1][coluna_matriz2];
    MULTIPLICACAO(linha_matriz1, coluna_matriz1, linha_matriz2, coluna_matriz2, matriz1_arquivo, matriz2_arquivo, multiplicacao);
    fprintf(arqv_saida, "%s", texto2);
    for (l=0; l<linha_matriz1; l++){
      for (c=0; c<coluna_matriz2; c++){
        fprintf(arqv_saida,"%d ", multiplicacao[l][c]);
      }
      fprintf(arqv_saida,"\n");
    }
  }else{
    char texto2[500] = "\nNão foi possível realizar a operação MULTIPLICAÇÃO!!\n\n";
    fprintf(arqv_saida, "%s", texto2);
  }

  int transposta1[coluna_matriz1][linha_matriz1], transposta2[coluna_matriz2][linha_matriz2];
  TRANSPOSTA(linha_matriz1, coluna_matriz1, linha_matriz2, coluna_matriz2, matriz1_arquivo, matriz2_arquivo, transposta1, transposta2);

  char texto3[500] = "\nTransposta matriz 1:\n\n";
  fprintf(arqv_saida, "%s", texto3);  
  for (l=0; l<linha_matriz1; l++){
    for (c=0; c<coluna_matriz1; c++){
      fprintf(arqv_saida,"%d ", transposta1[l][c]);
    }
    fprintf(arqv_saida,"\n");
  }
  char texto4[500] = "\nTransposta matriz 2:\n\n";
  fprintf(arqv_saida, "%s", texto4);  
  for (l=0; l<linha_matriz2; l++){
    for (c=0; c<coluna_matriz2; c++){
      fprintf(arqv_saida,"%d ", transposta2[l][c]);
    }
    fprintf(arqv_saida,"\n");
  }

  if(linha_matriz1 == coluna_matriz1){
    char texto5[500] = "\nInversa matriz 1:\n\n";
    fprintf(arqv_saida, "%s", texto5);  
    float inversa1[linha_matriz1][coluna_matriz1];
    INVERSA(linha_matriz1, coluna_matriz1, matriz1_arquivo, inversa1);
    for (l=0; l<linha_matriz1; l++){
      for (c=0; c<coluna_matriz1; c++){
        fprintf(arqv_saida, "%.2f ", inversa1[l][c]);
      }
        fprintf(arqv_saida, "\n");
    }
  }else{
    char texto5[500] = "\nNão foi possível realizar a operação INVERSA da matriz 1!!\n\n";
    fprintf(arqv_saida, "%s", texto5);
  }
  if(linha_matriz2 == coluna_matriz2){
    char texto5[500] = "\nInversa matriz 2:\n\n";
    fprintf(arqv_saida, "%s", texto5);  
    float inversa2[linha_matriz2][coluna_matriz2];
    INVERSA(linha_matriz2, coluna_matriz2, matriz2_arquivo, inversa2);
    for (l=0; l<linha_matriz2; l++){
      for (c=0; c<coluna_matriz2; c++){
        fprintf(arqv_saida, "%.2f ", inversa2[l][c]);
      }
        fprintf(arqv_saida, "\n");
    }
  }else{
    char texto5[500] = "\nNão foi possível realizar a operação INVERSA da matriz 2!!\n\n";
    fprintf(arqv_saida, "%s", texto5);
  }
      
  fclose(arqv_entrada);
  fclose(arqv_saida);
  return 0;
}