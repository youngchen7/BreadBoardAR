// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#include "pch.h"
#include "Game.h"

#include "Common\DirectXHelper.h"
#include "HitTestingHelpers.h"

using namespace StarterKit;

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace VSD3DStarter;

// Loads vertex and pixel shaders from files and instantiates the cube geometry.
Game::Game(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
m_loadingComplete(false),
m_deviceResources(deviceResources)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// Loads meshes and other resources that depend on the device, but not on window size.
void Game::CreateDeviceDependentResources()
{
	m_graphics.Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext(), m_deviceResources->GetDeviceFeatureLevel());

	// Set DirectX to not cull any triangles so the entire mesh will always be shown.
	CD3D11_RASTERIZER_DESC d3dRas(D3D11_DEFAULT);
	d3dRas.CullMode = D3D11_CULL_NONE;
	d3dRas.MultisampleEnable = true;
	d3dRas.AntialiasedLineEnable = true;

	ComPtr<ID3D11RasterizerState> p3d3RasState;
	m_deviceResources->GetD3DDevice()->CreateRasterizerState(&d3dRas, &p3d3RasState);
	m_deviceResources->GetD3DDeviceContext()->RSSetState(p3d3RasState.Get());

	// Load the scene objects.
	auto loadMeshTask = Mesh::LoadFromFileAsync(
		m_graphics,
		L"breadboard.cmo",
		L"",
		L"",
		m_meshModels)
		.then([this]()
	{
		return Mesh::LoadFromFileAsync(
			m_graphics,
			L"Wire1.cmo",
			L"",
			L"",
			m_meshModels,
			false)
			.then([this]()
		{
			return Mesh::LoadFromFileAsync(
				m_graphics,
				L"Wire2.cmo",
				L"",
				L"",
				m_meshModels,
				false)
				.then([this]()
			{
				return Mesh::LoadFromFileAsync(
					m_graphics,
					L"Wire3.cmo",
					L"",
					L"",
					m_meshModels,
					false)
					.then([this]()
				{
					return Mesh::LoadFromFileAsync(
						m_graphics,
						L"Wire4.cmo",
						L"",
						L"",
						m_meshModels,
						false)
						.then([this]()
					{
						return Mesh::LoadFromFileAsync(
							m_graphics,
							L"WireBridge.cmo",
							L"",
							L"",
							m_meshModels,
							false)
							.then([this]()
						{
							return Mesh::LoadFromFileAsync(
								m_graphics,
								L"WirePowerL.cmo",
								L"",
								L"",
								m_meshModels,
								false)
								.then([this]()
							{
								return Mesh::LoadFromFileAsync(
									m_graphics,
									L"WirePowerR.cmo",
									L"",
									L"",
									m_meshModels,
									false)
									.then([this]()
								{
									return Mesh::LoadFromFileAsync(
										m_graphics,
										L"WireGroundL.cmo",
										L"",
										L"",
										m_meshModels,
										false)
										.then([this]()
									{
										return Mesh::LoadFromFileAsync(
											m_graphics,
											L"WireGroundR.cmo",
											L"",
											L"",
											m_meshModels,
											false)
										.then([this]()
										{
											return Mesh::LoadFromFileAsync(
												m_graphics,
												L"Cap1.cmo",
												L"",
												L"",
												m_meshModels,
												false)
												.then([this]()
											{
												return Mesh::LoadFromFileAsync(
													m_graphics,
													L"LED1.cmo",
													L"",
													L"",
													m_meshModels,
													false)
													.then([this]()
												{
													return Mesh::LoadFromFileAsync(
														m_graphics,
														L"Resistor1.cmo",
														L"",
														L"",
														m_meshModels,
														false)
														.then([this]()
													{
														
														return Mesh::LoadFromFileAsync(
															m_graphics,
															L"Resistor4220.cmo",
															L"",
															L"",
															m_meshModels,
															false)
															.then([this]()
														{

															return Mesh::LoadFromFileAsync(
																m_graphics,
																L"Potentiometer1K.cmo",
																L"",
																L"",
																m_meshModels,
																false);
														});
													});
												});
											});
										});
									});
								});
							});
						});
					});
				});
			});
		});
	})
		.then([this]()
	{
		// Each mesh object has its own "time" used to control the glow effect.
		m_time.clear();
		for (size_t i = 0; i < m_meshModels.size(); i++)
		{
			m_time.push_back(0.0f);
		}
	});

	//auto initializeSkinnedMeshRendererTask = m_skinnedMeshRenderer.InitializeAsync(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());

	(loadMeshTask).then([this]()
	{
		// Scene is ready to be rendered.
		m_loadingComplete = true;
		my_build = my_factory.createBuild(-1); //hardcoded
		my_step = 0;
	});
}

