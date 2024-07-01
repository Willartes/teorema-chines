#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n, n2;
    double soma1 = 0.0, soma2 = 0.0, pi = 0.0;

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    //Calcula a série
    for(int i = 0;i <= n;i++){
        soma1 += (pow(-1, i))/(2*i +1);
    }
    for(int i = 0;i <= n+1;i++){
        soma2 += pow(-1, i)/(2*i +1);
    }
    soma1 *= 4;
    soma2 *= 4;

    pi = (soma1 + soma2)/2;

    double subtrair = soma1 - pi;
    printf("A interação de Libniz é: %.20lf\n", soma1);
    printf("O número de pi é: %.20lf\n", pi);
    printf("A diferença é: %.20lf\n", subtrair);

    system("pause");

    return 0;
}
