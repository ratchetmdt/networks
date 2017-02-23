/*
 * Copyright (C) 2017 naluem
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

/* 
 * File:   subscripcio.h
 * Author: naluem
 *
 * Created on 23 de febrero de 2017, 21:55
 */
#include "estat_client.h"
#include "arguments.h"

#ifndef SUBSCRIPCIO_H
#define SUBSCRIPCIO_H 

/*
 * PDU fase de subscripcio
 */
typedef struct pdu {
    unsigned char tipus_paquet;
    char mac[13];
    char numero_aleatori[9];
    char dades[80];
} PDU;

/*
 * Tipus de paquets per a la fase de registre
 */
#define SUBS_REQ (int) 0X00
#define SUBS_ACK (int) 0X01
#define SUBS_INFO (int) 0X02
#define INFO_ACK (int) 0X03
#define SUBS_NACK (int) 0X04
#define SUBS_REJ (int) 0X05

/*
 * Estats del client en la fase de registre
 */
#define DISCONNECTED (int) 0XA0
#define NOT_SUBSCRIBED (int)0XA1
#define WAIT_ACK_SUBS (int) 0XA2
#define WAIT_ACK_INFO (int) 0XA3
#define SUBSCRIBED (int) 0XA4
#define SEND_HELLO (int) 0XA5
#define WAIT_INFO (int) 0XA6

/*
 * Valors dels temporitzadors i llindars de la fase de registre
 */
#define T (int) 1
#define U (int) 3
#define N (int) 8
#define O (int) 3
#define P (int) 3
#define Q (int) 4

int subscripcio(Estat* estat_client, Configuracio* configuracio);

#endif /* SUBSCRIPCIO_H */

