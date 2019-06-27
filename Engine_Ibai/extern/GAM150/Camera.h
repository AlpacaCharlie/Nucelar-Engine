// ---------------------------------------------------------------------------
// Project Name		:	GAM150 Lab 6 - Cameras & Graphics Management
// File Name		:	Camera.h
// Author			:	Thomas Komair
// Creation Date	:	2015/01/27
// Purpose			:	Header for the Camera class
// ---------------------------------------------------------------------------
#ifndef CAMERA_H_
#define CAMERA_H_

#include <AEEngine.h>
#include "GameObject.h"

// typedef for pointer to point to object containment functions
typedef bool(*ObjectPointContainFn) (const AEPoint2 &, GameObject *);

class Camera
{
public:
	std::string		mName;			// name of the camera
	AETransform2D	mTransform;		// transform of the camera
	f32				mViewportTop;	// camera viewport top edge
	f32				mViewportBot;	// camera viewport bottom edge
	f32				mViewportLeft;	// camera viewport left edge
	f32				mViewportRight;	// camera viewport right edge
	f32				mZorder;		// camera render order within a render layer
	bool			mbClearBG;		// specified whether the viewport should be cleared before drawing
	u32				mClearColor;	// color used to clear the viewport before drawing

	// Default constructor
	Camera(const char * camName = "Camera");

	// returns the camera to world transformation
	AEMtx33			GetCamToWorld();

	// return the world to camera transformation
	AEMtx33			GetWorldToCam();

	// converts a  point in centered window coordinates to world coordinates 
	AEPoint2		ConvertPointToWorld(const AEPoint2 & pointWindow);

	// converts a  point in world coordinates to centered window coordinates
	AEPoint2		ConvertPointToWindow(const AEPoint2 &pointWorld);

	// Returns whether a point is contained in this camera's viewport
	bool			PointInViewport(const AEPoint2 & pointWindow);

	// Determines if a point in centered window coordinates is contained in the specified object. 
	// this function converts the point to world and then checks for containment using the function provided in 'selector'
	// returns true if the point is contained, false otherwise
	bool			PickGameObject(const AEPoint2 & pointWin, GameObject * pObj, ObjectPointContainFn selector);

	// Determines if a point in centered window coordinates is contained in one of objects specified in 'inObjects'. 
	// this function converts the point to world and then checks for containment using the function provided in 'selector'
	// returns the first object that contains the point.
	GameObject *	PickGameObject(const AEPoint2 & pointWin, const OBJECT_PTR_LIST & inObjects, ObjectPointContainFn selector);

	// Determines if a point in centered window coordinates is contained in one of objects specified in 'inObjects'. 
	// this function converts the point to world and then checks for containment using the function provided in 'selector'
	// it will add to the output list (outObjects) any object that contains the point. 
	// returns the number of objects that contains the point (i.e. that were added to outObjects).
	u32				PickGameObjects(const AEPoint2 & pointWin, const OBJECT_PTR_LIST & inObjects, OBJECT_PTR_LIST & outObjects, ObjectPointContainFn selector);
};

// ---------------------------------------------------------------------------
#endif
