/**
 * Coexistence Reality Software Framework (CRSF)
 * Copyright (c) Center of Human-centered Interaction for Coexistence. All rights reserved.
 * See the LICENSE.md file for more details.
 */

#include "setup.h"

#include <render_pipeline/rpcore/util/rpmaterial.hpp>

#include <crsf/RenderingEngine/TGraphicRenderEngine.h>
#include <crsf/CRModel/TWorld.h>
#include <crsf/CRModel/TCube.h>
#include <crsf/CRModel/TSphere.h>

#include <crsf/CREngine/TPhysicsManager.h>

#include <crsf/CoexistenceInterface/TAvatarMemoryObject.h>
#include <crsf/System/TPose.h>


void ExampleApplication02Module::Impl::Example3DModel(void)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	crsf::TWorld* cr_world = rendering_engine->GetWorld();

	// Set hand property
	crsf::TCRProperty crHandProperty;
	crHandProperty.m_propAvatar.SetJointNumber(44);
	crHandProperty.m_propHand.m_strName = "Hand";
	float m_vec3ZeroToSensor_x = self_.m_property.get("handprop.m_vec3ZeroToSensor_x", 0.0f);
	float m_vec3ZeroToSensor_y = self_.m_property.get("handprop.m_vec3ZeroToSensor_y", 0.0f);
	float m_vec3ZeroToSensor_z = self_.m_property.get("handprop.m_vec3ZeroToSensor_z", 0.0f);
	crHandProperty.m_propHand.m_vec3ZeroToSensor = LVecBase3(m_vec3ZeroToSensor_x, m_vec3ZeroToSensor_y, m_vec3ZeroToSensor_z);
	crHandProperty.m_propHand.SetRenderMode(false, false, true);

	// Load hand model
	m_pTwoHand_Object = cr_world->LoadModel("resources/models/hands/leap_hand.bam");
	m_pTwoHand_Object->FindByName("Left_hand")->Hide();


	//m_pTwoHand_Object->SetScale(0.011f, cr_world);
	//m_pTwoHand_Object->DisableTestBounding();
	//m_pTwoHand_Character = m_pTwoHand_Object->GetChild("leap_hand")->GetPtrOf<crsf::TCharacter>();
	//m_pTwoHand_Character->MakeAllControlJoint();
	//crHandProperty.m_propHand.m_p3DModel = m_pTwoHand_Character;
	//m_pTwoHand_Object->PrintAll();

	// Create hand instance
	//m_pHand = new crsf::TCRHand(crHandProperty);

	// Set DSM for hand
	//m_pHandInteractionEngineConnector = new crsf::THandInteractionEngineConnector();
	//m_pHandInteractionEngineConnector->Init(m_pHand);
	//m_pHandInteractionEngineConnector->ConnectHand(boost::bind(&ExampleApplication02Module::Impl::ExampleRenderHand, this, _1), crsf::TDynamicStageMemory::GetInstance()->GetAvatarMemoryObjectByName("Hands"));


	
	/*
	table = world->LoadPandaModel("models/table/table");
	table->SetScale(table_scale);
	table->SetPosition(table_pos, world);  // 기본 table->SetPosition(ofVec3f(0.0f, 1.0f, 0.7f), world); 왜 이렇게 세팅했을까. 아래 있는 params 이랑 무슨 관계일까
	table->SetRotation(table_ori);
	/// 테이블 그래픽 모델 생성
	crsf::TCube::Parameters table_params;
	table_params.m_strName = "table";
	table_params.m_vec3fOrigin = ofVec3f(0.0f, 0.0f, 0.0f);
	//table_params.m_vec3fHalfExtent = ofVec3f(2.2f, 1.2f, 0.02f);	
	m_pTable = new crsf::TCube(table_params);
	crsf::TGraphicModel* pTableGraphicModel = m_pTable->CreateGraphicModel();
	pTableGraphicModel->Hide();
	world->AddWorldObject(m_pTable);

	// 테이블 물리적 모델 생성
	crsf::TPhysicsModel::Parameters table_phyx_params;
	table_phyx_params.m_fMass = 0.0f;
	crsf::TPhysicsModel *pTablePhysicsModel = m_pTable->CreatePhysicsModel(table_phyx_params);
	// 테이블 모델 추가
	crsf::TPhysicsManager::GetInstance()->AddModel(m_pTable);
	*/


}

