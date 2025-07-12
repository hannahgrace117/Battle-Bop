#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

//paramters define
#define MODEL ST7796S
#define CS   7    
#define CD   8
#define RST  6
#define LED  -1   //if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V

//the definiens of hardware spi mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_SPI mylcd(MODEL,CS,CD,RST,LED); //model,cs,dc,reset,led


//define some colour values
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() 
{
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);
  mylcd.Set_Text_Mode(0);
}

void loop() 
{
  // idle
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String(" O", 0, 0);
  mylcd.Print_String("/|\\", 0, 60);
  mylcd.Print_String("/ \\", 0, 120);
  mylcd.Set_Text_colour(RED);
  mylcd.Print_String(" O", 350, 0);
  mylcd.Print_String("/|\\", 350, 60);
  mylcd.Print_String("/ \\", 350, 120);
  mylcd.Set_Text_Size(10);
  mylcd.Set_Text_colour(MAGENTA);
  mylcd.Set_Text_Back_colour(CYAN);
  mylcd.Print_String(" FIGHT!  ", 0, 245);
  delay(3000);

  // kick it
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String(" O", 0, 0);
  mylcd.Print_String("/|\\", 0, 60);
  mylcd.Print_String("/ \\_____", 0, 120);
  mylcd.Set_Text_colour(RED);
  mylcd.Print_String(" O", 350, 0);
  mylcd.Print_String("/|\\", 350, 60);
  mylcd.Print_String("/ \\", 350, 120);
  delay(3000);

  // idle
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String(" O", 0, 0);
  mylcd.Print_String("/|\\", 0, 60);
  mylcd.Print_String("/ \\", 0, 120);
  mylcd.Set_Text_colour(RED);
  mylcd.Print_String(" O", 350, 0);
  mylcd.Print_String("/|\\", 350, 60);
  mylcd.Print_String("/ \\", 350, 120);
  mylcd.Set_Text_Size(10);
  mylcd.Set_Text_colour(MAGENTA);
  mylcd.Set_Text_Back_colour(CYAN);
  mylcd.Print_String("  FIGHT! ", 0, 245);
  delay(3000);

  // // punch it
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String(" O", 0, 0);
  mylcd.Print_String("/|----------", 0, 60);
  mylcd.Print_String("/ \\", 0, 120);
  mylcd.Set_Text_colour(RED);
  mylcd.Print_String(" O", 350, 0);
  mylcd.Print_String("/|\\", 350, 60);
  mylcd.Print_String("/ \\", 350, 120);
  delay(3000);

  // idle
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String(" O", 0, 0);
  mylcd.Print_String("/|\\", 0, 60);
  mylcd.Print_String("/ \\", 0, 120);
  mylcd.Set_Text_colour(RED);
  mylcd.Print_String(" O", 350, 0);
  mylcd.Print_String("/|\\", 350, 60);
  mylcd.Print_String("/ \\", 350, 120);
  delay(3000);

  // dodge it 
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(8);
  mylcd.Print_String(" O", 0, 65);
  mylcd.Print_String("/ \\", 0, 125);
  mylcd.Set_Text_colour(RED);
  mylcd.Print_String("------ O", 50, 0);
  mylcd.Print_String(" |\\", 340, 60);
  mylcd.Print_String("/ \\", 340, 120);
  delay(3000);

}
