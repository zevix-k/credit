/*
Allyson Curtis
allyson.curtis@aggiemail.usu.edu
6-22-17
cs50/pset1/credit

Validate a credit card number according to Luhn's Algorithmn and output the credit card company

*/
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long long credit_number = 0;    
    long long number_of_digits = 0;
    int get_credit_company = 0;
    int get_credit_company_divide = 0;
    double get_credit_company_mod = 0;
    int get_credit_company_digits = 1;
    int count_digits = 0;
    long long modulo = 10;
    
    int number_of_loops = 0;
    long long divide_for_number_of_loops = 2;
    long long modulo_power = 2;    
    long long check_sum_first_mod = 0;
    long long check_sum_first_divide = 0;
    long long check_sum_first = 0;
    long long check_sum_first_multiply = 0;
    int multiply_digit_counter = 1;
    long long check_sum_first_digits = 0;
    long long credit_number_change = 0;
    long long check_sum_extra_digits_sum = 0;
    
    long long second_sum = 0;
    long long check_sum_second_mod = 0;
    long long check_sum_second_divide = 0;
    int n = 1;
    int x = 0;
    
    long long total_sum = 0;
    long long total_sum_check = 0;
    
    int american_express = 3;    //credit card specs
    int american_express_length = 15;
    int mastercard = 5;
    int mastercard_length = 16;
    int visa = 4;
    int visa_length_a = 13;
    int visa_length_b = 16;
    
    do
    {
    printf("Please enter your credit card number: %lld\n", credit_number);  //get credit card number
    credit_number = get_long_long();
    }while(credit_number <= 0);
    
    number_of_digits = credit_number;
    
    while (number_of_digits != 0)   //find the number of digits in credit card number
    {
        number_of_digits /= 10;
        count_digits++;
    }
    
    get_credit_company_divide = count_digits - get_credit_company_digits;   //arithmetic for getting credit card company
    get_credit_company_mod = pow(modulo, get_credit_company_divide);
    get_credit_company = credit_number / get_credit_company_mod;
    
    number_of_loops = count_digits / divide_for_number_of_loops;    //get number of times the loop to find every other digit needs to be iterated
    
    credit_number_change = credit_number;
    
    for (int i = 0; i < number_of_loops; i++)   //loop over credit card number for first set of checksum
    {
        check_sum_first_mod = pow(modulo, modulo_power);
        check_sum_first_divide = pow(modulo, (modulo_power - 1));
        check_sum_first = ((credit_number_change % check_sum_first_mod) / check_sum_first_divide);
        check_sum_first_multiply = check_sum_first * 2;
        if (check_sum_first_multiply != 0)   //make sure the product of check sum first is only one digit
        {
            check_sum_first_digits = check_sum_first_multiply; 
            while ((modulo % check_sum_first_digits) == 10) //make sure there is only one digit left
            {
                check_sum_first_digits /= 10;
                multiply_digit_counter++;
            }
            check_sum_first_digits = check_sum_first_multiply; 
            for (int j = 0; j < multiply_digit_counter; j++)    //multiply the split digits
            {
                check_sum_extra_digits_sum += (check_sum_first_digits % modulo);
                check_sum_first_digits /= 10;
            }
        }
        modulo_power += 2;
        credit_number_change = credit_number;
    }
    
    for(int k = 0; k < number_of_loops + 1; k++)
    {
        check_sum_second_mod = pow(modulo, n);
        check_sum_second_divide = pow(modulo, x);
        second_sum += ((credit_number % check_sum_second_mod) / check_sum_second_divide);
        n += 2;
        x += 2;
    }
    
    total_sum = check_sum_extra_digits_sum + second_sum;
    
    total_sum_check = total_sum % modulo;
    if(total_sum_check == 0)
    {
        printf("The credit card is valid!\n");
    }
    else
    {
        printf("The credit card is invalid\n");
    }
    
    if (count_digits == american_express_length && (get_credit_company == american_express))  //check for American Express
    {
        printf("AMEX\n");
    }
    else if (count_digits == mastercard_length && (get_credit_company == mastercard)) //check for MasterCard
    {
        printf("MASTERCARD\n");
    }
    else if ((count_digits == visa_length_a || count_digits == visa_length_b) && get_credit_company == visa)    //check for Visa
    {
        printf("VISA\n");
    }
    else    //invalid default
    {
        printf("INVALID\n");
    }
    
    return 0;
}