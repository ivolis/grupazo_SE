//=====[Libraries]=============================================================

#include "arm_book_lib.h"


//=====[Declarations (prototypes) of public functions]=========================
void setRTC();
void printRTC();


//=====[Main function, the program entry point after power on or reset]========
int main()
{
    setRTC();
    printRTC();
    while (true) {
    }
}


//=====[Implementations of public functions]===================================
void setRTC(){
    struct tm rtcTime;
    int strIndex;
                    
    uartUsb.write( "\r\nType four digits for the current year (YYYY): ", 48 );
    for( strIndex=0; strIndex<4; strIndex++ ) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[4] = '\0';
    rtcTime.tm_year = atoi(str) - 1900;
    uartUsb.write( "\r\n", 2 );

    uartUsb.write( "Type two digits for the current month (01-12): ", 47 );
    for( strIndex=0; strIndex<2; strIndex++ ) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[2] = '\0';
    rtcTime.tm_mon  = atoi(str) - 1;
    uartUsb.write( "\r\n", 2 );

    uartUsb.write( "Type two digits for the current day (01-31): ", 45 );
    for( strIndex=0; strIndex<2; strIndex++ ) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[2] = '\0';
    rtcTime.tm_mday = atoi(str);
    uartUsb.write( "\r\n", 2 );

    uartUsb.write( "Type two digits for the current hour (00-23): ", 46 );
    for( strIndex=0; strIndex<2; strIndex++ ) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[2] = '\0';
    rtcTime.tm_hour = atoi(str);
    uartUsb.write( "\r\n", 2 );

    uartUsb.write( "Type two digits for the current minutes (00-59): ", 49 );
    for( strIndex=0; strIndex<2; strIndex++ ) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[2] = '\0';
    rtcTime.tm_min  = atoi(str);
    uartUsb.write( "\r\n", 2 );

    uartUsb.write( "Type two digits for the current seconds (00-59): ", 49 );
    for( strIndex=0; strIndex<2; strIndex++ ) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[2] = '\0';
    rtcTime.tm_sec  = atoi(str);
    uartUsb.write( "\r\n", 2 );

    rtcTime.tm_isdst = -1;
    set_time( mktime( &rtcTime ) );
    uartUsb.write( "Date and time has been set\r\n", 28 );
}

void printRTC(){
    time_t epochSeconds;
    epochSeconds = time(NULL);
    sprintf ( str, "Date and Time = %s", ctime(&epochSeconds));
    uartUsb.write( str , strlen(str) );
    uartUsb.write( "\r\n", 2 );
}