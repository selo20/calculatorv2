#include <stdio.h> 

int main(){
    
    char buffer[64];
    float result;
    int number_one, number_two;
    char answer = '0',approval;

    printf("Welcome to my calculator\nPress enter to continue...");
    getchar();

    while(1){

        printf("\n\n┌───────────────────────────────────────┐\n│Enter 1 for addition\t\t\t│\n├───────────────────────────────────────┤\n│Enter 2 for subtraction\t\t│\n├───────────────────────────────────────┤\n│Enter 3 for multiplication\t\t│\n├───────────────────────────────────────┤\n│Enter 4 for division\t\t\t│\n├───────────────────────────────────────┤\n│Enter x for closing the program\t│\n└───────────────────────────────────────┘\n► ");
        scanf(" %s", buffer);

        switch (buffer[0])
        {

        case '1':
            printf("\nPlease enter the numbers that you wanna add up.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one+number_two;
            break;
        
        case '2':
            printf("\nPlease enter the number you wanna substract from and then enter the second number.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one-number_two;
            break;

        case '3':
            printf("\nPlease enter the number you wanna multiply.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one*number_two;
            break;

        case '4':
            printf("\nPlease enter the number you wanna divide then enter the diviser.\n► ");
            scanf("%d %d",&number_one,&number_two);
            if(number_two==0){
                printf("You cant divide any number with zero!\n");
                continue;
            }
            result = (float) number_one/number_two;
            break;

        case 'x':
            return 0;

        default:
            printf("Please enter a valid operation.\n");
            continue;
        }
        if(answer=='4'){
            printf("The result is: %.2f\n",result);
            printf("\nPress enter to continue...");
            getchar();
        }
        else{
            printf("The result is: %.0f\n",result);
            printf("\nPress enter to continue...");
    }
    }
}