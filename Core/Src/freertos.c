/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stream_buffer.h"
#include "filtering_algorithms.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
float64_t test_data[400] =
        {
                1700818, 1989363, 1994475, 1996110, 1997032, 1997350, 1997110, 1996960, 1996969, 1996949, 1997004,
                1997299, 1997674, 1998283, 2261279, 2261813, 2262108, 2262302, 2262452, 2262521,
                2262540, 2262558, 2262545, 2262545, 2262563, 2262592, 2262522, 2262249, 2262191, 2262350, 2262562,
                2262789, 2262882, 2262859, 2262836, 2262903, 2262983, 2263104, 2263136, 2263115,
                2263021, 2262968, 2262953, 2262962, 2262965, 2263011, 2263029, 2263017, 2262895, 2262748, 2262759,
                2262830, 2262864, 2262905, 2262896, 2262887, 2262864, 2262864, 2262861, 2262867,
                2262860, 2262869, 2262866, 2262872, 2262868, 2262868, 2262885, 2262829, 2262656, 2262594, 2262644,
                2262683, 2262714, 2262749, 2262731, 2262718, 2262715, 2262737, 2262755, 2262763,
                2262790, 2262798, 2262797, 2262808, 2262802, 2262746, 2262588, 2262564, 2262630, 2262680, 2262702,
                2262722, 2262719, 2262698, 2262699, 2262713, 2262712, 2262728, 2262724, 2262730,
                2262728, 2262733, 2262751, 2262632, 2262464, 2262483, 2262547, 2262599, 2262629, 2262638, 2262635,
                2262621, 2262613, 2262613, 2262630, 2262646, 2262659, 2262666, 2262675, 2262674,
                2262690, 2262688, 2262644, 2262450, 2262421, 2262497, 2262555, 2262595, 2262625, 2262618, 2262621,
                2262614, 2262605, 2262624, 2262632, 2262631, 2262605, 2262587, 2262560, 2262553,
                2262560, 2262561, 2262573, 2262441, 2262279, 2262306, 2262398, 2262467, 2262488, 2262518, 2262522,
                2262498, 2262490, 2262496, 2262526, 2262566, 2262586, 2262606, 2262639, 2262644,
                2262653, 2262662, 2262669, 2262610, 2262425, 2262349, 2262389, 2262425, 2262451, 2262458, 2262455,
                2262435, 2262449, 2262457, 2262501, 2262510, 2262493, 2262488, 2262472, 2262478,
                2262501, 2262508, 2262445, 2262307, 2262293, 2262357, 2262404, 2262418, 2262426, 2262429, 2262401,
                2262403, 2262405, 2262432, 2262438, 2262448, 2262454, 2262460, 2262448, 2262386,
                2262224, 2262209, 2262275, 2262324, 2262363, 2262382, 2262388, 2262372, 2262371, 2262378, 2262379,
                2262402, 2262402, 2262414, 2262416, 2262405, 2262221, 2262109, 2262157, 2262210,
                2262264, 2262288, 2262300, 2262293, 2262292, 2262286, 2262303, 2262317, 2262336, 2262338, 2262336,
                2262344, 2262318, 2262133, 2262024, 2262100, 2262151, 2262195, 2262224, 2262229,
                2262213, 2262208, 2262214, 2262223, 2262242, 2262249, 2262259, 2262271, 2262265, 2262263, 2262272,
                2262155, 2261985, 2262003, 2262069, 2262109, 2262125, 2262157, 2262145, 2262140,
                2262135, 2262137, 2262165, 2262179, 2262183, 2262200, 2262224, 2262212, 2262204, 2262213, 2262226,
                2262197, 2262047, 2261985, 2262045, 2262092, 2262109, 2262133, 2262117, 2262112,
                2262103, 2262125, 2262131, 2262145, 2262152, 2262160, 2262166, 2262167, 2262166, 2262170, 2262171,
                2262191, 2262186, 2262120, 2261943, 2261919, 2261986, 2262041, 2262068, 2262084,
                2262086, 2262065, 2262066, 2262073, 2262092, 2262107, 2262106, 2262114, 2262132, 2262123, 2262114,
                2262133, 2262134, 2262139, 2262140, 2262065, 2261904, 2261894, 2261982, 2262014,
                2262044, 2262066, 2262059, 2262039, 2262038, 2262048, 2262059, 2262084, 2262079, 2262091, 2262100,
                2262109, 2262105, 2262116, 2262127, 2262120, 2262083, 2261935, 2261846, 2261902,
                2261972, 2262012, 2262024, 2262019, 2262005, 2262005, 2262006, 2262024, 2262030, 2262046, 2262056,
                2262066, 2262055, 2262056, 2262059, 2262060, 2262077, 2262078, 2261970, 2261832,
                2261861, 2261926, 2261972, 2261989, 2262012, 2261980, 2261973, 2261986, 2261990, 2262008, 2262018,
                2262025, 2262024, 2262024, 2262029, 2262021, 2262036, 2262039, 2262050, 2262037,
                2261900, 2261795, 2261850, 2261906, 2261935, 2261958, 2261950, 2261958, 2261944, 2261947, 2261963,
                2261977, 2261984, 2262003, 2261995, 2262006, 2262005, 2262001, 2262008, 2262018,
        };

