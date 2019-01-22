#include "stdafx.h"
//
//#include <iostream>
//#include <D3d12.h>
//#include <dxgi1_4.h>
//#include <Windows.h>
//#include <wrl.h>
//#include <assert.h>
//
//#include "d3dx12.h"
//
//#include "Utils.h"
//
//using namespace Microsoft::WRL;
//
//
//
//void exec()
//{
//	std::cout << "Hello DirectX12 World!\n";
//
//#if defined(DEBUG) || defined(_DEBUG)
//	// Enable the D3D12 debug layer.
//	{
//		ComPtr<ID3D12Debug> debugController;
//		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf())));
//		debugController->EnableDebugLayer();
//	}
//#endif
//
//	// vars
//	const int SwapChainBufferCount = 2;
//	
//	ComPtr<IDXGIFactory4> factory;
//	ComPtr<ID3D12Device> device;
//	ComPtr<IDXGIAdapter> warpAdapter;
//	ComPtr<ID3D12Fence> fence;
//	ComPtr<ID3D12CommandQueue> commandQueue;
//	ComPtr<ID3D12CommandAllocator> directCmdListAlloc;
//	ComPtr<ID3D12GraphicsCommandList> commandList;
//	ComPtr<IDXGISwapChain> swapChain;
//	ComPtr<ID3D12DescriptorHeap> mRtvHeap;
//	ComPtr<ID3D12DescriptorHeap> mDsvHeap;
//	ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
//	ComPtr<ID3D12Resource> mDepthStencilBuffer;
//
//	HWND mhMainWnd = nullptr;
//
//	UINT rtvDescriptorSize;
//	UINT dsvDescriptorSize;
//	UINT cbvSrvDescriptorSize;
//	UINT m4xMsaaQuality;
//	const UINT clientWidth = 1024;
//	const UINT clientHeight = 768;
//	bool m4xMsaaState = true;
//	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
//	D3D12_RECT mScissorRect;
//	double mSecondsPerCount;
//	
//	int mCurrBackBuffer = 0;
//
//	// create factory
//	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(factory.GetAddressOf())));
//
//
//	// create device
//	ThrowIfFailed(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(device.GetAddressOf())));
//
//	// create fence
//	ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(fence.GetAddressOf())));
//
//	// cache descriptor's size
//	rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
//	dsvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
//	cbvSrvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
//
//	// MSAA 4x support check
//	DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
//	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
//	msQualityLevels.Format = backBufferFormat;
//	msQualityLevels.SampleCount = 4;
//	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
//	msQualityLevels.NumQualityLevels = 0;
//	ThrowIfFailed(device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msQualityLevels, sizeof(msQualityLevels)));
//
//	m4xMsaaQuality = msQualityLevels.NumQualityLevels;
//	assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");
//
//	// create command queue, command allocator, command list
//	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
//	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
//	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//	ThrowIfFailed(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(commandQueue.GetAddressOf())));
//	ThrowIfFailed(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(directCmdListAlloc.GetAddressOf())));
//	ThrowIfFailed(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, directCmdListAlloc.Get(), nullptr, IID_PPV_ARGS(commandList.GetAddressOf())));
//
//	// Start off in a closed state. This is because the	first time we
//	// refer to the command list we will Reset it, and it needs to be
//	// closed before calling Reset.
//	commandList->Close();
//
//
//	// create swap chain
//
//	// Release the previous swap chain we will be recreating.
//	swapChain.Reset();
//
//	DXGI_SWAP_CHAIN_DESC sd;
//	sd.BufferDesc.Width = clientWidth;
//	sd.BufferDesc.Height = clientHeight;
//	sd.BufferDesc.RefreshRate.Numerator = 60;
//	sd.BufferDesc.RefreshRate.Denominator = 1;
//	sd.BufferDesc.Format = backBufferFormat;
//	sd.BufferDesc.ScanlineOrdering =
//		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//	sd.BufferDesc.Scaling =
//		DXGI_MODE_SCALING_UNSPECIFIED;
//	sd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
//	sd.SampleDesc.Quality = m4xMsaaState ?
//		(m4xMsaaQuality - 1) : 0;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.BufferCount = SwapChainBufferCount;
//	sd.OutputWindow = mhMainWnd;
//	sd.Windowed = true;
//	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
//	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//
//	// Note: Swap chain uses queue to perform flush.
//	ThrowIfFailed(factory->CreateSwapChain(commandQueue.Get(), &sd, swapChain.GetAddressOf()));
//
//	// Create descriptors heap
//	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
//	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
//	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
//	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//	rtvHeapDesc.NodeMask = 0;
//	ThrowIfFailed(device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(mRtvHeap.GetAddressOf())));
//
//	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
//	dsvHeapDesc.NumDescriptors = 1;
//	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
//	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
//	dsvHeapDesc.NodeMask = 0;
//	ThrowIfFailed(device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(mDsvHeap.GetAddressOf())));
//
//	//D3D12_CPU_DESCRIPTOR_HANDLE	CurrentBackBufferView()const
//	{
//		// CD3DX12 constructor to offset to the RTV of the current back buffer.
//			/*return*/ CD3DX12_CPU_DESCRIPTOR_HANDLE(
//				mRtvHeap->GetCPUDescriptorHandleForHeapStart(),// handle start
//				mCurrBackBuffer, // index to offset
//				rtvDescriptorSize); // byte size of descriptor
//	} 
//	//D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const
//	{
//		/*return*/ mDsvHeap->GetCPUDescriptorHandleForHeapStart();
//	}
//
//	// Create Render Target View
//	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
//	for (UINT i = 0; i < SwapChainBufferCount; i++)
//	{
//		// Get the ith buffer in the swap chain.
//		ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&mSwapChainBuffer[i])));
//		// Create an RTV to it.
//		device->CreateRenderTargetView(mSwapChainBuffer[i].Get(), nullptr, rtvHeapHandle);
//		// Next entry in heap.
//		rtvHeapHandle.Offset(1, rtvDescriptorSize);
//	}
//
//	// Create the depth/stencil buffer and view.
//	D3D12_RESOURCE_DESC depthStencilDesc;
//	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
//	depthStencilDesc.Alignment = 0;
//	depthStencilDesc.Width = clientWidth;
//	depthStencilDesc.Height = clientHeight; depthStencilDesc.DepthOrArraySize = 1;
//	depthStencilDesc.MipLevels = 1;
//	depthStencilDesc.Format = mDepthStencilFormat;
//	depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
//	depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
//	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
//	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
//	
//	D3D12_CLEAR_VALUE optClear;
//	optClear.Format = mDepthStencilFormat;
//	optClear.DepthStencil.Depth = 1.0f;
//	optClear.DepthStencil.Stencil = 0;
//	
//	ThrowIfFailed(device->CreateCommittedResource(
//		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
//		D3D12_HEAP_FLAG_NONE,
//		&depthStencilDesc,
//		D3D12_RESOURCE_STATE_COMMON,
//		&optClear,
//		IID_PPV_ARGS(mDepthStencilBuffer.GetAddressOf())));
//	
//	// Create descriptor to mip level 0 of entire resource	using the
//	// format of the resource.
//	device->CreateDepthStencilView(
//		mDepthStencilBuffer.Get(),
//		nullptr,
//		mDsvHeap->GetCPUDescriptorHandleForHeapStart()); //DepthStencilView()
//	
//	// Transition the resource from its initial state to be used as a depth buffer.
//	commandList->ResourceBarrier(
//		1,
//		&CD3DX12_RESOURCE_BARRIER::Transition(
//			mDepthStencilBuffer.Get(),
//			D3D12_RESOURCE_STATE_COMMON,
//			D3D12_RESOURCE_STATE_DEPTH_WRITE));
//
//	// set Viewport
//	D3D12_VIEWPORT vp;
//	vp.TopLeftX = 0.0f;
//	vp.TopLeftY = 0.0f;
//	vp.Width = static_cast<float>(clientWidth);
//	vp.Height = static_cast<float>(clientHeight);
//	vp.MinDepth = 0.0f;
//	vp.MaxDepth = 1.0f;
//	commandList->RSSetViewports(1, &vp);
//
//	// Set Scissor rectangle
//	mScissorRect = { 0, 0, clientWidth / 2, clientHeight / 2	};
//	commandList->RSSetScissorRects(1, &mScissorRect);
//
//	////////////////////////////////////////////////
//	// ANIMATION
//	////////////////////////////////////////////////
//
//	// Performance timer
//	__int64 currTime;
//	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
//
//	__int64 countsPerSec;
//	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
//
//	mSecondsPerCount = 1.0 / (double)countsPerSec;
//
//	//valueInSecs = valueInCounts * mSecondsPerCount;
//
//	__int64 A = 0;
//	QueryPerformanceCounter((LARGE_INTEGER*)&A);
//	/* Do work */
//	__int64 B = 0;
//	QueryPerformanceCounter((LARGE_INTEGER*)&B);
//
//}