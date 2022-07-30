#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define size 4


int map[size][size] = {
    0,2,2,2,
    2,2,2,0,
    2,2,4,0,
    0,2,0,0
};
int score = 0;

void initmap();
void randomap();
void printmap();
void maingame();

int gameover();
int check();

void up();
void down();
void right();
void left();
void reset();

int main(){
    maingame();
    return 0;
}


void maingame(){
    
    initmap();

    int gameshouldclose = 0;
    
    while(!gameshouldclose){
        system("cls");
        printmap();
        int key = getch();
        if(key == 224 ) key = getch();
        if(key == 27) gameshouldclose = 1;
        else if(key == 72 || key == 119) up();
        else if(key == 80 || key == 115) down();
        else if(key == 75 || key == 97) left();
        else if(key == 77 || key == 100) right();
        else if(key == 114) reset();
        if(check() == 0) randomap();
        else if(check() == 1) continue;
        else gameshouldclose = gameover();
    }
}
int gameover(){
    printf("FINAL SCORE: %d\n" , score);
    printf("PRESS R TO PLAY ANGIN\nPRESS E TO EXIT\n");
    while(1){
        int key2 = getch();
        if(key2 == 224 ) key2 = getch();
        if(key2 == 114){
            reset();
            return 0;
        }
        else if(key2 == 27 || key2 == 101) return 1;
    }
    return -1;
}
void initmap(){
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            map[i][j] = 0;
        }
    }
    randomap();
}
void randomap(){
    int i,j;
    srand(time(NULL));
    do{
        i = rand() % size;
        j = rand() % size;
    }while(map[i][j] != 0);
    map[i][j]= 2 ;
}
void printmap()
{
    printf(" SCORE: %d\n" , score);
    for(int i = 0 ; i < size ; i++){
        for(int j = 0 ; j < size ; j++){
            printf(" %d",map[i][j]);
        }
        printf("\n");
    }
}
//平移->合并->平移
void up(){
    for(int j = 0 ; j < size ; j++){
        for(int i = 0 ; i < size ; i++){
            if(map[i][j] == 0){
                for(int k = i + 1 ; k < size ; k++){
                    if(map[k][j] != 0){
                        int temp = map[k][j];
                        map[k][j] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
        for(int i = 1 ; i < size ; i++){
            if(map[i-1][j] == map[i][j]){
                map[i-1][j] *= 2;
                score += map[i-1][j];
                map[i][j] = 0;
            } 
        }
        for(int i = 0 ; i < size ; i++){
            if(map[i][j] == 0){
                for(int k = i + 1 ; k < size ; k++){
                    if(map[k][j] != 0){
                        int temp = map[k][j];
                        map[k][j] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
    }
}
void down(){
    for(int j = 0 ; j < size ; j++){
        for(int i = size - 1 ; i > -1 ; i--){
            if(map[i][j] == 0){
                for(int k = i - 1 ; k > -1 ; k--){
                    if(map[k][j] != 0){
                        int temp = map[k][j];
                        map[k][j] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
        for(int i = size - 2 ; i > -1 ; i--){
            if(map[i + 1][j] == map[i][j]){
                map[i + 1][j] *= 2;
                score += map[i + 1][j];
                map[i][j] = 0;
            } 
        }
         for(int i = size - 1 ; i > -1 ; i--){
            if(map[i][j] == 0){
                for(int k = i - 1 ; k > -1 ; k--){
                    if(map[k][j] != 0){
                        int temp = map[k][j];
                        map[k][j] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
    }
}
void left(){
    for(int i = 0 ; i < size ; i++ ){
        for(int j = 0 ; j < size ; j++){
            if(map[i][j] == 0){
                for(int l = j + 1 ; l < size ; l++){
                    if(map[i][l] != 0){
                        int temp = map[i][l];
                        map[i][l] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
        for(int j = 1 ; j < size ; j++ ){
            if(map[i][j-1] == map[i][j]){
                map[i][j-1] *= 2;
                score += map[i][j - 1];
                map[i][j] = 0;
            }
        }
        for(int j = 0 ; j < size ; j++){
            if(map[i][j] == 0){
                for(int l = j + 1 ; l < size ; l++){
                    if(map[i][l] != 0){
                        int temp = map[i][l];
                        map[i][l] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
    }
}
void right(){
     for(int i = 0 ; i < size ; i++ ){
        for(int j = size -1 ; j > -1 ; j--){
            if(map[i][j] == 0){
                for(int l = j - 1 ; l > -1 ; l--){
                    if(map[i][l] != 0){
                        int temp = map[i][l];
                        map[i][l] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
        for(int j = size - 2 ; j > -1 ; j-- ){
            if(map[i][j + 1] == map[i][j]){
                map[i][j + 1] *= 2;
                score += map[i][j + 1];
                map[i][j] = 0;
            }
        }
        for(int j = 0 ; j < size ; j++){
            if(map[i][j] == 0){
                for(int l = j - 1 ; l > -1 ; l--){
                    if(map[i][l] != 0){
                        int temp = map[i][l];
                        map[i][l] = map[i][j];
                        map[i][j] = temp;
                        break;
                    }
                }
            }
        }
    }
}
void reset(){
    initmap();
    score = 0;
}
int check(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(map[i][j] == 0) return 0;
        }
    }
    for(int i = 1; i < size; i++){
        for(int j = 1; j < size; j++){
            if((map[i][j]==map[i-1][j])||(map[i][j]==map[i][j-1])) return 1;
        }
    }
    return -1;
}