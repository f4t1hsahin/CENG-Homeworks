#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define SIZE 201

int harfler[26] = {0,0};
int indexes[26] = {0,0};
int precedence_of(char op){
    int value;
    switch(op){
        case '+':
        case '-': value = 1; break;
        case '/':
        case '*':value = 2; break;
        case '^':value = 3;break;
        default: value = 4;break; /* for the exp*/
    }
    return value;
}
int is_operator(char op){
    if(op == '+' || op == '-' || op == '*' || op == '/' || op == '^') return 1;
    return 0;
}
int is_higher(char stack[], int cursor,char exp){
    if(precedence_of(stack[cursor - 1]) > precedence_of(exp)) return 1;
    else if( precedence_of(stack[cursor - 1]) == precedence_of(exp)){
        if(exp == '^') return 0;
        else return 1;
    }
    return 0;
}
char top_stack(char stack[], int cursor){
    return stack[cursor - 1];
}
char pop_stack(char stack[], int *cursor){
    char res;
    res = stack[*cursor - 1];
    stack[*cursor] = 0;
    *cursor -= 1;
    return res;

}
void push_que(char exp[],char stack[][20],int *cursor){
    int i;
    for(i = 0; exp[i] ; i++){
        stack[*cursor][i] = exp[i];
    }
    stack[*cursor][i] = '\0';
    *cursor += 1; 
}
void push_stack(char exp,char stack[],int *cursor){
    stack[*cursor] = exp;
    *cursor += 1;
}
int itop(char exp[], char que[][20]){
    char stack[SIZE],temp[20], temp_func[20];
    int i, t, z, cursor_stack = 0, cursor_que = 0, cursor_temp = 0, cursor_func = 0, oo, yy;
    for(oo = 0;oo < SIZE; oo++){
        for(yy= 0; yy < 20; yy++){
            que[oo][yy] = 0;
        }
    }
    for(i = 0; exp[i] != '\0'; i++){
        if((exp[i] >= 'A' && exp[i] <= 'Z') || isdigit(exp[i]) || exp[i] == '.'){
            push_stack(exp[i],temp,&cursor_temp);
        }
        if( (exp[i] >= 'a' && exp[i] <= 'z') || exp[i] == '~'){
            temp_func[cursor_func] = exp[i];
            cursor_func++;
        }
        else if(is_operator(exp[i])){
            temp[cursor_temp] = '\0';
            for(t = 0; temp[t]; t++){
            }
            push_que(temp, que, &cursor_que);
            cursor_temp = 0;
            while(cursor_stack && top_stack(stack,cursor_stack) != '(' && is_higher(stack, cursor_stack,exp[i])){
                que[cursor_que][0] = top_stack(stack,cursor_stack);
                que[cursor_que][1] = '\0';
                cursor_que++;
                pop_stack(stack, &cursor_stack);
            }
            push_stack(exp[i], stack, &cursor_stack);
        }
        else if(exp[i] == '('){
            temp_func[cursor_func] = '\0';
            if(temp_func[0] == 's'){
                if(temp_func[1] == 'i'){
                    push_stack('s', stack, &cursor_stack);
                temp_func[1] = 0;
                }
                else{
                    push_stack('q', stack, &cursor_stack);
                temp_func[1] = 0;
                }
                temp_func[0] = 0;
            }
            else if(temp_func[0] == 'l'){
                push_stack('l', stack, &cursor_stack);
                temp_func[0] = 0;               
            }
            else if(temp_func[0] == 'c'){
                push_stack('c', stack, &cursor_stack);
                temp_func[0] = 0;
            }
            else if(temp_func[0] == '~'){
                push_stack('~', stack, &cursor_stack);
                temp_func[0] = 0;
            }
            cursor_func = 0;
            push_stack(exp[i], stack, &cursor_stack);
        }
        else if(exp[i] == ')'){
            temp[cursor_temp] = '\0';
            push_que(temp, que, &cursor_que);
            cursor_temp = 0;
            while(cursor_stack && top_stack(stack, cursor_stack) != '('){
                que[cursor_que][0] = top_stack(stack,cursor_stack);
                que[cursor_que][1] = '\0';
                cursor_que++;
                pop_stack(stack, &cursor_stack);
            }
            pop_stack(stack, &cursor_stack);
        }
    }
    temp[cursor_temp] = '\0';
    push_que(temp, que, &cursor_que);
    cursor_temp = 0;  
    for(z = 0;z < cursor_stack; z++){
        }      
    while(cursor_stack){
        que[cursor_que][0] = top_stack(stack,cursor_stack);
        que[cursor_que][1] = '\0';
        cursor_que++;
        pop_stack(stack, &cursor_stack);
    }
    que[cursor_que][0] = '\0';

    return cursor_que;
}
double xx_pop_stack(double stack[], int *cursor){
    double res;
    res = stack[*cursor - 1];
    stack[*cursor] = 0;
    *cursor -= 1;
    return res;
}
void xx_push_stack(double exp,double stack[],int *cursor){
    stack[*cursor] = exp;
    *cursor += 1;
}
double eval(char arr[][20],int len,double numbers[]){
    int i, j, cursor = 0;
    double stack[SIZE];
    double temp1,temp2;
    for(i = 0; i < len; i++){
        if( arr[i][0] >= 'A' && arr[i][0] <= 'Z'){
            xx_push_stack(numbers[arr[i][0] - 'A'],stack,&cursor);
        }
        if(isdigit(arr[i][0])){
            xx_push_stack(atof(arr[i]), stack, &cursor);
        }
        if(arr[i][0] == 's'){
            temp1 = sin(xx_pop_stack(stack, &cursor));
            xx_push_stack(temp1,stack, &cursor);        }
        if(arr[i][0] == 'l'){
            xx_push_stack(log(xx_pop_stack(stack, &cursor)),stack, &cursor);
        }
        if(arr[i][0] == 'c'){
            xx_push_stack(cos(xx_pop_stack(stack, &cursor)),stack, &cursor);
        }
        if(arr[i][0] == 'q'){
            xx_push_stack(sqrt(xx_pop_stack(stack, &cursor)),stack, &cursor);
        }
        if(arr[i][0] == '~'){
            xx_push_stack((-1 * xx_pop_stack(stack, &cursor)),stack, &cursor);
        }
        if(arr[i][0] == '+'){
            temp1 = xx_pop_stack(stack,&cursor);
            temp2 = xx_pop_stack(stack,&cursor);
            xx_push_stack( temp1 + temp2, stack, &cursor);
        }
        if(arr[i][0] == '-'){
            temp1 = xx_pop_stack(stack,&cursor);
            temp2 = xx_pop_stack(stack,&cursor);
            xx_push_stack( temp2 - temp1, stack, &cursor);
        }
        if(arr[i][0] == '*'){
            for(j = 0; j < 5; j++){
            }
            temp1 = xx_pop_stack(stack,&cursor);
            temp2 = xx_pop_stack(stack,&cursor);
            xx_push_stack( temp1 * temp2, stack, &cursor);
        }
        if(arr[i][0] == '/'){
            temp1 = xx_pop_stack(stack,&cursor);
            temp2 = xx_pop_stack(stack,&cursor);
            xx_push_stack( temp2 / temp1, stack, &cursor);
        }
        if(arr[i][0] == '^'){

            temp1 = xx_pop_stack(stack,&cursor);
            temp2 = xx_pop_stack(stack,&cursor);
            xx_push_stack( pow(temp2,temp1), stack, &cursor);
        }
    }
    return stack[0];
}
int* hangi_olasilik(double arr[],int interval,int len1){
    int i,j = 0,*res, index;
    double aralik = 0,random;
    res = malloc(26 * sizeof(int));
    for(i = 0;i < len1; i++){
        index = indexes[i];
        aralik = 0;
        j=0;
        random = rand() / ((double)RAND_MAX);
        while(aralik <= random && j < interval){
            aralik += arr[index * interval + j];
            j++;
        }
        res[index] = j-1;
    }
    return res;
}
double* olasilik_deger(double min[],double max[],int araliklar[],int interval,int len1){
    double *sayilar, uzunluk, min1;
    int i,aralik, index;
    sayilar = malloc(26 * sizeof(double));
    for(i = 0; i < len1; i++){
        index = indexes[i];
        aralik = araliklar[index];
        uzunluk = (max[index] - min[index]) / interval;
        min1 = (aralik - 1) * uzunluk + min[index];
        sayilar[index] = (rand() / ((double)RAND_MAX) + 1) * uzunluk + min1;
    }
    free(araliklar);
    return sayilar;
}
int main(){
    char exp[SIZE],res[SIZE][20],karakter;
    double *maxs,*mins,*probs,x, len, sum = 0;
    int i, j, slots,letter_count = 0;
    long int number_of_exp;
    register long int *counts;
    register double result, temp_min = LONG_MAX,temp_max = LONG_MIN, *numbers;
    register int index;
    srand(time(NULL));
    scanf("%[^\n]",exp);
    for(i = 0;exp[i];i++){
        if(exp[i] >= 'A' && exp[i] <= 'Z'){
            if(harfler[exp[i] -'A'] != 1){
                harfler[exp[i] -'A'] = 1;
                letter_count++;
            }
        }
    }
    for(i = 0, j = 0;i < 26; ++i){
        if(harfler[i] == 1){
            indexes[j] = i;
            j++;
        }
    }
    x = itop(exp,res);
    scanf(" %d %ld",&slots,&number_of_exp);
    maxs = malloc(26 * sizeof(double));
    mins = malloc(26 * sizeof(double));
    probs = malloc(26 * slots * sizeof(double));
    for(i = 0;i < letter_count;i++){
        scanf(" %c",&karakter);
        scanf(" %lf %lf", &mins[karakter - 'A'], &maxs[karakter - 'A']);
        for(j = 0; j < slots; j++){
        scanf(" %lf",&probs[(karakter - 'A') * slots + j]);
        }
    }
    numbers = calloc(26,sizeof(double));
    for(i = 0;i < 1000000; i++){
            numbers = olasilik_deger(mins,maxs,hangi_olasilik(probs,slots,letter_count),slots,letter_count);
            result = eval(res, x + 2,numbers);
            free(numbers);
            if(result > temp_max){
                temp_max = result;
            }
            if(result < temp_min){
                temp_min = result;
                
            }
        }
    counts = calloc(slots,sizeof(long int));
    len = (temp_max - temp_min) / slots;
    for(i = 0;i < number_of_exp; ++i){
        numbers = olasilik_deger(mins,maxs,hangi_olasilik(probs,slots,letter_count),slots,letter_count);
        result = eval(res, x + 2, numbers);
        free(numbers);
        if(result >= temp_max){
            index = slots - 1;
        }
        else if(result <= temp_min){
            index = 0;
        }
        else{
        index = (result - temp_min) / len;
        counts[index] += 1;
    }
    }
    printf("%.8f %.8f ",temp_min,temp_max);
    for(i = 0;i < slots; ++i){
        sum += (counts[i]/(double)number_of_exp);
    }
    for(i = 0;i < slots - 1; i++){
        printf("%.8f ", counts[i]/(double)number_of_exp);
    }
    printf("%.8f ",counts[i]/(double)number_of_exp + 1 - sum);
    return 0;
}