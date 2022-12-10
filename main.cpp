
// #include "stm32f4xx_hal.h"

// void Configure_GPIO(void);
// void configure_ADC2_Channel_0(void);
// void Delay_ms(volatile int time_ms);
// double voltage;
// //ADC in single conversion mode( 1-2 samples per second only)
// uint32_t Adc_value;
// ADC_HandleTypeDef myADC2Handle;
// uint32_t counter;
// int main(void)
// {
// 	Configure_GPIO(); // initialize PA0 pin 
// 	configure_ADC2_Channel_0(); // configure ADC2
// 	// while (1){
// 	// HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

// 	// 			// Wait for 500 ms
// 	// 			HAL_Delay(10000);}
// 	while(1)
// 	{
// 	 HAL_ADC_Start(&myADC2Handle); // start A/D conversion
// 		if(HAL_ADC_PollForConversion(&myADC2Handle, 5) == HAL_OK) //check if conversion is completed
// 		{
// 		Adc_value  = HAL_ADC_GetValue(&myADC2Handle); // read digital value and save it inside uint32_t variable
// 		voltage=(Adc_value * 8) / 10000;
		
		
// 		if (voltage > 2.5){
// 			counter++;
// 			if (counter >= 5){
// 				//LED blinks
				

// 				counter=0;
// 			}
		

// 		}
// 		else{
// 			counter=0;
// 		}
// 		}
// 		HAL_ADC_Stop(&myADC2Handle); // stop conversion 
// 		Delay_ms(200);
// 	}
// }

// /* Configure and initialize PA0 pin as analog input pin for A/D conversion */
// void Configure_GPIO(void)
// {
// 	 __HAL_RCC_GPIOA_CLK_ENABLE(); // enable clock to GPIOA
// 	GPIO_InitTypeDef ADCpin; //create an instance of GPIO_InitTypeDef C struct
// 	ADCpin.Pin = GPIO_PIN_0; // Select pin PA0
// 	ADCpin.Mode = GPIO_MODE_ANALOG; // Select Analog Mode
// 	ADCpin.Pull = GPIO_NOPULL; // Disable internal pull-up or pull-down resistor
// 	HAL_GPIO_Init(GPIOA, &ADCpin); // initialize PA0 as analog input pin
// }
// void configure_ADC2_Channel_0(void)
// {
// __HAL_RCC_ADC2_CLK_ENABLE(); // enable clock to ADC2 module
// 	myADC2Handle.Instance = ADC2; // create an instance of ADC2
// 	myADC2Handle.Init.Resolution = ADC_RESOLUTION_12B; // select 12-bit resolution 
// 	myADC2Handle.Init.EOCSelection = ADC_EOC_SINGLE_CONV; //select  single conversion as a end of conversion event
// 	myADC2Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT; // set digital output data right justified
// 	myADC2Handle.Init.ClockPrescaler =ADC_CLOCK_SYNC_PCLK_DIV8; 
// 	HAL_ADC_Init(&myADC2Handle); // initialize AD2 with myADC2Handle configuration settings
	
//   /*select ADC2 channel */
// 	ADC_ChannelConfTypeDef Channel_AN0; // create an instance of ADC_ChannelConfTypeDef
// 	Channel_AN0.Channel = ADC_CHANNEL_0; // select analog channel 0
// 	Channel_AN0.Rank = 1; // set rank to 1
// 	Channel_AN0.SamplingTime = ADC_SAMPLETIME_15CYCLES; // set sampling time to 15 clock cycles
// 	HAL_ADC_ConfigChannel(&myADC2Handle, &Channel_AN0); // select channel_0 for ADC2 module. 
// }
// void Init_OnBoard_LEDs(void)
// {
// 	 __HAL_RCC_GPIOD_CLK_ENABLE();
// 	GPIO_InitTypeDef BoardLEDs;
// 	BoardLEDs.Mode = GPIO_MODE_OUTPUT_PP;
// 	BoardLEDs.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
// 	HAL_GPIO_Init(GPIOD, &BoardLEDs);
// }

