# include "iGraphics.h"
#include<windows.h>
#include<mmsystem.h>

#define screenHeight 1000
#define screenWidth 1600
int x = 300, y = 300, r = 1, i, j, c=0,number = 0, numberOfPlayers = 4, runningPlayerno = 1, finishCOunter = 0,winnerno = 100;

char p[4][20] = {"Player 1","Player 2","Player 3","Player 4"};
char win[4][25] = {"winner\\p1wins.bmp","winner\\p2wins.bmp","winner\\p3wins.bmp","winner\\p4wins.bmp"};


bool initialized = false, diceRollingMusicOn = false,rollingdone = false, oneWinnerFound = false;

bool gameWindow = false, MenuPage = false, startingWindow = true, musicOn = true, pauseWindow = false, helpPage = false;
bool creditsPage = false, optionsWindow = false;


struct cell
{
    float x;
    float y;
    int no;
} mazeCells[100];

typedef struct button
{
    float left;
    float bottom;
    float length;
    float height;
}button;

button dice_button, menu, options, quit, new_game, help, credits, b2menu, resume, back_button, sound_button, pause, gameWindowSound;

typedef struct PLAYER
{
    float posX;
    float posY;
    int cellNO;
    char name[25];
}character;

typedef struct snakes
{
    int head;
    int tail;
    float posX;
    float posY;
}snake;

snake snakes_all[10];

typedef struct slides
{
    int head;
    int tail;
    float posX;
    float posY;
}slide;

slide slide1;

typedef struct ladders
{
    int head;
    int tail;
    float posX;
    float posY;
}ladder;

ladder ladders_all[10];

struct dice
{
    int topSide;
    float bottom;
    float left;
    float sides;
    int idx;
    bool rolling;
    bool rolldice;

}die;

typedef struct GameCharacter
{
    int no;
    float x;
    float y;
    int cellNo;
    int willMove;
    bool turn;
    bool moving;
    bool free;
    bool winner;
    int haveToMove;
    int previousTurn;


}GamePlayer;

GamePlayer players[4];

int maze[10][10] = {0};

char digits[100][20] = {"digits\\01.bmp","digits\\02.bmp","digits\\03.bmp","digits\\04.bmp","digits\\05.bmp","digits\\06.bmp","digits\\07.bmp","digits\\08.bmp","digits\\09.bmp","digits\\10.bmp",
                        "digits\\11.bmp","digits\\12.bmp","digits\\13.bmp","digits\\14.bmp","digits\\15.bmp","digits\\16.bmp","digits\\17.bmp","digits\\18.bmp","digits\\19.bmp","digits\\20.bmp",
                        "digits\\21.bmp","digits\\22.bmp","digits\\23.bmp","digits\\24.bmp","digits\\25.bmp","digits\\26.bmp","digits\\27.bmp","digits\\28.bmp","digits\\29.bmp","digits\\30.bmp",
                        "digits\\31.bmp","digits\\32.bmp","digits\\33.bmp","digits\\34.bmp","digits\\35.bmp","digits\\36.bmp","digits\\37.bmp","digits\\38.bmp","digits\\39.bmp","digits\\40.bmp",
                        "digits\\41.bmp","digits\\42.bmp","digits\\43.bmp","digits\\44.bmp","digits\\45.bmp","digits\\46.bmp","digits\\47.bmp","digits\\48.bmp","digits\\49.bmp","digits\\50.bmp",
                        "digits\\51.bmp","digits\\52.bmp","digits\\53.bmp","digits\\54.bmp","digits\\55.bmp","digits\\56.bmp","digits\\57.bmp","digits\\58.bmp","digits\\59.bmp","digits\\60.bmp",
                        "digits\\61.bmp","digits\\62.bmp","digits\\63.bmp","digits\\64.bmp","digits\\65.bmp","digits\\66.bmp","digits\\67.bmp","digits\\68.bmp","digits\\69.bmp","digits\\70.bmp",
                        "digits\\71.bmp","digits\\72.bmp","digits\\73.bmp","digits\\74.bmp","digits\\75.bmp","digits\\76.bmp","digits\\77.bmp","digits\\78.bmp","digits\\79.bmp","digits\\80.bmp",
                        "digits\\81.bmp","digits\\82.bmp","digits\\83.bmp","digits\\84.bmp","digits\\85.bmp","digits\\86.bmp","digits\\87.bmp","digits\\88.bmp","digits\\89.bmp","digits\\90.bmp",
                        "digits\\91.bmp","digits\\92.bmp","digits\\93.bmp","digits\\94.bmp","digits\\95.bmp","digits\\96.bmp","digits\\97.bmp","digits\\98.bmp","digits\\99.bmp","digits\\100.bmp",
                        };

