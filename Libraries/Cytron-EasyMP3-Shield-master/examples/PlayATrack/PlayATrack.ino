#include <CytronEZMP3.h>
#include <SoftwareSerial.h>
CytronEZMP3 mp3;

void setup () {
	Serial.begin(9600);
  if(!mp3.begin(2, 3))
  {
    Serial.println("Init failed");
    while(1);
  }
  mp3.setVolume(25);
  Serial.print("Device: ");
  Serial.println(mp3.getCurrentDevice()==1?"U-Disk":"microSD");

  Serial.print("Total files: ");
  Serial.println(mp3.getTotalFiles());
}

void loop () {        
	mp3.playTrack(1);
  Serial.println("Now playing track " + (String)mp3.getTrackNo());
	delay (6000);
	mp3.next();
  Serial.println("Now playing track " + (String)mp3.getTrackNo());
	delay (6000);
	mp3.prev();
  Serial.println("Now playing track " + (String)mp3.getTrackNo());
	delay (6000);
	mp3.playTrack(2);
  Serial.println("Now playing track " + (String)mp3.getTrackNo());
	delay (6000);
}
