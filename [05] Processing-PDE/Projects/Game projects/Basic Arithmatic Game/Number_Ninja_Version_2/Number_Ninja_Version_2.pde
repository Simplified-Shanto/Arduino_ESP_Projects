import processing.sound.*; 
SoundFile correctSound; 
SoundFile wrongSound; 

int lower = 15; 
int upper = 100; 
int A = 0; 
int B = 0; 
int answer = A + B; 
int CorrectAnswer = 0; //# of correct answer; 
int WrongAnswer = 0; 

int flag = 0; 
int submit = 0; 

//Position variables. 
float quizX = 87; 
float quizY = 160; 
float tileY = 230; 
float tileX = 2; 
float gap = 0; 
int debug = 0;   //Whether we want to print debug messages

Tile[] tiles; 
Tile nextButton; 
 
void setup()
{
  if(debug==1)
  {
    print("Setup started  at "); 
     print(millis());
     print('\n'); 
  }
 size(400, 400); 
 tiles =  new Tile[4]; 
 for(int i = 0; i<4; i++) { 
   tiles[i] = new Tile("-1", tileX + gap, tileY); 
   gap+=100; 
   
   correctSound = new SoundFile(this, "coinsound.mp3"); 
   wrongSound = new SoundFile(this, "wronganswer.wav");
   
   
 }
 
 nextButton =  new Tile( "Next", 200, 320); 
 nextButton.Length = 150; 
 
 if(debug==1)
  {
   print("Set up ended at "); 
     print(millis());
     print('\n');
  }
}

void draw()
{
  background(255, 202, 173); 
  nextButton.select(); 
  nextButton.drawTile(); 
  
  
           if(debug==1)
          {
     print("Time : "); 
     print(millis());
     print('\n');
          }
          
  if(flag==0)
  {
    A = ceil(random(lower, upper)); 
    B = ceil(random(lower, upper)); 
    answer = A+B; 
    
      if(debug==1)
          {
     print("Calculated random A, B, and answer successfully at : "); 
     print(millis());
     print('\n');
          }
    
    int filled = 0; 
    while(filled<4)
    {
      int wrongAnswer = floor(random(answer-10, upper*2));
      
        if(debug==1)
          {
     print("Calculated wrong answer = : "); print(wrongAnswer);
     print(" at "); 
     print(millis());
     print('\n');
          }
          
      int flg = 1; 
      for(int i = 0; i<4; i++)
      {
        if(int(tiles[i].value)==wrongAnswer || wrongAnswer==answer) { flg = 0; } 
      }
      if(flg==1){tiles[filled].value = str(wrongAnswer); filled++; 
                    
                      if(debug==1)
          {
     print("Filling  "); print(filled); print("th option at ");  
     print(millis());
     print('\n');
          }
  
                 }
    }
    
      print("Tiles are filled successfully at "); 
     print(millis());
     print('\n'); 
    
    int randomIndex = floor(random(0, 4)); 
     //Placing the correct answer to some random index. 
    tiles[randomIndex].value = str(answer);
   
   
            flag  = 1; 
            if(debug==1)
          {
     print("Created quiz successfully at "); 
     print(millis());
     print('\n');
          }
  }
  
 
  
  for(int i = 0; i<4; i++)
  {
   if(tiles[i].select()==1)
   {
      if(submit==0)
      {
        if(int(tiles[i].value)==answer)
        { 
        CorrectAnswer++; 
        correctSound.play(); 
        }
        else 
        {
        WrongAnswer++; 
        wrongSound.play(); 
        }
      } 
     submit=1; 
   }
   
   if(submit==1)
  {
    if(int(tiles[i].value)==answer)
    {
      tiles[i].activeColor = tiles[i].correctColor; 
    }
    else
    { 
      tiles[i].activeColor = tiles[i].wrongColor; 
    }
  }
  
  tiles[i].drawTile(); 
  }
  
  //Making new quiz
  if(submit==1 && nextButton.select()==1)
  {
              if(debug==1)
          {
     print("Resetting flag and submit at "); 
     print(millis());
     print('\n');
          }
   submit = 0; 
   flag = 0; 
  }
  
  //Drawing the question. 
     textSize(50); 
     fill(0, 98, 255);
     text(A, quizX-30, quizY); 
     text("+", quizX + 40, quizY); 
     text(B, quizX + 100, quizY); 
     text(" =   ?", quizX + 200, quizY);
  
  //Drawing the wrong answer and correct answer values
        float scoreY = 31; 
     {
     textSize(30); 
     fill(132, 173, 29);
     text("Correct: ", 20, scoreY); 
     text(CorrectAnswer, 162, scoreY); 
     fill(149, 0, 255);
     text("Wrong: ", 200, scoreY); 
     text(WrongAnswer,350, scoreY);  
     }
   
  
}