char diceAnimation[5][20] = {"diceAnim\\danim1.bmp","diceAnim\\danim2.bmp","diceAnim\\danim3.bmp","diceAnim\\danim4.bmp","diceAnim\\danim4.bmp"};
char diceSides[6][20] = {"diceSides\\dice1.bmp","diceSides\\dice2.bmp","diceSides\\dice3.bmp","diceSides\\dice4.bmp","diceSides\\dice5.bmp","diceSides\\dice6.bmp"};

void hudai();
void posUpdater();
void snake_ladder_checker();
void initializeALL();
void snake_deifinition();
void ladder_definition();
void defineMaze();
void printMaze();
void showPlayers();
void showSlides();
void showLadders();
void showSnakes();
void rollDice();
void showDice();
void diceRollingAnim();
void playGame();
void onePlayerPlays();
void gameKhela();
void diceAnimator();
void whoseTurn();
void gameMains();
void winChecker();
void playerCurrentPositionPrinter();
void winPrinter();

void rollingSoundPlayer();

void gameStarter();

void menuPageMouseCommands();
void gameWindowMouseCommands();

void mainGameWindowPrint();
void showMenuPage();
void showStartingWindow();
void showPauseMenu();
void showHelpPage();
void showCreditsPage();
void showOptionPage();


/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();

//    iShowBMP(0,0,"snakes and ladders bg.bmp");

    if(gameWindow && !MenuPage && !startingWindow && !pauseWindow && !helpPage && !creditsPage && !optionsWindow)
    {
        mainGameWindowPrint();

    }
    else if(MenuPage && !gameWindow && !startingWindow && !pauseWindow && !helpPage && !creditsPage && !optionsWindow)
    {
        showMenuPage();
    }
    else if(startingWindow && !gameWindow && !MenuPage && !pauseWindow && !helpPage && !creditsPage && !optionsWindow)
    {
        showStartingWindow();
    }
    else if(pauseWindow && !gameWindow && !startingWindow && !MenuPage && !helpPage && !creditsPage && !optionsWindow)
    {
        showPauseMenu();
    }
    else if(helpPage && !gameWindow && !startingWindow && !MenuPage && !pauseWindow && !creditsPage && !optionsWindow)
    {
        showHelpPage();
    }
    else if(creditsPage && !gameWindow && !startingWindow && !MenuPage && !pauseWindow && !helpPage && !optionsWindow)
    {
        showCreditsPage();
    }
    else if(optionsWindow && !gameWindow && !startingWindow && !MenuPage && !pauseWindow && !helpPage && !creditsPage)
    {
        showOptionPage();
    }

