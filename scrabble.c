#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util/print_board.h"
#include "util/scrabble.h"

int number(char *p) //transforma un element de tip char intr-un int 
{
    int l=strlen(p);
    int suma=0;
    for(int i=0; i<l; i++)
    {
        if(p[i]>='0' && p[i]<='9')
        {
            suma=suma*10;
            suma+=p[i]-'0';
        }
    }
    return suma;
}

void task0(char game_board[15][15]) //adauga caracterul '.' pe toate pozitiile in matrice
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
            game_board[i][j]='.';
    }
}

void adaugare_matrice(char game_board[15][15], int y, int x, int d, char string[20])
//adauga un cuvant in matrice, litera cu litera in functie de directie
{
    int indice_cuvant;
    long unsigned int j;
    if(d==0)
        {
            indice_cuvant=0;
            for(j=x; j<x+strlen(string); j++)
            {
                game_board[y][j]=string[indice_cuvant];
                indice_cuvant++;
            }    
        }
        else
        {
            if(d==1)
            {
                indice_cuvant=0;
                for(j=y; j<y+strlen(string); j++)
                {
                    game_board[j][x]=string[indice_cuvant];
                    indice_cuvant++;
                }
            }
        }
}

void coordonate_cuvant(char sir[50], int *y, int *x, int *d, char **cuvant)
//memoreaza coordonatele y, x, d pentru un cuvant dat
{
    char *xchar, *ychar, *dchar;
    fgets(sir, 50, stdin);
    sir[strlen(sir)-1]=0;
    ychar=strtok(sir," ");
    *y=number(ychar);
    xchar=strtok(NULL," ");
    *x=number(xchar);
    dchar=strtok(NULL," ");
    *d=number(dchar);
    *cuvant=strtok(NULL," ");
}

void task1(char game_board[15][15]) 
//adauga in matricea de joc cele n cuvinte, in functie de coordonatele acestora
{
    char n_char[10], sir[50], *string;
    int n, Yi, Xi, Di;
    fgets(n_char, 10, stdin); //o metoda de a citi numarul de cuvinte ce urmeaza a fi prelucrate
    n=number(n_char);
    task0(game_board);
    for(int i=1; i<=n; i++)
    {
        coordonate_cuvant(sir, &Yi, &Xi, &Di, &string);
        adaugare_matrice(game_board, Yi, Xi, Di, string);
    }
    print_board(game_board);
}

int calculare_scor(char cuvant[20])
//calculeaza scorul pentru un cuvant in functie de literele sale
{
    int scor=0;
    for(long unsigned int k=0; k<strlen(cuvant); k++)
            {
                if(strchr("AEILNORSTU", cuvant[k])!=0)
                    scor=scor+1;
                else 
                    if(strchr("DG", cuvant[k])!=0)
                        scor=scor+2;
                else 
                    if(strchr("BCMP", cuvant[k])!=0)
                        scor=scor+3;
                else
                    if(strchr("FHVWY", cuvant[k])!=0)
                        scor=scor+4;
                else 
                    if(cuvant[k]=='K')
                        scor=scor+5;
                else 
                    if(strchr("JX", cuvant[k])!=0)
                        scor=scor+8;
                else 
                    if(strchr("QZ", cuvant[k])!=0)
                        scor=scor+10;
            }
    return scor;
}

void task2()
{
    char n_char[10], player1[50], player2[50], *cuvant;
    int n, scor_player1=0, scor_player2=0;
    fgets(n_char, 10, stdin);
    n=number(n_char);
    for(int i=1; i<=n; i++)
    {
        if(i%2!=0) //se calculeaza scorul pentru primul jucator 
        {
            fgets(player1, 50, stdin);
            player1[strlen(player1)-1]=0;
            cuvant=strtok(player1, " ");
            for(int contor=0; contor<3; contor++)
                cuvant=strtok(NULL, " ");
            scor_player1=scor_player1+calculare_scor(cuvant);
        }
        else //se calculeaza scorul pentru cel de-al doilea jucator
        {
            fgets(player2, 50, stdin);
            player2[strlen(player2)-1]=0;
            cuvant=strtok(player2, " ");
            for(int contor=0; contor<3; contor++)
                cuvant=strtok(NULL, " ");
            scor_player2=scor_player2+calculare_scor(cuvant);
        }
    }
    printf("Player1: %d Points\n", scor_player1);
    printf("Player2: %d Points", scor_player2);
}


