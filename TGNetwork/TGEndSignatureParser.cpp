//---------------------------------------------------------------------
#include "TGEndSignatureParser.h"
#include "..\TGSystem\TGBufferPool.h"
//---------------------------------------------------------------------
TGEndSignatureParser::TGEndSignatureParser(QByteArray signature)
{	
	SignatureCounter = 0;
	SetSignature(signature);
}
//---------------------------------------------------------------------
TGEndSignatureParser::~TGEndSignatureParser()
{

}
//---------------------------------------------------------------------
void TGEndSignatureParser::OnDataReceived(TGDataFragment data_fragment)
{
	const char* data_ptr = data_fragment.Data->GetConstData();
	
	bool use_full_buffer = true;

	for (uint32_t i = data_fragment.StartOffset; i < data_fragment.StartOffset + data_fragment.Size; ++i)
	{
		if (data_ptr[i] == Signature[SignatureCounter])
		{
			SignatureCounter++;
			if (SignatureCounter == Signature.length())
			{
				SignatureCounter = 0;
				ParserDataList.push_back(TGDataFragment(data_fragment.StartOffset, data_fragment.Data, i - data_fragment.StartOffset - 1));

				PTGBuffer buffer = new TGBuffer();
				for (TGDataFragmentList::iterator k = ParserDataList.begin(); k != ParserDataList.end(); ++k)
				{
					buffer->Append(k->StartOffset, k->Data, k->Size);
				}

				ParseRequest(buffer);
				ParserDataList.clear();

				if (CurrentParserID)
				{
					ParserDataList.push_back(TGDataFragment(i + 1, data_fragment.Data, data_fragment.Size - i - 1));
					PromoteData();
				}
	
				use_full_buffer = false;
			}
		}
		else
		{
			SignatureCounter = 0;
		}
	}

	if (use_full_buffer)
	{
		ParserDataList.push_back(TGDataFragment(data_fragment.StartOffset, data_fragment.Data, data_fragment.Size));
	}
}
//---------------------------------------------------------------------
void TGEndSignatureParser::ParseRequest(PTGBuffer buffer)
{
	char* data_ptr = (char*)buffer->GetConstData();
	uint32_t data_size = buffer->GetDataSize();

	PTGTextLineRequest request = new TGTextLineRequest();
	request->RequestBuffer = buffer;

	TGTextRequestLine first_line;
	first_line.TagName = data_ptr;
	first_line.TagValue = NULL;

	request->RequestLines.push_back(first_line);

	for (uint32_t i = 0; i < data_size - 1; ++i)
	{
		if (data_ptr[i] == ':' && data_ptr[i + 1] == ' ')
		{
			data_ptr[i] = 0;
			request->RequestLines.back().TagValue = data_ptr + (i + 2);
		}
		else
		{
			if (data_ptr[i] == '\r' && data_ptr[i + 1] == '\n')
			{
				data_ptr[i] = 0;
				if (i < data_size - 2)
				{
					TGTextRequestLine line;
					line.TagName = data_ptr + (i + 2);
					line.TagValue = NULL;
					request->RequestLines.push_back(line);
				}
			}
		}
	}
	ProcessRequest(request);
}
//---------------------------------------------------------------------
void TGEndSignatureParser::ProcessRequest(PTGTextLineRequest request)
{

}
//---------------------------------------------------------------------
void TGEndSignatureParser::SetSignature(QByteArray signature)
{
	Signature = signature;
}
//---------------------------------------------------------------------