//    printf("a %d %d %d\n",gameWindow,MenuPage,startingWindow);

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //main menu
        if(MenuPage && !gameWindow && !startingWindow && !pauseWindow && !helpPage && !creditsPage && !optionsWindow)
        {
            menuPageMouseCommands();
            if( mx >= new_game.left && mx <= (new_game.left+new_game.length)
                && my >= new_game.bottom && my <= (new_game.bottom+new_game.height) )
            {
                // starts new game
                MenuPage = false;
                gameWindow = true;
                initialized = false;
                PlaySound(0,0,0);
            }
            else if( mx >= quit.left && mx <= (quit.left+quit.length)
                && my >= quit.bottom && my <= (quit.bottom+quit.height) )
            {
                exit(0);
            }
            else if( mx >= help.left && mx <= (help.left+help.length)
                && my >= help.bottom && my <= (help.bottom+help.height) )
            {
                helpPage = true;
                MenuPage = false;
            }
            else if( mx >= credits.left && mx <= (credits.left+credits.length)
                && my >= credits.bottom && my <= (credits.bottom+credits.height) )
            {
                creditsPage = true;
                MenuPage = false;
            }
            else if( mx >= options.left && mx <= (options.left+options.length)
                && my >= options.bottom && my <= (options.bottom+options.height) )
            {
                optionsWindow = true;
                MenuPage = false;
            }

        }
        // game window
        else if(gameWindow && !MenuPage && !startingWindow && !pauseWindow && !helpPage && !creditsPage && !optionsWindow)
        {
            if( mx >= dice_button.left && mx <= (dice_button.left+dice_button.length)
                && my >= dice_button.bottom && my <= (dice_button.bottom+dice_button.height) )
            {
                if(!die.rolling)
                {
                    rollDice();
                }
            }

            else if( mx >= pause.left && mx <= (pause.left+pause.length)
                && my >= pause.bottom && my <= (pause.bottom+pause.height) )
            {
                gameWindow = false;
                pauseWindow = true;

                if(musicOn)
                PlaySound("sounds\\menubgmusic.wav", NULL, SND_ASYNC | SND_LOOP);
            }

            else if( mx >= gameWindowSound.left && mx <= (gameWindowSound.left+gameWindowSound.length)
                && my >= gameWindowSound.bottom && my <= (gameWindowSound.bottom+gameWindowSound.height) )
            {
                if(musicOn)
                {
                    musicOn = false;
                    PlaySound(0,0,0);
                }
                else
                {
                    musicOn = true;
                }
            }

            gameWindowMouseCommands();
        }


        // pause window
        else if(pauseWindow && !MenuPage && !startingWindow && !gameWindow && !helpPage && !creditsPage && !optionsWindow)
        {
            if( mx >= resume.left && mx <= (resume.left+resume.length)
                && my >= resume.bottom && my <= (resume.bottom+resume.height) )
            {
                pauseWindow = false;
                gameWindow = true;
                PlaySound(0,0,0);

            }
            else if( mx >= b2menu.left && mx <= (b2menu.left+b2menu.length)
                && my >= b2menu.bottom && my <= (b2menu.bottom+b2menu.height) )
            {
                pauseWindow = false;
                MenuPage = true;
                initialized = false;
            }
        }

        // help page
        else if(helpPage && !MenuPage && !startingWindow && !gameWindow && !pauseWindow && !creditsPage && !optionsWindow)
        {
            if( mx >= back_button.left && mx <= (back_button.left+back_button.length)
                && my >= back_button.bottom && my <= (back_button.bottom+back_button.height) )
            {
                helpPage = false;
                MenuPage = true;
            }

        }
        else if(creditsPage && !MenuPage && !startingWindow && !gameWindow && !pauseWindow && !helpPage && !optionsWindow)
        {
            if( mx >= back_button.left && mx <= (back_button.left+back_button.length)
                && my >= back_button.bottom && my <= (back_button.bottom+back_button.height) )
            {
                creditsPage = false;
                MenuPage = true;
            }
        }
        else if(optionsWindow && !MenuPage && !startingWindow && !gameWindow && !pauseWindow && !helpPage && !creditsPage)
        {
            if( mx >= back_button.left && mx <= (back_button.left+back_button.length)
                && my >= back_button.bottom && my <= (back_button.bottom+back_button.height) )
            {
                optionsWindow = false;
                MenuPage = true;
            }
            else if( mx >= sound_button.left && mx <= (sound_button.left+sound_button.length)
                && my >= sound_button.bottom && my <= (sound_button.bottom+sound_button.height) )
            {
                if(musicOn)
                {
                    musicOn = false;
                    PlaySound(0,0,0);
                }
                else
                {
                    musicOn = true;
                    PlaySound("sounds\\menubgmusic.wav", NULL, SND_ASYNC | SND_LOOP);
                }
            }
        }

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'q')
    {
        exit(0);
    }
    if(gameWindow && !MenuPage && !startingWindow)
    {
        if(key == ' ' && !die.rolling)
        {
            rollDice();

        }
    }
    if(key == 'p')
    {
        printf("%d %d %d %d\t%d\n",players[0].winner,players[1].winner,players[2].winner,players[3].winner,oneWinnerFound);
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

    if(gameWindow && !MenuPage && !startingWindow)
    {
        if(key == GLUT_KEY_INSERT)
        {
            gameWindow = false;
            pauseWindow = true;
            if(musicOn)
                PlaySound("sounds\\menubgmusic.wav", NULL, SND_ASYNC | SND_LOOP);

        }
    }

    //place your codes for other keys here
}




/// my functions

void menuPageMouseCommands()
{

}

void gameWindowMouseCommands()
{

}


void mainGameWindowPrint()
{
    if(!initialized)
    {

        defineMaze();

        snake_deifinition();
        ladder_definition();
        initializeALL();

        initialized = true;

    }



    snake_deifinition();
    ladder_definition();
    defineMaze();
    printMaze();
    showSnakes();
    showLadders();
    showPlayers();
    playGame();


    if(!die.rolling)
        showDice();
    else
    {
        diceAnimator();
    }

    playerCurrentPositionPrinter();

    winPrinter();

}

// printing winners name
void winPrinter()
{
    int t;

    if(!oneWinnerFound)
    {
        for(t = 0; t < 4; t++)
        {
            if(players[t].winner)
            {
                winnerno = t;
                oneWinnerFound = true;
                break;
            }
        }
    }

    if(oneWinnerFound)
    {
        if(winnerno == 0)
        {
            iShowBMP2(screenWidth/2 - 400, 15, "winner\\p1wins.bmp", 16777215);
        }
        else if(winnerno == 1)
        {
            iShowBMP2(screenWidth/2 - 400, 15, "winner\\p2wins.bmp", 16777215);
        }
        else if(winnerno == 2)
        {
            iShowBMP2(screenWidth/2 - 400, 15, "winner\\p3wins.bmp", 16777215);
        }
        else if(winnerno == 3)
        {
            iShowBMP2(screenWidth/2 - 400, 15, "winner\\p4wins.bmp", 16777215);
        }
    }

}