int scor_bonusuri_2_3(char cuvant[20], int Yi, int Xi, int Di, int scor_intermediar)
//bonusul pentru cazul cand cuvantul are in componenta sa "XX" si se termina cu "YY"
{
    if(Di==0) //calcularea bonusului se face in functie de directia in care este scris cuvantul in matrice
        {
            for(long unsigned int j=Xi; j<Xi+strlen(cuvant); j++)
            {
                if(bonus_board[Yi][j]==1)
                    scor_intermediar=scor_intermediar*2;
                else 
                    if(bonus_board[Yi][j]==2)
                        scor_intermediar=scor_intermediar*3;
            }
        }
        else 
        {
            for(long unsigned int j=Yi; j<Yi+strlen(cuvant); j++)
            {
                if(bonus_board[j][Xi]==1)
                    scor_intermediar=scor_intermediar*2;
                else 
                    if(bonus_board[j][Xi]==2)
                        scor_intermediar=scor_intermediar*3;
            }
        }
    return scor_intermediar;

}

int scor_bonusuri_2(char cuvant[20], int Yi, int Xi, int Di, int scor_intermediar)
//bonusul pentru cazul cand cuvantul are in componenta sa "XX"
{
    if(Di==0)
    {
        for(long unsigned int j=Xi; j<Xi+strlen(cuvant); j++)
        {
            if(bonus_board[Yi][j]==1)
                scor_intermediar=scor_intermediar*2;
        }
    }
    else 
    {
        for(long unsigned int j=Yi; j<Yi+strlen(cuvant); j++)
        {
            if(bonus_board[j][Xi]==1)
                scor_intermediar=scor_intermediar*2;
        }
    }
    return scor_intermediar;
}

int scor_bonusuri_3(char cuvant[20], int Yi, int Xi, int Di, int scor_intermediar)
//bonusul pentru cazul cand cuvantul se termina cu "YY"
{
    if(Di==0)
    {
        for(long unsigned int j=Xi; j<Xi+strlen(cuvant); j++)
        {
            if(bonus_board[Yi][j]==2)
                scor_intermediar=scor_intermediar*3;
        }
    }
    else 
    {
        for(long unsigned int j=Yi; j<Yi+strlen(cuvant); j++)
        {
            if(bonus_board[j][Xi]==2)
                scor_intermediar=scor_intermediar*3;
        }
    }
    return scor_intermediar;
}