// void Delay_ms(volatile int time_ms)
// {
// 	      int j;
//         for(j = 0; j < time_ms*4000; j++)
//             {}  /* excute NOP for 1ms */
// }


#include "stm32f4xx_hal.h"
void Configure_GPIO(void);
void configure_ADC1_Channel_0(void);
void Delay_ms(volatile int time_ms);

ADC_HandleTypeDef myADC2Handle;
 uint32_t rawValue;
 uint32_t counter;
 double voltage;
 float temp;
int main(void)
{
   Configure_GPIO(); // initialize PA0 pin 
	configure_ADC1_Channel_0(); // configure ADC2
	while(1)
	{

 //HAL_ADC_PollForConversion(&myADC2Handle, HAL_MAX_DELAY);

 rawValue = HAL_ADC_GetValue(&myADC2Handle);
 temp = ((float)rawValue) / 4095 * 3300;
 voltage=(temp * 8) / 10000;
		
		
		// if (voltage > 2.5){
		// 	counter++;
		// 	if (counter >= 5){
		// 		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

		// 		// Wait for 500 ms
		// 		HAL_Delay(10000);
		// 		//LED blinks
				

		// 		counter=0;
		// 	}
		

		// }
		// else{
		// 	counter=0;
		// }
	}
}

/* Configure and initialize PA0 pin as analog input pin for A/D conversion */
void Configure_GPIO(void)
{
	 __HAL_RCC_GPIOA_CLK_ENABLE(); // enable clock to GPIOA
	GPIO_InitTypeDef ADCpin; //create an instance of GPIO_InitTypeDef C struct
	ADCpin.Pin = GPIO_PIN_0; // Select pin PA0
	ADCpin.Mode = GPIO_MODE_ANALOG; // Select Analog Mode
	ADCpin.Pull = GPIO_NOPULL; // Disable internal pull-up or pull-down resistor
	HAL_GPIO_Init(GPIOA, &ADCpin); // initialize PA0 as analog input pin
}
void configure_ADC1_Channel_0(void)
{
__HAL_RCC_ADC1_CLK_ENABLE(); // enable clock to ADC1 module
	myADC2Handle.Instance = ADC1; // create an instance of ADC2
	myADC2Handle.Init.ClockPrescaler =ADC_CLOCK_SYNC_PCLK_DIV8; 
	myADC2Handle.Init.Resolution = ADC_RESOLUTION_12B; // select 12-bit resolution 
	myADC2Handle.Init.ScanConvMode = DISABLE;
	myADC2Handle.Init.ContinuousConvMode = ENABLE;
	myADC2Handle.Init.DiscontinuousConvMode = DISABLE;
	myADC2Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT; // set digital output data right justified
        myADC2Handle.Init.NbrOfConversion = 1;
        myADC2Handle.Init.DMAContinuousRequests = DISABLE;
        myADC2Handle.Init.EOCSelection = ADC_EOC_SEQ_CONV;

	HAL_ADC_Init(&myADC2Handle); // initialize AD2 with myADC2Handle configuration settings
	
  /*select ADC2 channel */
	ADC_ChannelConfTypeDef Channel_AN0; // create an instance of ADC_ChannelConfTypeDef
	Channel_AN0.Channel = ADC_CHANNEL_0; // select analog channel 0
	Channel_AN0.Rank = 1; // set rank to 1
	Channel_AN0.SamplingTime = ADC_SAMPLETIME_480CYCLES; // set sampling time to 15 clock cycles
	HAL_ADC_ConfigChannel(&myADC2Handle, &Channel_AN0); // select channel_0 for ADC2 module. 
}
void Delay_ms(volatile int time_ms)
{
	      int j;
        for(j = 0; j < time_ms*4000; j++)
            {}  /* excute NOP for 1ms */
}


