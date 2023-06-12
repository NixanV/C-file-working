

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    char name[36];
    char r_plate[9];
    double price;
    int priority;
}Car;


void selectByAverage(Car cars[], int number_ofCars){
   double avgPrice=0, sum = 0;
   for(int i = 0; i<number_ofCars; i++){
        sum += cars[i].price;

   }
   avgPrice = sum/number_ofCars;
   for(int i=0; i<number_ofCars; i++){
        if(cars[i].price > avgPrice){
            printf("%s - %.2lf", cars[i].r_plate, cars[i].price);
        }
   }

}

void printByPlate(char l_plate[9]){
    FILE *fp;
    unsigned len;
    Car cars;
    fp = fopen("auto.bin", "rb");
    if(fp == NULL){
        printf("Error of opening a binary fail!");
        exit(3);
    }


    while(true){
        if(fread(&len, sizeof(unsigned), 1, fp) != 1){
            if(!feof(fp)){
                printf("Error!");
                fclose(fp);
                exit(4);
            }
            else {
                break;
            }
        }
        if(fread(&cars.name, sizeof(char), len, fp) != len){
            printf("Error!");
                fclose(fp);
                exit(4);
        }
        cars.name[len] = '\0';

        if(fread(&cars.r_plate, sizeof(char), 8, fp) != 8){
            printf("Error!");
                fclose(fp);
                exit(5);
        }
        if(fread(&cars.price, sizeof(double), 1, fp) != 1){
            printf("Error!");
                fclose(fp);
                exit(6);
        }
        if(fread(&cars.priority, sizeof(int), 1, fp) != 1){
            printf("Error!");
                fclose(fp);
                exit(7);
        }

        if(l_plate == cars.r_plate){
            printf("Bin Name: %s\n", cars.name);
            printf("Bin License plate: %s\n", cars.r_plate);
            printf("Bin Price: %.2lf\n", cars.price);
            printf("Bin Priority: %d\n", cars.priority);

        }

    }
    fclose(fp);

}

void writeIntoFail(Car cars[], int num){

    FILE *fptr;
    int size;
    fptr = fopen("auto.bin", "ab");
    if(fptr == NULL){
        printf("ERROR!");
        exit(18);
    }

    for(int i = 0; i<num; i++){
        size = strlen(cars[i].name);
        fwrite(&size, sizeof(int), 1, fptr);
        fwrite(cars[i].name, sizeof(char),size, fptr);
        fwrite(cars[i].r_plate, sizeof(char), 8, fptr);
        fwrite(&cars[i].price, sizeof(double), 1, fptr);
        fwrite(&cars[i].priority, sizeof(int), 1, fptr);

    }
    fclose(fptr);


}

int* arr;

int main(){
    int number_of_cars;
    printf("Import number of cars: ");
    scanf("%d", &number_of_cars);
    getchar();
    Car* cars = calloc(number_of_cars, sizeof(Car));
    //printf("%zu bites\n", sizeof(*cars));
    //printf("%zu bites\n", sizeof(Car));

    if(cars == NULL){
        printf("Memory allocation fail");
        exit(1);
    }


    for(int i=0; i<number_of_cars; i++){
        printf("Enter name: ");
        fgets(cars[i].name, 36, stdin);
        cars[i].name[strlen(cars[i].name)-1] = '\0';

        printf("Enter register plate: ");
        fgets(cars[i].r_plate, 9, stdin);

        printf("Enter price: ");
        scanf("%lf", &cars[i].price);

        printf("Enter priority number: ");
        scanf("%d", &cars[i].priority);

        getchar();

    }

    FILE *fptr;
    fptr = fopen("autoText.txt", "a");
    if(fptr == NULL){
        printf("Cant find file!");
        exit(1);
    }

    for(int i=0; i<number_of_cars; i++){
        fprintf(fptr, "%d; %s; %s; %.2lf; %d\n", strlen(cars[i].name), cars[i].name, cars[i].r_plate, cars[i].price, cars[i].priority);
    }
    fclose(fptr);

    selectByAverage(cars, number_of_cars);
    writeIntoFail(cars, number_of_cars);
    printByPlate("AB1234CD");
    return 0;


}




