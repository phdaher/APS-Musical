#include "asf.h"
#include "music.h"
// LED da Placa
#define LED_PIO           PIOC                 
#define LED_PIO_ID        ID_PIOC              
#define LED_PIO_IDX       8                    
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   

// Buzzer
#define PIN0_PIO           PIOA
#define PIN0_PIO_ID        ID_PIOA
#define PIN0_PIO_IDX       0
#define PIN0_PIO_IDX_MASK  (1 << PIN0_PIO_IDX)

// Botao Play/Pause
#define BUT_PIO           PIOA
#define BUT_PIO_ID        ID_PIOA
#define BUT_PIO_IDX       11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

 
// Função de inicialização do uC
void init(void){
	sysclk_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	pmc_enable_periph_clk(PIN0_PIO_ID);
	pmc_enable_periph_clk(LED_PIO_ID);
	pio_configure(LED_PIO, PIO_OUTPUT_0, LED_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_output(PIN0_PIO, PIN0_PIO_IDX_MASK, 0, 0, 0);
}

void play(int duration[], int notes[], int n);


int main(void)
{
	init();
	
	int num = 0;
	int song = 1;
	
	while (1)
	{
		if (song = 1) {
			num = sizeof(hb_notes) / sizeof(hb_notes[0]);
			play(hb_duration, hb_notes, num);
			song = 2;
		}
		
		if (song = 2) {
			num = sizeof(caribe_notes) / sizeof(caribe_notes[0]);
			play(caribe_duration, caribe_notes, num);
			song = 1;
		} 
	}
	return 0;
}

void play(int duration[], int notes[], int n){
	int h;
	int delay;
	int dur;
	delay_s(0.5);
	for(int i = 0; i < n; i++){
		h = 0;
		delay = 1000000/notes[i];
		dur = duration[i] * 1000;
		while(h<dur/delay){
			pio_clear(LED_PIO, LED_PIO_IDX_MASK);
			pio_set(PIN0_PIO, PIN0_PIO_IDX_MASK);
			delay_us(delay/2);
			
			pio_clear(PIN0_PIO, PIN0_PIO_IDX_MASK);
			pio_set(LED_PIO, LED_PIO_IDX_MASK);
			delay_us(delay/2);
			
			h++;
		}
		if (pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 0){
			delay_s(0.5);
			if (pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 0) {
				return;
			}
			while(pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK) == 1){
			}
			delay_s(0.5);
		}
		
		delay_us(65000);
	}
	return;
}