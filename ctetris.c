#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
char x[4];
char y[4];
char tipo;
int rot;
} pezzo;

void ruota(pezzo*pz, char mat[18][12], char *t, WINDOW *s)
{
    if (*t == 'w' && (*pz).tipo != 'O')
    {
                                //la coordinata 2,2 è quella centrale
        char tx[4];             //coordinate temporanee
        char ty[4];


        for (int i = 0;i < 4;i++)
        {
            if (i != 2)
            {

            int dx = (*pz).x[i] - (*pz).x[2];       //distanza orizzontale dal centro = x del pixel - x del centro
            int dy = (*pz).y[i] - (*pz).y[2];

            tx[i] = dy + (*pz).x[2];                //applicazione della matrice di rotazione [0  1]
            ty[i] = (*pz).y[2] - dy;               //                                        [-1 0]


            }
        }

        if (
        mat[tx[0]][ty[0]] != 'X' &&
        mat[tx[1]][ty[1]] != 'X' &&
        mat[tx[2]][ty[2]] != 'X' &&
        mat[tx[3]][ty[3]] != 'X')
        {
            for (int i = 0;i < 4;i++)
            {
                mvwaddch(s, (*pz).y[i], (*pz).x[i], ' ');
                (*pz).x[i] = tx[i];
                (*pz).y[i] = ty[i];
                mvwaddch(s, (*pz).y[i], (*pz).x[i], (*pz).tipo);
            }
        }
    }
}

void creapezzo(pezzo *pz)
{
    int r = rand() % 7;



    (*pz).rot = 0;      //reset della rotazione

    
    
    
    if (r == 0)
    {
        (*pz).tipo = 'O';
        (*pz).x[0] = 5;
        (*pz).y[0] = 1;
        (*pz).x[1] = 5;
        (*pz).y[1] = 2;
        (*pz).x[2] = 6;
        (*pz).y[2] = 1;
        (*pz).x[3] = 6;
        (*pz).y[3] = 2;
    }
    else if (r == 1)
    {
        (*pz).tipo = 'L';
        (*pz).x[0] = 7;
        (*pz).y[0] = 1;
        (*pz).x[1] = 5;
        (*pz).y[1] = 2;
        (*pz).x[2] = 6;
        (*pz).y[2] = 2;
        (*pz).x[3] = 7;
        (*pz).y[3] = 2;
    }
    else if (r == 2)
    {
        (*pz).tipo = 'J';
        (*pz).x[0] = 5;
        (*pz).y[0] = 1;
        (*pz).x[1] = 5;
        (*pz).y[1] = 2;
        (*pz).x[2] = 6;
        (*pz).y[2] = 2;
        (*pz).x[3] = 7;
        (*pz).y[3] = 2;
    }
    else if (r == 3)
    {
        (*pz).tipo = 'S';
        (*pz).x[0] = 5;
        (*pz).y[0] = 1;
        (*pz).x[1] = 5;
        (*pz).y[1] = 2;
        (*pz).x[2] = 6;
        (*pz).y[2] = 2;
        (*pz).x[3] = 6;
        (*pz).y[3] = 3;
    }
    else if (r == 4)
    {
        (*pz).tipo = 'Z';
        (*pz).x[0] = 6;
        (*pz).y[0] = 1;
        (*pz).x[1] = 5;
        (*pz).y[1] = 2;
        (*pz).x[2] = 6;
        (*pz).y[2] = 2;
        (*pz).x[3] = 5;
        (*pz).y[3] = 3;
    }
    else if (r == 5)
    {
        (*pz).tipo = 'I';
        (*pz).x[0] = 5;
        (*pz).y[0] = 1;
        (*pz).x[1] = 5;
        (*pz).y[1] = 2;
        (*pz).x[2] = 5;
        (*pz).y[2] = 3;
        (*pz).x[3] = 5;
        (*pz).y[3] = 4;
    }
    else if (r == 6)
    {
        (*pz).tipo = 'T';
        (*pz).x[0] = 5;
        (*pz).y[0] = 1;
        (*pz).x[1] = 6;
        (*pz).y[1] = 1;
        (*pz).x[2] = 7;
        (*pz).y[2] = 1;
        (*pz).x[3] = 6;
        (*pz).y[3] = 2;
    }
}

void leggitasto(WINDOW *s, WINDOW *p, char *t)
{
    *t = wgetch(s);
    mvwprintw(p,2,1,"char = %c", *t); // queste tre funzioni sono solo a scopo di debug
    wrefresh(p);
    wrefresh(s);
}

void disegna(WINDOW *s, WINDOW *p, char mat[18][12], pezzo *pz)
{
    for (int i = 0;i < 4; i+=1) // a quanto pare servono le parentesi per accedere ad uno struct puntato
    {
        mat[(*pz).y[i]][(*pz).x[i]] = (*pz).tipo;
        mvwaddch(s, (*pz).y[i], (*pz).x[i], (*pz).tipo);
        wrefresh(s);
        wrefresh(p);


    }
}

void caduta(WINDOW *s, WINDOW *p, char mat[18][12], pezzo *pz)
{
    if          
    (
    mat[(*pz).y[0]+1][(*pz).x[0]] != 'X' &&
    mat[(*pz).y[1]+1][(*pz).x[1]] != 'X' &&
    mat[(*pz).y[2]+1][(*pz).x[2]] != 'X' &&
    mat[(*pz).y[3]+1][(*pz).x[3]] != 'X'
    )
    {
        for (int i=3;i>-1;i-=1)
        {
            mat[(*pz).y[i]][(*pz).x[i]] = mat[(*pz).y[i-1]][(*pz).x[i]];
            mvwaddch(s, (*pz).y[i], (*pz).x[i], ' ');
            (*pz).y[i] +=1;
            mvwaddch(s, (*pz).y[i], (*pz).x[i], (*pz).tipo);
            wrefresh(s);
        }        
    }

    for (int i=17;i>1;i--)      //pulisci schermo
    {
        for (int j=10;j>1;j--)
        {
            if (mat[i][j] == 'O')
            {
                mat[i][j] = ' ';
            }
        }
    }

}

