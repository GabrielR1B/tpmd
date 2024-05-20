#include <stdio.h>
#include <stdbool.h>

#define MAX_CONJUNTO 50
#define MAX_PARES 2500			// 50 * 50

// Funcao para verificar se um par ordenado esta presente na matriz de pares
bool parEstaPresente (int par[2], int pares[][2], int num_pares){
  for(int i = 0; i < num_pares; i++){
	  if (pares[i][0] == par[0] && pares[i][1] == par[1]){
		  return true;
	  }
	}
  return false;
}

// Funcao para adicionar pares ao conjunto de pares e imprimir os pares adicionados
void adicionarPar (int a, int b, int pares[][2], int *num_pares){
  pares[*num_pares][0] = a;
  pares[*num_pares][1] = b;
  (*num_pares)++;
}

// Funcao para ordenar os pares na ordem crescente
void ordenarPares (int pares[][2], int num_pares){
  for (int i = 0; i < num_pares - 1; i++){
	  for (int j = 0; j < num_pares - i - 1; j++){
		  if(pares[j][0] > pares[j + 1][0]
			  || (pares[j][0] == pares[j + 1][0]
			  && pares[j][1] > pares[j + 1][1])){
			  int temp0 = pares[j][0];
			  int temp1 = pares[j][1];
			  pares[j][0] = pares[j + 1][0];
			  pares[j][1] = pares[j + 1][1];
			  pares[j + 1][0] = temp0;
			  pares[j + 1][1] = temp1;
			}
		}
	}
}

