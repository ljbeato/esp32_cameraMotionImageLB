
/**
 * Camera motion detection demo
 */

#include "ESP32Cam.h"
#include "PlaneLB.h"



#define THUMB_WIDTH 160
#define THUMB_HEIGHT 120
int motionCounter = 0;

PlaneLB im;
PlaneLB prevIm;
ESP32Cam cam;
BOOLEAN motionDetected;

void setup() 
{
    Serial.begin(115200);
    im.set_m_iLines(320);
    im.set_m_iPixels(240);
    // turn on high freq for fast streaming speed
    Serial.println("Camera init OK");
    cam.InitCamera(PIXFORMAT_GRAYSCALE);
}


void loop()
{
  cam.RedLED(1);
  cam.TakePhoto();
  byte *buf = cam.GetDataBuffer();
  im.set_m_Data(buf);
  im.DownSample(2);
  
  im.DetectMotion(prevIm, motionDetected);
  if (motionDetected == TRUE)
  {
    PRINTF("MOTION DETECTED-%d\n", motionCounter++);
    //cam.SavePhoto();
    cam.FlashLED(1);
  }
  else
  {
    cam.FlashLED(0);
  }

  cam.ReleasePhoto();
  
  prevIm = im;
  cam.RedLED(0);
}

 
