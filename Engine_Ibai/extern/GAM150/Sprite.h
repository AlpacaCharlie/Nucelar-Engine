/*!
*	\file		Sprite.h
*	\brief		Header for the Sprite class
*	\details	Sprite class derives from GameObject class and provides 
*				functionality to play a sprite animation. It uses the 
*				SpriteAnimationData resource. 
*
*	\remark		Sprite Overloads the GameObject Render method.
*
*	\author		Thomas Komair - tkomair@digipen.edu
*	\date		12/02/2018
*	\copyright	Copyright DigiPen Institute Of Technology. All Rights Reserved
*
*/
#ifndef SPRITE_H_
#define SPRITE_H_
// ----------------------------------------------------------------------------
#include "GameObject.h" // Sprite derives from GameObject

// Forward declare the sprite animation data. It's fine to not include 
// it in this file because we only are referencing the SpriteAnimationData
// as pointers in the Sprite class(below). Since a pointer has a fixed size
// in bytes regardless of the data type it points to, the compiler
// won't need to know what SpriteAnimationData really is until we use it; and 
// that's in the CPP
struct SpriteAnimationData; 

struct Sprite : public GameObject
{
	// ------------------------------------------------------------------------
	// DATA MEMBERS

	// Animation Data
	SpriteAnimationData *	mpAnim;					//! Animation Resource: This should be loaded by the game state
	u32						mAnimCurrentFrame;		//! Current frame of the sprite animatoin
	f32						mAnimTimer;				//! Current time (in seconds) of the animation
	f32						mAnimSpeed;				//! Scalar to multiply the animation speed, greater >= 0.0f;
	bool					mbAnimLoop;				//! Boolean specifying if the animation should loop
	bool					mbAnimPlaying;			//! Boolean specifying if the animation is currently playing. 
	bool					mbAnimReachedEnd;		//! Boolean specifying if the animation has finished. 

	// ------------------------------------------------------------------------
	// MEMBER FUNCTIONS

	// Default Constructor - Sets data members to default value and calls
	// base constructor.
	Sprite();

	// Animation Methods

	void		PlayAnimation();
	void		PauseAnimation();
	void		ResetAnimation();
	void		SetLoop(bool enable);
	void		UpdateAnimation();
	void		SetAnimationFrame(u32 frameIndex);
	void		SetAnimation(SpriteAnimationData * pNewAnim);

	// Overloaded Game Object state methods
	virtual void Render();
	virtual void Render(AEMtx33 * pCam);
};


// ----------------------------------------------------------------------------
#endif