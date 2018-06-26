

// 10-RHI_VR_TMS //

/**
 * Coexistence Reality Software Framework (CRSF)
 * Copyright (c) Center of Human-centered Interaction for Coexistence. All rights reserved.
 * See the LICENSE.md file for more details.
 */

#include "setup.h"

#include <render_pipeline/rppanda/task/task_manager.hpp>

#include <crsf/RenderingEngine/TGraphicRenderEngine.h>

#include <crsf/CREngine/TPhysicsManager.h>

CRSEEDLIB_MODULE_CREATOR(ExampleApplication02Module);

// ************************************************************************************************
ExampleApplication02Module::ExampleApplication02Module(void): crsf::TDynamicModuleInterface(CRMODULE_ID_STRING), m_impl(std::make_unique<Impl>(*this))
{
}

ExampleApplication02Module::Impl::Impl(ExampleApplication02Module& self) : self_(self)
{
}

void ExampleApplication02Module::OnLoad(void)
{
	// Setup physics manager
	crsf::TPhysicsManager* physics_manager = crsf::TPhysicsManager::GetInstance();
	physics_manager->Init(crsf::EPHYX_ENGINE_BULLET);
	physics_manager->SetGravity(LVecBase3(0.0, 0.0, -0.98));
}

void ExampleApplication02Module::OnStart(void)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();

	rendering_engine->SetWindowTitle(CRMODULE_ID_STRING);

	// setup (mouse) controller
	rendering_engine->EnableControl();
	rendering_engine->SetControllerInitialPosHpr(
		LVecBase3(0, -1.0f, 1.7f),
		LVecBase3(0, 0, 1.0f));
	rendering_engine->ResetControllerInitial();

	//m_impl->UpdateOpenVRDevices();


	m_impl->SetupEvent();
	m_impl->Example3DModel();
	//m_impl->ExampleSpatialTouch();
	//m_impl->
	// OPENVR ½ÇÇà
	rppanda::TaskManager::get_global_instance()->add([this](rppanda::FunctionalTask*){
		UpdateOpenVRDevices();
		return AsyncTask::DS_cont;
	}, "ExampleGraphics::UpdateOpenVRDevices");

}

void ExampleApplication02Module::OnExit(void)
{
	// Clear physics manager
	crsf::TPhysicsManager* physics_manager = crsf::TPhysicsManager::GetInstance();
	if (physics_manager)
		delete physics_manager; physics_manager = NULL;
}