// Initializes view parameters when the window size changes.
void Game::CreateWindowSizeDependentResources()
{
	m_miscConstants.ViewportHeight = m_deviceResources->GetScreenViewport().Height;
	m_miscConstants.ViewportWidth = m_deviceResources->GetScreenViewport().Width;
	m_graphics.UpdateMiscConstants(m_miscConstants);

	m_graphics.GetCamera().SetOrientationMatrix(m_deviceResources->GetOrientationTransform3D());

	Size outputSize = m_deviceResources->GetOutputSize();

	// Setup the camera parameters for our scene.
	m_graphics.GetCamera().SetViewport((UINT)outputSize.Width, (UINT)outputSize.Height);
	m_graphics.GetCamera().SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f)); //pitch, roll, yaw type
	m_graphics.GetCamera().SetLookAt(XMFLOAT3(0.0f, 0.0f, 1.0f));
	

	float aspectRatio = outputSize.Width / outputSize.Height;
	//float fovAngleY = 70.0f * XM_PI / 180.0f;
	float fovAngleY = 67.0f * XM_PI / 180.0f;

	 
	if (aspectRatio < 1.0f)
	{
		// Portrait or snap view
		m_graphics.GetCamera().SetUpVector(XMFLOAT3(1.0f, 0.0f, 0.0f));
		fovAngleY = 120.0f * XM_PI / 180.0f;
	}
	else
	{
		// Landscape view.
		m_graphics.GetCamera().SetUpVector(XMFLOAT3(0.0f, 1.0f, 0.0f));
	}

	m_graphics.GetCamera().SetProjection(fovAngleY, aspectRatio, 1.0f, 1000.0f);

	// Setup lighting for our scene.
	static const XMVECTORF32 s_vPos = { 5.0f, 5.0f, -2.5f, 0.f };

	XMFLOAT4 dir;
	DirectX::XMStoreFloat4(&dir, XMVector3Normalize(s_vPos));

	m_lightConstants.ActiveLights = 1;
	m_lightConstants.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_lightConstants.IsPointLight[0] = false;
	m_lightConstants.LightColor[0] = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_lightConstants.LightDirection[0] = dir;
	m_lightConstants.LightSpecularIntensity[0].x = 2;

	m_graphics.UpdateLightConstants(m_lightConstants);
}

// Release resources that depend on the device. Called when the device is released.
void Game::ReleaseDeviceDependentResources()
{
	for (Mesh* m : m_meshModels)
	{
		if (m != nullptr)
		{
			AnimationState* animState = (AnimationState*)m->Tag;
			if (animState != nullptr)
			{
				m->Tag = nullptr;
				delete animState;
			}
		}
		delete m;
	}
	m_meshModels.clear();

	m_loadingComplete = false;
}

// Called once per frame, updates the scene state.
void Game::Update(DX::StepTimer const& timer)
{
	auto timeDelta = static_cast<float>(timer.GetElapsedSeconds());

	// Update animated models.
	m_skinnedMeshRenderer.UpdateAnimation(timeDelta, m_meshModels);

	// Rotate scene.
	m_rotation = static_cast<float>(timer.GetTotalSeconds()) * -.5f;

	// Update the "time" variable for the glow effect.
	for (float &time : m_time)
	{
		time = std::max<float>(0.0f, time - timeDelta);
	}
}

// Computes rotation and translation matrix to move a component to its proper location
XMMATRIX Game::computeMatrix(int xPos, int yPos, int zPos, int degrees){
	XMMATRIX transformation = XMMatrixIdentity();	//final translation matrix
	float MatRotate = degrees * -3.14159f/180.0f;	//degrees to radians
	XMMATRIX rotation = XMMatrixRotationY(MatRotate);	//computes rotation matrix
	transformation = transformation*rotation;		//mulitplies in

	XMMATRIX translation = XMMatrixTranslation(11.6f - xPos*0.795f, 0.0f, 
		-4.3f + zPos*0.795f + (zPos / 5)*1.4f);	//translation, 3rd term to bridge the partition
	transformation = transformation*translation; 

	return transformation;
}

void Game::setProjection(XMMATRIX & projection)
{
	m_graphics.GetCamera().SetProjection(projection); 
}

void Game::setUniversalTransform(XMMATRIX & universal_transform)
{
	//m_graphics.GetCamera().SetView(universal_transform); //changes camera view
	m_universal_transform = universal_transform;			//set object transform
}

