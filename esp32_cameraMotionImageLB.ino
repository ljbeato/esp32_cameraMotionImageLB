
/**
 * Camera motion detection demo
 */

#include "ESP32Cam.h"




#define THUMB_WIDTH 32
#define THUMB_HEIGHT 24
int motionCounter = 0;


ESP32Cam cam;

void setup() 
{

    Serial.begin(115200);

    // turn on high freq for fast streaming speed




    Serial.println("Camera init OK");


    cam.InitCamera(PIXFORMAT_GRAYSCALE);
}


void loop()
 {


     cam.TakePhoto();

     cam.ReleasePhoto();

}

 