void ExampleApplication02Module::Impl::ExampleRenderHand(crsf::TAvatarMemoryObject *pAvatarMemoryObject)
{
	crsf::TWorld* virtual_world = crsf::TGraphicRenderEngine::GetInstance()->GetWorld();

	//////////////////////////////////////////////////////////////////////////
	// if- TCRHand,
	if (m_pHand)
	{
		// # joint
		const unsigned int nJointNumber = m_pHand->GetJointNumber();

		//////////////////////////////////////////////////////////////////////////
		// Loop all joint
		for (int i = 0; i < nJointNumber; i++)
		{
			//////////////////////////////////////////////////////////////////////////
			// <<< Read joint TPose from AvatarMemory >>>
			crsf::TPose getTPose = pAvatarMemoryObject->GetAvatarMemory().at(i);
			// <<< Read joint TAvatarHeader from AvatarMemory >>>
			crsf::TAvatarHeader getTAvatarHeader = pAvatarMemoryObject->GetAvatarHeader().at(i);


			//////////////////////////////////////////////////////////////////////////
			// <<< Update flag >>>
			// 1. Read joint update flag
			bool bUpdate = getTAvatarHeader.m_bUpdate;

			// 2. Register hand joint update flag
			m_pHand->GetJointData(i)->SetIsUpdate(bUpdate);


			//////////////////////////////////////////////////////////////////////////
			// <<< Position >>>
			// 1. Read joint position
			LVecBase3 vec3Position = getTPose.GetPosition();

			// 2. Translation to designated hand pose (set sensor's origin on CRSF)
			vec3Position = vec3Position + m_pHand->GetHandProperty().m_vec3ZeroToSensor;

			// 3. Register hand joint position
			m_pHand->GetJointData(i)->SetPosition(vec3Position);


			//////////////////////////////////////////////////////////////////////////
			// <<< Orientation >>>
			// 1. Read joint orientation
			LQuaternionf quatOrientation = getTPose.GetQuaternion();

			// 2. Register hand joint orientation
			m_pHand->GetJointData(i)->SetOrientation(quatOrientation);

			// 3. Update 3D model's orientation
			if (m_pHand->GetHandProperty().m_bRender3DModel && (m_pHand->GetHandProperty().m_p3DModel || m_pHand->GetHandProperty().m_p3DModel_Left || m_pHand->GetHandProperty().m_p3DModel_Right))
			{
				crsf::TWorldObject* pTextureModel = m_pHand->GetJointData(i)->Get3DModel();
				std::string strTextureName = m_pHand->GetJointData(i)->Get3DModelNodeName();

				if (pTextureModel && strTextureName != "")
				{
					//////////////////////////////////////////////////////////////////////////
					// Left
					if (i == 1) // Thumb_1
					{
						// Calculate quaternion for hand model
						LQuaternionf a, b, ba;
						a.set_from_axis_angle(-90, LVecBase3(0, -1, 0));
						b.set_from_axis_angle(-90, LVecBase3(0, 0, 1));
						ba = b* a;
						// Mapped quaternion result
						LQuaternionf quat_result = ba.conjugate() * quatOrientation * ba;
						// Multiply quaternion for thumb rotation
						LQuaternionf c, d, e, edc;
						c.set_from_axis_angle(24, LVecBase3(0, 1, 0));
						d.set_from_axis_angle(75, LVecBase3(-1, 0, 0));
						e.set_from_axis_angle(-54, LVecBase3(0, 0, 1));
						edc = e * d* c;
						quat_result = quat_result * edc;
						// Set hpr
						LVecBase3 hpr = quat_result.get_hpr();
						pTextureModel->SetHPR(hpr);
					}
					else if (i >= 2 && i <= 20)
					{
						// Calculate quaternion for hand model
						LQuaternionf a, b, ba;
						a.set_from_axis_angle(90, LVecBase3(0, 1, 0));
						b.set_from_axis_angle(90, LVecBase3(0, 0, -1));
						ba = b * a;
						// Mapped quaternion result
						LQuaternionf quat_result = ba.conjugate() * quatOrientation * ba;
						LVecBase3 hpr = quat_result.get_hpr();
						// Set hpr
						pTextureModel->SetHPR(hpr);
					}
					else if (i == 21) // Root(wrist)
					{
						// Set position
						pTextureModel->SetPosition(vec3Position, virtual_world);

						// Rotate hand model to LEAP base
						LQuaternionf a, b, ba;
						a.set_from_axis_angle(-90, LVecBase3(0, 1, 0));
						b.set_from_axis_angle(-90, LVecBase3(1, 0, 0));
						ba = b * a;
						// Quaternion result
						LQuaternionf quat_result = ba * quatOrientation;
						LVecBase3 hpr = quat_result.get_hpr();
						// Set hpr
						pTextureModel->SetHPR(hpr);
					}

					//////////////////////////////////////////////////////////////////////////
					// Right
					else if (i == 23) // Thumb_1
					{
						// Calculate quaternion for hand model
						LQuaternionf a, b, ba;
						a.set_from_axis_angle(90, LVecBase3(0, 1, 0));
						b.set_from_axis_angle(-90, LVecBase3(0, 0, 1));
						ba = b* a;
						// Mapped quaternion result
						LQuaternionf quat_result = ba.conjugate() * quatOrientation * ba;
						// Multiply quaternion for thumb rotation
						LQuaternionf c, d, e, edc;
						c.set_from_axis_angle(24, LVecBase3(0, 1, 0));
						d.set_from_axis_angle(-75, LVecBase3(1, 0, 0));
						e.set_from_axis_angle(-54, LVecBase3(0, 0, 1));
						edc = e * d* c;
						quat_result = quat_result * edc;
						// Set hpr
						LVecBase3 hpr = quat_result.get_hpr();
						pTextureModel->SetHPR(hpr);
					}
					else if (i >= 24 && i <= 42)
					{
						// Calculate quaternion for hand model
						LQuaternionf a, b, ba;
						a.set_from_axis_angle(90, LVecBase3(0, 1, 0));
						b.set_from_axis_angle(-90, LVecBase3(0, 0, 1));
						ba = b * a;
						// Mapped quaternion result
						LQuaternionf quat_result = ba.conjugate() * quatOrientation * ba;
						LVecBase3 hpr = quat_result.get_hpr();
						// Set hpr
						pTextureModel->SetHPR(hpr);
					}
					else if (i == 43) // Root(wrist)
					{
						// Set position
						pTextureModel->SetPosition(vec3Position, virtual_world);

						// Rotate hand model to LEAP base
						LQuaternionf a, b, ba;
						a.set_from_axis_angle(-90, LVecBase3(0, 1, 0));
						b.set_from_axis_angle(90, LVecBase3(1, 0, 0));
						ba = b * a;
						// Quaternion result
						LQuaternionf quat_result = ba * quatOrientation;
						LVecBase3 hpr = quat_result.get_hpr();
						// Set hpr
						pTextureModel->SetHPR(hpr);
					}
				}
			}


			//////////////////////////////////////////////////////////////////////////
			// <<< Width >>>
			// 1. Read joint width
			float fWidth = getTAvatarHeader.m_fWidth;

			// 2. Register hand joint width
			m_pHand->GetJointData(i)->SetWidth(fWidth);


			//////////////////////////////////////////////////////////////////////////
			// <<< Normal >>>
			// 1. Read joint normal
			LVecBase3 vec3Normal = getTAvatarHeader.m_vec3Normal;

			// 2. Register hand joint normal
			m_pHand->GetJointData(i)->SetNormal(vec3Normal);
		}
	}
}

