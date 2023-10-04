// Cesar Hideki Imai - 32255659
// Luiz Henrique Bonilha Pasquinelli - 32224419


#include <stdio.h>
#include <stdlib.h>


int **geraMatriz(int n, int m){
  int **matriz;
  matriz = (int**)calloc(n, sizeof(int*));
  for(int x = 0; x < n; x++){
    matriz[x] = (int*)calloc(m, sizeof(int));
  }
  for(int x = 0; x < n; x++){
    for(int y = 0; y < m; y++){
      matriz[x][y] = 0;
    }
  }
  return matriz;
}

int somaVetor(int n, int *v){
  int soma = 0;
  for(int i = 0; i < n; i++){
    soma += v[i];
  }
  return soma;
}

int imprimeVetor(int n, int *v){
  for(int i = 0; i < n; i++){
    if(v[i] > 0){
      printf("%i GB\n",v[i]);
    }
  }
}

int pendriveRec(int tam_pd, int n_arq, int count_arq, int soma_total, int soma_a, int soma_b, int *v, int *pd_a, int *pd_b, int *usados){
  if(count_arq == n_arq){ // Verifica se todos os arquivos foram adicionados
    if(soma_a+soma_b == soma_total){ // Caso a soma dos pendrives seja igual à soma total retorna 1
      return 1;
    }
    else{ // Caso algum arquivo não tenha sido adicionado retorna 0
      return 0;
    }
  }
  for(int i = 0; i < n_arq; i++){ 
    if(usados[i] == 0){
      if(somaVetor(50,pd_a)+v[i] < tam_pd){ // Caso haja lugar no pendrive A o arquivo é adicionado
        pd_a[count_arq] = v[i];
        usados[i] = 1;
        return pendriveRec(tam_pd, n_arq, count_arq+1, soma_total, soma_a+v[i], soma_b, v, pd_a, pd_b, usados);
        usados[i] = 0;
      }
      else if(somaVetor(50,pd_b)+v[i] < tam_pd){ // Caso haja lugar no pendrive B o arquivo é adicionado
        pd_b[count_arq] = v[i];
        usados[i] = 1;
        return pendriveRec(tam_pd, n_arq, count_arq+1, soma_total, soma_a, soma_b+v[i], v, pd_a, pd_b, usados);
        usados[i] = 0;
      }
    }
  }
}

void pendrive(int tam,int n_arq,int soma, int *v){
  int tam_pd = tam/2; // Tamanho de cada pendrive
  int **pd = geraMatriz(3,50); // Matriz que contém o pendrive A, pendrive B e um vetor de arquivos já usados
  int ok = pendriveRec(tam_pd, n_arq, 0, soma, 0, 0, v, pd[0], pd[1], pd[2]); // Verifica se há combinação válida
  if(ok == 1){ // Caso encontre uma combinação válida lista os arquivos dentro de cada pendrive
    printf("Pendrive A (%i GB)\n",tam_pd);
    imprimeVetor(50, pd[0]);
    printf("Pendrive B (%i GB)\n",tam_pd);
    imprimeVetor(50, pd[1]);
  }
  else{
    puts("Impossível gravar todos os arquivos nos pendrives.");
  }
}

int main(void) {
  FILE *arq;
  int n;
  arq = fopen("teste.txt", "r");
  fscanf(arq, "%i", &n); // Lê o número de testes
  for(int i = 0; i < n; i++){
    int tam, n_arq;
    fscanf(arq, "%i %i", &tam, &n_arq); // Lê o tamanho máximo e o número de arquivos
    printf("%i GB\n",tam);
    if(n_arq > 50){ // Caso o número de arquivos ultrapasse o limite (50) gera erro
      puts("Impossível gravar todos os arquivos nos pendrives.");
      continue;
    }
    int vetor_arq[n_arq], soma = 0;
    for(int j = 0; j < n_arq; j++){ // Inclui todos os arquivos no vetor 'v'
      fscanf(arq, "%i", &vetor_arq[j]);
      soma += vetor_arq[j];
    }
    if(soma > tam){ // Caso a soma do tamanho dos arquivos ultrapasse o tamanho máximo gera erro
      puts("Impossível gravar todos os arquivos nos pendrives.");
      continue;
    }
    int *p = vetor_arq;
    pendrive(tam, n_arq, soma, p);
    puts("");
  }
  fclose(arq);
  return 0;
}