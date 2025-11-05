#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "fonts.h"
#include "ssd1306_oled.h"

#include "bmp.h"
#include <stdio.h>

char buf_oled[20];

void SystemClock_Config(void);

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	SSD1306_Init();

	while(1)
	{
		SSD1306_GotoXY(10,20);
		SSD1306_Puts("OLED I2C SSD1306", &Font_7x10, WHITE);
		SSD1306_GotoXY(15,40);
		SSD1306_Puts("STM32F103C8T6", &Font_7x10, WHITE);
		SSD1306_UpdateScreen();
		HAL_Delay(2000);

		SSD1306_Clear();
		SSD1306_GotoXY(10,1);
		SSD1306_Puts("Font 1", &Font_7x10, WHITE);
		SSD1306_GotoXY(10,15);
		SSD1306_Puts("Font 2", &Font_11x18, WHITE);
		SSD1306_GotoXY(10,35);
		SSD1306_Puts("Font 3", &Font_16x26, WHITE);
		SSD1306_UpdateScreen();
		HAL_Delay(2000);

		SSD1306_Clear();
		SSD1306_DrawRectangle(2, 2, 123, 60, WHITE);
		SSD1306_GotoXY(10,10);
		SSD1306_Puts("CONTADOR", &Font_7x10, WHITE);
		SSD1306_DrawCircle(95, 35, 16, WHITE);
		SSD1306_UpdateScreen();

		uint8_t contador = 0;
		while(contador <= 10)
		{
			SSD1306_GotoXY(30,30);
			sprintf(buf_oled, "%u ", contador);
			SSD1306_Puts(buf_oled, &Font_11x18, WHITE);
			SSD1306_UpdateScreen();
			contador++;
			HAL_Delay(400);
		}
		SSD1306_DrawFilledCircle(95, 35, 16, WHITE);
		SSD1306_UpdateScreen();
		HAL_Delay(1000);

		SSD1306_Clear();
		SSD1306_DrawBitmap(0, 0, imagen, 128, 64, WHITE);
		SSD1306_UpdateScreen();
		HAL_Delay(2000);

		SSD1306_ScrollRight(0, 0x0F);
		HAL_Delay(4000);
		SSD1306_ScrollLeft(0, 0x0F);
		HAL_Delay(4000);
		SSD1306_Stopscroll();
		HAL_Delay(1000);

		SSD1306_Clear();
		HAL_Delay(500);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