int main(){
  int conjunto[MAX_CONJUNTO];
  int pares[MAX_PARES][2];
  int paresArmazem[MAX_PARES][2];
  int n, i, j, k, g, h, count_pares = 0;

  // Leitura da quantidade de elementos do conjunto A e os elementos do conjunto
  scanf ("%d", &n);
  for (i = 0; i < n; i++){
	  scanf ("%d", &conjunto[i]);
	}

  // Leitura dos pares ordenados
  i = 0;
  while (scanf ("%d %d", &pares[i][0], &pares[i][1]) == 2){
	  i++;
	}
  int num_pares = i;
  // Verificacao das propriedades das relacoes binarias
  bool reflexiva = true, irreflexiva = true, simetrica =true,
  anti_simetrica = true, assimetrica = true, transitiva = true;

  printf ("Propriedades\n");
  for (i = 0; i < n; i++){
	  // Propriedade 1: Reflexiva
	  if (!parEstaPresente ((int[])
		{ conjunto[i], conjunto[i] }, pares, num_pares)){
		  reflexiva = false;
		  paresArmazem[count_pares][0] = conjunto[i];
		  paresArmazem[count_pares][1] = conjunto[i];
		  count_pares++;
		}
	}

  printf ("1. Reflexiva: %c", reflexiva ? 'V' : 'F');
  for (i = 0; i < count_pares; i++){
	  if (i > 0){
		  printf (",(%d, %d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	  else{
		  printf ("\n(%d, %d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	}
  count_pares = 0;

  // Propriedade 2: Irreflexiva
  for (i = 0; i < n; i++){
	  if (parEstaPresente ((int[]){ conjunto[i], conjunto[i] }, pares, num_pares)){
		  irreflexiva = false;
		  paresArmazem[count_pares][0] = conjunto[i];
		  paresArmazem[count_pares][1] = conjunto[i];
		  count_pares++;
		}
	}
  printf ("\n2. Irreflexiva: %c", irreflexiva ? 'V' : 'F');
  for (i = 0; i < count_pares; i++){
	  if (i > 0){
		  printf (", (%d, %d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	  else{
		  printf ("\n(%d, %d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	}
  count_pares = 0;
  
  // Propriedade 3: Simetrica
  for(i = 0; i < n; i++){
	  for (j = 0; j < n; j++){
		  
		  if (parEstaPresente ((int[]){ conjunto[i], conjunto[j] }, pares, num_pares) 
		  && !parEstaPresente ((int[]){ conjunto[j], conjunto[i] }, pares,num_pares)){
			  simetrica = false;
			  paresArmazem[count_pares][0] = conjunto[j];
			  paresArmazem[count_pares][1] = conjunto[i];
			  count_pares++;
			}
		}
	}
  printf ("\n3. Simetrica: %c", simetrica ? 'V' : 'F');
  for (i = 0; i < count_pares; i++){
	  if (i > 0){
		  printf (",(%d, %d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	  else{
		  printf ("\n(%d, %d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	}
  count_pares = 0;

  // Propriedade 4: Anti-simetrica
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (parEstaPresente((int[]){conjunto[i], conjunto[j]}, pares, num_pares) &&
                parEstaPresente((int[]){conjunto[j], conjunto[i]}, pares, num_pares) &&
                conjunto[i] != conjunto[j]){
                anti_simetrica = false;
                paresArmazem[count_pares][0] = conjunto[i];
                paresArmazem[count_pares][1] = conjunto[j];
                count_pares++;
            }
        }
    }

    printf("\n4. Anti-simetrica: %c", anti_simetrica ? 'V' : 'F');
    if (!anti_simetrica) {
        printf("\n");
        bool first = true;
        for(int i = 0; i < count_pares; i++){
            int par[2] = {paresArmazem[i][1], paresArmazem[i][0]};
            if(parEstaPresente(par, pares, num_pares)) {
                if (!first){
                    printf(", ");
                }
                printf("((%d, %d), (%d, %d))", paresArmazem[i][0], paresArmazem[i][1], par[0], par[1]);
                first = false;
                // Remover o par correspondente para evitar duplicação
                for (int j = i + 1; j < count_pares; j++) {
                    if (paresArmazem[j][0] == par[0] && paresArmazem[j][1] == par[1]) {
                        for (int k = j; k < count_pares - 1; k++) {
                            paresArmazem[k][0] = paresArmazem[k + 1][0];
                            paresArmazem[k][1] = paresArmazem[k + 1][1];}
                        count_pares--;
                        j--;
                    }
                }
            }
        }
    }
    count_pares = 0;
  // Propriedade 5: Assimetrica
  for (i = 0; i < n; i++){
	  for (j = 0; j < n; j++){
		  if(parEstaPresente ((int[]){ conjunto[i], conjunto[j] }, pares, num_pares)
		  && parEstaPresente ((int[]){ conjunto[j], conjunto[i] }, pares,num_pares)){
			  assimetrica = false;
			}
		}
	}
  printf ("\n5. Assimetrica: %c\n", assimetrica ? 'V' : 'F');
  
  // Propriedade 6: Transitiva
  for (i = 0; i < n; i++){
	  for (j = 0; j < n; j++){
		  for (k = 0; k < n; k++){
			  if (parEstaPresente ((int[]){ conjunto[i], conjunto[j] }, pares,num_pares) 
			  && parEstaPresente ((int[]){conjunto[j],conjunto[k]}, pares,num_pares)
			  && !parEstaPresente ((int[]){ conjunto[i], conjunto[k] }, pares,num_pares)){
				  transitiva = false;
				  paresArmazem[count_pares][0] = conjunto[i];
				  paresArmazem[count_pares][1] = conjunto[k];
				  count_pares++;
				}
			}
		}
	}
  printf ("6. Transitiva: %c", transitiva ? 'V' : 'F');
  for (i = 0; i < count_pares; i++){
	  if (i > 0){
		  printf (",(%d,%d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	  else{
		  printf ("\n(%d,%d)", paresArmazem[i][0], paresArmazem[i][1]);
		}
	}
  // Determina se a relacao e de equivalencia ou ordem parcial
  bool equivalencia = reflexiva && simetrica && transitiva;
  bool ordem_parcial = reflexiva && anti_simetrica && transitiva;

  printf ("\n\nRelação de equivalencia: %c\n", equivalencia ? 'V' : 'F');
  printf ("Relação de ordem parcial: %c\n", ordem_parcial ? 'V' : 'F');

  // Fecho Reflexivo
  printf ("\nFecho reflexivo da relacao:");
  for (int i = 0; i < n; i++){
	  bool par_existente = false;
	  int a = conjunto[i];
	  for (int j = 0; j < num_pares; j++){
		  if(pares[j][0] == a && pares[j][1] == a){
			  par_existente = true;
			  break;
			}
		}
	  if (!par_existente){
		  adicionarPar (a, a, pares, &num_pares);
		}
	}
	ordenarPares (pares, num_pares);

  for (int i = 0; i < num_pares; i++){
	  if (reflexiva)
		{
		  printf (" R");		
		  break;
		}
	  if (i > 0)
		{
		  printf (", (%d, %d)", pares[i][0], pares[i][1]);
		}
	  else
		{
		  printf ("\n(%d, %d)", pares[i][0], pares[i][1]);
		}
	}

  printf ("\n");
  //Fecho Simetrico
  for (int i = 0; i < num_pares; i++){
        int a = pares[i][0];
        int b = pares[i][1];
        bool par_simetrico_existente = false;
        for (int j = 0; j < num_pares; j++) {
            if (pares[j][0] == b && pares[j][1] == a) {
                par_simetrico_existente = true;
                break;
            }
        }
        if (!par_simetrico_existente){
            adicionarPar(b, a, pares, &num_pares);
        }
}
    ordenarPares(pares, num_pares);

    printf("Fecho simetrico da relacao:");
  
    for (int i = 0; i < num_pares; i++){
      if (simetrica){
		  printf (" R\n");
		  break;
      }
    if (i > 0){
		  printf (", (%d, %d)", pares[i][0], pares[i][1]);
		}
	  else{
		  printf ("\n(%d, %d)", pares[i][0], pares[i][1]);
		}
    }
    return 0;
}

