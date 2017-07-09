#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix2.h>
#include <Matrix3.h>
#include <Matrix4.h>

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	
	aie::Font*			m_font;
	aie::Audio*			m_audio;
	

	///+######################Tank-Start################################
	//Tank Body - Main
	aie::Texture*		m_tankTexture; float m_tankW, m_tankH;
	Matrix3<float>      m_tankMatrix; 
	float m_tankX, m_tankY, m_tankR, m_tankspeed; //XY, speed and Rotation

	//Tank Barrel - Child of Tank Body
	aie::Texture*		m_tankBATexture;
	Matrix3<float>      m_tankBMatrix; 
	float m_tankBarrelX, m_tankBarrelY, m_tankBarrelR; //XY and Rotation
	
	//Tank Boxing Glove - Child of Tank Barrel
	aie::Texture*		m_tankBoxerTexture;
	Matrix3<float>      m_tankBoxerMatrix; 
	float m_tankBoxerX, m_tankBoxerY, m_tankBoxerR; //XY and Rotation
	///-######################Tank-End##################################


	///+###########Box-Start#####
	aie::Texture*		m_BoxTexture; float m_BoxW, m_BoxH;
	Matrix3<float>      m_BoxMatrix; //Box, this should never change
	float m_BoxX, m_BoxY, m_BoxR; //Boxer
	///-###########Box-End#######
	
	//Camra
	float m_cameraX, m_cameraY;
	//Borders
	float m_screen_min_borderX, m_screen_min_borderY;
	float m_screen_max_borderX, m_screen_max_borderY;
	
	bool Debug_Mode;

	float m_timer;
};