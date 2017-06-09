#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifdef WIN32
    #include <conio.h>
    #include <windows.h>
#elif defined __linux__
    // bibliotecas exclusivas do linux
#else
    #error Plataforma não suportada
#endif

/* CARACTERES ESPECIAIS IMPORTANTES PARA A IMPRESSAO DAS INFORMACOES */
char ptaberto = 'o';
char ptfechado = '*';
#ifdef WIN32
    char reta[2] = {196,'\0'};
    char mult[2] = {158,'\0'};
    char qdrd[2] = {253,'\0'};
    char ccedilha[2] = {135,'\0'};
    char otil[2] = {228,'\0'};
    char atil[2] = {198,'\0'};
    char uagudo[2] = {163,'\0'};
    char eagudo[2] = {130,'\0'};
    char vazio[2] = {157,'\0'};
#elif defined __linux__
    char reta[] = {-30,-108,-128,'\0'};
    char mult[] = {-61,-105,'\0'};
    char qdrd[] = {-62,-78,'\0'};
    char ccedilha[] = {-61,-89,'\0'};
    char otil[] = {-61,-75,'\0'};
    char atil[] = {-61,-93,'\0'};
    char uagudo[] = {-61,-70,'\0'};
    char eagudo[] = {-61,-87,'\0'};
    char vazio[] = {-61,-104,'\0'};
#else
    #error Plataforma não suportada
#endif


/* FUNCAO PARA POSICIONAR O CURSOR EM DETERMINADA COORDENADA */
void gotoxy( int x, int y )
{
    #ifdef WIN32
        COORD coord;
        coord.X = (short)x;
        coord.Y = (short)y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #elif defined __linux__
        printf("%c[%d;%df",0x1B,y,x);
    #else
        #error Plataforma não suportada
    #endif
}

/* FUNCOES NECESSARIAS PARA O FUNCIONAMENTO DO SISTEMA */
void EqPrim(double *x, double a, double b); // funcao para calcular x de equacao de primeiro grau e mostrar sua resolução
int EqSeg(double *x1, double *x2, double a, double b, double c); // funcao para calcular os x de equacao de segundo grau e mostrar sua resolução
void InPrim(double *x, double a, double b, int *s); // funcao para calcular intervalo de inequacao de primeiro grau e mostrar sua resolução
int InSeg(double *x1, double *x2, double a, double b, double c, int s); // funcao para calcular intervalo de inequacao de segundo grau e mostrar sua resolução

