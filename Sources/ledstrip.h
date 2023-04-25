

#ifndef LEDSTRIP_H_
#define LEDSTRIP_H_

#include <stdint.h>
#include <stdbool.h>

#define NUMBER_OF_FRAMES    12*105U
#define TIMEOUT             1000000UL   /* 1 second interval */
#define BUFFER_SIZE         12
#define NUMBER_LED          105
#define SPI_TRANSFER        1



typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} rgb_t;


typedef enum
{
	Mode_Fade_Transition,
	Mode_Expand_to_Fill,
	Mode_Dashed_Expansion,
	Mode_Pixel_Light,
	Mode_News_Ticker,
	Mode_Breathing_Light,
} ledstrip_mode_t;


typedef enum
{
	Glacier_White ,
	Sunset_Orange,
	Velvet_Gold,
	Lake_Green,
	Sky_Cyan,
	Ocean_Blue,
	Lilac_Purple,
	Violet_Red
} ledstrip_color_t;

typedef struct {
	ledstrip_mode_t mode;
	ledstrip_color_t color;
} ledstrip_status_t;


void ledsrip_spi_init(void);
void dec_turn_spi_number(uint8_t num);
void rgb_select(uint8_t red, uint8_t green, uint8_t blue);
rgb_t rgb_color(ledstrip_color_t color);
void Fade_Transition(ledstrip_color_t color);
void Expand_to_Fill(void);
void Dashed_Expansion(void);
void Pixel_Light(ledstrip_color_t color);
void News_Ticker(ledstrip_color_t color);
void Breathing_Light(ledstrip_color_t color);
void color_test(uint8_t red, uint8_t green, uint8_t blue);
void color_test1(uint8_t mode);
ledstrip_status_t get_ledsrip_status(void);



#endif /* LEDSTRIP_H_ */
