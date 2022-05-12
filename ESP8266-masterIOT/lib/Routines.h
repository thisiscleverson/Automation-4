#ifndef _Routines_H
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

///////////////////////////////////////////////////////////////////////////////////////////////////

int hourM1 = 5;
int hourM2 = 5;
int hourM3 = 5;
int hourM4 = 5;

int minutM1 = 0;
int minutM2 = 0;
int minutM3 = 0;
int minutM4 = 0;

int secondM1 = 0;
int secondM2 = 0;
int secondM3 = 0;
int secondM4 = 0; 


/////////////////////////////////////////////////////////////////////////////////////////////////////

int getTime(){
  timeClient.update();

  int currentHour = timeClient.getHours();

  int currentMinute = timeClient.getMinutes();

  int currentSecond = timeClient.getSeconds();

  return (currentHour,currentMinute,currentSecond);

}

String getWeekDays(){
	timeClient.update();
	return weekDays[timeClient.getDay()];
}

void Routines(){

	int hours,minutes, seconds = getTime();
	String week_day = getWeekDays();

	///////////////////////////////////////

	if((hours == hourM1) && (minutes >= minutM1 && minutes <= minutM1+10)){
		Mode1();
	}

	if(){

	}

	if(){

	}

	if(){

	}


}

///////////////////////////////////////////

void Mode1(){

}

void Mode2(){

}

void Mode3(){

}

void Mode4(){

}


#endif