void sinistra (WINDOW *s, WINDOW *p, char mat[18][12], pezzo *pz, char *t)
{
    if 
    (
    mat[(*pz).y[0]][(*pz).x[0]-1] != 'X' &&
    mat[(*pz).y[1]][(*pz).x[1]-1] != 'X' &&
    mat[(*pz).y[2]][(*pz).x[2]-1] != 'X' &&
    mat[(*pz).y[3]][(*pz).x[3]-1] != 'X' &&
    *t == 'a'  //tasto 'a' schiacciato
    )
    {
        for (int i=0;i<4;i+=1)
        {
            mat[(*pz).y[i]][(*pz).x[i]-1] = mat[(*pz).y[i]][(*pz).x[i]];
            mvwaddch(s, (*pz).y[i], (*pz).x[i], ' ');
            (*pz).x[i] -= 1;
            mvwaddch(s, (*pz).y[i], (*pz).x[i], (*pz).tipo);
            wrefresh(s);
        }        
    }

}

void destra (WINDOW *s, WINDOW *p, char mat[18][12], pezzo *pz, char *t)
{
    if 
    (
        mat[(*pz).y[0]][(*pz).x[0]+1] != 'X' &&
        mat[(*pz).y[1]][(*pz).x[1]+1] != 'X' &&
        mat[(*pz).y[2]][(*pz).x[2]+1] != 'X' &&
        mat[(*pz).y[3]][(*pz).x[3]+1] != 'X' &&
        *t == 'd'  //tasto 'd' schiacciato
    )
    {
        for (int i=3;i>-1;i-=1)
        {
            mat[(*pz).y[i]][(*pz).x[i]+1] = mat[(*pz).y[i]][(*pz).x[i]];
            mvwaddch(s, (*pz).y[i], (*pz).x[i], ' ');
            (*pz).x[i] += 1;
            mvwaddch(s, (*pz).y[i], (*pz).x[i], (*pz).tipo);
            wrefresh(s);
        }        
    }
}

void pulisci(char mat[18][12], WINDOW *s)
{
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if(mat[i][j] != 'X' && mat[i][j] != ' ')
            {
                mat[i][j] = ' ';
                mvwaddch(s, i, j, ' ');
                wrefresh(s);
            }
        }
    }
    
}

void linea(char mat[18][12], WINDOW *s)
{
    pulisci(mat, s);

    for (int k = 17;k>0;k--)
    {
        if
        (
            mat[k][1] == 'X' && mat[k][2] == 'X' && mat[k][3] == 'X' &&
            mat[k][4] == 'X' && mat[k][5] == 'X' && mat[k][6] == 'X' &&
            mat[k][7] == 'X' && mat[k][8] == 'X' && mat[k][9] == 'X' &&
            mat[k][10] == 'X' && mat[k][11] == 'X' && mat[k][12] == 'X'
        )
        {
            for (int i=k;i>1;i--)
            {
                for (int j=10;j>0;j--)
                {
                    
                    if(mat[i][j] == 'X')
                    {
                        mat[i][j] = mat[i-1][j];
                        mvwaddch(s,i,j,mat[i-1][j]);
                    }
                }
            }
            wrefresh(s);
        }
    }
    box(s,0,0); 
}


int main() {

    initscr();		            //queste funzioni inizializzano ncurses
    keypad(stdscr, TRUE);	
    halfdelay(3);               //tick speed in decimi di secondo
    noecho();
    curs_set(0);

    srand( time(NULL));

    WINDOW *schermo= newwin(18,12,1,1);         //queste funzioni inizializzano le finestre.
    box(schermo,0,0);                           //é praticamente magia oscura
    wrefresh(schermo);
    WINDOW *punteggio = newwin(5,13,1,23);
    box(punteggio,0,0);
    wrefresh(schermo);

    char tasto = 0;

    char matrice[18][12] = {
        'X','X','X','X','X','X','X','X','X','X','X','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',
        'X','X','X','X','X','X','X','X','X','X','X','X'
        
    };

    //l'assegnazione di questa matrice é tremenda. non ripetere a casa

    
    box(schermo,0,0); 


    pezzo p;
    creapezzo(&p); 

    while (1)
    {
        linea(matrice, schermo);

        leggitasto(schermo, punteggio, &tasto);

        ruota(&p, matrice, &tasto, schermo);

        //disegna(schermo, punteggio, matrice, &p);

        caduta(schermo, punteggio, matrice, &p);

        sinistra(schermo, punteggio, matrice, &p, &tasto);

        destra(schermo, punteggio, matrice, &p, &tasto);

        if
        (
            matrice[p.y[0]+1][p.x[0]] == 'X' ||
            matrice[p.y[1]+1][p.x[1]] == 'X' ||
            matrice[p.y[2]+1][p.x[2]] == 'X' ||
            matrice[p.y[3]+1][p.x[3]] == 'X'
        )
        {
            
            p.tipo = 'X';
            disegna(schermo, punteggio, matrice, &p);
            creapezzo(&p);
        }

        


        
        
        








    


    }
    endwin();
}