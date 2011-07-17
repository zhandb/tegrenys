#ifndef TGDXVertexBuffer_h__
#define TGDXVertexBuffer_h__

#include <wtypes.h>
#include <d3d9.h>

struct TGPrimitiveVertex
{
	FLOAT x, y, z;   // ������� �������
	DWORD color;        // ���� �������
	FLOAT tu, tv;        //���������� ��������
};
//-----------------------------------------------------------------------------
#define TGPrimitiveVertex_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//-----------------------------------------------------------------------------

class TGDXVertexBuffer
{
public:
	TGDXVertexBuffer();
	~TGDXVertexBuffer();
	//�������� � ��������� ������� Vertex-������ � ����������� ������
	HRESULT Resize(DWORD new_vertex_buffer_size); 
	//���������� ������, �������� ������������ ����� ��� ��������� ��������� ��� ��������� ����������
	TGPrimitiveVertex* Lock(DWORD start_index = 0, DWORD count = 0);
	//�������������
	void Unlock();
	//���������� �������� � �����, ��� ������������� � ���������� ������� ������
	void AddVertex(TGPrimitiveVertex* vertex);
	//������� ���������� ��������� � ������
	DWORD GetVerticesCount();
	//��������� �� ������ IDirect3DVertexBuffer9
	IDirect3DVertexBuffer9* GetVertexBuffer();
	//����� ���������� ��������� � ������
	void ClearVertexBuffer();
	//����� ���������� � ������� ��� ������
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