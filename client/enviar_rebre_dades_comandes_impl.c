/*
 * Copyright (C) 2017 mdt3
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "enviar_rebre_dades_comandes.h"
#include "estat_client.h"
#include "subscripcio.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

void* espera_comandes(void* params) {
    Parametres* parametres = (Parametres*) params;
    if (comandes(parametres->estat_client, parametres->configuracio) == -1) {
        fprintf(stderr, "Hi ha hagut un error inesperat\n");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

void quit() {
    printf("Sortint ...\n");
    kill(getpid(), SIGINT);
}

void stat(Configuracio* configuracio) {
    printf("MAC : %s\n", configuracio->mac);
    printf("Nom : %s\n", configuracio->name);
    printf("Situacio : %s\n", configuracio->situation);
    int i;
    for (i = 0; i < 10; i++) {
        printf("Element %i : { codi = %s , valor = %i }\n", i,
                strlen(configuracio->elements[i].codi) == 0 ? "No assignat" : configuracio->elements[i].codi,
                configuracio->elements[i].valor);
    }
}

void set(char* commanda, Configuracio* configuracio) {
    char dispositiu[20];
    char valor[20];
    sscanf(commanda, "set %s %s\n", dispositiu, valor);
    int i;
    for (i = 0; i<sizeof (configuracio->elements) / sizeof (Element); i++) {
        if (strcmp(dispositiu, configuracio->elements[i].codi) == 0) {
            configuracio->elements[i].valor = atoi(valor);
            break;
        }
    }
}

/*int send(char* nom_dispositiu,Configuracio* configuracio){
    return 0;
}*/

int comandes(Estat* estat_client, Configuracio* configuracio) {
    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(0, &read_set);
    struct timeval time_out;
    time_out.tv_sec = 0;
    int result = 0;

    char commanda [100];
    while (estat_client->estat == SEND_HELLO) {
        FD_ZERO(&read_set);
        FD_SET(0, &read_set);
        result = select(1, &read_set, NULL, NULL, &time_out);
        if (result > 0) {
            if (FD_ISSET(0, &read_set)) {
                if (fgets(commanda, 100, stdin) != NULL) {
                    if (strcmp("quit\n", commanda) == 0) {
                        quit();
                    } else if (strcmp("stat\n", commanda) == 0) {
                        stat(configuracio);
                    } else if (strncmp("set", commanda, strlen("set")) == 0) {
                        set(commanda, configuracio);
                    } else if (strcmp("\n", commanda) == 0) {

                    } else {
                        fprintf(stderr,"No es reconeix la commanda\n");
                    }
                }
            }
        } else if (result < 0) {
            fprintf(stderr, "SEVERE => Error al select() \n");
        }
    }
    return 0;
}