void ExampleApplication02Module::Impl::ExampleSetHand(void)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	crsf::TWorld* cr_world = rendering_engine->GetWorld();

	// Set hand property
	crsf::TCRProperty crHandProperty;
	crHandProperty.m_propAvatar.SetJointNumber(44);
	crHandProperty.m_propHand.m_strName = "Hand";
	float m_vec3ZeroToSensor_x = self_.m_property.get("handprop.m_vec3ZeroToSensor_x", 0.0f);
	float m_vec3ZeroToSensor_y = self_.m_property.get("handprop.m_vec3ZeroToSensor_y", 0.0f);
	float m_vec3ZeroToSensor_z = self_.m_property.get("handprop.m_vec3ZeroToSensor_z", 0.0f);
	crHandProperty.m_propHand.m_vec3ZeroToSensor = LVecBase3(m_vec3ZeroToSensor_x, m_vec3ZeroToSensor_y, m_vec3ZeroToSensor_z);
	crHandProperty.m_propHand.SetRenderMode(true, false, false);

	// Create hand instance
	m_pHand = new crsf::TCRHand(crHandProperty);

	// Create physics interactor
	m_pHand->ConstructPhysicsInteractor_FullJoint_Sphere(0.01f, true, false);

	// Set DSM for hand
	m_pHandInteractionEngineConnector = new crsf::THandInteractionEngineConnector();
	m_pHandInteractionEngineConnector->Init(m_pHand);
	m_pHandInteractionEngineConnector->ConnectHand(boost::bind(&ExampleApplication02Module::Impl::ExampleRenderHand, this, _1), crsf::TDynamicStageMemory::GetInstance()->GetAvatarMemoryObjectByName("Hands"));
}




