/**
 * Coexistence Reality Software Framework (CRSF)
 * Copyright (c) Center of Human-centered Interaction for Coexistence. All rights reserved.
 * See the LICENSE.md file for more details.
 */

#include <crsf/CREngine/TDynamicModuleManager.h>
#include <crsf/RenderingEngine/TGraphicRenderEngine.h>
#include <crsf/CRModel/TWorld.h>
#include <crsf/CRModel/TCube.h>
#include <crsf/CRModel/TGraphicModel.h>

#include <openvr_module.h>

#include <setup.h>

//@ [update openvr devices]
void UpdateOpenVRDevices(void)
{
	const auto& module_instance = crsf::TDynamicModuleManager::GetInstance()->GetModuleInstance("openvr");

	if (!module_instance)
		return;

	const auto& openvr_module = std::dynamic_pointer_cast<OpenVRModule>(module_instance);
	if (!openvr_module)
	{
		std::cout << "Cannot cast OpenVR module.";
		return;
	}

	crsf::TGraphicRenderEngine* rendering_engine = crsf::TGraphicRenderEngine::GetInstance();
	crsf::TWorld* cr_world = rendering_engine->GetWorld();

	// update pose of devices.
	for (int i = 1; i <= 4; ++i)
	{
		if (openvr_module->IsDeviceConnected(i))
		{
			const std::string& device_name = "device" + std::to_string(i);
			if (!cr_world->Exists(device_name))
			{
				crsf::TCube::Parameters params;
				params.m_strName = device_name;
				auto device =  crsf::CreateObject<crsf::TCube>(params);
				if (openvr_module->IsTrackerReference(i))
					device->CreateGraphicModel()->SetBaseColor(LColor(0, 0, 0, 1));
				else if (openvr_module->IsController(i))
					device->CreateGraphicModel()->SetBaseColor(LColor(1, 0, 0, 1));

				device->SetScale(0.05f);
				cr_world->AddWorldObject(device);
			}

			auto device = cr_world->Find(device_name);
			device->SetPosition(openvr_module->GetDevicePosition(i));
			device->SetRotation(openvr_module->GetDeviceOrientation(i));
		}
	}

	const auto& HMD = openvr_module->GetHMDInstance();

	if (!HMD)
		return;

	// process events
	vr::VREvent_t ev;
	while (HMD->PollNextEvent(&ev, sizeof(ev)))
	{
		std::cout << "Event : " << HMD->GetEventTypeNameFromEnum(vr::EVREventType(ev.eventType)) << std::endl;
	}

	// process controller state
	for (int i=0, i_end=openvr_module->GetMaximumDeviceCount(); i < i_end; ++i)
	{
		vr::VRControllerState_t state;
		if (HMD->GetControllerState(i, &state, sizeof(vr::VRControllerState_t)))
		{
			if (state.ulButtonPressed != 0)
				std::cout << "Controller (" << i << ") Pressed" << std::endl;

			if (state.ulButtonTouched != 0)
				std::cout << "Controller (" << i << ") Touched" << std::endl;
		}
	}
}
//@ [update openvr devices]
