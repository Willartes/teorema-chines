#include <stdio.h>
#include <stdlib.h>
//Variável global do produto dos módulos
int M;
/*
Função para calcular o MDC usando o algoritmo de Euclides
*/

int mdc(int numero1, int numeros2){
    while(numeros2 != 0){
        int temporaria = numeros2;
        numeros2 = numero1 % numeros2;
        numero1 = temporaria;
    }
    return numero1;
}

/* Função para calcular o inverso modular de
'a' módulo 'm'
*/

int inversoModular(int a, int m){
    // Se 'a' e 'm' não são primos entre si, o
    //inverso modular não existe
    if(mdc(a, m) != 1){
        // Retorna -1 para indicar que o inverso não existe
        return -1;
    }
    /*Encontra o inverso modular usando o Algoritmo
    Estendido de Euclides
    */
    int novoT = 0, novoR = m;
    int antigoT = 1, antigoR = a;

    while(novoR != 0){
        int quociente = antigoR/novoR;
        int temporaria = novoR;
        novoR = antigoR - quociente * novoR;
        antigoR = temporaria;

        temporaria = novoT;
        novoT = antigoT - quociente * novoT;
        antigoT = temporaria;
    }

    if(antigoT < 0){
        antigoT += m;
    }

    return antigoT;
}

/*Função para resolver o Teorema Chinês do resto */

int teoremaChinesDoResto(int *restos, int *modulos, int numeroDeCongruencias){
    // Calcula o produto de todos os módulos (m)
    M = 1;
    for(int i=0; i < numeroDeCongruencias; i++){
        M *= modulos[i];
    }

    //Calcula a solução do sistema de congruências

    int solucao = 0;

    for(int i=0; i < numeroDeCongruencias;i++){
        //Calcula Mi (produto dos módulos, exceto mi)
        int Mi = M/ modulos[i];

        //Calcula o inverso modular de Mi módulo mi
        int yi = inversoModular(Mi, modulos[i]);

        // Calcula a parcela da solução
        solucao += restos[i] * Mi * yi;
    }
    // Retorna a solução módulo M
    return solucao%M;
}

int main()
{

    int numeroDeCongruencias = 1;
    char texto[] = "DIGITE O NÚMERO DE CONGRUÊNCIAS NO SISTEMA OU 'ZERO' PARA SAIR: ";
    int largura = 70;

    while(numeroDeCongruencias != 0){

        printf("%*s", largura, texto);
        //printf("Digite o número de congruências no sistema: ");
        scanf("%d", &numeroDeCongruencias);

        if(numeroDeCongruencias == 0){
            break;
        }
        //Alocar memória para arrays de restos e módulos
        int *restos = (int*) malloc(numeroDeCongruencias * sizeof(int));
        int *modulos = (int*) malloc(numeroDeCongruencias * sizeof(int));
        printf("\n");
        // Solicitar os restos e módulos ao usuário
        printf("Digite os restos e módulos para cada congruência:\n");
        printf("\n");
        for(int i = 0; i < numeroDeCongruencias;i++){
            printf("Congruência %d\n", i+1);
            printf("Resto: ");
            scanf("%d", &restos[i]);
            printf("Módulo: ");
            scanf("%d", &modulos[i]);
            printf("\n");
        }

        //Verificar se são coprimos
        int coprimos = 1;

        for(int i=0;i < numeroDeCongruencias;i++){
            for(int j = i + 1;j < numeroDeCongruencias;j++){
                if(mdc(modulos[i], modulos[j]) != 1){
                    coprimos = 0;
                    break;
                }
            }
            if(!coprimos){
                break;
            }
        }

        //Resolver o Teorema Chinês do Resto
        int solucao = teoremaChinesDoResto(restos, modulos, numeroDeCongruencias);

        //Imprimir a solução
        if(!coprimos){
            printf("O sistema não está na condição do teorema chinês dos restos\n");
        } else {
            printf("A solução do sistema de congruência é: %d mod %d\n", solucao, M);
        }
        printf("\n");

        //Liberar memória alocada
        free(restos);
        free(modulos);


    }

        system("pause");

        return 0;

}
