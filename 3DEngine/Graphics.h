#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "WinFixed.h"
#include "WinException.h"
#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

class Graphics
{
public:
	Graphics(HWND hwnd);

	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept
	{
		const float color[] = { red, green, blue, 1.0f };
		pContext->ClearRenderTargetView(pTarget.Get(), color);
	}

	unsigned int GetRefreshRate() const noexcept;
	void SetRefreshRate(int refreshRate) noexcept;

private:
	wrl::ComPtr<ID3D11Device> pDevice = NULL;
	wrl::ComPtr<IDXGISwapChain> pSwap = NULL;
	wrl::ComPtr<ID3D11DeviceContext> pContext = NULL;
	wrl::ComPtr<ID3D11RenderTargetView> pTarget = NULL;
	unsigned int refreshRate = 1u;
};

#endif