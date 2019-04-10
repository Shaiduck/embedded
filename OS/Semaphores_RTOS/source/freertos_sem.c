/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define TASK_PRIO (configMAX_PRIORITIES - 1)
#define CONSUMER_LINE_SIZE 3
SemaphoreHandle_t xSemaphore_producer;
SemaphoreHandle_t xSemaphore_consumer;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void producer_task(void *pvParameters);
static void consumer_task(void *pvParameters);

typedef struct {
    uint8_t * const buffer;
    int head;
    int tail;
    const int maxlen;
} circ_bbuf_t;

int circ_bbuf_push(circ_bbuf_t *c, uint8_t data)
{
    int next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->maxlen)
        next = 0;

    if (next == c->tail)  // if the head + 1 == tail, circular buffer is full
        return -1;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
    return 0;  // return success to indicate successful push.
}

int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data)
{
    int next;

    if (c->head == c->tail)  // if the head == tail, we don't have any data
        return -1;

    next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->maxlen)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
    return 0;  // return success to indicate successful push.
}

#define CIRC_BBUF_DEF(x,y)                \
    uint8_t x##_data_space[y];            \
    circ_bbuf_t x = {                     \
        .buffer = x##_data_space,         \
        .head = 0,                        \
        .tail = 0,                        \
        .maxlen = y                       \
    }

    CIRC_BBUF_DEF(my_circ_buf, 32);

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    if (xTaskCreate(producer_task, "PRODUCER_TASK", configMINIMAL_STACK_SIZE + 128, NULL, TASK_PRIO, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }

    uint8_t out_data=0, in_data = 0x55;

    if (circ_bbuf_push(&my_circ_buf, in_data)) {
        printf("Out of space in CB\n");
        return -1;
    }

    if (circ_bbuf_pop(&my_circ_buf, &out_data)) {
        printf("CB is empty\n");
        return -1;
    }

    // here in_data = in_data = 0x55;
    printf("Push: 0x%x\n", in_data);
    printf("Pop:  0x%x\n", out_data);
    return 0;
    /* Start scheduling. */
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task producer_task.
 */
static void producer_task(void *pvParameters)
{
    uint32_t i;

    PRINTF("Producer_task created.\r\n");
    xSemaphore_producer = xSemaphoreCreateBinary();
    if (xSemaphore_producer == NULL)
    {
        PRINTF("xSemaphore_producer creation failed.\r\n");
        vTaskSuspend(NULL);
    }

    xSemaphore_consumer = xSemaphoreCreateBinary();
    if (xSemaphore_consumer == NULL)
    {
        PRINTF("xSemaphore_consumer creation failed.\r\n");
        vTaskSuspend(NULL);
    }

    for (i = 0; i < CONSUMER_LINE_SIZE; i++)
    {
        if (xTaskCreate(consumer_task, "CONSUMER_TASK", configMINIMAL_STACK_SIZE, (void *)i, TASK_PRIO, NULL) != pdPASS)
        {
            PRINTF("Task creation failed!.\r\n");
            vTaskSuspend(NULL);
        }
        else
        {
            PRINTF("Consumer_task %d created.\r\n", i);
        }
    }

    while (1)
    {
        /* Producer is ready to provide item. */
        xSemaphoreGive(xSemaphore_consumer);
        /* Producer is waiting when consumer will be ready to accept item. */
        if (xSemaphoreTake(xSemaphore_producer, portMAX_DELAY) == pdTRUE)
        {
            PRINTF("Producer released item.\r\n");
        }
        else
        {
            PRINTF("Producer is waiting for customer.\r\n");
        }
    }
}

/*!
 * @brief Task consumer_task.
 */
static void consumer_task(void *pvParameters)
{
    PRINTF("Consumer number: %d\r\n", pvParameters);
    while (1)
    {
        /* Consumer is ready to accept. */
        xSemaphoreGive(xSemaphore_producer);
        /* Consumer is waiting when producer will be ready to produce item. */
        if (xSemaphoreTake(xSemaphore_consumer, portMAX_DELAY) == pdTRUE)
        {
            PRINTF("Consumer %d accepted item.\r\n", pvParameters);
        }
        else
        {
            PRINTF("Consumer %d is waiting for producer.\r\n", pvParameters);
        }
    }
}
