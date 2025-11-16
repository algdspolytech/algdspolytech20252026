#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUM_OPERATION 4
#define MAX_DIGITS 100
int read_input_from_file(const char* filename, char* num1_str, long long* num2) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open input file %s\n", filename);
        return 0;
    }
    

      if (fscanf(file, "%101s", num1_str) != 1) {
        fclose(file);
        return 0;
    }
    printf("First number - %d\n",*num2);
    
    // Читаем B как long long
    if (fscanf(file, "%lld", num2) != 1) {
        fclose(file);
        return 0;
    }

    
     printf("Second number - %d\n",*num2);
    
    fclose(file);
    return 1;
}
void write_output_to_file(const char* filename, int digits[], int n, char* result_oper, int target, int found) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot open output file %s\n", filename);
        return;
    }
    
    if (found) {
        int has_operations = 0;
        for (int i = 0; i < n-1; i++) {
            if (result_oper[i] != 0) {
                has_operations = 1;
                break;
            }
        }
        
        if (has_operations) {
            fprintf(file, "%d", digits[0]);
            for (int i = 0; i < n-1; i++) {
                fprintf(file, "%c%d", result_oper[i], digits[i+1]);
            }
            fprintf(file, "=%d\n", target);
        } else {
            int original_number = 0;
            for (int i = 0; i < n; i++) {
                original_number = original_number * 10 + digits[i];
            }
            fprintf(file, "%d=%d\n", original_number, target);
        }
    } else {
        fprintf(file, "0\n");
    }
    
    fclose(file);
}

double solve_equation(int digits[], char oper[], int n) {
    if (n==1){
        return digits[0];
    }
    double temp_numbers[MAX_DIGITS];
    char temp_operators[MAX_DIGITS];
    
    for (int i = 0; i < n; i++) {
        temp_numbers[i] = digits[i];
    }
    
    int new_size = n;
    for (int i = 0; i < new_size - 1; i++) {
        if (oper[i] == '*' || oper[i] == '/') {
            if (oper[i] == '*') {
                temp_numbers[i] = temp_numbers[i] * temp_numbers[i + 1];
            } else { 
                if (temp_numbers[i + 1] == 0) return NAN; 
                temp_numbers[i] = temp_numbers[i] / temp_numbers[i + 1];
            }
            
            for (int j = i + 1; j < new_size - 1; j++) {
                temp_numbers[j] = temp_numbers[j + 1];
                oper[j - 1] = oper[j];
            }
            new_size--;
            i--; 
        }
    }

    double result = temp_numbers[0];
    for (int i = 0; i < new_size - 1; i++) {
        if (oper[i] == '+') {
            result += temp_numbers[i + 1];
        } else if (oper[i] == '-') {
            result -= temp_numbers[i + 1];
        }
    }
    
    return result;
}
int digits_split(const char* num_str,int* digits){
    int len = strlen(num_str);
    for (int i = 0; i < len; i++) {
        digits[i] = num_str[i] - '0';  // '5' → 5
    }
    return len;
}


 int find_equation(int* digits,int n,int depth,char*result_oper,char* current_oper,char* operations,int target) {
    if (depth == 0) { 
        int original_number = 0;
        for (int i = 0; i < n; i++) {
            original_number = original_number * 10 + digits[i];
        }
        if (original_number == target) {
            return 1;  
        }
    }
    if (depth==n-1){
        double result=solve_equation(digits,current_oper,n);
        if (result==target) {
             for(int i = 0; i < n-1; i++) {
                result_oper[i] = current_oper[i];
            }
            return 1;
        }
        return 0;
    }
    for(int i=0;i<NUM_OPERATION;i++){
        current_oper[depth]=operations[i];
        if(find_equation(digits,n,depth+1,result_oper,current_oper,operations,target)) {
            return 1;
        }
    }
    return 0;
 }