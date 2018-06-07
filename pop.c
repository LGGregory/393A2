#include <stdio.h>
#include <stdbool.h>
#define MINVALUE 30
#define MAXVALUE 105
#define NVALUE 5
#define DVALUE 10
#define PVALUE 20
#define MODVALUE 5
#define DIMEUPPER 'D'
#define DIMELOWER 'd'
#define NICKUPPER 'N'
#define NICKLOWER 'n'
#define PENTUPPER 'P'
#define PENTLOWER 'p'
#define RTRNUPPER 'R'
#define RTRNLOWER 'r'
#define EXITUPPER 'E'
#define EXITLOWER 'e'

void giveChange(int change){
    int remaining = change;
    int dimes = 0;
    int nickels = 0;

    while(remaining >= DVALUE){
        dimes++;
        remaining = remaining - DVALUE;
    }
    if(remaining>0){ //Either going to be 5 or 0
        nickels++;
    }
    printf("\t\tChange given: %d centimes as %d dime(s) and %d nickel(s).\n", change, dimes, nickels);
}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Please specify selling price as command line argument.\n");
        printf("Usage: pop [price]\n");
        return (1);
    }
    int price;
    sscanf(argv[1], "%d", &price);
    if(price%MODVALUE != 0){
        printf("Price must be a multiple of %d.\n", MODVALUE);
        return (1);
    }
    if(price < MINVALUE || price > MAXVALUE){
        printf("Price must be from %d to %d centimes inclusive\n", MINVALUE, MAXVALUE);
        return (1);
    }

    printf("\nWelcome to my C Pop Machine!\n");

    char input ='t';
    bool running = true;
    int change;
    int total;
    bool restarting;

    while(running){
        total = 0;
        restarting = false;
        printf("\nPop is %d centimes. Please insert any combinartion of nickels", price);
        printlf("[%c or %c], dimes [%c or %c] or pentes [%c or %c].", NICKUPPER, NICKLOWER, DIMEUPPER, DIMELOWER, PENTUPPER, PENTLOWER);
        printf("You can also press %c or %c for coin return.\n\n", RTRNUPPER, RTRNLOWER);
        while(total < price && running && !restarting){
            printf("Enter coin (NDPR) : ");
            scanf(" %c", &input);
            switch (input){
                case NICKUPPER :
                case NICKLOWER :
                    printf("\tNickel detected.\n");
                    total += NVALUE;
                    break;
                case DIMEUPPER :
                case DIMELOWER :
                    printf("\tDime detected.\n");
                    total += DVALUE;
                    break;
                case PENTUPPER :
                case PENTLOWER :
                    printf("\tPente detected.\n");
                    total += PVALUE;
                    break;
                case RTRNUPPER :
                case RTRNLOWER :
                    restarting = true;
                    break;
                case EXITUPPER :
                case EXITLOWER :
                    running = false;
                    break;
                default :
                    printf("\tUnknown coin rejected.\n");
                    break;
            }

            if(running && !restarting){
                printf("\t\tYou have inserted %d centimes.\n", total);
                if(total>=price){
                    change = total - price;
                    printf("\t\tPop is dispensed. Thank you for you business! Please come again.\n");
                } else {
                    printf("\t\tPlease insert %d more centimes.\n", (price - total));
                }
            } else {
                change = total;
           }
        }
        giveChange(change);
    }
    printf("Shutting down. Goodbye.\n");
    return (0);
}
