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

	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	
	m_tankX = 0;
	m_tankY = 0;
	//m_tankX = m_tankMatrix.m31;
	//m_tankY = m_tankMatrix.m32;

	m_tankR = 0;

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

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// use arrow keys to move camera
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		//m_tankY -= 0.1f;
		m_tankY -= 0.5f;
		m_tankMatrix.m32 = m_tankY;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) 
	{
		m_tankY += 0.5f;
		m_tankMatrix.m32 = m_tankY;
	}

	if (input->isKeyDown(aie::INPUT_KEY_LEFT)) 
	{
		
		m_tankR -= 1.0f;
		m_tankMatrix.setRotateZ(m_tankR);
	}
		

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) 
	{
		m_tankR += 1.0f;
		m_tankMatrix.setRotateZ(m_tankR);
		
		
	}
		

	// example of audio
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		/*
		std::cout << m_tankMatrix.m11 + " " + m_tankMatrix.m12 + " " + m_tankMatrix.m13 + "\n";
		std::cout << m_tankMatrix.m21 + " " + m_tankMatrix.m22 + " " + m_tankMatrix.m23 + "\n";
		std::cout << m_tankMatrix.m31 + " " + m_tankMatrix.m32 + " " + m_tankMatrix.m33 + "\n";
		*/
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
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
	
	//m_2dRenderer->drawSprite(m_tankBATexture, m_tankX, m_tankY, 0, 0, m_timer, 1);
	//m_2dRenderer->drawSprite(m_tankTexture, 0, 0, m_tankX, m_tankY, m_tankR, 1);
	
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSpriteTransformed3x3(m_tankBATexture, m_tankMatrix.m, 0, 0, 0, -5, -2);
	

	//m_tankMatrix.m[6] = m_tankX;
	//m_tankMatrix.m[7] = m_tankY;

	
	//m_2dRenderer->drawSpriteTransformed3x3(m_tankBATexture, m_tankMatrix.m, 0, 0, 0, m_tankMatrix.m31, m_tankMatrix.m32);

	// output some text, uses the last used colour
	char fps[32];
	char TankT[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	
	// done drawing sprites
	
	m_2dRenderer->end();

}