#ifndef TGDXVertexBuffer_h__
#define TGDXVertexBuffer_h__

#include <wtypes.h>
#include <d3d9.h>

struct TGPrimitiveVertex
{
	FLOAT x, y, z;   // Позиция вершины
	DWORD color;        // Цвет вершины
	FLOAT tu, tv;        //Координаты текстуры
};
//-----------------------------------------------------------------------------
#define TGPrimitiveVertex_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//-----------------------------------------------------------------------------

class TGDXVertexBuffer
{
public:
	TGDXVertexBuffer();
	~TGDXVertexBuffer();
	//Создание и изменение размера Vertex-буфера с сохранением данных
	HRESULT Resize(DWORD new_vertex_buffer_size); 
	//Блокировка буфера, возможен многократный вызов для получения указателя без повторной блокировки
	TGPrimitiveVertex* Lock(DWORD start_index = 0, DWORD count = 0);
	//Разблокировка
	void Unlock();
	//Добавление вертекса в буфер, при необходимости с изменением размера буфера
	void AddVertex(TGPrimitiveVertex* vertex);
	//Текущее количество вертексов в буфере
	DWORD GetVerticesCount();
	//Указатель на объект IDirect3DVertexBuffer9
	IDirect3DVertexBuffer9* GetVertexBuffer();
	//Сброс количества вертексов в буфере
	void ClearVertexBuffer();
	//Смена устройства с потерей все данных
	void SetD3DDevice(IDirect3DDevice9 *device);
private:
	void Release();
private:
	bool IsLocked;
	DWORD VertexBufferSize;
	DWORD VerticesCount;
	IDirect3DVertexBuffer9* VertexBuffer;
	TGPrimitiveVertex* VertexBufferPtr;
	IDirect3DDevice9* Device;
};

#endif // TGDXVertexBuffer_h__