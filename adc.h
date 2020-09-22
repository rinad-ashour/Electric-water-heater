#ifndef __ADC_H__
#define __ADC_H__

void ADC_Init(unsigned char clock_source);
void ADC_Update(void);
unsigned int ADC_GetResult(unsigned char channel);
#endif // __ADC_H__