// current position of players
void playerCurrentPositionPrinter()
{
    //iShowBMP(screenWidth/2, screenHeight/2+50,"Players\\positions.bmp");
    iShowBMP(screenWidth - 250, screenHeight/2+60,"Players\\player1.bmp");
    iShowBMP2(screenWidth - 250, screenHeight/2+60*0,"Players\\player2.bmp",16777215);
    iShowBMP2(screenWidth - 250, screenHeight/2-60*1,"Players\\player3.bmp",16777215);
    iShowBMP2(screenWidth - 250, screenHeight/2-60*2,"Players\\player4.bmp",16777215);

    iShowBMP(screenWidth/2,screenHeight/2 + 50,"diceSides\\rollit.bmp");

    iShowBMP2(screenWidth - 250, screenHeight/2+60*2,"Players\\players.bmp",16777215);

    if(players[0].cellNo != 0)
        iShowBMP(screenWidth - 60, screenHeight/2+60*1,digits[players[0].cellNo - 1]);
    else
        iShowBMP(screenWidth - 60, screenHeight/2+60*1,"digits\\00.bmp");

    if(players[1].cellNo != 0)
        iShowBMP(screenWidth - 60, screenHeight/2+60*0,digits[players[1].cellNo - 1]);
    else
        iShowBMP(screenWidth - 60, screenHeight/2+60*0,"digits\\00.bmp");

    if(players[2].cellNo != 0)
        iShowBMP(screenWidth - 60, screenHeight/2-60*1,digits[players[2].cellNo - 1]);
    else
        iShowBMP(screenWidth - 60, screenHeight/2-60*1,"digits\\00.bmp");

    if(players[3].cellNo != 0)
        iShowBMP(screenWidth - 60, screenHeight/2-60*2,digits[players[3].cellNo - 1]);
    else
        iShowBMP(screenWidth - 60, screenHeight/2-60*2,"digits\\00.bmp");

    iShowBMP2(pause.left, pause.bottom,"buttons\\pause.bmp",16777215);



    if(musicOn)
        iShowBMP2(gameWindowSound.left, gameWindowSound.bottom,"buttons\\soundon.bmp",16777215);
    else
        iShowBMP2(gameWindowSound.left,gameWindowSound.bottom,"buttons\\soundoff.bmp",16777215);

}


void defineMaze()
{
    int i;
    for(i = 1; i <= 100; i++)
    {
        mazeCells[i-1].no = i;
        iSetColor(255,255,0);
        //printf("%d ",mazeCells[i-1].no);
        //iFilledCircle(100+i*10,500,10);
    }

    for(i = 1;i <= 100; i++)
    {
        if(((mazeCells[i-1].no - 1) / 10) % 2 == 0)
        {
            mazeCells[i-1].x = 100 + 100 - 60 + 60 * ((mazeCells[i-1-1].no % 10));
        }
        else
        {
            mazeCells[i-1].x = 100 + 600-(100 - 60 + 60 * ((mazeCells[i-1-1].no % 10)));
        }

        mazeCells[i-1].y = 100 + 100 - 60 + 60 * ((mazeCells[i-1].no - 1)/ 10);

    }


}

void printMaze()
{
    int d1,d2,i,j;

    iSetColor(10,10,10);
    iFilledRectangle(0,0,screenWidth,screenHeight);

    //iShowBMP(0,0,"snakes and ladders bg.bmp");

    iShowBMP2(screenWidth/2-650/2,800,"snakesandladders.bmp",16777215);

    iShowBMP(mazeCells[0].x+80-30+10-100,-100+mazeCells[0].y+80-10,"digits\\vineframe.bmp");

//    iShowBMP(50,50,"digits\\mainBG.bmp");
    for(i = 1;i <= 100; i++)
    {
        iSetColor(200,0,0);
        iShowBMP(mazeCells[i-1].x,mazeCells[i-1].y,digits[mazeCells[i-1].no-1]);
    }
}

// starting page

void showStartingWindow()
{
    iShowBMP(0,0,"snakes and ladders bg.bmp");
    iShowBMP2(80+450,220,"starting page\\welcome.bmp",16777215);
    iShowBMP2(20+450-50,60,"starting page\\gfzs_2.bmp",16777215);
    iShowBMP(100,100,"starting page\\me.bmp");
}


// menu page part

void showMenuPage()
{
    iShowBMP(0,0,"snakes and ladders bg.bmp");



    iShowBMP2(new_game.left,new_game.bottom,"buttons\\new game.bmp",16777215);
    iShowBMP2(options.left,options.bottom,"buttons\\options.bmp",16777215);
    iShowBMP2(help.left,help.bottom,"buttons\\help.bmp",16777215);
    iShowBMP2(quit.left,quit.bottom,"buttons\\quit.bmp",16777215);
    iShowBMP2(credits.left,credits.bottom,"buttons\\credits.bmp",16777215);
}

