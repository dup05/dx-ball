#include<SFML/Graphics.hpp>
#include<time.h>
#include<stdlib.h>
using namespace sf;

bool isCollide(Sprite s1,Sprite s2)
{	
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}
int main()
{
	srand(time(0)); 
	RenderWindow app(VideoMode(520,450),"DX-BALL");
	app.setFramerateLimit(60);

	Texture t1,t2,t3,t4,t5;

	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");
	t5.loadFromFile("images/gameover.png");

	Sprite sBackground(t2), sBall(t3), sPaddle(t4),gameover(t5);
	sPaddle.setPosition(300,440);
	sBall.setPosition(330,430);
	gameover.setPosition(100,100);
	Sprite block[1000];
	
	int n=0;

	for(int i=1;i<=10;i++)
	for(int j=1;j<=10;j++)
	{
		block[n].setTexture(t1);
		block[n].setPosition(i*43,j*20);
		n++;
	}	
	app.clear();
		app.draw(sBall);
		app.draw(sPaddle);
		for(int i=0;i<n;i++)
			app.draw(block[i]);
		app.display();
		
	float dx=3,dy=3,x=300,y=300;
	int flag=1,start=0;
	while(app.isOpen())
	{
		
		Event e;
		while(app.pollEvent(e))
		{
			if(e.type==Event::Closed)
				app.close();
		}
		

		while(!start)
		{
			if(Keyboard::isKeyPressed(Keyboard::Right))
				start=1;
		}
		
		sBall.move(dx,0);
		for(int i=0;i<n;i++)
			if(isCollide(sBall,block[i]))
			{
				block[i].setPosition(-100,0);
					dx=-dx;
			}
	
		sBall.move(0,dy);
		for(int i=0;i<n;i++)
			if(isCollide(sBall,block[i]))
			{
				block[i].setPosition(-100,0);
					dy=-dy;
			}
		
		
		Vector2f b=sBall.getPosition();

		if(b.y>450)
		{
			flag=0;
		}
		if(b.x<0||b.x>520)
			dx=-dx;
		if(b.y<0||b.y>450)
			dy=-dy;
		

		if(Keyboard::isKeyPressed(Keyboard::Right))
			sPaddle.move(7,0);
		if(Keyboard::isKeyPressed(Keyboard::Left))
			sPaddle.move(-7,0);

		if(isCollide(sPaddle,sBall)) dy=-(rand()%5+3);

		app.clear();
		app.draw(sBall);
		app.draw(sPaddle);
		

		for(int i=0;i<n;i++)
			app.draw(block[i]);
		
		if(flag==0)
		{
			app.clear();
			app.draw(gameover);
		}
		app.display();
		
	}
	

}
