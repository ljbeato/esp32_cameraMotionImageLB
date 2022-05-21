
/**
 * Camera motion detection demo
 */

#include "ESP32Cam.h"
#include "PlaneLB.h"
#include "ArduinoComm.h"


#define CAMERA_WIDTH 360
#define CAMERA_HEIGHT 240
int motionCounter = 0;

PlaneLB im;
PlaneLB prevIm;
ESP32Cam cam;
ArduinoComm comm;
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

void CheckForTransmit(unsigned char *ptr, int len)
{
  //Serial.printf("Length in bytes %d\n", size);
  if (comm.Available()) 
  {
    // read the incoming byte:
    byte incomingByte = comm.ReadSerialByte();
    if (incomingByte == 'S')
    {
      comm.TransmitRawBytes(ptr, len);
    }
  } 
  
}
void loop()
{
  cam.RedLED(1);
  cam.TakePhoto();
  byte *buf = cam.GetDataBuffer();
  im.set_m_Data(buf);
  im.DownSample(CAMERA_HEIGHT/CAMERA_WIDTH);
  
  CheckForTransmit(buf, CAMERA_HEIGHT*CAMERA_WIDTH);
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

 