// pause menu
void showPauseMenu()
{
    iShowBMP(0,0,"snakes and ladders bg.bmp");

    iShowBMP2(b2menu.left,b2menu.bottom,"buttons\\b2menu.bmp",16777215);
    iShowBMP2(b2menu.left + b2menu.length,b2menu.bottom + b2menu.height/4,"buttons\\progloss.bmp",16777215);
    iShowBMP2(resume.left,resume.bottom,"buttons\\resume.bmp",16777215);

}

// help page
void showHelpPage()
{
    iShowBMP(0,0,"snakes and ladders bg.bmp");

    iShowBMP2(screenWidth/2 - 400,screenHeight - 150,"buttons\\thisishelppage.bmp",16777215);

    iShowBMP2(back_button.left,back_button.bottom,"buttons\\back.bmp",16777215);



    iShowBMP(screenWidth/2-710,50,"buttons\\helpdetails.bmp");

}

// credits page

void showCreditsPage()
{
    iShowBMP(0,0,"snakes and ladders bg.bmp");

    iShowBMP2(back_button.left,back_button.bottom,"buttons\\back.bmp",16777215);

    iShowBMP2(screenWidth/2 - 150,screenHeight - 120,"buttons\\creditsheader.bmp",16777215);


    iShowBMP2(300,50,"buttons\\courtesy.bmp",16777215);
    iShowBMP2(300,500,"buttons\\madeby.bmp",16777215);

    iShowBMP(screenWidth - 250,700,"buttons\\me.bmp");

}

// options menu
void showOptionPage()
{
    iShowBMP(0,0,"snakes and ladders bg.bmp");

    if(musicOn)
        iShowBMP2(sound_button.left,sound_button.bottom,"buttons\\soundon.bmp",16777215);
    else
        iShowBMP2(sound_button.left,sound_button.bottom,"buttons\\soundoff.bmp",16777215);

    iShowBMP2(back_button.left,back_button.bottom,"buttons\\back.bmp",16777215);


}

/// dice related

void diceAnimator()
{
    iSetColor(0,0,255);
    iFilledRectangle(die.left-10,die.bottom-10,95,95);

    iShowBMP(die.left,die.bottom,diceAnimation[die.idx]);
}

void rollingSoundPlayer()
{
    ///
    if(diceRollingMusicOn && musicOn)
        PlaySound("sounds\\rolldice3s.wav", NULL, SND_ASYNC);
}

void rollDice()
{
    //if(die.rolldice)
    {
        srand(time(NULL));

        diceRollingMusicOn = true;
        rollingSoundPlayer();

        die.topSide = rand() % 6 + 1;
        die.rolling = true;
    }

}

void diceRollingAnim()
{

    if(die.rolling)
    {
        iResumeTimer(1);


        die.idx = die.idx+1;
        c++;
        if(die.idx > 4)
        {
            die.idx = 0;
        }

        if(c >= 15)
        {
            iPauseTimer(1);
            rollingdone = true;
            die.rolling = false;
            die.rolldice = false;
            c=0;

            rollingdone = true;

        }
    }

}

void showDice()
{
    iSetColor(0,0,255);
    iFilledRectangle(die.left-10,die.bottom-10,95,95);
    iShowBMP(die.left,die.bottom,diceSides[die.topSide-1]);
}


/// players

void showPlayers()
{
    iShowBMP2(players[0].x,players[0].y,"Players\\red3d.bmp",16777215);
    iShowBMP2(players[1].x,players[1].y,"Players\\blue3d.bmp",16777215);
    iShowBMP2(players[2].x,players[2].y,"Players\\green3d.bmp",16777215);
    iShowBMP2(players[3].x,players[3].y,"Players\\yellow3d.bmp",16777215);

}



/// snakes

void snake_deifinition()
{
    snakes_all[0].posX = 660+70-100;
    snakes_all[0].posY = 320-40+120-100;
    snakes_all[0].head = 52;
    snakes_all[0].tail = 29;

    snakes_all[1].posX = 500-45;
    snakes_all[1].posY = 360+60;
    snakes_all[1].head = 93;
    snakes_all[1].tail = 46;

    snakes_all[2].posX = 500-45-170;
    snakes_all[2].posY = 360+60-200;
    snakes_all[2].head = 83;
    snakes_all[2].tail = 15;

    snakes_all[3].posX = 500-45+5;
    snakes_all[3].posY = 360+60-265;
    snakes_all[3].head = 28;
    snakes_all[3].tail = 6;

    snakes_all[4].posX = 500-45+5+20-120;
    snakes_all[4].posY = 360+60-265-10+120;
    snakes_all[4].head = 64;
    snakes_all[4].tail = 27;

    snakes_all[5].posX = 500-45+5+30-60*2;
    snakes_all[5].posY = 360+95-125+120;
    snakes_all[5].head = 73;
    snakes_all[5].tail = 56;

    snakes_all[6].posX = 500-45-30+5+10-60*4+30;
    snakes_all[6].posY = 360+95-150-120-10+60;
    snakes_all[6].head = 37;
    snakes_all[6].tail = 16;

    snakes_all[7].posX = 500-45-40+5+10-120-60;
    snakes_all[7].posY = 360+200-100-240+20;
    snakes_all[7].head = 45;
    snakes_all[7].tail = 15;

    snakes_all[8].posX = 500-45-40-300;
    snakes_all[8].posY = 360+200-100-120+10;
    snakes_all[8].head = 97;
    snakes_all[8].tail = 40;



}

