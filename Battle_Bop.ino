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

void setup() {
  // put your setup code here, to run once:
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

  Serial.begin(9600);
  randomSeed(analogRead(seed_generator));
}

void loop() {
  // put your main code here, to run repeatedly:
  bool start = digitalRead(start_button);
  if (start == 0)
  {
    delay(250);
    reset_game();
    start_turn();
  }
}

void start_turn(){
  // Generate turn
  int num = random(1,4);
  if (num == 1){
    Serial.print("Kick It\n");
  }
  else if (num == 2){
    Serial.print("Dodge It\n");
  }
  else{
    Serial.print("Punch It\n");
  }

  // Poll user inputs
  bool kick = true;
  double dodge_x = 0.0;
  double dodge_y = 0.0;
  bool punch = true;
  bool again = false;

  while(1){
    kick = digitalRead(kick_it);
    if (kick == false)
    {
      again = led_strip_display(1, num);
      break;
    }

    dodge_x = analogRead(dodge_it_x);
    dodge_y = analogRead(dodge_it_y);
    if (dodge_x > 700 || dodge_x < 300 || dodge_y > 700 || dodge_x < 300)
    {
      again = led_strip_display(2, num);
      break;
    }

    punch = digitalRead(punch_it);
    if (punch == false)
    {
      again = led_strip_display(3, num);
      break;
    }
  }

  if (again == true){
    start_turn();
  }
  else{
    return 0;
  }
}

bool led_strip_display(int response, int action){
  if (response == action){ // User chose correctly
    digitalWrite(hex_increment, HIGH);
    digitalWrite(green_led, HIGH);
    delay(500);
    digitalWrite(hex_increment, LOW);
    digitalWrite(green_led, LOW);
    return true;
  }

  else if (response != action){ // User chose incorrectly
    digitalWrite(red_led, HIGH);
    return false;
  }

  else{} //do nothing

  return false;
}

void reset_game(){
  //reset hex
  digitalWrite(hex_reset, HIGH);
  delay(200);
  digitalWrite(hex_reset, LOW);

  // reset leds
  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, HIGH);
  delay(200);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);

  // ckear serial monitor
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

  return 0;
}