#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix2.h>
#include <Matrix3.h>
#include <Matrix4.h>
#include <iostream>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_audio = new aie::Audio("./audio/powerup.wav");
	/// Screen Border
	//Min
	m_screen_min_borderX = 40;
	m_screen_min_borderY = 40;
	//Max
	m_screen_max_borderX = 1240;
	m_screen_max_borderY = 680;

	///Asserts
	//Box
	m_BoxTexture = new aie::Texture("./textures/tankBeige.png");//Box
	m_BoxW = 75; m_BoxH = 70; //Width and Height
	m_BoxX = 500; m_BoxY = 500; m_BoxR = 0; //XY and Rotation
	
	///Tank-Start
	//+Tank Graphics - Start
	m_tankBATexture = new aie::Texture("./textures/barrelGreen.png"); //Body
	m_tankW = 75; m_tankH = 70; //Width and Height
	m_tankTexture = new aie::Texture("./textures/tankGreen.png"); //Barrel
	m_tankBoxerTexture = new aie::Texture("./textures/rock_small.png"); //Boxing Glove
	
	//Tank
	m_tankX = 500;		//X
	m_tankY = 200;		//Y
	m_tankspeed = 2.0f; //Speed
	m_tankR = 0;        //Rotation
	
	//Barrel
	m_tankBarrelX = 0;  //X
	m_tankBarrelY = 0; //Y 40
	m_tankBarrelR = 0;  //Rotation

	//Boxing Glove
	m_tankBoxerX = 0;  //X
	m_tankBoxerY = m_tankBarrelY + 70; //Y
	m_tankBoxerR = 0;  //Rotation
	///Tank-End
	
	Debug_Mode = false;
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_font;
	
	delete m_tankBATexture;
	delete m_tankTexture;

	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	//###Box###
	Matrix3<float> Box_translation;
	Matrix3<float> Box_roatation;
	Box_translation.m31 = m_BoxX;
	Box_translation.m32 = m_BoxY;
	Box_roatation.setRotateZ(m_BoxR);
	m_BoxMatrix = Box_translation * Box_roatation;
	
	//###TANK###
	Matrix3<float> translation;
	Matrix3<float> roatation;
	translation.m31 = m_tankX;
	translation.m32 = m_tankY;
	
	roatation.setRotateZ(m_tankR);
	m_tankMatrix = translation * roatation;
	
	//##Barrel##
	Matrix3<float> translation_barrel;
	Matrix3<float> roatation_barrel;
	Matrix3<float> child;
	translation_barrel.m31 = m_tankBarrelX;
	translation_barrel.m32 = m_tankBarrelY;

	child = translation_barrel;// *roatation_barrel;
	child.setRotateZ(m_tankBarrelR);

	m_tankBMatrix = m_tankMatrix * child;

	//##Boxing Glove##
	Matrix3<float> translation_boxer;
	Matrix3<float> roatation_boxer;
	Matrix3<float> child_of_child;
	translation_boxer.m31 = m_tankBoxerX;
	translation_boxer.m32 = m_tankBoxerY;
	
	child_of_child = translation_boxer;
	child_of_child.setRotateZ(m_tankBoxerR);

	m_tankBoxerMatrix = m_tankMatrix * child * child_of_child;
	
	m_timer += deltaTime;

	/*Collision-Start*/
	///Boarder
	//Tank
	if (m_tankX <= m_screen_min_borderX) { m_tankX = m_screen_min_borderX; } if (m_tankY <= m_screen_min_borderY) { m_tankY = m_screen_min_borderY; } //X
	if (m_tankX >= m_screen_max_borderX) { m_tankX = m_screen_max_borderX; } if (m_tankY >= m_screen_max_borderY) { m_tankY = m_screen_max_borderY; } //Y
	//Box - Didn't finish due to Time
	//if (m_BoxX >= m_screen_min_borderX ) { m_BoxX = m_screen_min_borderX; } if (m_BoxY <= m_screen_min_borderY) { m_BoxY = m_screen_min_borderY; } //X
	//if (m_BoxX >= m_screen_max_borderX) { m_BoxX = m_screen_max_borderX; } if (m_BoxY >= m_screen_max_borderY) { m_BoxY = m_screen_max_borderY; } //Y
	///Tank on Box  - Didn't finish due to Time
	//if (m_tankW < m_BoxW) { m_tankX = m_BoxX - 1; } 
	//if ((m_tankH < m_BoxH) { m_tankY = m_BoxY - 1; }
	/*Collision-End*/

	/*
	--------Controls------------
	Forwards	=	NUM8
	Backwards	=	NUM5
	Rotate		=	NUM 4 or 6
	Barrel		=	Num 7 or 9
	Debug		=	~
	Exit		=	Escape
	----------------------------
	*/
	//Tank Controls ###############################################	
	aie::Input* input = aie::Input::getInstance(); // initzlier
	//Fowards and Backwards
	if (input->isKeyDown(aie::INPUT_KEY_KP_8)) //Forward
	{
		m_tankY += roatation.m11 * m_tankspeed;
		m_tankX -= roatation.m12 * m_tankspeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_KP_5)) //Backward
	{
		m_tankY -= roatation.m11 * m_tankspeed;
		m_tankX += roatation.m12 * m_tankspeed;
	}

	//Rotation
	if (input->isKeyDown(aie::INPUT_KEY_KP_4)) //Rotate Left
	{
		m_tankR -= 0.1f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_KP_6)) //Rotate Right
	{
		m_tankR += 0.1f;
	}
	//Barrel Controls #############################################	
	if (input->isKeyDown(aie::INPUT_KEY_KP_7)) //Rotate Left
	{
		m_tankBarrelR -= 0.2f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_KP_9)) //Rotate Right
	{
		m_tankBarrelR += 0.2f;
	}
	/*Fire #############################################	
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) 
	{
		if (m_tankBoxerY <= m_tankY + 0.5f)
		{
			m_tankBarrelY += 5.0f;
			m_tankBarrelX -= roatation_barrel.m11;
				//roatation.m11
				//roatation.m12
			//m_tankBarrelX -= roatation_barrel.m12 + 5.0f;
			m_tankBoxerY += 10;
			m_tankBoxerX += 10;
		}
	}
	else
		if (m_tankBarrelY != 0)
		{
			m_tankBarrelY += 5.0f;
			m_tankBarrelX -= roatation_barrel.m12;
			//m_tankBarrelX += roatation_barrel.m12 + 5.0f;
			m_tankBoxerY -= 10;
		}
	*/ 
	//Other #######################################################		
	if (input->wasKeyPressed(aie::INPUT_KEY_GRAVE_ACCENT)) //Debug
	{
		if (Debug_Mode == true)
		{
			Debug_Mode = false;
		}
		else
		{
			Debug_Mode = true;
		}
	}

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE)) // exit the application
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();
	
	//###Box###  - Didn't finish due to Time
	//m_2dRenderer->drawSpriteTransformed3x3(m_BoxTexture, m_BoxMatrix.m);

	//###Tank###
	m_2dRenderer->drawSpriteTransformed3x3(m_tankTexture, m_tankMatrix.m); //Tank
	m_2dRenderer->drawSpriteTransformed3x3(m_tankBATexture, m_tankBMatrix.m); //Barrel
	m_2dRenderer->drawSpriteTransformed3x3(m_tankBoxerTexture, m_tankBoxerMatrix.m); //Boxer

	// Debug Info
	if (Debug_Mode == true)
	{
		char fps[32];
		char TankX[32];
		char TankY[32];
		char TankZ[32];
		sprintf_s(fps, 32, "FPS: %i", getFPS());
		sprintf_s(TankX, 32, "X: %f", m_tankMatrix.m31);
		sprintf_s(TankY, 32, "Y: %f", m_tankMatrix.m32);
		sprintf_s(TankZ, 32, "Z: %f", m_tankMatrix.m33);
		m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
		m_2dRenderer->drawText(m_font, TankX, 0, 720 - 64); //Debug X of Tank
		m_2dRenderer->drawText(m_font, TankY, 0, 720 - 96); //Debug Y of Tank
		m_2dRenderer->drawText(m_font, TankZ, 0, 720 - 128); //Debug Z of Tank
	}
	// done drawing sprites
	m_2dRenderer->end();

}