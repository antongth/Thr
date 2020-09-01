#include"cl.h"
class PLAYER {

public:

int m;
float dx,dy;
bool onGround;
sf::FloatRect rect;
sf::RectangleShape rectangleP;

PLAYER()
{
	rectangleP.setFillColor(sf::Color(255,104,0));
	//rectangleP.setPosition(50,WINDOW_Y-GRN-CELL);
	rectangleP.setSize(sf::Vector2f(CELL,CELL));
	rect=FloatRect(50,WINDOW_Y-GRN-CELL,CELL,CELL);
	dx=dy=0;
	m=2;
	onGround=false;
}

void update(float time)
{
	rect.left+=dx*time;
	//if (rect.top < WINDOW_Y-GRN-CELL) 
	//{
	//	onGround=false;
	//}
	onGround=false;
	if (!onGround) 
	{
		dy+=Ac*time;
	}
	rect.top+=dy*time;
	if (rect.top > WINDOW_Y-GRN-CELL) 
	{
		//cout<<dy<<" "<<m*dy<<endl;
		if (m*dy>=3) rectangleP.setFillColor(sf::Color(100,100,100));
		rect.top=WINDOW_Y-GRN-CELL; dy=0; onGround=true;
	}
	if (rect.left>WINDOW_X-CELL) 
		rect.left=WINDOW_X-CELL;
	if (rect.left<0) 
		rect.left=0;
	rectangleP.setPosition(rect.left,rect.top);
	dx=0;
	
}

};

class IT {

public:

int m;
float dx,dy;
bool onGround;
sf::FloatRect rect;
sf::RectangleShape rectangleP;

IT() 
{
	rectangleP.setFillColor(sf::Color(255,144,10));
	//rectangleP.setPosition(rand()%(WINDOW_X-200)+200,WINDOW_Y-GRN-CELL*4);
	rectangleP.setSize(sf::Vector2f(CELL*3,CELL*4));
	rect=FloatRect(rand()%(WINDOW_X-200)+200,WINDOW_Y-GRN-CELL*4,CELL*3,CELL*4);
	dx=dy=0;
	m=10;
	onGround=false;
	
}

void update(float time)
{
	rect.left+=dx*time;
	//if (rect.top < WINDOW_Y-GRN-CELL*4) 
	//{
	//	onGround=false;
	//}
	if (!onGround) 
	{
		dy+=Ac*time;
	}
	rect.top+=dy*time;
	if (rect.top > WINDOW_Y-GRN-CELL*4) 
	{
		cout<<dy<<" "<<m*dy<<endl;
		if (m*dy>=4) rectangleP.setFillColor(sf::Color(100,100,100));
		rect.top=WINDOW_Y-GRN-CELL*4; dy=0; onGround=true;
	}
	rectangleP.setPosition(rect.left,rect.top);
	
	
	dx=0;
}
};

class Drop {

public:

float dy;
sf::RectangleShape line;

Drop(){
	line.setFillColor(sf::Color(0,83,138));
	line.setSize(sf::Vector2f(1,rand()%3+4));
	line.setPosition(rand()%WINDOW_X, -(rand()%WINDOW_Y+1));
	dy=(float)(rand()%10+21)/100;
}

void update(float time){
	dy+=Ac*time/100;
	line.move(0,dy*time);
	if (line.getPosition().y>=WINDOW_Y-GRN-line.getSize().y) {
		line.setPosition(rand()%WINDOW_X, -(rand()%WINDOW_Y+1));
		dy=(float)(rand()%10+21)/100;
	}
}

};
