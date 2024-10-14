#include <stdio.h> 

int main(){
    int number_one, number_two, result;
    char answer = '0';

    printf("Welcome to my calculator.\nPress enter to continue...");
    getchar();
calc_loop:

        printf("\nEnter 1 for addition\nEnter 2 for subtraction\nEnter 3 for multiplication\nEnter 4 for division\nEnter x for closing the program\n----------------------------------------\n► ");
        scanf("%c",&answer);

        switch (answer)
        {

        case '1':
            printf("\n\nPlease enter the numbers that you wanna add up.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one+number_two;
            printf("The result is: %d\n",result);
            break;
        
        case '2':
            printf("\n\nPlease enter the number you wanna substract from and then enter the second number.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one-number_two;
            printf("The result is: %d\n",result);
            break;

        case '3':
            printf("\nPlease enter the number you wanna multiply.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one*number_two;
            printf("The result is: %d\n",result);
            break;

        case '4':
            printf("\n\nPlease enter the number you wanna divide then enter the diviser.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one/number_two;
            printf("The result is: %d\n",result);
            break;

        case 'x':
            return 0;

        default:
            printf("Please enter a valid operation.\n");
            goto calc_loop;
        }
        printf("The result is: %d\n",result);
        goto calc_loop;
}