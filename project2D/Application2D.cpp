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
	m_TankRenderer = new aie::Renderer2D();


	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_tankBATexture = new aie::Texture("./textures/barrelGreen.png");
	m_tankTexture = new aie::Texture("./textures/tankGreen.png");
	m_tankBoxerTexture = new aie::Texture("./textures/rock_small.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	///Tank-Start
	//Tank
	m_tankX = 200;		//X
	m_tankY = 200;		//Y
	m_tankspeed = 2.0f; //Speed
	m_tankR = 0;        //Rotation
	
	//Barrel
	m_tankBarrelX = 0;  //X
	m_tankBarrelY = 0; //Y 40
	m_tankBarrelR = 0;  //Rotation

	//Boxer
	m_tankBoxerX = 0;  //X
	m_tankBoxerY = m_tankBarrelY + 70; //Y
	m_tankBoxerR = 0;  //Rotation

	///Tank-End
	m_timer = 0;


	return true;
}

void Application2D::shutdown() {
	
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	
	delete m_tankBATexture;
	delete m_tankTexture;

	delete m_TankRenderer;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

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

	//##Boxer##
	Matrix3<float> translation_boxer;
	Matrix3<float> roatation_boxer;
	Matrix3<float> child_of_child;
	translation_boxer.m31 = m_tankBoxerX;
	translation_boxer.m32 = m_tankBoxerY;
	
	child_of_child = translation_boxer;
	child_of_child.setRotateZ(m_tankBoxerR);

	m_tankBoxerMatrix = m_tankMatrix * child * child_of_child;
	
	m_timer += deltaTime;

	
	
	//Tank Controls ###############################################	
	aie::Input* input = aie::Input::getInstance(); // initzlier
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

	//Fire #############################################	
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) 
	{
		if (m_tankBoxerY <= m_tankY + 0.5f)
		{
			m_tankBarrelY += roatation_barrel.m11 + 5.0f;
			//m_tankBarrelX -= roatation_barrel.m12 + 5.0f;
			m_tankBoxerY += 10;
		}
	}
	else
		if (m_tankBarrelY != 0)
		{
			m_tankBarrelY -= roatation_barrel.m11 + 5.0f;
			//m_tankBarrelX += roatation_barrel.m12 + 5.0f;
				m_tankBoxerY -= 10;
		}


	//Other #######################################################		
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
	


	// demonstrate spinning sprite
	
	//m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSpriteTransformed3x3(m_tankTexture, m_tankMatrix.m); //Tank
	m_2dRenderer->drawSpriteTransformed3x3(m_tankBATexture, m_tankBMatrix.m); //Barrel
	m_2dRenderer->drawSpriteTransformed3x3(m_tankBoxerTexture, m_tankBoxerMatrix.m); //Boxer
	

	// output some text, uses the last used colour
	char fps[32];
	char TankX[32];
	char TankY[32];
	char TankZ[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	sprintf_s(TankX, 32, "X: %f", m_tankMatrix.m31);
	sprintf_s(TankY, 32, "Y: %f", m_tankMatrix.m32);
	sprintf_s(TankZ, 32, "Z: %f", m_tankMatrix.m33);
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, TankX, 0, 720 - 64);
	m_2dRenderer->drawText(m_font, TankY, 0, 720 - 96);
	m_2dRenderer->drawText(m_font, TankZ, 0, 720 - 128);
	
	// done drawing sprites
	
	m_2dRenderer->end();

}