void showSnakes()
{
    iShowBMP2(snakes_all[0].posX,snakes_all[0].posY,"snakes\\snake1_1.bmp",0);
    iShowBMP2(snakes_all[1].posX,snakes_all[1].posY,"snakes\\snake2_1.bmp",0);//16777215
    iShowBMP2(snakes_all[2].posX,snakes_all[2].posY,"snakes\\snake2_3.bmp",0);//16777215
    iShowBMP2(snakes_all[3].posX,snakes_all[3].posY,"snakes\\snake2_4.bmp",0);//16777215
    iShowBMP2(snakes_all[4].posX,snakes_all[4].posY,"snakes\\snake3_temp.bmp",0);//16777215
    iShowBMP2(snakes_all[5].posX,snakes_all[5].posY,"snakes\\snake3_2.bmp",0);//16777215
    iShowBMP2(snakes_all[7].posX,snakes_all[7].posY,"snakes\\snake4_3.bmp",0);//16777215
    iShowBMP2(snakes_all[8].posX,snakes_all[8].posY,"snakes\\snake3_3.bmp",0);//16777215
    iShowBMP2(snakes_all[6].posX,snakes_all[6].posY,"snakes\\snake4_2.bmp",0);//16777215

}

/// ladders

void ladder_definition()
{
    ladders_all[0].posX = 200;
    ladders_all[0].posY = 220;
    ladders_all[0].head = 19;
    ladders_all[0].tail = 42;

    ladders_all[1].posX = 570;
    ladders_all[1].posY = 520;
    ladders_all[1].head = 68;
    ladders_all[1].tail = 91;

    ladders_all[2].posX = 380+15-120;
    ladders_all[2].posY = 400+10;
    ladders_all[2].head = 44;
    ladders_all[2].tail = 63;

    ladders_all[3].posX = 430+235;
    ladders_all[3].posY = 215;
    ladders_all[3].head = 11;
    ladders_all[3].tail = 30;

    ladders_all[4].posX = 430+235-275;
    ladders_all[4].posY = 215-60+5;
    ladders_all[4].head = 05;
    ladders_all[4].tail = 25;

    ladders_all[5].posX = 430+235-240-120;
    ladders_all[5].posY = 215+360+10;
    ladders_all[5].head = 77;
    ladders_all[5].tail = 96;

    ladders_all[6].posX = 430+235-240-300+30;
    ladders_all[6].posY = 215+360+10-70;
    ladders_all[6].head = 61;
    ladders_all[6].tail = 79;

    ladders_all[7].posX = 380+15+30+5;
    ladders_all[7].posY = 400+10+60-10;
    ladders_all[7].head = 54;
    ladders_all[7].tail = 75;

    ladders_all[8].posX = 545;
    ladders_all[8].posY = 335;
    ladders_all[8].head = 33;
    ladders_all[8].tail = 48;



}

void showLadders()
{
    iShowBMP2(ladders_all[0].posX,ladders_all[0].posY,"ladders\\ladder1.bmp",0);
    iShowBMP2(ladders_all[1].posX,ladders_all[1].posY,"ladders\\ladder2.bmp",0);
    iShowBMP2(ladders_all[2].posX,ladders_all[2].posY,"ladders\\ladder3.bmp",0);
    iShowBMP2(ladders_all[3].posX,ladders_all[3].posY,"ladders\\ladder4.bmp",0);
    iShowBMP2(ladders_all[4].posX,ladders_all[4].posY,"ladders\\ladder5.bmp",16777215);
    iShowBMP2(ladders_all[5].posX,ladders_all[5].posY,"ladders\\ladder6.bmp",16777215);
    iShowBMP2(ladders_all[6].posX,ladders_all[6].posY,"ladders\\ladder4.bmp",0);
    iShowBMP2(ladders_all[7].posX,ladders_all[7].posY,"ladders\\ladder7.bmp",0);
    iShowBMP2(ladders_all[8].posX,ladders_all[8].posY,"ladders\\ladder8.bmp",0);

    iShowBMP2(130,685,"digits\\winner.bmp",16777215);
}

