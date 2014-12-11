// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#include <memory>
#include <vector>

#include "VSD3DStarter.h"
#include "Animation\Animation.h"

#include "Common\DeviceResources.h"
#include "Common\StepTimer.h"

#include "ARComponent.h"

namespace StarterKit
{
	class Game
	{
	public:
		Game(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();
		void ReleaseDeviceDependentResources();
		void Update(DX::StepTimer const& timer);
		void Render();
		void setUniversalTransform(DirectX::XMMATRIX & universal_transform);
		void setBuild(int ID);
		void nextStep();
		void previousStep();
		int getStep();
		int getMaxStep();
		String^ getDescription();
		void setProjection(DirectX::XMMATRIX & projection);
		DirectX::XMMATRIX computeMatrix(int xPos, int yPos, int zPos, int orientation);
		DirectX::XMMATRIX computeLegoMatrix(int xPos, int yPos, int zPos, int orientation);


		// Methods used to manipulate the objects in the scene.
		Platform::String^ OnHitObject(int x, int y);
		void ToggleHitEffect(Platform::String^ object);
		void ChangeMaterialColor(Platform::String^ object, float r, float g, float b);

		int getID();
		int getMarkerID();
		void setMarkerID(int markerID);
	private:
		// Members used to keep track of the scene state.
		SkinnedMeshRenderer m_skinnedMeshRenderer;
		std::vector<VSD3DStarter::Mesh*> m_meshModels;
		DirectX::XMFLOAT4X4 m_teapotTransform;
		std::vector<float> m_time;
		float m_rotation;

		// Members used to keep track of the graphics state.
		VSD3DStarter::Graphics m_graphics;
		VSD3DStarter::LightConstants m_lightConstants;
		VSD3DStarter::MiscConstants m_miscConstants;

		// Cached pointer to device resources.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// Variables used with the rendering loop.
		bool m_loadingComplete;

		DirectX::XMMATRIX m_universal_transform = DirectX::XMMatrixTranslation(0.0f, 0.0f, 5.0f);
		int my_step;
		instructAR::componentsFactory my_factory;
		vector<instructAR::Component> my_build;

		//ID
		int gameID = 0;
		int m_markerID = 0;
	};
}