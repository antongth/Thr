#include<iostream>
#include<cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define TITLE "Thr"
#define WINDOW_X 700
#define WINDOW_Y 500
#define CELL 10
#define MAP_Y WINDOW_Y/CELL
#define MAP_X WINDOW_X/CELL
#define FPS 30
#define GRN 50
#define Ac 0.0008
#define PLANET_R 10e+7

using namespace sf;
using namespace std;

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

void fall(int a, int v, float t){

float x,y;
x = (v*cos(a))*t;
y= (v*sin(a))*t-1/2*Ac*pow(t,2);
}

void earth(sf::RenderWindow *window){

float h;
h=CELL*PLANET_R-sqrt(CELL*PLANET_R*CELL*PLANET_R-WINDOW_X*WINDOW_X/4);
cout<<h<<endl;
sf::CircleShape circle;
circle.setRadius(CELL*PLANET_R);
circle.setOutlineColor(sf::Color::Red);
circle.setOutlineThickness(5);
circle.setPosition(WINDOW_X/2, h);
window->draw(circle);

}

int main()
{
//cout<<__STDC__<<endl;
//Окно
sf::RenderWindow window(sf::VideoMode(WINDOW_X,WINDOW_Y), TITLE, sf::Style::Titlebar | sf::Style::Close);
window.setFramerateLimit(FPS);
earth(window);

//Земля
sf::RectangleShape rectangle;
rectangle.setFillColor(sf::Color(143,254,9));
rectangle.setPosition(0,WINDOW_Y-GRN);
rectangle.setSize(sf::Vector2f(WINDOW_X,GRN));

//Время
Clock clock;

//Классы
PLAYER pl;
IT it,it2;
Drop drs[500];
//Drop *drs = new Drop [10];
pl.rect.top=200;
it.rect.top=200;
it2.rect.top=350;
//int *drss = new int [10];
for (int i = 0; i<500; i++){
	Drop dr;
	drs[i] = (Drop) dr;
}
//cout<<sizeof(drs)/sizeof(drs[0])<<endl;

//Звук
SoundBuffer buffer;
buffer.loadFromFile("fire.ogg");
Sound sound(buffer);
sound.setVolume(20);

//Музыка
Music music;
music.openFromFile("ddlc.ogg");
music.play();
music.setVolume(30);

//Осн луп программы
while (window.isOpen()) 
{ 
	sf::Event event; 
	
	//время, как работает?
	float time = clock.getElapsedTime().asMilliseconds();
	clock.restart();
	
	//time = time;  // Скорость игры
	//if (time > 20) time = 20;
	
	//правильные коорд мыши
	float X= (int)sf::Mouse::getPosition(window).x;
	float Y= (int)sf::Mouse::getPosition(window).y;
	
	while (window.pollEvent(event)) 
	{ 
		if (event.type == sf::Event::Closed) window.close();
		
		//cout<<(float&)rectangle.getPosition().x<<endl;
		//rectangle.setPosition(rectangle.getPosition().x+X,rectangle.getPosition().y+Y);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Middle)
			{			
				if (music.getStatus()==2) music.pause();
				else music.play();
			}
		};
	}; 
	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
	//if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	//{  
	//}; 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		//p.setPosition(p.getPosition().x+1,p.getPosition().y+0);
		//p.move(0.1*time,0);
		pl.dx+=0.2;
	};
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		pl.dx+=-0.2;
	};
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
		if (pl.onGround) 
		{
			pl.dy=-0.4; 
			pl.onGround=false;
			sound.play();
		}
		
	};
	
	if (pl.rect.intersects(it.rect)&&(pl.dy>0)) 
	{
		pl.dy=-0.6;
		//pl.rect.top=it.rect.top-CELL;
		pl.onGround=false;
	}

	pl.update(time);
	it.update(time);
	it2.update(time);
	
	if (pl.rect.intersects(it2.rect)&&(pl.dy>0)) 
	{
		pl.rect.top=it2.rectangleP.getPosition().y-CELL;
		pl.onGround=true;
		pl.dy=0;
	}
	
	
	
	for (int i = 0; i<500; i++){
		drs[i].update(time);
	}
	
	window.clear(Color(107,140,255));
	
	window.draw(rectangle);
	for (int i = 0; i<500; i++){
		window.draw(drs[i].line);
	}
	window.draw(it.rectangleP);
	window.draw(it2.rectangleP);
	window.draw(pl.rectangleP);
	window.display();
	
};
return 0;
}