void initializeALL()
{
    int i;

    die.left = 850;
    die.bottom = 400;
    die.rolling = false;
    die.idx = 0;
    die.topSide = 6;

    /// players
    for(i = 0; i < numberOfPlayers; i++)
    {
        players[i].cellNo = 0;
        players[i].moving = false;
        players[i].no = i + 1;
        players[i].turn = false;
        players[i].willMove = 0;
        players[i].x = 50*i;
        players[i].y = 50;
        players[i].free = false;
        players[i].haveToMove = 100 - players[i].cellNo;
        players[i].winner = false;
        players[i].previousTurn = 0;

    }

    players[0].turn = true;
    //players[0].x -= 30;


    // buttons

    new_game.height = 100;
    new_game.length = 400;
    new_game.bottom = 450;
    new_game.left = 10;

    options.height = 100;
    options.length = 400;
    options.bottom = 350;
    options.left = 10;

    help.height = 100;
    help.length = 400;
    help.bottom = 250;
    help.left = 10;

    credits.height = 100;
    credits.length = 400;
    credits.bottom = 150;
    credits.left = 10;

    quit.height = 100;
    quit.length = 400;
    quit.bottom = 50;
    quit.left = 10;

    b2menu.height = 100;
    b2menu.length = 400;
    b2menu.bottom = screenHeight/2 - b2menu.height;
    b2menu.left = screenWidth/2 - b2menu.length/2;

    resume.height = 100;
    resume.length = 400;
    resume.bottom = screenHeight/2 + 50;
    resume.left = screenWidth/2 - resume.length/2;

    back_button.height = 150;
    back_button.length = 150;
    back_button.bottom = screenHeight - 200;
    back_button.left = 100;


    sound_button.height = 200;
    sound_button.length = 200;
    sound_button.bottom = screenHeight/2 - 100;
    sound_button.left = screenWidth/2 - 100;

    dice_button.height = 75;
    dice_button.length = 75;
    dice_button.bottom = die.bottom;
    dice_button.left = die.left;

    pause.height = 250;
    pause.length = 170;
    pause.bottom = screenHeight - 300;
    pause.left = screenWidth - 220;

    gameWindowSound.height = 200;
    gameWindowSound.length = 200;
    gameWindowSound.bottom = 100;
    gameWindowSound.left = screenWidth - 300;




    finishCOunter = 0;
    oneWinnerFound = false;
    runningPlayerno = 1;
    winnerno = 100;

}



void playGame()
{
    int i,n;
    char p1[] = "Player 1",p2[] = "Player 2",p3[] = "Player 3",p4[] = "Player 4";
    for(i = 0; i < numberOfPlayers; i++)
    {
        if(players[i].turn == true)
        {
            n = i;
            break;

        }
    }

    iSetColor(250,250,0);

    if(n == 0)
        iText(800,520,p1);
    else if(n == 1)
        iText(800,520,p2);
    else if(n == 2)
        iText(800,520,p3);
    else if(n == 3)
        iText(800,520,p4);


    //iText(800,520,p[n]);
    iSetColor(220,10,250);

    iText(800,500,"Press SPACE BAR to roll the dice");
    iSetColor(250,10,220);
    iText(1070,500,"or Click the DICE with the cursor");


}

void snake_ladder_checker()
{
    int i,j;

    for(i = 0; i < numberOfPlayers; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(players[i].cellNo == ladders_all[j].head)
            {
                players[i].cellNo = ladders_all[j].tail;
                players[i].haveToMove = 100 - players[i].cellNo;

                if(musicOn && gameWindow && !MenuPage)
                {
                    PlaySound(0,0,0);
                    PlaySound("sounds\\laddersound_new.wav", NULL, SND_ASYNC);
                }
            }

        }
    }

    for(i = 0; i < numberOfPlayers; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(players[i].cellNo == snakes_all[j].head)
            {
                players[i].cellNo = snakes_all[j].tail;
                players[i].haveToMove = 100 - players[i].cellNo;
                if(musicOn && gameWindow && !MenuPage)
                {
                    PlaySound(0,0,0);
                    PlaySound("sounds\\snakehiss3s.wav", NULL, SND_ASYNC);
                }
            }


        }
    }

}

void posUpdater()
{
    int i,j;



    for(i = 0; i < numberOfPlayers; i++)
    {
        if(players[i].cellNo == 0)
        {
            players[i].x = 150-20*i;
            players[i].y = 80;

        }
        else
        {
            players[i].x = mazeCells[players[i].cellNo - 1].x;
            players[i].y = mazeCells[players[i].cellNo - 1].y;

        }
    }


}


