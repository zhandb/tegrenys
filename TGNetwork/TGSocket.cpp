#include "TGSocket.h"
//---------------------------------------------------------------------
TGSocket::TGSocket(UID module_uid, PTGModule system) : TGModule(module_uid, system)
{
	SocketHandle = INVALID_SOCKET;

	ReconnectTime = 5000;

	SocketEvent = WSACreateEvent();
	SetEvent(SocketEvent);

	ConnectTime.start();

	InitSocket();

	State = Waiting;
}
//---------------------------------------------------------------------
TGSocket::~TGSocket()
{

}
//---------------------------------------------------------------------
void TGSocket::CloseSocket()
{
	if (SocketHandle != INVALID_SOCKET)
	{
		CancelIo((HANDLE) SocketHandle);
		closesocket(SocketHandle);
		SocketHandle = INVALID_SOCKET;
	}
}
//---------------------------------------------------------------------
void TGSocket::InitSocket()
{
	if (SocketHandle != INVALID_SOCKET)
		CloseSocket();

	SocketHandle =  WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	WSAEventSelect(SocketHandle, SocketEvent, FD_READ | FD_CONNECT | FD_CLOSE | FD_WRITE);

	Bind();
}
//---------------------------------------------------------------------
void TGSocket::DoConnect()
{
	InitSocket();
	
	PHOSTENT remote_host = NULL;

	std::string host = Host.toStdString();

	//if (isalpha(host[0]))
	{   
		remote_host = gethostbyname(host.c_str());
	}
	/*else  
	{ 
		unsigned int addr = inet_addr(host.c_str());
		remote_host = gethostbyaddr((char *) &addr, 4, AF_INET);
	}*/

	SOCKADDR_IN dest_sin;
	memset(&dest_sin, 0, sizeof(dest_sin));
	dest_sin.sin_family = AF_INET;
	dest_sin.sin_addr.s_addr = INADDR_ANY;
	dest_sin.sin_port = 0;

	State = SocketError;

	ConnectTime.start();

	dest_sin.sin_family = AF_INET;
	dest_sin.sin_port = htons(Port);

	if(remote_host != NULL)
	{
		memcpy((char FAR *)&(dest_sin.sin_addr), remote_host->h_addr, remote_host->h_length);
	};

	if (::connect(SocketHandle, (SOCKADDR *)&dest_sin, sizeof(SOCKADDR)) != SOCKET_ERROR || WSAGetLastError() == WSAEWOULDBLOCK)
	{
		State = Connecting;
		OutputDebugStringA("Connecting\r\n");
	}
	else
	{
		int r = WSAGetLastError();
		r = r;
	}
}
//---------------------------------------------------------------------
void TGSocket::OnSocketConnect(TGString host, uint32_t remote_port, uint32_t localport)
{
	Host = host;
	Port = remote_port;

	if (State == Waiting)
		State = StartConnect;
}
//---------------------------------------------------------------------
void TGSocket::Poll()
{
	if (State == SocketError && ReconnectTime && ConnectTime.elapsed() > ReconnectTime)
	{
		State = StartConnect;
	}

	if (State == StartConnect)
	{
		DoConnect();
	}

	WSANETWORKEVENTS netEvents;
	memset(&netEvents, 0, sizeof(netEvents));

	if(WSAEnumNetworkEvents(SocketHandle, SocketEvent, &netEvents) != SOCKET_ERROR)
	{
		sockaddr Addr;

		int AddrSize = sizeof(Addr);

		if (netEvents.lNetworkEvents & FD_CONNECT) 
		{
			if (netEvents.iErrorCode[FD_CONNECT_BIT] == 0)
			{
				State = Connected;
				OutputDebugStringA("Connected\r\n");

				emit SocketConnected();
			}
			else
			{
				State = SocketError;
				ConnectTime.restart();
				OutputDebugStringA("Connection error\r\n");
			}
		}

		if (netEvents.lNetworkEvents & FD_READ) 
		{
			do 
			{
				PTGBuffer buffer = Pool->Allocate();
				buffer->Allocate(1000);

				int s = recv(SocketHandle, (char*)buffer->GetConstData(), buffer->GetBufferSize(), 0);
				if (s == -1)
				{
					int err = WSAGetLastError();
					if (err != WSAEWOULDBLOCK)
					{
						char c[100];
						sprintf_s(c, 100, "Err %i\r\n", err);
						OutputDebugStringA(c);
					}
					break;
				}
				else
				{
					if (!s) break;

					/*char c[100];
					sprintf_s(c, 100, "Read %i\r\n", s);
					OutputDebugStringA(c);*/
					buffer->Allocate(s);

					emit DataReceived(buffer);
				}
			} while (true);
		}

		if (netEvents.lNetworkEvents & FD_WRITE) 
		{
			OutputDebugStringA("Written\r\n");
			
			if (Buffers.size())
				Buffers.pop_front();
			
			if (Buffers.size())
				WriteFrontBuffer();
		}

		if (netEvents.lNetworkEvents & FD_CLOSE)
		{
			OutputDebugStringA("Disconnected\r\n");
			CloseSocket();
			State = StartConnect;
			emit SocketDisconnected();
		}
	}
}
//---------------------------------------------------------------------
void TGSocket::Bind()
{
	SOCKADDR_IN dest_sin;
	memset(&dest_sin, 0, sizeof(dest_sin));
	dest_sin.sin_family = AF_INET;
	dest_sin.sin_addr.s_addr = INADDR_ANY;
	dest_sin.sin_port = 0;

	if (bind(SocketHandle, (struct sockaddr *)&dest_sin, sizeof(dest_sin)) == SOCKET_ERROR)
	{
		State = FatalError;
		OutputDebugStringA("Bind Error\r\n");
	}
}
//---------------------------------------------------------------------
void TGSocket::Write(PTGBuffer data)
{
	Buffers.push_back(data);
	if (Buffers.size() == 1)
		WriteFrontBuffer();
}
//---------------------------------------------------------------------
void TGSocket::WriteFrontBuffer()
{
	send(SocketHandle, Buffers.front()->GetConstData(), Buffers.front()->GetDataSize(), 0);
}
//---------------------------------------------------------------------


