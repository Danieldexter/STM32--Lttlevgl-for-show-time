#include "lv_calendar.h"
#include "lvgl.h"
#include "key.h"
#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
#include "delay.h"
#include <string.h>

/*��������*/
void get_time(void);
void event_handler(lv_obj_t * obj,lv_event_t event);
//static void btn_event_cb(lv_obj_t * obj,lv_event_t event);
void lv_calendar_roller_set(void);
void lv_calendar_start(void);


/*��������*/
lv_obj_t * label_hour;
lv_obj_t * label_min;
lv_obj_t * label_second;
lv_obj_t * scr;
lv_obj_t * scr1;
lv_obj_t * roller_hour;
lv_obj_t * roller_min;
lv_obj_t * roller_second;

/*RTC�洢��������*/
uint8_t tbuf[40];
uint8_t tbuf_Hour[20];
uint8_t tbuf_min[20];
uint8_t tbuf_second[20];

char  set_hour[2];
char  set_min[2];
char  set_second[2];
int x;
int y;
int z;
u8 xa=0;
u8 ya=0;
u8 za=0;

lv_style_t bg_style;
lv_style_t sel_style;

int tt=0;

lv_style_t my_style_btn_release;// ��Ŧ�ͷ�״̬�µ���ʽ
lv_style_t my_style_btn_press;// ��Ŧ���µ���ʽ
lv_obj_t * btn1,* btn2,* btn3;
lv_obj_t * btn1_label,* btn3_label;


void get_time(void)
{	
		if(label_hour != NULL)
		{
		RTC_TimeTypeDef RTC_TimeStruct;
		tt++;
		if((tt%10)==0)	//ÿ100ms����һ����ʾ����
		{	
			RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct); // ��ȡRTC�����ʱ��	
			//sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
			sprintf((char*)tbuf_Hour,"%02d",RTC_TimeStruct.RTC_Hours); // ��RTC�����ʱ���-ʱ-����tbuf_hour�� 
			lv_label_set_text(label_hour,(char*)tbuf_Hour);
			sprintf((char*)tbuf_min,"%02d",RTC_TimeStruct.RTC_Minutes); // ��RTC�����ʱ���-��-����tbuf_hour�� 
			lv_label_set_text(label_min,(char*)tbuf_min);
			sprintf((char*)tbuf_second,"%02d",RTC_TimeStruct.RTC_Seconds); // ��RTC�����ʱ���-��-����tbuf_hour�� 
			lv_label_set_text(label_second,(char*)tbuf_second);
		}
	}

}



void lv_calendar_start(void)
{	
	
	//ҳ���ʼ��
	scr = lv_scr_act(); // ��ȡ��ǰ��Ծ����Ļ����
	bg_style.body.main_color = LV_COLOR_BLACK;//����
	lv_obj_set_click(scr,true); // ʹ�ܴ�������
	//lv_obj_set_event_cb(scr,event_handler);//�����¼��ص�����
	
	//����label��ǩ--ʱ
	label_hour = lv_label_create(scr,NULL);
	lv_obj_set_width(label_hour,200);
	lv_label_set_recolor(label_hour,true);
	lv_label_set_align(label_hour,LV_LABEL_ALIGN_CENTER); 
	lv_label_set_style(label_hour,LV_LABEL_STYLE_MAIN,&lv_style_pretty);
	lv_label_set_body_draw(label_hour,true);
	lv_obj_align(label_hour,NULL,LV_ALIGN_CENTER,-35,-20);
	
	
	//����label��ǩ--��
	label_min = lv_label_create(scr,NULL);
	lv_obj_set_width(label_min,200);
	lv_label_set_recolor(label_min,true);
	lv_label_set_align(label_min,LV_LABEL_ALIGN_CENTER);
	lv_label_set_style(label_min,LV_LABEL_STYLE_MAIN,&lv_style_pretty);
	lv_label_set_body_draw(label_min,true);
	lv_obj_align(label_min,NULL, LV_ALIGN_CENTER,5,-20);
	

	//����label��ǩ--��
	label_second = lv_label_create(scr,NULL);
	lv_obj_set_width(label_second,200);
	lv_label_set_recolor(label_second,true);
	lv_label_set_align(label_second,LV_LABEL_ALIGN_CENTER);
	lv_label_set_style(label_second,LV_LABEL_STYLE_MAIN,&lv_style_pretty);
	lv_label_set_body_draw(label_second,true);
	lv_obj_align(label_second,NULL,LV_ALIGN_CENTER,45,-20);

	
}



