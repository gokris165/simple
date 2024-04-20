#include <stdio.h>

main() {
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;      // lower limit of temperature scale
    upper = 300;    // upper limit
    step = 20;      // step size

    fahr = lower;
    printf("Fahr\tCelsius\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    printf("\n");

    printf("Celsius\tFahr\n");
    celsius = lower;
    while(celsius <= upper){
        fahr = (celsius * 9.0 / 5.0) + 32.0;
        printf("%3.0f\t%6.1f\n", celsius, fahr);
        celsius += step;
    }
}