StructBuffer Red_Data_Buffer;
StructBuffer Red_AC_Buffer;
/* USER CODE END Variables */
osThreadId touchGFXHandle;
osThreadId taskPPGHandle;
osThreadId filterTaskHandle;
osMessageQId Queue_PPG_IRHandle;
osMessageQId Queue_PPG_RedHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TouchGFX_Task(void const * argument);
void PPG_Task(void const * argument);
void FilterTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of Queue_PPG_IR */
  osMessageQDef(Queue_PPG_IR, 16, float64_t);
  Queue_PPG_IRHandle = osMessageCreate(osMessageQ(Queue_PPG_IR), NULL);

  /* definition and creation of Queue_PPG_Red */
  osMessageQDef(Queue_PPG_Red, 16, float64_t);
  Queue_PPG_RedHandle = osMessageCreate(osMessageQ(Queue_PPG_Red), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of touchGFX */
  osThreadDef(touchGFX, TouchGFX_Task, osPriorityNormal, 0, 2048);
  touchGFXHandle = osThreadCreate(osThread(touchGFX), NULL);

  /* definition and creation of taskPPG */
  osThreadDef(taskPPG, PPG_Task, osPriorityBelowNormal, 0, 1024);
  taskPPGHandle = osThreadCreate(osThread(taskPPG), NULL);

  /* definition and creation of filterTask */
  osThreadDef(filterTask, FilterTask, osPriorityAboveNormal, 0, 1024);
  filterTaskHandle = osThreadCreate(osThread(filterTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_TouchGFX_Task */
/**
  * @brief  Function implementing the touchGFX thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TouchGFX_Task */
__weak void TouchGFX_Task(void const * argument)
{
  /* USER CODE BEGIN TouchGFX_Task */
    /* Infinite loop */
    for (;;) {
        osDelay(1);
    }
  /* USER CODE END TouchGFX_Task */
}

/* USER CODE BEGIN Header_PPG_Task */
/**
* @brief Function implementing the taskPPG thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PPG_Task */
void PPG_Task(void const * argument)
{
  /* USER CODE BEGIN PPG_Task */
    int a = 0;
    /* Infinite loop */
    for (;;) {
        uint32_t IR_data_raw = 0, RED_data_raw = 0;
        float64_t IR_data = 0, RED_data = 0;
        if (HAL_GPIO_ReadPin(PPG_INT_GPIO_Port, PPG_INT_Pin) == GPIO_PIN_RESET) {
            // MAX_Read_N_Samples(17, MAX_IR_Sample_Buffer, MAX_RED_Sample_Buffer);
            MAX_Read_One_Sample(&IR_data_raw, &RED_data_raw);
            IR_data = test_data[a];
            RED_data = test_data[a];
            a = (a + 1) % 400;
            if(a == 399) HAL_UART_Transmit(&huart1, (uint8_t *)"Cycle\n", 6, 1000);
//            IR_data = (float32_t) IR_data_raw;
//            RED_data = (float32_t) RED_data_raw;
            if (IR_data > 100000)
                if (xQueueSend(Queue_PPG_IRHandle, &IR_data, portMAX_DELAY) == errQUEUE_FULL)
                    HAL_UART_Transmit(&huart1, (uint8_t *) "Queue IR Full\n", 15, 1000);
            if (RED_data > 100000)
                if (xQueueSend(Queue_PPG_RedHandle, &RED_data, portMAX_DELAY) == errQUEUE_FULL)
                    HAL_UART_Transmit(&huart1, (uint8_t *) "Queue Red Full\n", 16, 1000);
        }

        osDelay(20);
    }
  /* USER CODE END PPG_Task */
}

/* USER CODE BEGIN Header_FilterTask */
/**
* @brief Function implementing the filterTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FilterTask */
void FilterTask(void const * argument)
{
  /* USER CODE BEGIN FilterTask */
//    StructWindowAVG * Red_Avg = slide_avg_init(50, &Red_Data_Buffer);
    StructWindowMinMax * Red_MinMax = slide_minmax_init();
    float64_t max_red_ac = 0, min_red_ac = 0;
    float64_t avg_red = 0, red_ac = 0, minmaxed_red = 0;
    /* Infinite loop */
    for (;;) {
        char str[40] = "";
        float64_t IR_data = 0, Red_data = 0;
        if (xQueueReceive(Queue_PPG_RedHandle, &Red_data, portMAX_DELAY) == pdFALSE);
        if (xQueueReceive(Queue_PPG_IRHandle, &IR_data, portMAX_DELAY) == pdFALSE);
        avg_red = update_window_avg(&Red_Data_Buffer, Red_data);
        red_ac = Red_data - avg_red;
        update_window_avg(&Red_AC_Buffer, red_ac);
        update_window_MinMax(Red_MinMax, red_ac, Red_AC_Buffer.RemovedValue, &max_red_ac, &min_red_ac);
        minmaxed_red = red_ac / (max_red_ac - min_red_ac);
        sprintf(str, "PPG: %lf,%lf,%lf,%lf\n", IR_data, minmaxed_red, max_red_ac, min_red_ac);
        HAL_UART_Transmit(&huart1, str, strlen(str), 1000);
        osDelay(pdMS_TO_TICKS(10));
    }
  /* USER CODE END FilterTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
