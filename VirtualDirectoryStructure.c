#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

const int rmConst = 9999;

char nome[8][1023];
char data[10][1023];
char hora[8][1023];
int pai[1023];

int posicaoAtual = 0;
int codDir = 0;

void setup() {
    setlocale(LC_ALL, "Portuguese");

    nome[0][0] = '/';
    data[0][0] = 'X';
    hora[0][0] = 'X';
    pai[0] = 0;

    printf("========================> Trabalho Especial S.O <========================\n\n");
    printf("Bem vindo ao trabalho especial da mat�ria de\nSistemas Operacionais, Fatec Americana - 2� Semestre 2019.\n");
    printf("\nPara saber as funcionalidades e os comandos dispon�veis digite 'help'.\n");
    printf("\n========================> Trabalho Especial S.O <========================\n");
}

void pwd() {
    for (int i = 0; i < posicaoAtual + 1; i++) {
       printf("%s", nome[i]);

        if (i > 0)
            printf("/");
    }
    printf("\n");
}

void mkdir(char nomeP[8]) {

    for (int i = 1; i <= codDir; i++) {
        if (strcmp(nomeP, nome[i]) == 0 && pai[i] == posicaoAtual) {
            printf("(!) N�o � poss�vel criar o diret�rio indicado. Causa: O diret�rio j� existe.\n");
            return;
        }
    }

    codDir++;

    for (int i = 0; i < 8; i++) {
        nome[codDir][i] = nomeP[i];
    }

    struct tm * tm;
    time_t t;

    time(&t);
    tm = localtime(&t);
    strftime(data[codDir], 10, "%d-%m-%y", tm);

    time(&t);
    tm = localtime(&t);
    strftime(hora[codDir], 100, "%H:%M:%S", tm);

    pai[codDir] = posicaoAtual;
}

void rmdir(char param[8]) {
    if (codDir == 0) {
        printf("(!) Diret�rio informado n�o encontrado.\n");
        return;
    }

    bool found = false;

    for (int i = 1; i <= codDir; i++) {
        if (strcmp(nome[i], param) == 0 && pai[i] == posicaoAtual) {
            bool hasSon = false;

            for (int j = 1; j <= codDir; j++) {
                if (pai[j] == posicaoAtual + 1 && (posicaoAtual + 1) == i) {
                    hasSon = true;
                }
            }

            if (hasSon) {
                printf("(!) N�o � poss�vel remover o diret�rio indicado. Causa: O diret�rio n�o est� vazio.\n");
                return;
            }

            pai[i] = rmConst;
            found = true;
        }
    }

    if (!found) {
         printf("(!) Diret�rio informado n�o encontrado.\n");
    }
}

void ls(bool lParam) {
   if (lParam) {
        for (int i = 1; i <= codDir; i++) {
            if (pai[i] != rmConst && pai[i] == posicaoAtual) {
                printf("%s %s %s\n", nome[i], data[i], hora[i]);
            }
        }
   } else {
        for (int i = 1; i <= codDir; i++) {
             if (pai[i] != rmConst && pai[i] == posicaoAtual) {
                printf("%s\n", nome[i]);
             }
        }
   }
}

void cd(char param[8]) {
    if (strcmp(param, "..") == 0) {
        if (posicaoAtual > 0) {
            posicaoAtual--;
        }
    } else if (strcmp(param, "/") == 0) {
        posicaoAtual = 0;
    } else {
        if (codDir == 0) {
            printf("(!) Diret�rio informado n�o encontrado.\n");
            return;
        }

        bool found = false;

        for (int i = 1; i <= codDir; i++) {
            if (strcmp(nome[i], param) == 0 && pai[i] == posicaoAtual) {
                 if (pai[i] != rmConst) {
                     posicaoAtual = pai[i] + 1;
                     found = true;
                 }
            }
        }

        if (!found) {
            printf("(!) Diret�rio informado n�o encontrado.\n");
        }
    }
}

void clear() {
    system("cls");
}