void task3()
{
    char XX[10], YY[10], player[50], *cuvant;
    //sunt citite cele doua cuvine dupa care de decide cum se calculeaza bonusul
    fgets(XX, 10, stdin);
    XX[strlen(XX)-1]=0;
    fgets(YY, 10, stdin);
    YY[strlen(YY)-1]=0;
    char n_char[10];
    fgets(n_char, 10, stdin);
    int n, Yi, Xi, Di, scor_intermediar=0, scor_player1=0, scor_player2=0;
    n=number(n_char);
    for(int i=1; i<=n; i++)
    {
        scor_intermediar=0;
        coordonate_cuvant(player, &Yi, &Xi, &Di, &cuvant);        
        scor_intermediar=calculare_scor(cuvant);
        //calcularea de face pentru fiecare jucator in parte, tinandu-se cont de coordonatele cuvantului ce ii corespunde 
        if(i%2!=0)
        {    
            if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1]))
            {
                scor_intermediar=scor_bonusuri_2_3(cuvant, Yi, Xi, Di, scor_intermediar);
            }
            else 
                if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]!=YY[0]  || cuvant[strlen(cuvant)-1]!=YY[1]))
                {
                    scor_intermediar=scor_bonusuri_2(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            else
                if(cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1] && strstr(cuvant, XX)==0)
                {
                    scor_intermediar=scor_bonusuri_3(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            scor_player1=scor_player1+scor_intermediar;
        }
        else
        {
            if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1]))
            {
                scor_intermediar=scor_bonusuri_2_3(cuvant, Yi, Xi, Di, scor_intermediar);
            }
            else 
                if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]!=YY[0]  || cuvant[strlen(cuvant)-1]!=YY[1]))
                {
                    scor_intermediar=scor_bonusuri_2(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            else
                if(cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1] && strstr(cuvant, XX)==0)
                {
                    scor_intermediar=scor_bonusuri_3(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            scor_player2=scor_player2+scor_intermediar;
        }
    }
    printf("Player1: %d Points\n", scor_player1);
    printf("Player2: %d Points", scor_player2);
}

int verificare_orizontala(char game_board[15][15], int y, int x, char cuvant[20])
//verifica daca primul cuvant din words care nu a fost pus de niciunul dintre jucatori, poate fi pus pe orizontala
{
    int conditie=1, solve=0;
    if(x+strlen(cuvant)<=15) //se verifica daca dimensiunea permite adaugarea in matrice a cuvantului
    {
        for(long unsigned int k=x+1; k<x+strlen(cuvant); k++)
        {
            if(game_board[y][k]!='.') //se verifica daca mai exista litere la de pozitia x+1 pana la x+strlen(cuvant)
                conditie=0;
        }
        if(conditie==1)
        {
            solve=1;
        }
    }
    if(solve==1)
        return 1;
        else return 0;
}

int verificare_verticala(char game_board[15][15], int y, int x, char cuvant[20])
//verifica daca primul cuvant din words care nu a fost pus de niciunul dintre jucatori, poate fi pus pe verticala
{
    int conditie=1, solve=0;
    if(y+strlen(cuvant)<=15) 
    //se verifica daca dimensiunea permite adaugarea in matrice a cuvantului
    {
        for(long unsigned int k=y+1; k<y+strlen(cuvant); k++)
        {
            if(game_board[k][x]!='.') //se verifica daca mai exista litere la de pozitia x+1 pana la x+strlen(cuvant)
                conditie=0;
        }
        if(conditie==1)
        {
            solve=1;
        }
    }
    if(solve==1)
        return 1;
        else return 0;
}

void task4()
{
    char game_board[15][15], XX[10], YY[10], nchar[10], player[50], *cuvant, SIR[250], primul_cuvant[20];
    fgets(XX, 10, stdin);
    XX[strlen(XX)-1]=0;
    fgets(YY, 10, stdin);
    YY[strlen(YY)-1]=0;
    int n, Yi, Xi, Di, y_litera, x_litera, rezolvat=0;
    fgets(nchar, 10, stdin);
    n=number(nchar);
    task0(game_board);
    for(int i=1; i<=n; i++)
    {
        coordonate_cuvant(player, &Yi, &Xi, &Di, &cuvant);
        strcat(SIR, cuvant); //se adauga la un sir toate cuvintele folosie
        strcat(SIR, " ");
        adaugare_matrice(game_board, Yi, Xi, Di, cuvant);   
    }
    for(int i=0; i<100; i++)
    {
        if(strstr(SIR, words[i])==0) 
        //se verifica daca words[i] a fost folosit de unul dintre cei 2 jucatori
        {
            strcpy(primul_cuvant, words[i]);
            for(y_litera=0; y_litera<15; y_litera++)
            {
                for(x_litera=0; x_litera<15; x_litera++)
                {
                    if(game_board[y_litera][x_litera]==primul_cuvant[0]) 
                    //daca se gaseste un cuvant care corespunde, nu se mai parcurge vectorul in continuare
                    {
                        if(game_board[y_litera][x_litera+1]=='.')
                        {
                            if(verificare_orizontala(game_board, y_litera, x_litera, primul_cuvant))
                            {
                                adaugare_matrice(game_board, y_litera, x_litera, 0, primul_cuvant);
                                rezolvat=1;
                                break;
                            }
                        }
                        else 
                        if(game_board[y_litera+1][x_litera]=='.')
                        {
                            if(verificare_verticala(game_board, y_litera, x_litera, primul_cuvant))
                            {
                                adaugare_matrice(game_board, y_litera, x_litera, 1, primul_cuvant);
                                rezolvat=1;
                                break;
                            } 
                        }
                    }
                }
                if(rezolvat==1) 
                    break;
            }
        }
        if(rezolvat==1)
            break;
    }
    print_board(game_board);

}

