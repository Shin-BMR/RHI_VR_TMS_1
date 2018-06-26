/**
 * Coexistence Reality Software Framework (CRSF)
 * Copyright (c) Center of Human-centered Interaction for Coexistence. All rights reserved.
 * See the LICENSE.md file for more details.
 */

#include "setup.h"
#include <mouseWatcher.h>

#include <render_pipeline/rppanda/showbase/messenger.hpp>

#include <crsf/RenderingEngine/TGraphicRenderEngine.h>
#include <crsf/CRModel/TWorld.h>
#include <crsf/CRModel/TGraphicModel.h>

#include <crsf/CREngine/TPhysicsManager.h>

bool LsPandaNodePath(void)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	rendering_engine->GetWorld()->GetNodePath().ls();

	return true;
}

void PrintWorldObject(const Event*)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	rendering_engine->GetRenderNode()->GetNodePath().ls();
}

void PrintClickPosition(const Event*)
{
	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	const LPoint2& mouse_pos = rendering_engine->GetMouseWatcherNode()->get_mouse();

	std::cout << "Mouse: (" << mouse_pos.get_x() << ", " << mouse_pos.get_y() << ")" << std::endl;
}

void StartPhysicsSimulation(const Event*)
{
	// Note: After physics simulation setting, start physics manager thread.
	crsf::TPhysicsManager::GetInstance()->Start();
}

void RHI_VR_TMS(const Event*)
{
	// Note: After physics simulation setting, start physics manager thread.
	//crsf::TPhysicsManager::GetInstance()->Start();

	cout << "hello" << endl;
}

void ExampleApplication02Module::Impl::SetupEvent(void)
{
	auto messenger = rppanda::Messenger::get_global_instance();
	messenger->accept("p", PrintWorldObject);
	messenger->accept("mouse1", PrintClickPosition);
	//messenger->accept("0", StartPhysicsSimulation);

	messenger->accept("0", RHI_VR_TMS);
}