/*
void ExampleApplication02Module::Impl::ExampleSpatialTouch(void)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	crsf::TWorld* cr_world = rendering_engine->GetWorld();

	{
		// Set cube graphics
		crsf::TCube::Parameters params;
		params.m_strName = "test_Cube";
		params.m_vec3Origin = LVecBase3(0.0f, 0.4f, 1.7f);
		params.m_vec3HalfExtent = LVecBase3(0.05f);
		m_pCube = crsf::CreateObject<crsf::TCube>(params);
		auto m_pCubeGraphicModel = m_pCube->CreateGraphicModel();
		rpcore::RPMaterial mat(m_pCubeGraphicModel->GetMaterial());
		mat.set_roughness(1.0f);
		mat.set_base_color(LColorf(1.0, 0.2, 0.2, 1));
		m_pCubeGraphicModel->SetMaterial(mat.get_material());
		cr_world->AddWorldObject(m_pCube);
		// Set cube physics
		crsf::TPhysicsModel::Parameters phyx_params;
		phyx_params.m_fMass = 0.0f;
		auto pCubePhysicsModel = m_pCube->CreatePhysicsModel(phyx_params);
		crsf::TPhysicsManager::GetInstance()->AddModel(m_pCube);
		// Set collision event
		pCubePhysicsModel->AttachCollisionListener(boost::bind(&ExampleApplication02Module::Impl::ExampleCollisionEvent, this, _1, _2), "ExampleApplication02Module::Impl::ExampleCollisionEvent");
	}

	CreateText_PhysicsState();
}

bool ExampleApplication02Module::Impl::ExampleCollisionEvent(const std::shared_ptr<crsf::TCRModel>& MyModel, const std::shared_ptr<crsf::TCRModel>& EventedModel)
{
	iter++;
	m_strTyping = "Collision count : " + std::to_string(iter);
	m_pText_PhysicsState->SetText(m_strTyping);

	if (iter % 2 == 0)
	{
		auto m_pCubeGraphicModel = MyModel->GetGraphicModel();
		rpcore::RPMaterial mat(m_pCubeGraphicModel->GetMaterial());
		mat.set_roughness(1.0f);
		mat.set_base_color(LColorf(1.0, 0.2, 0.2, 1));
		m_pCubeGraphicModel->SetMaterial(mat.get_material());
	}
	else
	{
		auto m_pCubeGraphicModel = MyModel->GetGraphicModel();
		rpcore::RPMaterial mat(m_pCubeGraphicModel->GetMaterial());
		mat.set_roughness(1.0f);
		mat.set_base_color(LColorf(0.2, 0.2, 1.0, 1));
		m_pCubeGraphicModel->SetMaterial(mat.get_material());
	}

	return false;
}
void ExampleApplication02Module::Impl::CreateText_PhysicsState(void)
{
	m_strTyping = "Collision Count : 0";

	crsf::TText3D::Parameters params;
	params.pos = LVecBase3(-0.10, 0.4, 1.6);
	params.scale = 0.02f;
	params.text_color = LColorf(0, 0, 0, 1);
	params.font = "resources/fonts/nanum-gothic-coding/nanum-gothic-coding.ttf";
	params.text = m_strTyping;

	m_pText_PhysicsState = crsf::CreateObject<crsf::TText3D>("Text_PhysicsState", params);

	crsf::TGraphicRenderEngine::GetInstance()->GetWorld()->AddWorldObject(m_pText_PhysicsState);
}
*/