// ---------------------------------------------------------------------------
// Project Name		:	GAM150 Lab 6 - Cameras & Graphics Management
// File Name		:	GraphicsManager.h
// Author			:	Thomas Komair
// Creation Date	:	2015/01/27
// Purpose			:	Header for the Graphics Manager class
// ---------------------------------------------------------------------------
#ifndef GRAPHICS_MANAGER_H_H
#define GRAPHICS_MANAGER_H_H

#include "Camera.h"
#include "RenderLayer.h"

class GraphicsManager
{
public:
	// List of render layers
	std::list<RenderLayer*> mRenderLayers;
	
	// List of cameras
	std::list<Camera *>		mCameras;
	
	// ------------------------------------------------------------------------

	// render all render layers
	void Render();
	void SortRenderLayers();

	// Create Camera
	Camera * GetCamera(const char * camName);
	Camera * CreateCamera(const char * camName);
	Camera * CreateCameraToRenderLayer(const char * camName, const char * layerName);

	// Create Sprite Layers
	RenderLayer *	GetRenderLayer(const char * layerName);
	RenderLayer *	CreateRenderLayer(const char * layerName, s32 order);
	RenderLayer *	AddRenderLayer(const char * layerName, s32 order, RenderLayer * layer);
	void			DeleteRenderLayer(const char * layerName);

	// Add object
	void AddObject(GameObject * pObj, const char * layerName);
	void RemoveObject(GameObject * pObj, const char * layerName);
	void RemoveObject(GameObject * pObj);

	// Clear sprite layer from its objects
	void EmptyRenderLayer(const char * layerName);
	void EmptyAllRenderLayers();

	// Free the data
	void FreeCameras();
	void FreeRenderLayers();
	void FreeAll();
};

// Global Graphics Manager
extern GraphicsManager gGraphics;

// ---------------------------------------------------------------------------
#endif
