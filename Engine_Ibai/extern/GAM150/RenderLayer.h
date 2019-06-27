// ---------------------------------------------------------------------------
// Project Name		:	GAM150 Lab 6 - Cameras & Graphics Management
// File Name		:	RenderLayer.h
// Author			:	Thomas Komair
// Creation Date	:	2015/01/27
// Purpose			:	Header for the RenderLayer class
// ---------------------------------------------------------------------------
#ifndef SPRITE_LAYER_H_
#define SPRITE_LAYER_H_

#include <AEEngine.h>
#include "GameObject.h"	// included because OBJECT_PTR_LIST
#include "Camera.h"		// included because object containment typedef

class RenderLayer
{
public:
	std::string				mName;		// Name of the layer.
	bool					mbVisible;	// render the sprite layer or not.
	s32						mOrder;		// order of the sprite layer.
	std::list<Camera *>		mCameras;	// cameras used to render the layer
	OBJECT_PTR_LIST			mObjects;	// objects to render.

public:

	// ---------------------------------------------------------------------------
	// Default Constructor - note that if no name is provided, the
	// default name will  be renderlayer.
	RenderLayer(const char * name = "RenderLayer");

	// render the game objects using the camera
	virtual void Render();
	void RenderCam(Camera * pCam);

	// ---------------------------------------------------------------------------
	// CAMERA MANAGEMENT
	void		AddCamera(Camera * pCam);
	void		RemoveCamera(Camera * pCam);
	void		RemoveAllCameras();
	Camera *	FindCamera(const char * camName);

	// Sort the game object by their Z-Order
	void		SortCameras();

	// ---------------------------------------------------------------------------
	// OBJECT MANAGEMENT

	// Add/remove objects
	void			AddObject(GameObject * pObj);
	void			RemoveObject(GameObject * pObj);
	void			ClearAll();

	// Sort the game object by their Z-Order
	void SortObjects();

	// Find objects
	GameObject *	FindObject(u32 id);
	GameObject *	FindObject(const char * objectName);
	void			FindObject(const char * objectName, OBJECT_PTR_LIST & outObjects);
};

// ---------------------------------------------------------------------------
#endif
