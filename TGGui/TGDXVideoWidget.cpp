#include "TGDXVideoWidget.h"
#include "TGBasePolygon.h"
#include "TGBaseRectangle.h"
#include "TGBaseTexturedRectangle.h"
#include "TGDXViewPort.h"
#include "TGDXPrimitiveLayer.h"

TGDXVideoWidget::TGDXVideoWidget() : TGBaseVideoWidget()
{
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DDevice = NULL;
	WindowHandle = winId();
	ReInitRequired = true;
	ReInitTimer.start();

	PP = new TGDXPrimitivePainter();
	
	/*TGBaseTexturedRectangle* p = new TGBaseTexturedRectangle(2);
	p->SetColor(QColor("red"));
	p->SetSize(QSizeF(0.3, 0.3));
	p->SetPos(TGPointF(-0.9, -0.9, 1.0));
	PP->AddPrimitive(p);

	TGBaseTextureDescriptor descr;
	descr.parent = NULL;
	descr.texture_size = QSize(32, 32);

	UID video_texture_id = PP->AddTexture(descr);

	TGBaseTexturedRectangle* p2 = new TGBaseTexturedRectangle(video_texture_id);
	p2->SetColor(QColor("red"));
	p2->SetSize(QSizeF(1.0, 1.0));
	p2->SetPos(TGPointF(-0.5, -0.5, 1.0));
	PP->AddPrimitive(p2);*/

	//video = PP->GetTexture(video_texture_id);

	
	startTimer(40);
}

TGDXVideoWidget::~TGDXVideoWidget()
{
	DeInitDevice();
	if (D3D)
	{
		D3D->Release();
		D3D = NULL;
	}
}
//---------------------------------------------------------------------
void TGDXVideoWidget::InitDevice()
{
	DeInitDevice();
	
	bool res = false;
	if (D3D && WindowHandle)
	{
		D3DPRESENT_PARAMETERS d3dpp = {};

		d3dpp.BackBufferWidth            = width();
		d3dpp.BackBufferHeight           = height();
		d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount            = 1;
		d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality         = 0;
		d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow              = WindowHandle;
		d3dpp.Windowed                   = TRUE;
		d3dpp.EnableAutoDepthStencil     = FALSE;
		d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
		d3dpp.Flags                      =  D3DPRESENTFLAG_VIDEO;

		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

		D3DCAPS9 Caps;

		HRESULT hrResult = 0;

		D3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL, &Caps);

		bool HardwareProcessing = (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT);

		D3DDISPLAYMODE disp_mode;
		D3D->GetAdapterDisplayMode(0, &disp_mode);

		D3DFORMAT formats[] = {D3DFMT_A8R8G8B8, D3DFMT_A1R5G5B5, D3DFMT_R5G6B5, D3DFMT_A2B10G10R10, D3DFMT_X8R8G8B8, D3DFMT_X1R5G5B5};
		UINT iMode = 0;

		for (iMode = 0; iMode < sizeof(formats) / sizeof(D3DFORMAT); ++iMode)
		{
			if (D3D_OK == D3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, disp_mode.Format, formats[iMode], TRUE))
			{
				d3dpp.BackBufferFormat = formats[iMode];
				hrResult = D3D->CreateDevice(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_HAL,
					WindowHandle,
					HardwareProcessing ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
					&d3dpp,
					&D3DDevice);           // возвращает созданное устройство

				if (SUCCEEDED(hrResult))
					break;
			}
		}

		if (SUCCEEDED(hrResult))
		{
			D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
			D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			D3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
			D3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

			res = true;
			ReInitRequired = false;

			((TGDXPrimitivePainter*)&*PP)->SetDevice(D3DDevice, QSize(width(), height()));
		}
		else
		{
			ReInitTimer.start();
		}
	}

	//LastWindowWidth  = width();
	//LastWindowHeight = height();

	//PP2->SetCanvasSize(QSize(width(), height()));
	//EventCommonWindowSizeChanged(LastWindowWidth, LastWindowHeight);
}
//---------------------------------------------------------------------
void TGDXVideoWidget::DeInitDevice()
{
	if (D3DDevice)
	{
		D3DDevice->Release();
		D3DDevice = NULL;
	};
}
//---------------------------------------------------------------------
void TGDXVideoWidget::timerEvent(QTimerEvent* event)
{
	if (ReInitRequired && ReInitTimer.elapsed() > 500)
	{
		InitDevice();
	}
	else
	{
		/*uchar data[32*32*4];
		for (int i = 0; i < 32*32*4; ++i)
		{
			data[i] = rand() % 255;
		}*/

		//PP->TextureManager->SetTextureImage(video, data, 128);

		Rendering();
	}
}
//---------------------------------------------------------------------
void TGDXVideoWidget::Rendering()
{
	if (D3DDevice)
	{
		PP->Build();
		PP->Render();

		HRESULT Res = D3DDevice->Present(0, 0, 0, 0);
		if (Res == D3DERR_DEVICELOST)
		{
			ReInitRequired = true;
		};
	}
}
//---------------------------------------------------------------------
void TGDXVideoWidget::resizeEvent(QResizeEvent* event)
{
	ReInitRequired = true;
	ReInitTimer.start();
}
//---------------------------------------------------------------------------

//void TGDXVideoWidget::AddViewport(UID uid, TGDataObject& config)
//{
//	PTGBaseViewport viewport = new TGDXViewport(config);
//	PP->AddViewport(uid, viewport);
//}
////---------------------------------------------------------------------------
//
//void TGDXVideoWidget::AddLayer(UID viewport_uid, UID layer_uid, TGDataObject& config)
//{
//	PTGBasePrimitiveLayer layer = new TGDXPrimitiveLayer(config);
//	PP->AddLayer(viewport_uid, layer_uid, layer);
//}
////---------------------------------------------------------------------
