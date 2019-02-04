//#pragma once
//
//#include "d3dApp.h"
//#include "MathHelper.h"
//#include "UploadBuffer.h"
//#include "GeometryGenerator.h"
//#include "FrameResource.h"
//#include "Waves.h"
//#include "MeshGeometry.h"
//
//
//struct RenderItem;
//using Microsoft::WRL::ComPtr;
//
//enum class RenderLayer : int
//{
//	Opaque = 0,
//	Count
//};
//
//class LandAndWavesApp : public D3DApp
//{
//public:
//	LandAndWavesApp(HINSTANCE hInstance);
//	LandAndWavesApp(const LandAndWavesApp& rhs) = delete;
//	LandAndWavesApp& operator=(const LandAndWavesApp& rhs) = delete;
//	~LandAndWavesApp();
//
//	virtual bool Initialize()override;
//
//private:
//	virtual void OnResize()override;
//	virtual void Update(const GameTimer& gt)override;
//	virtual void Draw(const GameTimer& gt)override;
//
//	virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
//	virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
//	virtual void OnMouseMove(WPARAM btnState, int x, int y)override;
//
//	void OnKeyboardInput(const GameTimer& gt);
//	void UpdateCamera(const GameTimer& gt);
//	void UpdateObjectCBs(const GameTimer& gt);
//	void UpdateMainPassCB(const GameTimer& gt);
//	void UpdateWaves(const GameTimer& gt);
//
//	void BuildRootSignature();
//	void BuildShadersAndInputLayout();
//	void BuildLandGeometry();
//	void BuildWavesGeometryBuffers();
//	void BuildPSOs();
//	void BuildFrameResources();
//	void BuildRenderItems();
//	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
//
//	float GetHillsHeight(float x, float z)const;
//	DirectX::XMFLOAT3 GetHillsNormal(float x, float z)const;
//
//private:
//
//	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
//	FrameResource* mCurrFrameResource = nullptr;
//	int mCurrFrameResourceIndex = 0;
//
//	UINT mCbvSrvDescriptorSize = 0;
//
//	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
//
//	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
//	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
//	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
//
//	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
//
//	RenderItem* mWavesRitem = nullptr;
//
//	// List of all the render items.
//	std::vector<std::unique_ptr<RenderItem>> mAllRitems;
//
//	// Render items divided by PSO.
//	std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];
//
//	std::unique_ptr<Waves> mWaves;
//
//	PassConstants mMainPassCB;
//
//	bool mIsWireframe = false;
//
//	DirectX::XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
//	DirectX::XMFLOAT4X4 mView = MathHelper::Identity4x4();
//	DirectX::XMFLOAT4X4 mProj = MathHelper::Identity4x4();
//
//	float mTheta = 1.5f*DirectX::XM_PI;
//	float mPhi = DirectX::XM_PIDIV2 - 0.1f;
//	float mRadius = 50.0f;
//
//	float mSunTheta = 1.25f*DirectX::XM_PI;
//	float mSunPhi = DirectX::XM_PIDIV4;
//
//	POINT mLastMousePos;
//};