void Game::setBuild(int ID)
{
	my_build = my_factory.createBuild(ID);
	my_step = 0;
}

void Game::nextStep()
{
	if (my_step < my_build.size())
	{
		++my_step;
	}
}

void Game::previousStep()
{
	if (my_step > 0)
	{
		--my_step;
	}
}

int Game::getStep()
{
	return my_step;
}

// Renders one frame using the Starter Kit helpers.
void Game::Render()
{
	// Loading is asynchronous. Only draw geometry after it's loaded.
	if (!m_loadingComplete)
	{
		return;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Set render targets to the screen.
	auto rtv = m_deviceResources->GetBackBufferRenderTargetView();
	auto dsv = m_deviceResources->GetDepthStencilView();
	ID3D11RenderTargetView *const targets[1] = { rtv };
	context->OMSetRenderTargets(1, targets, dsv);

	//test transformation matrix
	//XMMATRIX translation = XMMatrixTranslation(0.25f, 0.0f, 2.75f);

	// Transform matrices
	XMMATRIX rotation = XMMatrixRotationY(m_rotation); //continuous spin
	//XMMATRIX rotation2 = XMMatrixRotationX(m_rotation);
	XMMATRIX scaleDown = {	(float).3, (float)0, (float)0, (float)0,
							(float)0, (float).3, (float)0, (float)0,
							(float)0, (float)0, (float).3, (float)0, 
							(float)0, (float)0, (float)0, (float)1 };

	XMMATRIX modelTransform = XMMatrixIdentity()* XMMatrixRotationX(-XM_PI/2.0f)*scaleDown*m_universal_transform*XMMatrixTranslation(0.0f,0.0f,0.0f);

	int xPos = 0;
	int yPos = 0;
	int zPos = 0; 
	int degrees = 0;
	int index;
	m_meshModels[0]->Render(m_graphics, modelTransform);	//breadboard
	for (int i = 0; i < my_step; ++i){
		// Update the time shader variable for the objects in our scene.
		m_miscConstants.Time = m_time[i];
		m_graphics.UpdateMiscConstants(m_miscConstants);
		index = my_build.at(i).getModel();
		xPos = my_build.at(i).getX();
		yPos = my_build.at(i).getY();
		zPos = my_build.at(i).getZ();
		degrees = my_build.at(i).getOrientation();
		m_meshModels[index]->Render(m_graphics, computeMatrix(xPos, yPos, zPos, degrees)*modelTransform);
	}
}

// Starts the glow animation for an object.
void Game::ToggleHitEffect(String^ object)
{
	for (UINT i = 0; i < m_meshModels.size(); i++)
	{
		Mesh* m = m_meshModels[i];
		String^ meshName = ref new String(m->Name());
		if (String::CompareOrdinal(object, meshName) == 0)
		{
			m_time[i] = 1.0f;
			break;
		}
	}
}

// Changes an object's diffuse material color.
void Game::ChangeMaterialColor(String^ object, float r, float g, float b)
{
	for (Mesh* m : m_meshModels)
	{
		String^ meshName = ref new String(m->Name());
		if (String::CompareOrdinal(object, meshName) == 0)
		{
			m->Materials()[0].Diffuse[0] = r;
			m->Materials()[0].Diffuse[1] = g;
			m->Materials()[0].Diffuse[2] = b;
			break;
		}
	}
}

// Hit tests the scene on the point (x,y), looking for objects. 
// If there's any valid hit, returns the name of the hit object.
String^ Game::OnHitObject(int x, int y)
{
	String^ result = nullptr;

	XMFLOAT3 point;
	XMFLOAT3 dir;
	m_graphics.GetCamera().GetWorldLine(x, y, &point, &dir);

	XMFLOAT4X4 world;
	XMMATRIX worldMat = XMMatrixRotationY(m_rotation);
	XMStoreFloat4x4(&world, worldMat);

	XMFLOAT4X4 teapotWorld;
	XMStoreFloat4x4(&teapotWorld, XMLoadFloat4x4(&m_teapotTransform) * worldMat);

	float closestT = FLT_MAX;
	for (Mesh* m : m_meshModels)
	{
		XMFLOAT4X4 meshTransform = world;

		auto name = ref new String(m->Name());

		if (String::CompareOrdinal(name, L"Teapot_Node") == 0)
		{
			meshTransform = teapotWorld;
		}

		float t = 0;
		bool hit = HitTestingHelpers::LineHitTest(*m, &point, &dir, &meshTransform, &t);
		if (hit && t < closestT)
		{
			result = name;
		}
	}

	return result;
}