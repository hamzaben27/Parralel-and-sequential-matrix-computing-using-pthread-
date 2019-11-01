//benbachir hamza M2 infrmatIQUE INDISTRUEL 
	//including bibliotheques
#include <stdio.h> 
#include <stdlib.h>
#include <sys/time.h> 
#include <pthread.h> 
#include <time.h> 
#include<math.h>
 //benbachir hamza
 // define global variable 
#define ligne 6
#define coll 4
#define collB 12
#define NBR_thr 4

int Matrix_A [ligne][coll];
int Matrix_B [coll][collB];
int Matrix_C [ligne][collB]; 
	
	// fonction de multiplication des deux matrix 
 void* multi(int ID) {

	 
	 int debut,fin;
  	debut=ID*(ligne/NBR_thr);
	 if(ID==NBR_thr-1)
     		fin=ligne-1;
	else 
		fin=debut+(ligne/NBR_thr)-1;

	for(int i = debut; i <= fin; i++){ 
      
   
	int sum ;
	for(int l = debut; l <= fin; l++){
		for (int i = 0; i < collB; i++ ){
			sum = 0;
	
			for (int j= 0; j < coll; j++)			
					sum += Matrix_A [l][j] * Matrix_B [j][i];

			Matrix_C [l][i] = sum;

		}
	}

	}

	pthread_exit(NULL);
	}
     // fin 
	
 
		//main 

int main(int argc, char *argv[]) {
	pthread_t threads[ligne]; 
    
      	int thr; 
      	double debut,fin;
      	srand(time(NULL));
// affichage matrice A 
printf("matrice A \n");

 for (int i = 0; i <ligne; i++) { 
        for (int j = 0; j < coll; j++) { 
            Matrix_A[i][j] = rand() % 10;
			printf("%d ",Matrix_A[i][j]); 
             
        } 
		printf(" \n");
    }
	// matrice B 
	printf("matrice B \n");
   for (int i = 0; i <ligne; i++) { 
        for (int j = 0; j < collB; j++) { 
	Matrix_B[i][j] = rand() % 10;
	 printf("%d ",Matrix_B[i][j]); 
		}
		printf(" \n");
   }


	printf("le calcul par \n");
	debut = clock();

	for(thr = 0; thr < NBR_thr ; thr++){ 
			//int pt;
	      int pt = pthread_create(&threads[thr], NULL, multi, thr); 
	}

	for(thr = 0; thr < NBR_thr; thr++){ 
	      (void)pthread_join(threads[thr],NULL);
         }

         fin =  clock();

		 for(int i = 0 ; i < ligne ; i++){
		 for (int j = 0 ; j < collB ; j++) 
	                printf("%d ",Matrix_C[i][j]);
	         printf(" \n");                  
	}
		//affichage
	printf("temps parallele=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);


	printf("le calcul seq \n");
	debut =  clock();
	for(int i=0; i<ligne; i++){
		int sum=0;
		for(int j=0; j<collB; j++){
	            	sum = 0;
			for(int k=0; k<coll; k++)
	                  	 sum = sum + Matrix_A[i][k] * Matrix_B[k][j];
	                 Matrix_C[i][j] = sum;
	        }
	 }
	fin =  clock();

	        for(int i = 0 ; i < ligne ; i++){
	        	for (int j = 0 ; j < collB ; j++) 
	                	printf("%d ",Matrix_C[i][j]);
	        	printf(" \n");
	         }
	 printf("temps sequentielle=%f\n", (double)(fin-debut)/CLOCKS_PER_SEC);
	return 0;
}     
	
 

