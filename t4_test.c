// #include "t1.h"
// #include "t2.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 50
#define ARRAY_SIZE 18625
// #define ARRAY_SIZE 9


int numTerms = 0;

typedef struct Game Game;
struct Game
{
    char name[MAX_STRING_SIZE];
    char console[MAX_STRING_SIZE];
    int score;
    int year;
};

Game create_struct(char *NAME, char *CONSOLE, int SCORE, int YEAR)
{
    Game *game = (Game *)malloc(sizeof(Game));
    strcpy(game->name, NAME);
    strcpy(game->console, CONSOLE);
    game->score = SCORE;
    game->year = YEAR;

    return *game;
}   

void next_token(char *buf, FILE *f, int string_max)
{
    // start by skipping any characters we're not interested in
    buf[0] = fgetc(f);
    int quoted = 0;
    while ((!isalnum(buf[0])) && (!feof(f)) && (buf[0] != '*') && (buf[0] != '[') && (buf[0] != '{') && (buf[0] == '"'))
    {
        //move on
        if(buf[0] == '"'){ 
            quoted=!quoted; //turn on quotes
            buf[0] = fgetc(f);//get next character which will be "
            if(buf[0] == '"'){
                //then double quoted
                //making my own string here
                quoted=!quoted;
                buf[0]=' ';
                buf[1]='\0';
                return;
            }
           
        }else{
            buf[0] = fgetc(f);
        }
    }

    int i = 1;
    for (;;)
    {
        
        buf[i] = fgetc(f); // get next character from file

        if(buf[i] == '"'){ quoted=!quoted; buf[i] = fgetc(f);}
        if(buf[i] == ',' && !quoted){ break; }
        if(buf[i] == '\n'){ break; }
     

        if (feof(f))
        {
            break;
        } // file ended?
        if (i < (string_max - 1))
        {
            ++i;
        } // truncate strings that are too long
    }
    buf[i] = '\0'; // NULL terminate the string
}

//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char *fname, Game array[])
{
    FILE *f;
    char buf[MAX_STRING_SIZE];
    char tempNAME[MAX_STRING_SIZE];
    char tempCONSOLE[MAX_STRING_SIZE];
    int tempSCORE;
    int tempYEAR;
    int i = 0;

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }

    // read until the end of the file
    while (!feof(f))
    {
        next_token(buf, f, MAX_STRING_SIZE);
        if(feof(f)){
            break;
        }
        strcpy(tempNAME, buf);
        next_token(buf, f, MAX_STRING_SIZE);
        strcpy(tempCONSOLE, buf);
        next_token(buf, f, MAX_STRING_SIZE);
        tempSCORE = atoi(buf);
        next_token(buf, f, MAX_STRING_SIZE);
        tempYEAR = atoi(buf);

        if(strcmp(tempNAME, "title") != 0){
            array[i] = create_struct(tempNAME, tempCONSOLE, tempSCORE, tempYEAR);
            i++;
            numTerms++;
        }
       
    }
    printf("\nFile %s loaded\n", fname);
    float load = ((float)numTerms / (float)ARRAY_SIZE);
    printf("Capacity: %i\nNum Terms: %i\nLoad: %f\n\n", ARRAY_SIZE, numTerms, load);

    // always remember to close your file stream
    fclose(f);

    return 1;
}

void print_struct(Game game){
    printf("%-50s ", game.name);
    printf("%-20s ", game.console);
    printf("%-3i ", game.score);
    printf("%i\n", game.year);
}

void print_array(Game array[]){
    for(int i = 0; i<ARRAY_SIZE; i++){
        print_struct(array[i]);
    }
}

void swap(Game *x, Game *y){
  Game tmp = *x;
  *x = *y;
  *y = tmp;
  // number_swaps++;
//   printf("swaping\n");
}

void selectionSort(Game array[], int size){
    int min_pos;

    for(int i = 0; i<(size-1); i++){
        min_pos = i;

        for(int j=(i+1); j<size; j++){
            if(array[j].score < array[min_pos].score){
                min_pos = j;
            }
        }

        if(min_pos != i){
            swap(&array[min_pos], &array[i]);
        }
    }
}

void print_top10(Game array[]){
    int j = 1;
    for(int i=ARRAY_SIZE-1; i>=ARRAY_SIZE-10; i--){
        printf("%i.\t", j);
        print_struct(array[i]);
        j++;
    }
}


int main(){
    Game arr[ARRAY_SIZE];
    load_file("t4_ign.csv", arr);

    selectionSort(arr, ARRAY_SIZE);
    
    printf("\n\n");
    print_top10(arr);
    printf("\n\n");



    return 0;
}