/* FUNCAO PRINCIPAL */
int main() {
    #ifdef WIN32
        system("color F0");
    #elif defined __linux__
        //
    #else
        #error Plataforma não suportada
    #endif
    int i;
    char ch, temp[100];
    int Cx, Cy;
    double x, x1, x2, a, b, c;
    int opc, simb;
    do {
        inicio:
        #ifdef WIN32
            system("cls");
        #elif defined __linux__
            system("clear");
        #else
            #error Plataforma não suportada
        #endif
        printf("Calculadora de Equa%s%ses e Inequa%s%ses\n\n",ccedilha,otil,ccedilha,otil);
        printf("1. Equa%s%so do primeiro grau.\n",ccedilha,atil);
        printf("2. Equa%s%so do segundo grau.\n",ccedilha,atil);
        printf("3. Inequa%s%so do primeiro grau.\n",ccedilha,atil);
        printf("4. Inequa%s%so do segundo grau.\n",ccedilha,atil);
        printf("\n0. Sair.\n");
        printf("\n-> ");

        scanf("%d", &opc);
        switch(opc){
            case 0:
                    #ifdef WIN32
                        system("cls");
                    #elif defined __linux__
                        system("clear");
                    #else
                        #error Plataforma não suportada
                    #endif
                    printf("Volte logo!\n");
                    break;

            case 1:
                    #ifdef WIN32
                        system("cls");
                    #elif defined __linux__
                        system("clear");
                    #else
                        #error Plataforma não suportada
                    #endif
                    printf("Equa%s%so do primeiro grau\n\n",ccedilha,atil);
                    printf("v. Voltar.\n\n");
                    #ifdef WIN32
                        printf("( )x + ( ) = 0");
                        //lendo o a
                        i = 0;
                        Cx = 1; Cy = 4;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                printf(" )x + ( ) = 0");
                                gotoxy(Cx,Cy);
                                goto LERa1;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            printf(" )x + ( ) = 0");
                            gotoxy(Cx,Cy);
                            LERa1: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &a);
                        //lendo o b
                        i=0;
                        Cx = strlen(temp)+8;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                printf(" ) = 0");
                                gotoxy(Cx,Cy);
                                goto LERb1;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            printf(" ) = 0");
                            gotoxy(Cx,Cy);
                            LERb1: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &b);
                        gotoxy(0,5);
                    #elif defined __linux__
                        printf("Modelo: ax+b=0\na = ");
                        if(scanf("%lf",&a) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("b = ");
                        if(scanf("%lf",&b) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                    #else
                        #error Plataforma não suportada
                    #endif
                    if(a==0){
                        printf("a = 0. Impossivel calcular!\n");
                        getchar();
                        break;
                    }
                    EqPrim(&x, a, b);
                    printf("\nS = {x e R | x = %.3lf}\n\n",x);
                    getchar();
                    break;

            case 2:
                    #ifdef WIN32
                        system("cls");
                    #elif defined __linux__
                        system("clear");
                    #else
                        #error Plataforma não suportada
                    #endif
                    printf("Equa%s%so do segundo grau.\n\n",ccedilha,atil);
                    printf("v. Voltar.\n\n");
                    #ifdef WIN32
                        printf("( )x%s + ( )x + ( ) = 0",qdrd);
                        //lendo o a
                        i = 0;
                        Cx = 1; Cy = 4;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                printf(" )x%s + ( )x + ( ) = 0",qdrd);
                                gotoxy(Cx,Cy);
                                goto LERa2;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            printf(" )x%s + ( )x + ( ) = 0",qdrd);
                            gotoxy(Cx,Cy);
                            LERa2: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &a);
                        //lendo o b
                        i=0;
                        Cx = strlen(temp)+9;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                printf(" )x + ( ) = 0");
                                gotoxy(Cx,Cy);
                                goto LERb2;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            printf(" )x + ( ) = 0");
                            gotoxy(Cx,Cy);
                            LERb2: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &b);
                        //lendo o c
                        i=0;
                        Cx = Cx+7;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                printf(" ) = 0");
                                gotoxy(Cx,Cy);
                                goto LERc2;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            printf(" ) = 0");
                            gotoxy(Cx,Cy);
                            LERc2: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &c);
                        gotoxy(0,5);
                    #elif defined __linux__
                        printf("Modelo: ax%s+bx+c=0\na = ",qdrd);
                        if(scanf("%lf",&a) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("b = ");
                        if(scanf("%lf",&b) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("c = ");
                        if(scanf("%lf",&c) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                    #else
                        #error Plataforma não suportada
                    #endif
                    if(a==0){
                        if(b==0){
                            printf("a = 0 e b = 0. Impossivel calcular!\n");
                            getchar();
                            break;
                        }
                        else{
                            printf("%.3lfx%s + (%.3lf)x + (%.3lf) = 0\n",a,qdrd,b,c);
                            EqPrim(&x, b, c);
                            printf("\nS = {x e R | x = %.3lf}\n\n",x);
                            getchar();
                            break;
                        }
                    }
                    if(EqSeg(&x1, &x2, a, b, c) == 0){
                        if(x1 == x2)
                            printf("\nS = {x e R | x = %.3lf}\n\n",x1);
                        else
                            printf("\nS = {x e R | x = %.3lf ou x = %.3lf}\n\n",x1,x2);
                    }
                    else
                        printf("\nDelta negativo! Impossivel calcular raiz de n%smero negativo.\n\n",uagudo);
                    getchar();
                    break;

            case 3:
                    #ifdef WIN32
                        system("cls");
                    #elif defined __linux__
                        system("clear");
                    #else
                        #error Plataforma não suportada
                    #endif
                    printf("Inequa%s%so do primeiro grau.\n\n",ccedilha,atil);
                    printf("v. Voltar.\n\n");
                    #ifdef WIN32
                        printf("Simbolo a ser usado:\n1. >\t2. >=\t3. <\t4. <=\n-> ");
                        if(scanf("%d",&simb) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        switch(simb){
                            case 1: printf("( )x + ( ) > 0");; break;
                            case 2: printf("( )x + ( ) >= 0");; break;
                            case 3: printf("( )x + ( ) < 0");; break;
                            case 4: printf("( )x + ( ) <= 0");; break;
                        }
                        //lendo o a
                        i = 0;
                        Cx = 1; Cy = 7;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                switch(simb){
                                    case 1: printf(" )x + ( ) > 0");; break;
                                    case 2: printf(" )x + ( ) >= 0");; break;
                                    case 3: printf(" )x + ( ) < 0");; break;
                                    case 4: printf(" )x + ( ) <= 0");; break;
                                }
                                gotoxy(Cx,Cy);
                                goto LERa3;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            switch(simb){
                                case 1: printf(" )x + ( ) > 0");; break;
                                case 2: printf(" )x + ( ) >= 0");; break;
                                case 3: printf(" )x + ( ) < 0");; break;
                                case 4: printf(" )x + ( ) <= 0");; break;
                            }
                            gotoxy(Cx,Cy);
                            LERa3: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &a);
                        //lendo o b
                        i=0;
                        Cx = strlen(temp)+8;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                switch(simb){
                                    case 1: printf(" ) > 0"); break;
                                    case 2: printf(" ) >= 0"); break;
                                    case 3: printf(" ) < 0"); break;
                                    case 4: printf(" ) <= 0"); break;
                                }
                                gotoxy(Cx,Cy);
                                goto LERb3;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            switch(simb){
                                case 1: printf(" ) > 0"); break;
                                case 2: printf(" ) >= 0"); break;
                                case 3: printf(" ) < 0"); break;
                                case 4: printf(" ) <= 0"); break;
                            }
                            gotoxy(Cx,Cy);
                            LERb3: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &b);
                        gotoxy(0,8);
                    #elif defined __linux__
                        printf("Modelo:\n1. ax+b > 0, 2. ax+b >= 0, 3. ax+b < 0, 4. ax+b <= 0\n-> ");
                        if(scanf("%d",&simb) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("a = ");
                        if(scanf("%lf",&a) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("b = ");
                        if(scanf("%lf",&b) == 0){
                            setbuf(stdin,NULL);
                            break;
                    }
                    #else
                        #error Plataforma não suportada
                    #endif
                    if(a==0){
                        printf("a = 0. Impossivel calcular!\n");
                        getchar();
                        break;
                    }
                    InPrim(&x,a,b,&simb);
                    switch(simb){
                        case 1: printf("\nS = {x e R | x > %.3lf}\n\n",x);
                                break;
                        case 2: printf("\nS = {x e R | x >= %.3lf}\n\n",x);
                                break;
                        case 3: printf("\nS = {x e R | x < %.3lf}\n\n",x);
                                break;
                        case 4: printf("\nS = {x e R | x <= %.3lf}\n\n",x);
                                break;
                    }
                    getchar();
                    break;

            case 4:
                    #ifdef WIN32
                        system("cls");
                    #elif defined __linux__
                        system("clear");
                    #else
                        #error Plataforma não suportada
                    #endif
                    printf("Inequa%s%so do segundo grau.\n\n",ccedilha,atil);
                    printf("v. Voltar.\n\n");
                    #ifdef WIN32
                        printf("Simbolo a ser usado:\n1. >\t2. >=\t3. <\t4. <=\n-> ");
                        if(scanf("%d",&simb) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        switch(simb){
                            case 1: printf("( )x%s + ( )x + ( ) > 0",qdrd); break;
                            case 2: printf("( )x%s + ( )x + ( ) >= 0",qdrd); break;
                            case 3: printf("( )x%s + ( )x + ( ) < 0",qdrd); break;
                            case 4: printf("( )x%s + ( )x + ( ) <= 0",qdrd); break;
                        }
                        //lendo o a
                        i = 0;
                        Cx = 1; Cy = 7;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                switch(simb){
                                    case 1: printf(" )x%s + ( )x + ( ) > 0",qdrd); break;
                                    case 2: printf(" )x%s + ( )x + ( ) >= 0",qdrd); break;
                                    case 3: printf(" )x%s + ( )x + ( ) < 0",qdrd); break;
                                    case 4: printf(" )x%s + ( )x + ( ) <= 0",qdrd); break;
                                }
                                gotoxy(Cx,Cy);
                                goto LERa4;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            switch(simb){
                                case 1: printf(" )x%s + ( )x + ( ) > 0",qdrd); break;
                                case 2: printf(" )x%s + ( )x + ( ) >= 0",qdrd); break;
                                case 3: printf(" )x%s + ( )x + ( ) < 0",qdrd); break;
                                case 4: printf(" )x%s + ( )x + ( ) <= 0",qdrd); break;
                            }
                            gotoxy(Cx,Cy);
                            LERa4: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &a);
                        //lendo o b
                        i=0;
                        Cx = strlen(temp)+9;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                switch(simb){
                                    case 1: printf(" )x + ( )  > 0");; break;
                                    case 2: printf(" )x + ( )  >= 0");; break;
                                    case 3: printf(" )x + ( )  < 0");; break;
                                    case 4: printf(" )x + ( )  <= 0");; break;
                                }
                                gotoxy(Cx,Cy);
                                goto LERb4;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            switch(simb){
                                case 1: printf(" )x + ( )  > 0"); break;
                                case 2: printf(" )x + ( )  >= 0"); break;
                                case 3: printf(" )x + ( )  < 0"); break;
                                case 4: printf(" )x + ( )  <= 0"); break;
                            }
                            gotoxy(Cx,Cy);
                            LERb4: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &b);
                        // lendo o c
                        i=0;
                        Cx = Cx+7;
                        gotoxy(Cx,Cy);
                        ch = getch();
                        while(ch != 13){
                            if(ch == 'v')
                                goto inicio;
                            else if(ch == 8){
                                i--;
                                Cx--;
                                gotoxy(Cx,Cy);
                                switch(simb){
                                    case 1: printf(" ) > 0");; break;
                                    case 2: printf(" ) >= 0");; break;
                                    case 3: printf(" ) < 0");; break;
                                    case 4: printf(" ) <= 0");; break;
                                }
                                gotoxy(Cx,Cy);
                                goto LERc4;
                            }
                            temp[i] = ch;
                            i++;
                            printf("%c",ch);
                            Cx++;
                            gotoxy(Cx,Cy);
                            printf(" ) = 0");
                            gotoxy(Cx,Cy);
                            LERc4: ch = getch();
                        }temp[i]='\0';
                        sscanf(temp, "%lf", &c);
                        gotoxy(0,8);
                    #elif defined __linux__
                        printf("Modelo:\n1. ax%s+bx+c > 0, 2. ax%s+bx+c >= 0, 3. ax%s+bx+c < 0, 4. ax%s+bx+c <= 0\n-> ",qdrd,qdrd,qdrd,qdrd);
                        if(scanf("%d",&simb) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("a = ");
                        if(scanf("%lf",&a) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("b = ");
                        if(scanf("%lf",&b) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                        printf("c = ");
                        if(scanf("%lf",&c) == 0){
                            setbuf(stdin,NULL);
                            break;
                        }
                    #else
                        #error Plataforma não suportada
                    #endif
                    if(a==0){
                        if(b==0){
                            printf("a = 0 e b = 0. Impossivel calcular!\n");
                            getchar();
                            break;
                        }
                        else{
                            printf("%.3lfx%s + (%.3lf)x + (%.3lf) = 0\n",a,qdrd,b,c);
                            InPrim(&x, b, c, &simb);
                            switch(simb){
                                case 1: printf("\nS = {x e R | x > %.3lf}\n\n",x);
                                        break;
                                case 2: printf("\nS = {x e R | x >= %.3lf}\n\n",x);
                                        break;
                                case 3: printf("\nS = {x e R | x < %.3lf}\n\n",x);
                                        break;
                                case 4: printf("\nS = {x e R | x <= %.3lf}\n\n",x);
                                        break;
                            }
                            getchar();
                            break;
                        }
                    }
                    if(InSeg(&x1, &x2, a, b, c, simb) == 0){
                        if(x1 == x2){
                            if((simb==1 && a>0) || (simb==3 && a<0))
                                printf("\nS = {x e R | x != %.3lf}\n\n",x1);
                            if((simb==1 && a<0) || (simb==3 && a>0))
                                printf("\nS = {%s}\n\n",vazio);
                            if((simb==2 && a>0) || (simb==4 && a<0))
                                printf("\nS = {x e R}\n\n");
                            if((simb==2 && a<0) || (simb==4 && a>0))
                                printf("\nS = {x e R | x = %.3lf}\n\n",x1);
                        }
                        else{
                            if((simb==1 && a>0) || (simb==3 && a<0))
                                printf("\nS = {x e R | x < %.3lf ou x > %.3lf}\n\n",x1,x2);
                            if((simb==1 && a<0) || (simb==3 && a>0))
                                printf("\nS = {x e R | %.3lf < x < %.3lf}\n\n",x1,x2);
                            if((simb==2 && a>0) || (simb==4 && a<0))
                                printf("\nS = {x e R | x <= %.3lf ou x >= %.3lf}\n\n",x1,x2);
                            if((simb==2 && a<0) || (simb==4 && a>0))
                                printf("\nS = {x e R | %.3lf <= x <= %.3lf}\n\n",x1,x2);
                        }
                    }
                    else
                        printf("Delta negativo! Impossivel calcular raiz de n%smero negativo.\n",uagudo);

                    getchar();
                    break;

            default:printf("Op%s%so inexistente!\n",ccedilha,atil);
                    getchar();
        }
    }while(opc!=0);

    return 0;
}

void EqPrim(double *x, double a, double b) {//ax+b=0
    *x = -b/a;
    getchar();
    printf("%.3lfx + (%.3lf) = 0\t",a,b); getchar();
    printf("%.3lfx = %.3lf\t",a,-b); getchar();
    printf("x = %.3lf/%.3lf\t",-b,a); getchar();
    printf("x = %.3lf\t",-b/a); getchar();
}

int EqSeg(double *x1, double *x2, double a, double b, double c) {
    getchar();
    printf("(%.3lf)x%s + (%.3lf)x + (%.3lf) = 0\t",a,qdrd,b,c); getchar();
    double delta = pow(b,2) - 4*a*c;
    printf("Delta = b%s - 4%sa%sc\t",qdrd,mult,mult); getchar();
    printf("Delta = (%.3lf)%s - 4%s(%.3lf)%s(%.3lf)\t",b,qdrd,mult,a,mult,c); getchar();
    printf("Delta = %.3lf - (%.3lf)\t",pow(b,2),4*a*c); getchar();
    printf("Delta = %.3lf\t",delta); getchar();
    printf("x = (-b + raiz(Delta))/2%sa ou x = (-b - raiz(Delta))/2%sa\t",mult,mult); getchar();
    printf("x = (-(%.3lf) + raiz(%.3lf))/2%s(%.3lf) ou x = (-(%.3lf) - raiz(%.3lf))/2%s(%.3lf)\t",b,delta,mult,a,b,delta,mult,a); getchar();
    if(delta < 0)
        return 1;
    else if(delta == 0){
        *x1 = (-b)/(2*a);
        *x2 = (-b)/(2*a);
        printf("x = %.3lf/%.3lf\t",-b,2*a); getchar();
        printf("x = %.3lf\t",*x1); getchar();
        return 0;
    }
    else {
        *x1 = (-b + sqrt(delta))/2*a;
        *x2 = (-b - sqrt(delta))/2*a;
        printf("x = %.3lf/%.3lf ou x = %.3lf/%.3lf\t",-b+sqrt(delta),2*a,-b-sqrt(delta),2*a); getchar();
        printf("x = %.3lf ou x = %.3lf\t",*x1,*x2); getchar();
        return 0;
    }
}

void InPrim(double *x, double a, double b, int *s) {//ax+b=0
    getchar();
    char simbolo[2];
    switch(*s){
        case 1: strcpy(simbolo,">"); break;
        case 2: strcpy(simbolo,">="); break;
        case 3: strcpy(simbolo,"<"); break;
        case 4: strcpy(simbolo,"<="); break;
    }
    *x = -b/a;
    printf("%.3lfx + %.3lf %s 0\t",a,b,simbolo); getchar();
    printf("%.3lfx %s %.3lf\t",a,simbolo,-b); getchar();
    if(a>0){
        printf("x %s %.3lf/%.3lf\t",simbolo,-b,a); getchar();
    }
    else{
        printf("-x %s %.3lf/%.3lf\t",simbolo,-b,-a); getchar();
        printf("-x %s %.3lf\t",simbolo,-b/-a); getchar();
        if(*s <= 2){
            simbolo[0] = '<';
            *s+=2;
        }
        else{
            simbolo[0] = '>';
            *s-=2;
        }
    }
    printf("x %s %.3lf\t",simbolo,*x); getchar();
}

int InSeg(double *x1, double *x2, double a, double b, double c, int s) {
    getchar();
    int i;
    double temp;
    switch(s){
        case 1: printf("(%.3lf)x%s + (%.3lf)x + (%.3lf) > 0\t",a,qdrd,b,c); getchar(); break;
        case 2: printf("(%.3lf)x%s + (%.3lf)x + (%.3lf) >= 0\t",a,qdrd,b,c); getchar(); break;
        case 3: printf("(%.3lf)x%s + (%.3lf)x + (%.3lf) < 0\t",a,qdrd,b,c); getchar(); break;
        case 4: printf("(%.3lf)x%s + (%.3lf)x + (%.3lf) <= 0\t",a,qdrd,b,c); getchar(); break;
    }
    printf("(%.3lf)x%s + (%.3lf)x + (%.3lf) = 0\t",a,qdrd,b,c); getchar();
    double delta = pow(b,2) - 4*a*c;
    printf("Delta = b%s - 4%sa%sc\t",qdrd,mult,mult); getchar();
    printf("Delta = (%.3lf)%s - 4%s(%.3lf)%s(%.3lf)\t",b,qdrd,mult,a,mult,c); getchar();
    printf("Delta = %.3lf - (%.3lf)\t",pow(b,2),4*a*c); getchar();
    printf("Delta = %.3lf\t",delta); getchar();
    printf("x1 = (-b + raiz(Delta))/2%sa; x2 = (-b - raiz(Delta))/2%sa\t",mult,mult); getchar();
    printf("x1 = (-(%.3lf) + raiz(%.3lf))/2%s(%.3lf); x2 = (-(%.3lf) - raiz(%.3lf))/2%s(%.3lf)\t",b,delta,mult,a,b,delta,mult,a); getchar();
    if(delta < 0)
        return 1;
    else if(delta == 0){
        //
        *x1 = (-b)/(2*a);
        *x2 = (-b)/(2*a);
        printf("x = %.3lf/%.3lf\t",-b,2*a); getchar();
        printf("x = %.3lf\t",*x1); getchar();
        printf("\nEstudando os sinais:\n\n");
        if(s==1){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("    (+)   %.3lf  (+)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) > 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, que %s toda a reta, exceto em x=%.3lf\t",eagudo,*x1); getchar();// x=R | x != x1
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("    (-)   %.3lf  (-)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) > 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, que n%so existem, portanto:\t",atil); getchar();//S= {vazio}
            }
        }
        if(s==2){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("    (+)   %.3lf  (+)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();;
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) >= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, que %s toda a reta\t",eagudo); getchar(); // x e R
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("    (-)   %.3lf  (-)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) >= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, que existe apenas em x=%.3lf\t",*x1); getchar(); // x = x1
            }
        }
        if(s==3){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("    (+)   %.3lf  (+)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) < 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, que n%so existem, portanto:\t",atil); getchar();//S= {vazio}
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("    (-)   %.3lf  (-)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) < 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, que %s toda a reta, exceto em x=%.3lf\t",eagudo,*x1); getchar();// x!=x1
            }
        }
        if(s==4){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("    (+)   %.3lf  (+)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) <= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, que existe apenas em x=%.3lf\t",*x1); getchar(); // x = x1
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("    (-)   %.3lf  (-)\n",*x1);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) <= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, que %s toda a reta\t",eagudo); getchar(); // x e R
            }
        }
        //
    }
    else {
        *x1 = (-b + sqrt(delta))/2*a;
        *x2 = (-b - sqrt(delta))/2*a;
        printf("x1 = %.3lf/%.3lf; x2 = %.3lf/%.3lf\t",-b+sqrt(delta),2*a,-b-sqrt(delta),2*a); getchar();
        printf("x1 = %.3lf; x2 = %.3lf\t",*x1,*x2); getchar();
        if(*x1 > *x2){
            temp = *x1;
            *x1 = *x2;
            *x2 = temp;
        }
        printf("x1 = %.3lf; x2 = %.3lf\t",*x1,*x2); getchar();
//
        printf("\nEstudando os sinais:\n\n");
        if(s==1){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("   (+)  %.3lf  (-)   %.3lf  (+)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) > 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, ou seja, x < %.3lf ou x > %.3lf\t",*x1,*x2); getchar();
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("   (-)  %.3lf  (+)   %.3lf  (-)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) > 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, ou seja, %.3lf < x < %.3lf\t",*x1,*x2); getchar();
            }
        }
        if(s==2){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("   (+)  %.3lf  (-)   %.3lf  (+)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) >= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, ou seja, x <= %.3lf ou x >= %.3lf\t",*x1,*x2); getchar();
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("   (-)  %.3lf  (+)   %.3lf  (-)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) >= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (+) da reta, ou seja, %.3lf <= x <= %.3lf\t",*x1,*x2); getchar();
            }
        }
        if(s==3){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("   (+)  %.3lf  (-)   %.3lf  (+)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) < 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, ou seja, %.3lf < x < %.3lf\t",*x1,*x2); getchar();
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("   (-)  %.3lf  (+)   %.3lf  (-)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptaberto);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) < 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, ou seja, x < %.3lf ou x > %.3lf\t",*x1,*x2); getchar();
            }
        }
        if(s==4){
            if(a>0){
                printf("Como a>0, a concavidade da curva %s para cima. Assim:\n\n",eagudo);
                printf("   (+)  %.3lf  (-)   %.3lf  (+)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) <= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, ou seja, %.3lf <= x <= %.3lf\t",*x1,*x2); getchar();
            }
            else{
                printf("Como a<0, a concavidade da curva %s para baixo. Assim:\n\n",eagudo);
                printf("   (-)  %.3lf  (+)   %.3lf  (-)\n",*x1,*x2);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<12;i++) printf("%s",reta);
                printf("%c",ptfechado);
                for(i=0;i<10;i++) printf("%s",reta);
                printf("> x\t"); getchar();
                printf("Como deseja-se saber os valores de x para que (%.3lf)x%s + (%.3lf)x + (%.3lf) <= 0,",a,qdrd,b,c);
                printf(" pega-se os valores (-) da reta, ou seja, x <= %.3lf ou x >= %.3lf\t",*x1,*x2); getchar();
            }
        }
//
    }
    return 0;
}
