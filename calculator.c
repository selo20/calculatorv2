#include <stdio.h> 

int main(){
    int number_one, number_two, result;
    char answer = '0';

    printf("Welcome to my calculator.\nPress enter to continue...");
    getchar();

    while(1){
        printf("\nEnter 1 for addition\nEnter 2 for subtraction\nEnter 3 for multiplication\nEnter 4 for division\nEnter x for closing the program\n----------------------------------------\n► ");
        scanf("%c",&answer);
        if(answer == 'x')
            break;
        else if(answer=='1'){
            printf("\n\nPlease enter the numbers that you wanna add up.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one+number_two;        
        }
        else if (answer =='2'){
            printf("\n\nPlease enter the number you wanna substract from and then enter the second number.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one-number_two;
        }
        else if (answer == '3'){
            printf("\nPlease enter the number you wanna multiply.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one*number_two;
        }
        else if (answer=='4')
        {
            printf("\n\nPlease enter the number you wanna divide then enter the diviser.\n► ");
            scanf("%d %d",&number_one,&number_two);
            result = number_one/number_two;
        }
        else{
            printf("Please enter a valid operation.\n");
        }
        if(answer!='x' | answer=='1'| answer == '2' | answer == '3' | answer == '4')
            printf("The result is: %d\n",result);
    }
    return 0;
}