void task5()
{
    char game_board[15][15], player[50], XX[10], YY[10], 
        nchar[10], SIR[250],*cuvant, primul_cuvant[20], cuvant_maxim[20];
    fgets(XX, 10, stdin);
    XX[strlen(XX)-1]=0;
    fgets(YY, 10, stdin);
    YY[strlen(YY)-1]=0;
    int n, Yi, Xi, Di, scor_player1=0, scor_player2=0, scor_intermediar, y_litera,
        x_litera, max_scor=0, copie_y, copie_x, copie_d, scor_words=0;
    fgets(nchar, 10, stdin);
    n=number(nchar);
    task0(game_board);
    for(int i=1; i<=n; i++)
    {
        scor_intermediar=0;
        coordonate_cuvant(player, &Yi, &Xi, &Di, &cuvant);
        strcat(SIR, cuvant);
        strcat(SIR, " ");
        adaugare_matrice(game_board, Yi, Xi, Di, cuvant);
        scor_intermediar=calculare_scor(cuvant);
        if(i%2!=0)
        {
            if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1]))
            {
                scor_intermediar=scor_bonusuri_2_3(cuvant, Yi, Xi, Di, scor_intermediar);
            }
            else 
                if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]!=YY[0]  || cuvant[strlen(cuvant)-1]!=YY[1]))
                {
                    scor_intermediar=scor_bonusuri_2(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            else
                if(cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1] && strstr(cuvant, XX)==0)
                {
                    scor_intermediar=scor_bonusuri_3(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            scor_player1=scor_player1+scor_intermediar;
        }
        else
        {
            if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1]))
            {
                scor_intermediar=scor_bonusuri_2_3(cuvant, Yi, Xi, Di, scor_intermediar);
            }
            else 
                if(strstr(cuvant, XX)!=0 && (cuvant[strlen(cuvant)-2]!=YY[0]  || cuvant[strlen(cuvant)-1]!=YY[1]))
                {
                    scor_intermediar=scor_bonusuri_2(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            else
                if(cuvant[strlen(cuvant)-2]==YY[0] && cuvant[strlen(cuvant)-1]==YY[1] && strstr(cuvant, XX)==0)
                {
                    scor_intermediar=scor_bonusuri_3(cuvant, Yi, Xi, Di, scor_intermediar);
                }
            scor_player2=scor_player2+scor_intermediar;
        }
    }
    for(int i=0; i<100; i++)
    {
        if(strstr(SIR, words[i])==0) 
        {
            strcpy(primul_cuvant, words[i]);
            for(y_litera=0; y_litera<15; y_litera++)
            {
                for(x_litera=0; x_litera<15; x_litera++)
                {
                    if(game_board[y_litera][x_litera]==primul_cuvant[0]) 
                    {
                        scor_words=0;
                        if(game_board[y_litera][x_litera+1]=='.')
                        {
                            if(verificare_orizontala(game_board, y_litera, x_litera, primul_cuvant))
                            {
                                scor_words=calculare_scor(primul_cuvant);
                                if(strstr(primul_cuvant, XX)!=0 && (primul_cuvant[strlen(primul_cuvant)-2]==YY[0] && primul_cuvant[strlen(primul_cuvant)-1]==YY[1]))
                                {
                                    scor_words=scor_bonusuri_2_3(primul_cuvant, y_litera, x_litera, 0, scor_words);
                                }
                                else 
                                if(strstr(primul_cuvant, XX)!=0 && (primul_cuvant[strlen(primul_cuvant)-2]!=YY[0]  || primul_cuvant[strlen(primul_cuvant)-1]!=YY[1]))
                                {
                                    scor_words=scor_bonusuri_2(primul_cuvant, y_litera, x_litera, 0, scor_words);
                                }
                                else
                                if(primul_cuvant[strlen(primul_cuvant)-2]==YY[0] && primul_cuvant[strlen(primul_cuvant)-1]==YY[1] && strstr(primul_cuvant, XX)==0)
                                {
                                    scor_words=scor_bonusuri_3(primul_cuvant, y_litera, x_litera, 0, scor_words);
                                }
                                if(scor_words>max_scor)
                                {
                                    max_scor=scor_words;
                                    strcpy(cuvant_maxim, primul_cuvant);
                                    copie_y=y_litera;
                                    copie_x=x_litera;
                                    copie_d=0;
                                }                               
                            }
                        }
                        else 
                        if(game_board[y_litera+1][x_litera]=='.')
                        {
                            if(verificare_verticala(game_board, y_litera, x_litera, primul_cuvant)!=0)
                            {
                                scor_words=calculare_scor(primul_cuvant);
                                if(strstr(primul_cuvant, XX)!=0 && (primul_cuvant[strlen(primul_cuvant)-2]==YY[0] && primul_cuvant[strlen(primul_cuvant)-1]==YY[1]))
                                {
                                    scor_words=scor_bonusuri_2_3(primul_cuvant, y_litera, x_litera, 1, scor_words);
                                }
                                else 
                                if(strstr(primul_cuvant, XX)!=0 && (primul_cuvant[strlen(primul_cuvant)-2]!=YY[0]  || primul_cuvant[strlen(primul_cuvant)-1]!=YY[1]))
                                {
                                    scor_words=scor_bonusuri_2(primul_cuvant, y_litera, x_litera, 1, scor_words);
                                }
                                else
                                if(primul_cuvant[strlen(primul_cuvant)-2]==YY[0] && primul_cuvant[strlen(primul_cuvant)-1]==YY[1] && strstr(primul_cuvant, XX)==0)
                                {
                                    scor_words=scor_bonusuri_3(primul_cuvant, y_litera, x_litera, 1, scor_words);
                                }
                                if(scor_words>max_scor)
                                {
                                    max_scor=scor_words;
                                    strcpy(cuvant_maxim, primul_cuvant);
                                    copie_y=y_litera;
                                    copie_x=x_litera;
                                    copie_d=1;
                                }             
                            } 
                        }
                    }
                }
            }
        }
    }

    if(max_scor+scor_player2>=scor_player1)
    {
        adaugare_matrice(game_board, copie_y, copie_x, copie_d, cuvant_maxim);
        print_board(game_board);
    }   
    else printf("Fail!");
}

int main()
{
    char game_board[15][15], caz_char[15];
    int caz;
    fgets(caz_char, 15, stdin);
    caz=number(caz_char);

    switch(caz)
    {
        case 0:
                task0(game_board);
                print_board(game_board);
            break;
        
        case 1:
                task1(game_board);
            break;
        
        case 2:
                task2();
            break;

        case 3:
                task3();
            break;

        case 4:
                task4();
            break;

        case 5:
                task5();
            break;        
    }

    return 0;
}