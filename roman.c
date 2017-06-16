#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "roman.h"
/*
struct dictionary *create(void);
void insert(struct dictionary *dict, char key, int value);
int error_check(char *roman_numerals);
int roman(char *roman_numerals, struct dictionary *dict);
*/
struct dictionary *create(void)
{
    struct dictionary *dict = malloc(sizeof(dictionary));
    struct key_value *end;
    dict->head = end;
    insert(dict, 'I', 1);
    insert(dict, 'V', 5);
    insert(dict, 'X', 10);
    insert(dict, 'L', 50);
    insert(dict, 'C', 100);
    insert(dict, 'D', 500);
    insert(dict, 'M', 1000);
    return(dict);
}

void insert(struct dictionary *dict, char key, int value)
{
    struct key_value *new = malloc(sizeof(key_value));
   
    new->key = key;
    new->value = value;
    new->next = dict->head;
    dict->head = new;

}

int error_check(char *roman_numerals)
{

    char valid[7] = "IVXLCDM";
    //Valid characters = IVXLCDM"
    //Largest number first
    //No more than 3 instances of a charachter
    //Exceptions IV,IX, XL, XC, CD, CM
    //Must be all caps
    //Max is 12 or 13 charcters
    

    //Search in groups of threes? 
    //Max of 4-5 sub categories. Add together, if they don't add sequential order. 

    if(strlen(roman_numerals) == 0)
    {
        perror("Must be between 0 and 4000");
        return 0;
    }
    
    int retFlag = 0;
    for(int i = 0; i < strlen(roman_numerals); i++)
    {

       // printf("%c\n", roman_numerals[i]);
        if(!isalpha(roman_numerals[i]))
        {
            perror("Numbers not allowed");
            retFlag = 1;
            break;
        }
        if (!isupper(roman_numerals[i]))
        {
            perror("Must be all caps");
            retFlag = 1;
            break;
        }
        
        int flag = 0;   
        for(int a = 0; a < strlen(valid); a++)
        {
            if(roman_numerals[i] == valid[a])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            perror("Invalid Character");
            retFlag = 1;
            break;
        }
    }
    if(retFlag == 1)
    {
        return 1;
    }
    return 0;
}


int roman(char *buf)
{
    
    char * roman_numerals = malloc(strlen(buf)-1);
    strncpy(roman_numerals, buf, strlen(buf)-1);
    struct dictionary *dict = create(); 
    int array[32];
    int err = error_check(roman_numerals);
    if(err == 1)
    {
        return 0;
    }   

    int a = 0;
    struct key_value *handle = dict->head;
    struct key_value *next_handle = dict->head->next;

    for(a; a < strlen(roman_numerals); a++)
    {   
        for(handle = dict->head; handle->next != NULL; handle = handle->next)
        {
            if(roman_numerals[a] == handle->key)
            {

                array[a] = handle->value;
                break;
            }
        }   
        
    }
   
    int sum = 0;
    int current = array[0];
    int occurence = 1;
    int v_flag = 0;
    int l_flag = 0;
    int d_flag = 0;
    for(int g = 0; g < a; g++)
    {
        if(array[g] == 5)
        {
            if(v_flag == 1)
            {
                fprintf(stderr, "Only one allowed\n");
                return 0;
            }
            v_flag = 1;
        }
        if(array[g] == 50)
        {
            if(l_flag == 1)
            {
                fprintf(stderr, "ONly one allowed\n");
                return 0;
            }
            l_flag = 1;
        }
        if(array[g] == 500)
        {
            if(d_flag == 1)
            {
                fprintf(stderr, "ONly one allowed\n");
                return 0;
            }
            d_flag = 1;
        }
        if( current == array[g])
        {
            occurence ++;
        }
        if(current < array[g])
        {
            fprintf(stderr, "Not valid\n");
            return 0;
        }
        if(current > array[g])
        {
            current = array[g];
            occurence = 1;
        }
        if(occurence > 4)
        {
            fprintf(stderr, "too many occurences\n");
            return 0;
        }
        sum += array[g];
    }
    
    /*        
    array[a] = 0;
    int outter = 0;
    int buf[32];
    int count =0;
    int sub_flag =0;
    int max_value = 0;
    int m_count = 0;
    int i_count = 0;
    int c_count = 0;
    int x_count = 0;
    int v_flag = 0;
    int l_flag = 0;
    int d_flag = 0;

    for(outter; outter < a; outter++)
    {
        if(sub_flag == 1)
        {
            if(array[outter] >= max_value)
            {
                fprintf(stderr,"Fuck you\n");
                return 0;
            }
        }  
        if(array[outter] < array[outter + 1])
        {
            if(array[outter] != 1 && array[outter] != 10 && array[outter] != 100)
            {
                fprintf(stderr,"invalid order\n");
                return 0;
            }
            if(array[outter + 1] > array[outter] * 10)
            {
                fprintf(stderr,"invalid subtraction\n");
                return 0;
            }
            if(array[outter + 1] == 500)
            {
                if(d_flag == 1)
                {
                    fprintf(stderr, "Too many D's\n");
                    return 0;
                }
                d_flag = 1;

            }
            else if(array[outter+1] == 50)
            {
                if(l_flag == 1)
                {
                    fprintf(stderr, "Too many L's\n");
                    return 0;
                }
                l_flag = 1;
            }
            else if(array[outter + 1] == 5)
            {
                if(v_flag == 1)
                {
                    fprintf(stderr, "Too many V's\n");
                    return 0;
                }
                v_flag = 1;  
            }
            sum += (array[outter + 1] - array[outter]);
            max_value = array[outter];
            sub_flag = 1;
            outter++;
        }
        else    
        {
            if(array[outter] == 1000)
            {
                if(m_count == 4)
                {
                    fprintf(stderr, "Too many M\n");
                    return 0;
                }
                m_count++;
            }
            else if(array[outter] == 500)
            {
                if(d_flag == 1)
                {
                    fprintf(stderr, "Too many D\n");
                    return 0;
                }
                d_flag = 1;
            }
            else if(array[outter] == 100)
            {
                if(c_count == 4)
                {
                    fprintf(stderr, "Too many Cs\n");
                    return 0;
                }
                c_count++;
            }
            else if(array[outter] == 50)
            {
                if(l_flag == 1)
                {
                    fprintf(stderr, "Too many L's\n");
                    return 0;
                }
                l_flag = 1;
            }
            else if(array[outter] == 10)
            {
                if(x_count == 4)
                {
                    fprintf(stderr, "Too many Xs\n");
                    return 0;
                }
                x_count++;
            }
            else if(array[outter] == 5)
            {
                if(v_flag == 1)
                {
                    fprintf(stderr, "Too many V's\n");
                    return 0;
                }
                v_flag = 1;
            }
            else if(array[outter] == 1)
            {
                if(i_count == 4)
                {
                    fprintf(stderr, "Too many i's\n");
                    return 0;
                }
                i_count++;
            }
            
            count+=1;
            sum += array[outter];
        }
            
    }   
    */
    
    if(sum > 4000)
    {
        fprintf(stderr, "Values greater than 4000 not allowed\n");
        return 0;
    }

    return sum;
}

/*
int main(int argc, char *argv[])
{
    struct dictionary *dict = create(); 
    int retval = roman(argv[1], dict);
    
    if(retval == 1)
    {
        printf("Valid\n");
    }
       
   return 0;
}
*/
