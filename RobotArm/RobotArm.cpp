// RobotArm.cpp
// Author: Sebastian Horoszkiewicz
// Graphics Assesment - Robot Arm
// Debugged and Tested with Visual Studio 2012

#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#include <time.h> 
#include <ctime>
#include <iomanip>
#include <math.h> 
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
int main() {
	const int size=4;
	const int noOfElements=5;
	int popBallon[5]={0,0,0,0,0};
	int i=0;
	float moveSpeed = 3.f, roateAngleRight=5.f, roateAngleLeft=-5.f;
	float rotation[4]={0.f,0.f,0.f,0.f};
	float ballonRad=20.f;
	
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	window.setFramerateLimit(60);
	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
 
	//get Textures
	sf::Texture bcg;
	if (!bcg.loadFromFile("background.png")){}
	sf::Texture body;
	if (!body.loadFromFile("body.png")){}
	sf::Texture mainArm;
	if (!mainArm.loadFromFile("mainArm.png")){}
	sf::Texture secondArm;
	if (!secondArm.loadFromFile("secondArm.png")){}
	sf::Texture clause;
	if (!clause.loadFromFile("clause.png")){}
	//Create sprite for background
	sf::Sprite bcgImg;
	bcgImg.setTexture(bcg);
	//Create objects
	//Base
	sf::VertexArray baseLines(sf::Quads, size);
	sf::Vector2f quad[size];
	quad[0] = sf::Vector2f(0  , 0);
	quad[1] = sf::Vector2f(160, 0);
	quad[2] = sf::Vector2f(160, 228);
	quad[3] = sf::Vector2f(0  , 228);
	baseLines[0].texCoords = sf::Vector2f(0  , 0);
	baseLines[1].texCoords = sf::Vector2f(160, 0);
	baseLines[2].texCoords = sf::Vector2f(160, 228);
	baseLines[3].texCoords = sf::Vector2f(0  , 228);
	sf::Vector2f basePos(150.f, 330.f);
	
	//Main (Bottom) Arm
	sf::VertexArray mainArmLines(sf::Quads, size);
	sf::Vector2f points2[size];
	points2[0]=sf::Vector2f(-21,-132);
	points2[1]=sf::Vector2f(100,-132);
	points2[2]=sf::Vector2f(100,20);
	points2[3]=sf::Vector2f(-21,20);
	mainArmLines[0].texCoords = sf::Vector2f(0,0);
	mainArmLines[1].texCoords = sf::Vector2f(121,0);
	mainArmLines[2].texCoords = sf::Vector2f(121,152);
	mainArmLines[3].texCoords = sf::Vector2f(0,152);
	sf::Vector2f mArmPos(70.f, 15.f);
	
	//Second (Top) Arm
	sf::VertexArray secondArmLines(sf::Quads, size);
	sf::Vector2f points3[size];
	points3[0]=sf::Vector2f(0,0);
	points3[1]=sf::Vector2f(113,0);
	points3[2]=sf::Vector2f(113,150);
	points3[3]=sf::Vector2f(0,150);
	secondArmLines[0].texCoords = sf::Vector2f(0, 0);
	secondArmLines[1].texCoords = sf::Vector2f(113, 0);
	secondArmLines[2].texCoords = sf::Vector2f(113, 150);
	secondArmLines[3].texCoords = sf::Vector2f(0, 150);
	sf::Vector2f sArmPos(83.f, -117.f);
	
	//Right Clause
	sf::VertexArray rightFinLines(sf::Quads, size);
	sf::Vector2f points4[size];
	points4[0]=sf::Vector2f(0,0);
	points4[1]=sf::Vector2f(13,0);
	points4[2]=sf::Vector2f(13,38);
	points4[3]=sf::Vector2f(0,38);
	rightFinLines[0].texCoords = sf::Vector2f(0, 0);
	rightFinLines[1].texCoords = sf::Vector2f(13, 0);
	rightFinLines[2].texCoords = sf::Vector2f(13, 38);
	rightFinLines[3].texCoords = sf::Vector2f(0, 38);
	sf::Vector2f rfArmPos(101.f,150.f);
	
	//Left Clause
	sf::VertexArray leftFinLines(sf::Quads, size);
	sf::Vector2f points5[size];
	points5[0]=sf::Vector2f(0,0);
	points5[1]=sf::Vector2f(-13,0);
	points5[2]=sf::Vector2f(-13,38);
	points5[3]=sf::Vector2f(0,38);
	leftFinLines[0].texCoords = sf::Vector2f(0, 0);
	leftFinLines[1].texCoords = sf::Vector2f(13, 0);
	leftFinLines[2].texCoords = sf::Vector2f(13, 38);
	leftFinLines[3].texCoords = sf::Vector2f(0, 38);
	sf::Vector2f lfArmPos(101.f,150.f);
	
	//Initialize ballons
	sf::CircleShape ballon[5];
	sf::Vector2f ballonPos[5];
	ballonPos[0].x=650.f;	ballonPos[0].y=450.f;
	ballonPos[1].x=125.f;	ballonPos[1].y=90.f;
	ballonPos[2].x=340.f;	ballonPos[2].y=150.f;
	ballonPos[3].x=600.f;	ballonPos[3].y=250.f;
	ballonPos[4].x=540.f;	ballonPos[4].y=50.f;

	ballon[0].setFillColor(sf::Color::Red);
	ballon[1].setFillColor(sf::Color::Green);
	ballon[2].setFillColor(sf::Color::Blue);
	ballon[3].setFillColor(sf::Color::Magenta);
	ballon[4].setFillColor(sf::Color::Yellow);
	//Set properties for ballons
	for (i=0; i<noOfElements; i++){
		ballon[i].setRadius(ballonRad);
		ballon[i].setOrigin(ballonRad,ballonRad);
		ballon[i].setPosition(ballonPos[i]);
	}
	// Create a text for Timer and Start it
	sf::Text text("", font);
	text.setCharacterSize(30);
	text.setColor(sf::Color::White);
	std::clock_t start;
    start = std::clock();
	int minutes=0,hours=0;
	double seconds;

	// Start game loop
	while (window.isOpen()){
		int poppedBaloons=popBallon[0]+popBallon[1]+popBallon[2]+popBallon[3]+popBallon[4];
		if (poppedBaloons != 5){
			//calculate, time and convert it to string
			seconds = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			hours=(int)seconds/(24*60);	seconds=(int)seconds%(24*60); minutes=(int)seconds/60; seconds=(int)seconds%60; 
			std::string hrs = std::to_string(hours); 
			std::string mins = std::to_string(minutes);
			std::string secs = std::to_string((int)seconds);
			if (seconds<10) secs="0"+secs; if (minutes<10) mins="0"+mins; if (hours<10)	hrs="0"+hrs;
			std::string s = hrs+":"+mins+":"+secs;
			text.setString(s);
		}
		// Process events
		sf::Event Event;
		while (window.pollEvent(Event)){
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				window.close();
			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right)){
				if (basePos.x<500)//stop base from moving over 500 (so it will look good with background image)
					basePos.x+=moveSpeed;
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left)){
				basePos.x-=moveSpeed;
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up)){
				if (rotation[0] > -139)
					rotation[0]-=moveSpeed;
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down)){
				if (rotation[0] < 81)
					rotation[0]+=moveSpeed;
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
				if (rotation[1] > -246)
					rotation[1]-=moveSpeed;
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::D)){
				if (rotation[1] < 30)
					rotation[1]+=moveSpeed;
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W)){
				if (rotation[2] > -50){
					rotation[2]-=moveSpeed;
					rotation[3]+=moveSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S)){
				if (rotation[2] < 0){
					rotation[2]+=moveSpeed;
					rotation[3]-=moveSpeed;
				}
			}
		}
		//Body transformation
		sf::Transform T;
		T.translate(basePos);
		//main Arm transformation & rotation
		sf::Transform T2;
		T2.translate(mArmPos);
		sf::Transform R2;
		R2.rotate(rotation[0]);
		sf::Transform M2=T*T2*R2;
		//second Arm transformation & rotation
		sf::Transform T3;
		T3.translate(sArmPos);
		sf::Transform R3;
		R3.rotate(rotation[1]);
		sf::Transform M3=M2*T3*R3;
		//right finger transformation & rotation
		sf::Transform T4;
		T4.translate(rfArmPos);
		sf::Transform R4;
		R4.rotate(rotation[2]);
		sf::Transform M4=M3*T4*R4;
		//left finger transformation & rotation
		sf::Transform T5;
		T5.translate(lfArmPos);
		sf::Transform R5;
		R5.rotate(rotation[3]);
		sf::Transform M5=M3*T5*R5;
	
		//update baseLines & check for collisions
		for(i=0;i<size;i++) {
			baseLines[i].position=T.transformPoint(quad[i]);
			mainArmLines[i].position=M2.transformPoint(points2[i]);
			secondArmLines[i].position=M3.transformPoint(points3[i]);
			rightFinLines[i].position=M4.transformPoint(points4[i]);
			leftFinLines[i].position=M5.transformPoint(points5[i]);
		
			//check does any of four points of each clause is in the circle, I do that by calculating distance from clause points to ballon origin
			for (int c=0; c<noOfElements; c++) {
				//right finger popping ballons
				float dist = sqrt(pow((ballonPos[c].x-rightFinLines[i].position.x), 2) + pow((ballonPos[c].y-rightFinLines[i].position.y), 2));
				//now check if distance is smaller than ballon radius, and if it is less than radius then set ballon as popped
				if (dist < ballonRad)
					popBallon[c]=1;
				//left finger popping ballons (as above)
				dist = sqrt(pow((ballonPos[c].x-leftFinLines[i].position.x), 2) + pow((ballonPos[c].y-leftFinLines[i].position.y), 2));
				if (dist < ballonRad)
					popBallon[c]=1;
			}
		}
		window.clear();
		//draw frame items
		window.draw(bcgImg);
		window.draw(baseLines, &body);
		window.draw(rightFinLines, &clause);
		window.draw(leftFinLines, &clause);
		window.draw(secondArmLines, &secondArm);
		window.draw(mainArmLines, &mainArm);
		//if ballon is not popped draw it
		for (i=0; i<noOfElements; i++) {
			if (popBallon[i]==0)
				window.draw(ballon[i]);
		}
		window.draw(text);
		// Finally, display rendered frame on screen
		window.display();
	} //loop back for next frame
	return EXIT_SUCCESS;
}