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
	aie::Renderer2D*	m_TankRenderer;
	
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;

	aie::Texture*		m_tankTexture;
	aie::Texture*		m_tankBATexture;
	Matrix3<float>      m_tankMatrix;

	float m_cameraX, m_cameraY;
	float m_tankX, m_tankY, m_tankR;
	float m_timer;
};