void gameMains()
{

    int current_player = runningPlayerno - 1, next_player = runningPlayerno;
    if(rollingdone)
    {

        if(players[current_player].turn)
        {
            players[current_player].previousTurn = players[current_player].willMove;
            players[current_player].willMove = die.topSide;

            if(players[current_player].free) // if free to move
            {
                if(players[current_player].willMove <= players[current_player].haveToMove)
                {
                    players[current_player].cellNo += players[current_player].willMove;
                    players[current_player].haveToMove = 100 - players[current_player].cellNo;

                    players[current_player].moving = false;
                }
                else
                {
                    if(players[current_player].previousTurn == 1)// if last time scored 1 and progressed
                    {
                        players[current_player].cellNo -= players[current_player].previousTurn;
                        players[current_player].haveToMove = 100 - players[current_player].cellNo;
                        //players[current_player].previousTurn = 0;
                    }

                    players[current_player].moving = false;
                }
            }
            else    // is not free still
            {
                if(players[current_player].willMove == 1)
                {
                    players[current_player].free = true;

                    players[current_player].cellNo += players[current_player].willMove;
                    players[current_player].haveToMove = 100 - players[current_player].cellNo;
                    players[current_player].previousTurn = players[current_player].willMove;
                    players[current_player].moving = false;


                }
            }


            rollingdone = false;

            if(players[current_player].willMove != 1)
            {
                players[current_player].turn = false;

                runningPlayerno++;
                if(runningPlayerno > 4)
                    runningPlayerno = 1;

                players[next_player].turn = true;
            }

        }
    }
    if(!players[current_player].free && players[current_player].winner)
    {
        players[current_player].cellNo = 100;

        runningPlayerno++;
        if(runningPlayerno > 4)
            runningPlayerno = 1;

        players[next_player].turn = true;

    }

    rollingdone = false;

}

void hudai()
{
    players[0].cellNo++;
    if(players[0].cellNo > 100)
        players[0].cellNo = 1;
}

//the func below is called by posUpdater() at the end
void whoseTurn()
{
    if(runningPlayerno == 1 && !players[0].winner)
    {
        players[0].turn = true;

    }
    else
    {
        players[0].turn = false;

//        if(players[0].winner)
//        {
//            runningPlayerno++;
//            if(runningPlayerno > 4)
//                runningPlayerno = 1;
//        }

    }

    if(runningPlayerno == 2 && !players[1].winner)
    {
        players[1].turn = true;

    }
    else
    {
        players[1].turn = false;

//        if(players[1].winner)
//        {
//            runningPlayerno++;
//            if(runningPlayerno > 4)
//                runningPlayerno = 1;
//        }

    }

    if(runningPlayerno == 3 && !players[2].winner)
    {
        players[2].turn = true;

    }
    else
    {
        players[2].turn = false;

//        if(players[2].winner)
//        {
//            runningPlayerno++;
//            if(runningPlayerno > 4)
//                runningPlayerno = 1;
//        }

    }

    if(runningPlayerno == 4 && !players[3].winner)
    {
        players[3].turn = true;

    }
    else
    {
        players[3].turn = false;

//        if(players[3].winner)
//        {
//            runningPlayerno++;
//            if(runningPlayerno > 4)
//                runningPlayerno = 1;
//        }

    }
//
//    if(runningPlayerno == 2 && !players[1].winner)
//        players[1].turn = true;
//    else
//        players[1].turn = false;
//
//    if(runningPlayerno == 3 && !players[2].winner)
//        players[2].turn = true;
//    else
//        players[2].turn = false;
//
//    if(runningPlayerno == 4 && !players[3].winner)
//        players[3].turn = true;
//    else
//        players[3].turn = false;

}

void winChecker()
{
    int i;

    for(i = 0; i < 4; i++)
    {
        if(players[i].haveToMove == 0 || players[i].cellNo == 100)
        {
            players[i].winner = true;
            players[i].free = false;
            finishCOunter++;
        }
    }

    if(finishCOunter == 4)
    {
        ;
    }

}

void gameStarter()
{

    startingWindow = false;
    MenuPage = true;
    if(musicOn)
        PlaySound("sounds\\menubgmusic.wav", NULL, SND_ASYNC | SND_LOOP);

    //gameWindow = true;

    iPauseTimer(5);
}

int main()
{
    int gameLoadingTime_ms = 3000;

    initializeALL();

    if(startingWindow && musicOn)
    {
        PlaySound("sounds\\intro.wav", NULL, SND_ASYNC);
    }
    //place your own initialization codes here.
    iSetTimer(200,diceRollingAnim); // timer no 0
    iSetTimer(30,snake_ladder_checker);
    iSetTimer(200,posUpdater);
    iSetTimer(1000,gameMains);
    iSetTimer(4000,whoseTurn);
    iSetTimer(gameLoadingTime_ms,gameStarter); // timer no 5
    iSetTimer(30,winChecker);

    iInitialize(screenWidth, screenHeight, "Demo!");


    return 0;
}
