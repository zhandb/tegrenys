#include "TGDXVertexBuffer.h"
//---------------------------------------------------------------------
TGDXVertexBuffer::TGDXVertexBuffer()
{
	VertexBuffer = NULL;
	VerticesCount = 0;
	Device = NULL;
	Release();
}
//---------------------------------------------------------------------
TGDXVertexBuffer::~TGDXVertexBuffer()
{
	Release();
}
//---------------------------------------------------------------------
HRESULT TGDXVertexBuffer::Resize(DWORD new_vertex_buffer_size)
{
	HRESULT res = S_OK;

	if (new_vertex_buffer_size > VertexBufferSize) //Если требуемый размер не больше текущего, то ничего не делаем
	{
		IDirect3DVertexBuffer9* tmp_vertex_buffer = NULL;
		TGPrimitiveVertex* tmp_vertex_buffer_ptr = NULL;

		//Создаем буфер нового размера

		if (FAILED(Device->CreateVertexBuffer(new_vertex_buffer_size * sizeof(TGPrimitiveVertex),
			0, TGPrimitiveVertex_FVF, D3DPOOL_DEFAULT, &tmp_vertex_buffer, NULL)))
		{
			res = E_FAIL;
		}
		else
		{
			//Если старый буфер существует и не был блокирован, блокируем его для копирования данных
			if (VertexBuffer && !IsLocked) 
			{
				VertexBuffer->Lock(0, 0, (void**)&VertexBufferPtr, 0);
			}

			//Блокируем также и новый буфер

			tmp_vertex_buffer->Lock(0, 0, (void**)&tmp_vertex_buffer_ptr, 0);

			//Если оба буфера заблокировались, копируем данные 

			if (VertexBufferPtr && tmp_vertex_buffer_ptr)
			{
				memcpy(tmp_vertex_buffer_ptr, VertexBufferPtr, VerticesCount * sizeof(TGPrimitiveVertex));

				//Разблокируем и удаляем старый буфер

				VertexBuffer->Unlock();
				Release();	
			}

			//Если старый буфер до ресайза не был заблокирован, то разблокируем и новый буфер
			//В противном случае, передаем указатель на новый буфер

			if (!IsLocked)
				tmp_vertex_buffer->Unlock();
			else
				VertexBufferPtr = tmp_vertex_buffer_ptr;

			VertexBuffer = tmp_vertex_buffer;
			VertexBufferSize = new_vertex_buffer_size;
		}
	}

	return res;
}
//---------------------------------------------------------------------
TGPrimitiveVertex* TGDXVertexBuffer::Lock(DWORD start_index /*= 0*/, DWORD count /*= 0*/)
{
	if (!IsLocked)
	{
		VertexBuffer->Lock(start_index * sizeof(TGPrimitiveVertex), count * sizeof(TGPrimitiveVertex), (void**)&VertexBufferPtr, 0);
		IsLocked = true;
	}

	return VertexBufferPtr;
}
//---------------------------------------------------------------------
void TGDXVertexBuffer::Unlock()
{
	if (IsLocked)
	{
		VertexBuffer->Unlock();
		IsLocked = false;
	}
}
//---------------------------------------------------------------------
void TGDXVertexBuffer::AddVertex(TGPrimitiveVertex* vertex)
{
	if (VertexBufferSize == VerticesCount)
		Resize(VerticesCount + 1000);

	TGPrimitiveVertex* ptr = Lock();
	ptr[VerticesCount] = *vertex;
	VerticesCount++;
}
//---------------------------------------------------------------------
DWORD TGDXVertexBuffer::GetVerticesCount()
{
	return VerticesCount;
}
//---------------------------------------------------------------------
IDirect3DVertexBuffer9* TGDXVertexBuffer::GetVertexBuffer()
{
	return VertexBuffer;
}
//---------------------------------------------------------------------
void TGDXVertexBuffer::ClearVertexBuffer()
{
	VerticesCount = 0;
}
//---------------------------------------------------------------------
void TGDXVertexBuffer::SetD3DDevice(IDirect3DDevice9 *device)
{
	DWORD curr_buffer_size = VertexBufferSize;
	Release();
	Device = device;
	if (Device)
	{
		Resize(curr_buffer_size ? curr_buffer_size : 1);
	}
}
//---------------------------------------------------------------------
void TGDXVertexBuffer::Release()
{
	if (VertexBuffer)
	{
		VertexBuffer->Release();
	}

	VertexBuffer = NULL;
	VertexBufferSize = 0;
	IsLocked = false;
	VertexBufferPtr = 0;
}