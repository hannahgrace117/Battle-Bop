/*
0001.mp3 - Welcome to BattleBop
0002.mp3 - Get Ready
0003.mp3 - Kick It
0004.mp3 - Punch It
0005.mp3 - Dodge It
0006.mp3 - You Win
0007.mp3 - Whomp Whomp
0008.mp3 - Game Over
*/


#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  Serial.begin(9600);
  delay(1000); // Let DFPlayer power up

  if (!myDFPlayer.begin(Serial, false, true)) {
    // Can't use Serial.println here without interfering
    while (true); // Hang if DFPlayer doesn't start
  }

  myDFPlayer.volume(10);  // 0-30
  delay(2000);
}

void loop()
{
  for(int i = 1; i<9; i++){
    myDFPlayer.playMp3Folder(i);
    delay (4000);
    }
}
