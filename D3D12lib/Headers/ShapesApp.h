//#pragma once
//
//#include "d3dApp.h"
//#include "MathHelper.h"
//#include "UploadBuffer.h"
//#include "GeometryGenerator.h"
//#include "FrameResource.h"
//#include "MeshGeometry.h"
//#include "d3dx12.h"
//#include <unordered_map>
//#include <DirectXMath.h>
//
//using Microsoft::WRL::ComPtr;
//
//
//
//// Lightweight structure stores parameters to draw a shape.  This will
//// vary from app-to-app.
//struct RenderItem;
//
//class ShapesApp : public D3DApp
//{
//public:
//	ShapesApp(HINSTANCE hInstance);
//	ShapesApp(const ShapesApp& rhs) = delete;
//	ShapesApp& operator=(const ShapesApp& rhs) = delete;
//	~ShapesApp();
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
//
//	void BuildDescriptorHeaps();
//	void BuildConstantBufferViews();
//	void BuildRootSignature();
//	void BuildShadersAndInputLayout();
//	void BuildShapeGeometry();
//	void BuildPSOs();
//	void BuildFrameResources();
//	void BuildRenderItems();
//	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
//
//private:
//
//	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
//	FrameResource* mCurrFrameResource;
//	int mCurrFrameResourceIndex;
//
//	ComPtr<ID3D12RootSignature> mRootSignature;
//	ComPtr<ID3D12DescriptorHeap> mCbvHeap;
//
//	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap;
//
//	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
//	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
//	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
//
//	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
//
//	// List of all the render items.
//	std::vector<std::unique_ptr<RenderItem>> mAllRitems;
//
//	// Render items divided by PSO.
//	std::vector<RenderItem*> mOpaqueRitems;
//
//	PassConstants mMainPassCB;
//
//	UINT mPassCbvOffset;
//
//	bool mIsWireframe;
//
//	DirectX::XMFLOAT3 mEyePos;
//	DirectX::XMFLOAT4X4 mView;
//	DirectX::XMFLOAT4X4 mProj;
//
//	float mTheta;
//	float mPhi;
//	float mRadius;
//
//	POINT mLastMousePos;
//};