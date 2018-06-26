/**
 * Coexistence Reality Software Framework (CRSF)
 * Copyright (c) Center of Human-centered Interaction for Coexistence. All rights reserved.
 * See the LICENSE.md file for more details.
 */

#pragma once

#include <crsf/CRAPI/TDynamicModuleInterface.h>

class ExampleApplication02Module: public crsf::TDynamicModuleInterface
{
public:
	ExampleApplication02Module(void);

	void OnLoad(void) override;
	void OnStart(void) override;
	void OnExit(void) override;

private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};
