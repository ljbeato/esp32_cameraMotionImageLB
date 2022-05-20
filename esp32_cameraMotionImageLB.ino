
/**
 * Camera motion detection demo
 */

#include "ESP32Cam.h"
#include "PlaneLB.h"



#define THUMB_WIDTH 360
#define THUMB_HEIGHT 240
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
    prevIm.set_m_iLines(32);
    prevIm.set_m_iPixels(24);
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
  im.DownSample(THUMB_HEIGHT/RESAMPLED_ROWS);
  
  im.DetectMotion(prevIm, motionDetected);
  if (motionDetected == TRUE)
  {
    PRINTF("MOTION DETECTED-%d\n", motionCounter++);
    //cam.SavePhoto();
    cam.FlashLED(1);
    delay(1);
    cam.FlashLED(0);
  }
  else
  {
    cam.FlashLED(0);
  }
  cam.ReleasePhoto();
  
  prevIm = im;
  cam.RedLED(0);
}

 