void copyright () {
    printf("\n=-=-=-=-= Trabalho Especial S.O =-=-=-=-=\n");
    printf("\nTrabalho da mat�ria de S.0 I,\nda Fatec Americana - 2� Semestre 2019.");
    printf("\n\nEquipe: \n");
    printf("- Andr� Nicola Nunes \n");
    printf("- Gustavo Rolim dos Santos \n");
    printf("- Maicon Gabriel de S� \n");
    printf("- Vinicius Penachioni Tenomaro \n\n");
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void help() {
    printf("\n===============================> AJUDA <===============================\n\n");
    printf("pwd - Exibe o caminho de diret�rios atual.\n");
    printf("mkdir - Cria um diret�rio. <Use: mkdir nome_do_diret�rio>\n");
    printf("ls - Lista os diret�rios no caminho atual.\n");
    printf("rmdir - Remove um diret�rio. <Use: rmdir nome_do_diret�rio>\n");
    printf("ls -l - Lista os diret�rios do caminho atual com informa��es de data e hora.\n");
    printf("cd - Vai para o diret�rio indicado. <Use: cd nome_do_diret�rio>.\n");
    printf("cd .. - Volta para o diret�rio anterior.\n");
    printf("cd / - Volta para o diret�rio raiz.\n");
    printf("clear - Limpa o prompt.\n");
    printf("copyright - Exibe os cr�ditos dos desenvolvedores.\n");
    printf("date - Exibe data e hora.\n");
    printf("poweroff - Desliga a m�quina.\n");
    printf("\nPara saber os parametros de cada comando digite help nome_do_comando.\n");
    printf("\n===========================> COMANDOS DO S.O <===========================\n");
}

void helpCommand(char *param) {
    if (strcmp(param, "pwd") == 0) {
        printf("pwd - Exibe o caminho de diret�rios atual.\n");
    } else if (strcmp(param, "mkdir") == 0) {
         printf("mkdir - Cria um diret�rio. <Use: mkdir nome_do_diret�rio>\n");
    } else if (strcmp(param, "ls") == 0) {
        printf("ls - Lista os diret�rios no caminho atual.\n");
        printf("ls -l - Lista os diret�rios do caminho atual com informa��es de data e hora.\n");
    } else if (strcmp(param, "rmdir") == 0) {
        printf("rmdir - Remove um diret�rio. <Use: rmdir nome_do_diret�rio>\n");
    } else if (strcmp(param, "cd") == 0) {
        printf("cd - Vai para o diret�rio indicado. <Use: cd nome_do_diret�rio>.\n");
        printf("cd .. - Volta para o diret�rio anterior.\n");
        printf("cd / - Volta para o diret�rio raiz.\n");
    } else if (strcmp(param, "clear") == 0) {
       printf("clear - Limpa o prompt.\n");
    } else if (strcmp(param, "copyright") == 0) {
        printf("copyright - Exibe os cr�ditos dos desenvolvedores.\n");
    } else if (strcmp(param, "date") == 0) {
        printf("date - Exibe data e hora.\n");
    } else if (strcmp(param, "poweroff") == 0) {
        printf("poweroff - Desliga a m�quina.\n");;
    } else {
        printf("\nOp��o inv�lida! Digite help para ver os comandos.");
    }
}

void date() {
    char data5[100];

    struct tm * tm;
    time_t t;

    time(&t);
    tm = localtime(&t);
    strftime(data5, 100, "%m/%d/%Y %H:%M:%S", tm);

    printf("\n%s", data5);
}

int main() {
    setup();

    char line[80];
    char *command, *param;

    bool off = false;

    while(!off) {
        printf("$ ");
        gets(line);
        command = strtok(line, " ");
        param = strtok(NULL, "\0");

        if (command == NULL) {
            printf("\nOp��o inv�lida! Digite help para ver os comandos.");
            continue;
        }

        if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "pwd") == 0) {
            pwd();
        } else if (strcmp(command, "mkdir") == 0 && param == NULL) {
            printf("\n(!) Use: mkdir <nome_do_diret�rio>");
        } else if (strcmp(command, "rmdir") == 0 && param == NULL) {
            printf("\n(!) Use: rmdir <nome_do_diret�rio>");
        } else if (strcmp(command, "mkdir") == 0 && strlen(param) > 8) {
             printf("(!) Nome muito grande. (M�ximo 8 caracteres)\n");
         } else if (strcmp(command, "mkdir") == 0) {
            mkdir(param);
        } else if (strcmp(command, "ls") == 0 && param == NULL) {
            ls(false);
        } else if (strcmp(command, "ls") == 0 && param != NULL) {
            if (strcmp(param, "-l") == 0) {
                ls(true);
            }
        } else if (strcmp(command, "cd") == 0 && param == NULL) {
            printf("\n(!) Use: cd <nome_do_diret�rio>");
        } else if (strcmp(command, "cd") == 0 && param != NULL) {
            cd(param);
        } else if (strcmp(command, "rmdir") == 0) {
            rmdir(param);
        } else if (strcmp(command, "clear") == 0) {
            clear();
        } else if (strcmp(command, "copyright") == 0) {
            copyright();
        } else if (strcmp(command, "help") == 0 && param == NULL) {
            help();
        } else if (strcmp(command, "help") == 0) {
            helpCommand(param);
        } else if (strcmp(command, "date") == 0) {
            date();
        } else if (strcmp(command, "poweroff") == 0) {
            printf("\nPrograma finalizado com sucesso!\n");
            off = true;
        } else {
            printf("\nOp��o inv�lida! Digite help para ver os comandos.");
        }
    }

    return 0;
}

