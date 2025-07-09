#include <DFRobotDFPlayerMini.h>
DFRobotDFPlayerMini myDFPlayer;

#define red_led 13
#define green_led 12
#define start_button 11
#define kick_it 10
#define dodge_it_x 18
#define dodge_it_y 17
#define punch_it 9
#define seed_generator 19
#define hex_increment 8
#define hex_reset 7
unsigned long round_start;
unsigned long round_time = 3000; // round timer (ms)
unsigned long round_end;
bool polling_inputs = false;
int score = 0;
bool test_mode = false;
bool initialized_for_test = false;

void setup() {
  // Configure all pins
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(start_button, INPUT);
  pinMode(kick_it, INPUT);
  pinMode(dodge_it_x, INPUT);
  pinMode(dodge_it_y, INPUT);
  pinMode(punch_it, INPUT);
  pinMode(seed_generator, INPUT);
  pinMode(hex_increment, OUTPUT);
  pinMode(hex_reset, OUTPUT);

  // Randomize the turn generator
  randomSeed(analogRead(seed_generator));

  //Setup for DF player
  Serial.begin(9600);
  delay(1000);
  if (!myDFPlayer.begin(Serial, false, true)) {
    // Can't use Serial.println here without interfering
    delay(100);
    while (true); // Hang if DFPlayer doesn't start
  }
  
  digitalWrite(green_led, HIGH);  
  delay(100);
  digitalWrite(green_led, LOW);

  myDFPlayer.volume(15); // volume is range 0-30
  delay(1000);
  myDFPlayer.playMp3Folder(1); // play the welcome to Battle Bop sound
  delay(3000);
}

void loop(){
  bool start = digitalRead(start_button);
  test_mode = digitalRead(punch_it);
  test_mode = !test_mode;
  if (test_mode && !initialized_for_test){
    score = 90;
    delay(200);

    // Reset Hex
    digitalWrite(hex_reset, HIGH);
    delay(100);
    digitalWrite(hex_reset, LOW);

    // Set hex to initialized score
    for (int i = 0; i < score; i++){
      digitalWrite(hex_increment, HIGH);
      delay(50);
      digitalWrite(hex_increment, LOW);
      delay(50);
    }

    // Set proper time frame of turn
    round_time = 3000 - score*20;
    
    initialized_for_test = true;
  }

  else if (test_mode && initialized_for_test){
    score = 0;
    // Reset Hex
    digitalWrite(hex_reset, HIGH);
    delay(100);
    digitalWrite(hex_reset, LOW);
    initialized_for_test = false;
  }

  if (start == 0){
    delay(200);
    reset_game();
    // Clear serial monitor
    start_turn();
    delay(200);
  }

  delay(100);
}

void start_turn(){
  // Generate turn
  int num = random(1,4);
  if (num == 1){
    // Play audio of "Kick It"
    myDFPlayer.playMp3Folder(3);
    delay(500);
  }
  else if (num == 2){
    // Play audio of "Dodge It"
    myDFPlayer.playMp3Folder(5);
    delay(500);
  }
  else{
    // Play audio of "Punch It"
    myDFPlayer.playMp3Folder(4);
    delay(500);
  }

  polling_inputs = true;
  round_start = millis(); // Start round timer
  round_end = round_start + round_time;

  // Poll user inputs
  bool kick = true;
  double dodge_x = 0.0;
  double dodge_y = 0.0;
  bool punch = true;
  bool again = false;
  long int t;

  while (polling_inputs && (millis() <= round_end)){
    kick = digitalRead(kick_it);
    if (kick == false)
    {
      polling_inputs = false;
      again = process_input(1, num);
      break;
    }

    dodge_x = analogRead(dodge_it_x);
    dodge_y = analogRead(dodge_it_y);
    if (dodge_x > 700 || dodge_x < 300 || dodge_y > 700 || dodge_x < 300)
    {
      polling_inputs = false;
      again = process_input(2, num);
      break;
    }

    punch = digitalRead(punch_it);
    if (punch == false)
    {
      polling_inputs = false;
      again = process_input(3, num);
      break;
    }
  }

  if (polling_inputs && millis() - round_start > round_time){ // time expired
    again = process_input(0, num);
    myDFPlayer.playMp3Folder(8);
    initialized_for_test = false;
  }

  if (again == true){
    start_turn();
  }
  else if (score == 99){ // User won, return to loop()
    initialized_for_test = false;
  }

  else {
    initialized_for_test = false;
  }

  return 0;
}

bool process_input(int response, int prompt){
  if (response == prompt && score != 99){ // User chose correctly, not at 100
    digitalWrite(hex_increment, HIGH); // Increment hex
    digitalWrite(green_led, HIGH); // Flash green led
    delay(500);
    digitalWrite(hex_increment, LOW);
    digitalWrite(green_led, LOW);
    // display image on lcd
    round_time -= 20; // decrease round time by 20ms
    round_start = 0; // reset round start time stamp
    score++; // Increase the user's score

    return true;
  }
  else if (response == prompt){ // User won the game!
    victory();
  }

  else if (response != prompt){ // User chose incorrectly
    // Display LCD of losing
    myDFPlayer.playMp3Folder(7);
    delay(1200);
    myDFPlayer.playMp3Folder(8);
    
    for (int i = 0; i < 12; i++){
    digitalWrite(red_led, HIGH);
    delay(200);
    digitalWrite(red_led,LOW);
    delay(200);
    }
  }

  else{} //do nothing

  return false;
}

void victory(){
  // Play audio of "You Won"
    myDFPlayer.playMp3Folder(6);
    delay(1000);
  for (int i = 0; i < 12; i++){
    // Display LCD of winning
    digitalWrite(green_led, HIGH);
    delay(200);
    digitalWrite(green_led,LOW);
    delay(200);
  }
  test_mode = false; //  Exit test mode
  initialized_for_test = false;
}

void reset_game(){
  if (!initialized_for_test){
    // Reset hex
    digitalWrite(hex_reset, HIGH);
    delay(200);
    digitalWrite(hex_reset, LOW);
    // Reset round timer
    round_time = 3000;

    // Reset score
    score = 0;
  }

  // Reset leds
  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, HIGH);
  delay(200);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);

  return 0;
}