/**
 * Coexistence Reality Software Framework (CRSF)
 * Copyright (c) Center of Human-centered Interaction for Coexistence. All rights reserved.
 * See the LICENSE.md file for more details.
 */

#pragma once

#include "main.h"

#include <crsf/CoexistenceInterface/TDynamicStageMemory.h>

#include <crsf/CRModel/TCRHand.h>
#include <crsf/CREngine/THandInteractionEngineConnector.h>

#include <crsf/CRModel/TCube.h>
#include <crsf/CRModel/TText3D.h>


#include <crsf/CRModel/TWorldObject.h>
#include <crsf/CRModel/TCharacter.h>
#include <crsf/CREngine/THandInteractionEngineConnector.h>

//#include "addon\example_openvr.cpp"

// OPENVR
void UpdateOpenVRDevices(void);

struct ExampleApplication02Module::Impl
{
	Impl(ExampleApplication02Module& self);

	// Event
	void SetupEvent(void);

	//void UpdateOpenVRDevices(void);


	void ExampleSetHand(void);
	void Example3DModel(void);
	void ExampleRenderHand(crsf::TAvatarMemoryObject *pAvatarMemoryObject);

	void ExampleSpatialTouch(void);
	bool ExampleCollisionEvent(const std::shared_ptr<crsf::TCRModel>& MyModel, const std::shared_ptr<crsf::TCRModel>& EventedModel);
	void CreateText_PhysicsState();

	//////////////////////////////////////////////////////////////////////////
	// Self instance
	ExampleApplication02Module& self_;

	// Hand parameter
	crsf::TCRHand* m_pHand;
	crsf::THandInteractionEngineConnector* m_pHandInteractionEngineConnector;

	crsf::TWorldObject* m_pTwoHand_Object;
	crsf::TCharacter* m_pTwoHand_Character;

	// Table parameter

	crsf::TWorldObject* table = nullptr;
	crsf::TCube* m_pTable = nullptr;
	
	// Cube parameter
	std::shared_ptr<crsf::TCube> m_pCube;
	std::shared_ptr<crsf::TText3D> m_pText_PhysicsState;
	std::string m_strTyping;
	int iter = 0;
};

