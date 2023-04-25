
#include "ledstrip.h"
#include <math.h>
#include "osif.h"
#include <stdlib.h>
#include "Send.h"


uint8_t master_send[BUFFER_SIZE]={0};
uint8_t master_receive[BUFFER_SIZE]={0};
uint8_t spi_transfer_number[BUFFER_SIZE/3]={0}; //rgb
uint8_t master_send_buffer[BUFFER_SIZE*NUMBER_LED+30]={0};

uint8_t de_light_index[NUMBER_LED],de_light_count,de_flag;
ledstrip_status_t ledsrip_status;

  void dec_turn_spi_number(uint8_t num)
    {
    	uint8_t i, data[8]={0};

    	for(i=0;i<8;i++)
    	{
    	    data[i]=num%2;
    	    num=num/2;
      }

    	for(i=0;i<8;i=i+2)
        {
    		if(data[i+1]==1)
    		{
    			if(data[i]==1)	spi_transfer_number[i/2]=238;
    			else spi_transfer_number[i/2]=232;
    		}
    		else
    		{
    			if(data[i]==1)	spi_transfer_number[i/2]=142;
    			else spi_transfer_number[i/2]=136;
    		}
        }
    }

    void rgb_select(uint8_t red, uint8_t green, uint8_t blue)
    {
		//r
		dec_turn_spi_number(red);
        master_send[0] = spi_transfer_number[3];
        master_send[1] = spi_transfer_number[2];
        master_send[2] = spi_transfer_number[1];
        master_send[3] = spi_transfer_number[0];
        //g
        dec_turn_spi_number(green);
        master_send[4] = spi_transfer_number[3];
        master_send[5] = spi_transfer_number[2];
        master_send[6] = spi_transfer_number[1];
        master_send[7] = spi_transfer_number[0];
        //b
        dec_turn_spi_number(blue);
        master_send[8] = spi_transfer_number[3];
        master_send[9] = spi_transfer_number[2];
        master_send[10] = spi_transfer_number[1];
        master_send[11] = spi_transfer_number[0];
    }

    rgb_t rgb_color(ledstrip_color_t color)
    {
    	rgb_t rgb;

    	switch(color)
    	{
    	case Glacier_White:
    		rgb.red = 255;
    		rgb.green = 255;
    		rgb.blue = 255;
    		break;
    	case Sunset_Orange:
    		rgb.red = 255;
    		rgb.green = 40;
    		rgb.blue = 10;
    		break;
    	case Velvet_Gold:
    		rgb.red = 255;
    		rgb.green = 70;
    		rgb.blue = 0;
    		break;
    	case Lake_Green:
    		rgb.red = 0;
    		rgb.green = 255;
    		rgb.blue = 80;
    		break;
    	case Sky_Cyan:
    		rgb.red = 0;
    		rgb.green = 180;
    		rgb.blue = 255;
    		break;
    	case Ocean_Blue:
    		rgb.red = 0;
    		rgb.green = 0;
    		rgb.blue = 255;
    		break;
    	case Lilac_Purple:
    		rgb.red = 80;
    		rgb.green = 0;
    		rgb.blue = 160;
    		break;
    	case Violet_Red:
    		rgb.red = 255;
    		rgb.green = 0;
    		rgb.blue = 100;
    		break;
    	}
    	return rgb;
    }

    void Fade_Transition(ledstrip_color_t color)
    {
    	float up_section=40,fade_section_front=20,fade_section_back=20;
    	float up_section_piece=1/up_section,fade_section_front_piece=1/fade_section_front,fade_section_back_piece=0.5/fade_section_back;
		uint8_t i,j,k,start_section=0,start_section_middle=start_section/2;
		uint8_t red, green,blue;
		ledstrip_color_t before_color=ledsrip_status.color;
    	rgb_t rgb;
    	ledsrip_status.mode = Mode_Fade_Transition;
    	ledsrip_status.color = color;

    	rgb=rgb_color(before_color);
    	red=rgb.red;
    	green=rgb.green;
    	blue=rgb.blue;

	   	for(j=start_section;j<=up_section;j++)
	    	{
	    		rgb_select(red*(0+up_section_piece*j),green*(0+up_section_piece*j),blue*(0+up_section_piece*j));
	    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
	    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
	    		OSIF_TimeDelay(50);
	    	}
	   	for(j=fade_section_front;j>10;j--)
    	{
    		rgb_select(red*(0+fade_section_front_piece*j),green*(0+fade_section_front_piece*j),blue*(0+fade_section_front_piece*j));
    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(50);
    	}
    	for(j=fade_section_back;j>start_section_middle;j--)
    	{
    		rgb_select(red*(0+fade_section_back_piece*j),green*(0+fade_section_back_piece*j),blue*(0+fade_section_back_piece*j));
    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(50);
    	}

    	rgb=rgb_color(color);
    	red=rgb.red;
    	green=rgb.green;
    	blue=rgb.blue;
    	for(j=start_section;j<=up_section;j++)
    	{
    		rgb_select(red*(0+up_section_piece*j),green*(0+up_section_piece*j),blue*(0+up_section_piece*j));
    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(50);
    	}
    	for(j=fade_section_front;j>10;j--)
    	    	{
    	    		rgb_select(red*(0+fade_section_front_piece*j),green*(0+fade_section_front_piece*j),blue*(0+fade_section_front_piece*j));
    	    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    	    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    	    		OSIF_TimeDelay(50);
    	    	}
    	    	for(j=fade_section_back;j>start_section_middle;j--)
    	    	{
    	    		rgb_select(red*(0+fade_section_back_piece*j),green*(0+fade_section_back_piece*j),blue*(0+fade_section_back_piece*j));
    	    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    	    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    	    		OSIF_TimeDelay(50);
    	    	}


    }

    void Expand_to_Fill(void)
    {
    	uint8_t i,j,k, red=255, green=255, blue=255;
    	uint8_t light_index[NUMBER_LED]={0},mudian_led_numer=floor(NUMBER_LED/2);
    	ledsrip_status.mode = Mode_Expand_to_Fill;

    	for(j=0;j<=NUMBER_LED/2+1;j++)
    	{
    		if(j==1) light_index[mudian_led_numer]=1;
    		if(j>1)
    		{
    			light_index[mudian_led_numer+(j-1)]=1;
    			light_index[mudian_led_numer-(j-1)]=1;
    		}

    		for(i=0;i<NUMBER_LED;i++)
    		{
    			if(light_index[i]==0)
    			{
    				rgb_select(0,0,0);
    				for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    			}
    			else
    			{
    				rgb_select(red,green,blue);
    				for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    			}
    		}
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		if(j<=10)OSIF_TimeDelay(1*15*100/52);
    		if(10<j&&j<45)OSIF_TimeDelay(1*5*100/52);
    		if(j>=45)OSIF_TimeDelay(1*15*100/52);
    	}
    	OSIF_TimeDelay(500);
    }

    void Dashed_Expansion(void)
    {
    	uint8_t i,j,k, red=255, green=255, blue=255;
    	uint8_t light_number=15,dislight_number=5,mudian_led_numer=floor(NUMBER_LED/2);
    	ledstrip_mode_t status_buff = ledsrip_status.mode;
    	ledsrip_status.mode = Mode_Dashed_Expansion;

    	if(status_buff != Mode_Dashed_Expansion)
    	{
    		for(i=0;i<NUMBER_LED;i++)de_light_index[i]=0;
    		de_light_count=0;
    	}

    	for(j=0;j<=NUMBER_LED/2;j++)
    	{
    		for(k=NUMBER_LED-1;k>mudian_led_numer;k--) de_light_index[k]=de_light_index[k-1];
    		for(k=0;k<mudian_led_numer;k++) de_light_index[k]=de_light_index[k+1];

    		de_light_index[mudian_led_numer+1]=de_light_index[mudian_led_numer];
    		de_light_index[mudian_led_numer-1]=de_light_index[mudian_led_numer];
    		if(de_light_count<light_number)de_light_index[mudian_led_numer]=1;
    		if(de_light_count>=light_number&&de_light_count<light_number+dislight_number)de_light_index[mudian_led_numer]=0;
    		de_light_count=de_light_count+1;
    		if(de_light_count==light_number+dislight_number)de_light_count=0;

    		for(i=0;i<NUMBER_LED;i++)
    		{
    			if(de_light_index[i]==0)
    			{
    				rgb_select(0,0,0);
    				for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    			}
    			else
    			{
    				rgb_select(red,green,blue);
    				for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    			}
    		}
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(30);
    	}
    }

    void Pixel_Light(ledstrip_color_t color)
    {
    	uint8_t i,k, red, green, blue;
    	uint8_t light_index[NUMBER_LED]={0},unlight[15]={0},unlight_number=sizeof(unlight)/sizeof(unlight[0]);
    	rgb_t rgb;
    	ledsrip_status.mode = Mode_Pixel_Light;
    	ledsrip_status.color = color;

    	rgb=rgb_color(color);
    	red=rgb.red;
    	green=rgb.green;
    	blue=rgb.blue;

    	for(i=0;i<unlight_number;i++)
    	{
    		unlight[i]=rand() % NUMBER_LED;
    		light_index[unlight[i]]=1;
    	}

    	for(i=0;i<NUMBER_LED;i++)
    	{
    		if(light_index[i]==1)	rgb_select(0,0,0);
    		else	rgb_select(red,green,blue);
    		for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    	}
    	LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    	OSIF_TimeDelay(200);
    }


    void News_Ticker(ledstrip_color_t color)
    {
    	uint8_t i,j,k, red, green, blue;
    	uint8_t light_trip[9]={0,1,2,3,4,5,6,7,8},fade_section=15;
    	float light_power[5]={1,0.3,0.05,0.05,0.05};
    	float light_section[3]={0.1,1,0.1};
    	uint8_t light_trip_number=sizeof(light_trip)/sizeof(light_trip[0]);
    	rgb_t rgb;
    	ledsrip_status.mode = Mode_News_Ticker;
    	ledsrip_status.color = color;

    	rgb=rgb_color(color);
    	red=rgb.red;
    	green=rgb.green;
    	blue=rgb.blue;

    	for(j=0;j<NUMBER_LED;j++)
    	{
    		for(i=0;i<NUMBER_LED;i++)
    		{
    			if(i==light_trip[0]||i==light_trip[8])
    			{
    				if(j<fade_section)rgb_select(red*light_power[4]*light_section[0],green*light_power[4]*light_section[0],blue*light_power[4]*light_section[0]);
    				else if(j>=NUMBER_LED-fade_section)rgb_select(red*light_power[4]*light_section[2],green*light_power[4]*light_section[2],blue*light_power[4]*light_section[2]);
    				else rgb_select(red*light_power[4]*light_section[1],green*light_power[4]*light_section[1],blue*light_power[4]*light_section[1]);
    			}
    			else if(i==light_trip[1]||i==light_trip[7])
    			{
    				if(j<fade_section)rgb_select(red*light_power[3]*light_section[0],green*light_power[3]*light_section[0],blue*light_power[3]*light_section[0]);
    				else if(j>=NUMBER_LED-fade_section)rgb_select(red*light_power[3]*light_section[2],green*light_power[3]*light_section[2],blue*light_power[3]*light_section[2]);
    				else rgb_select(red*light_power[3]*light_section[1],green*light_power[3]*light_section[1],blue*light_power[3]*light_section[1]);
    			}
    			else if(i==light_trip[2]||i==light_trip[6])
    			{
    				if(j<fade_section)rgb_select(red*light_power[2]*light_section[0],green*light_power[2]*light_section[0],blue*light_power[2]*light_section[0]);
    				else if(j>=NUMBER_LED-fade_section)rgb_select(red*light_power[2]*light_section[2],green*light_power[2]*light_section[2],blue*light_power[2]*light_section[2]);
    				else rgb_select(red*light_power[2]*light_section[1],green*light_power[2]*light_section[1],blue*light_power[2]*light_section[1]);
    			}
    			else if(i==light_trip[3]||i==light_trip[5])
    			{
    				if(j<fade_section)rgb_select(red*light_power[1]*light_section[0],green*light_power[1]*light_section[0],blue*light_power[1]*light_section[0]);
    				else if(j>=NUMBER_LED-fade_section)rgb_select(red*light_power[1]*light_section[2],green*light_power[1]*light_section[2],blue*light_power[1]*light_section[2]);
    				else rgb_select(red*light_power[1]*light_section[1],green*light_power[1]*light_section[1],blue*light_power[1]*light_section[1]);
    			}
    			else if(i==light_trip[4])
    			{
    				if(j<fade_section)rgb_select(red*light_power[0]*light_section[0],green*light_power[0]*light_section[0],blue*light_power[0]*light_section[0]);
    				else if(j>=NUMBER_LED-fade_section)rgb_select(red*light_power[0]*light_section[2],green*light_power[0]*light_section[2],blue*light_power[0]*light_section[2]);
    				else rgb_select(red*light_power[0]*light_section[1],green*light_power[0]*light_section[1],blue*light_power[0]*light_section[1]);
    			}
    			else
    			{
    				rgb_select(0,0,0);
    			}
    			for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		}
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(30);
    		for(i=0;i<light_trip_number;i++)
    		{
    			light_trip[i]=light_trip[i]+1;
    			light_trip[i]=light_trip[i]%NUMBER_LED;
    		}
    	}
    }

    void Breathing_Light(ledstrip_color_t color)
    {
    	uint8_t i,j,k, red, green, blue;
    	float up_section=40,fade_section_front=20,fade_section_back=20;
    	float up_section_piece=1/up_section,fade_section_front_piece=1/fade_section_front,fade_section_back_piece=0.5/fade_section_back;
		uint8_t start_section=6,start_section_middle=start_section/2;
    	rgb_t rgb;
    	ledsrip_status.mode = Mode_Breathing_Light;
    	ledsrip_status.color = color;

    	rgb=rgb_color(color);
    	red=rgb.red;
    	green=rgb.green;
    	blue=rgb.blue;

    	for(j=start_section;j<=up_section;j++)
    	{
    		rgb_select(red*(0+up_section_piece*j),green*(0+up_section_piece*j),blue*(0+up_section_piece*j));
    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(50);
    	}
    	for(j=fade_section_front;j>10;j--)
    	{
    		rgb_select(red*(0+fade_section_front_piece*j),green*(0+fade_section_front_piece*j),blue*(0+fade_section_front_piece*j));
    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(50);
    	}
    	for(j=fade_section_back;j>start_section_middle;j--)
    	{
    		rgb_select(red*(0+fade_section_back_piece*j),green*(0+fade_section_back_piece*j),blue*(0+fade_section_back_piece*j));
    		for(i=0;i<NUMBER_LED;i++)for(k=0;k<BUFFER_SIZE;k++)master_send_buffer[i*BUFFER_SIZE+k]=master_send[k];
    		LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    		OSIF_TimeDelay(50);
    	}
    }

    void color_test(uint8_t red, uint8_t green, uint8_t blue)
    {
    	uint8_t i,j;
    	rgb_select(red,green,blue);
    	for(i=0;i<NUMBER_LED;i++)for(j=0;j<BUFFER_SIZE;j++) master_send_buffer[i*BUFFER_SIZE+j]=master_send[j];
    	LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    	OSIF_TimeDelay(50);
    }

    void color_test1(uint8_t mode)
    {
    	uint8_t i,j;
    	if(mode==0) rgb_select(255,255,255);	//Glacier White
    	if(mode==1) rgb_select(255,40,10);		//Sunset Orange
    	if(mode==2) rgb_select(255,70,0);		//Velvet Gold
    	if(mode==3) rgb_select(0,255,80);		//Lake Green
    	if(mode==4) rgb_select(0,180,255);		//Sky Cyan
    	if(mode==5) rgb_select(0,0,255);		//Ocean Blue
    	if(mode==6) rgb_select(80,0,160);		//Lilac Purple
    	if(mode==7) rgb_select(255,0,100);		//Violet Red
    	for(i=0;i<NUMBER_LED;i++)for(j=0;j<BUFFER_SIZE;j++) master_send_buffer[i*BUFFER_SIZE+j]=master_send[j];
    	LPSPI_DRV_MasterTransfer(SEND, master_send_buffer,master_receive, NUMBER_OF_FRAMES);
    	OSIF_TimeDelay(2000);
    }

    ledstrip_status_t get_ledsrip_status(void)
    {
		return ledsrip_status;
    }
