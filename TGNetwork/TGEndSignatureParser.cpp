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
	int signature_bytes_count = SearchForSignature(data_fragment);

	
	//TODO: Что если сигнатура встречается несколько раз?

	//Если сигнатура в данном фрагменте не завершена
	if (signature_bytes_count == -1)
	{
		//Сохраним весь фрагмент
		ParserDataList.push_back(TGDataFragment(data_fragment.StartOffset, data_fragment.Data, data_fragment.Size));
	}
	else
	{
		//иначе сохраним часть фрагмента, завершающуюся сигнатурой
		ParserDataList.push_back(TGDataFragment(data_fragment.StartOffset, data_fragment.Data, signature_bytes_count));

		/*PTGBuffer buffer = new TGBuffer();
		for (TGDataFragmentList::iterator k = ParserDataList.begin(); k != ParserDataList.end(); ++k)
		{
			buffer->Append(k->StartOffset, k->Data, k->Size);
		}*/
		
		//Уберем сигнатуру из дальнейшей обработки
		RemoveSignature();
		//Отработаем данные и избавимся от них
		ProcessRequest();
		ParserDataList.clear();

		//Передадим рекурсивно остаток фрагмента на дальнейшую обработку

		int bytes_left = data_fragment.Size - signature_bytes_count;
		if (bytes_left > 0)
		{
			const char* c = data_fragment.Data->GetConstData() + data_fragment.StartOffset + signature_bytes_count;
			ReceiveData(TGDataFragment(data_fragment.StartOffset + signature_bytes_count, data_fragment.Data, bytes_left));
		}
	}
}
//---------------------------------------------------------------------
//void TGEndSignatureParser::ParseRequest(PTGBuffer buffer)
//{
//	char* data_ptr = (char*)buffer->GetConstData();
//	uint32_t data_size = buffer->GetDataSize();
//
//	PTGTextLineRequest request = new TGTextLineRequest();
//	request->RequestBuffer = buffer;
//
//	TGTextRequestLine first_line;
//	first_line.TagName = data_ptr;
//	first_line.TagValue = NULL;
//
//	request->RequestLines.push_back(first_line);
//
//	for (uint32_t i = 0; i < data_size - 1; ++i)
//	{
//		if (data_ptr[i] == ':' && data_ptr[i + 1] == ' ')
//		{
//			data_ptr[i] = 0;
//			request->RequestLines.back().TagValue = data_ptr + (i + 2);
//		}
//		else
//		{
//			if (data_ptr[i] == '\r' && data_ptr[i + 1] == '\n')
//			{
//				data_ptr[i] = 0;
//				if (i < data_size - 2)
//				{
//					TGTextRequestLine line;
//					line.TagName = data_ptr + (i + 2);
//					line.TagValue = NULL;
//					request->RequestLines.push_back(line);
//				}
//			}
//		}
//	}
//	ProcessRequest(request);
//}
////---------------------------------------------------------------------
void TGEndSignatureParser::ProcessRequest()
{

}
//---------------------------------------------------------------------
void TGEndSignatureParser::SetSignature(QByteArray signature)
{
	Signature = signature;
}
//---------------------------------------------------------------------
int TGEndSignatureParser::SearchForSignature(TGDataFragment data_fragment)
{
	int res = -1;

	const char* data_ptr = data_fragment.Data->GetConstData() + data_fragment.StartOffset;

	for (uint32_t i = 0; i < data_fragment.Size; ++i)
	{
		//Если вся сигнатура собрана
		if (data_ptr[i] == Signature[SignatureCounter])
		{
			SignatureCounter++;
			if (SignatureCounter == Signature.length())
			{
				SignatureCounter = 0;
				res = i + 1; //Количество байт, включая сигнатуру
			}
		}
		else
		{
			SignatureCounter = 0;
		}
	}

	return res;
}
//---------------------------------------------------------------------
void TGEndSignatureParser::RemoveSignature()
{
	uint32_t sign_counter = Signature.length();
	//Удаляем с конца фрагменты данных, полностью состоящие из частей сигнатуры
	//Это возможно при малых размерах фрагментов или большой длине сигнатуры
	while (!ParserDataList.empty() && ParserDataList.back().Size <= sign_counter)
	{
		sign_counter -= ParserDataList.back().Size;
		ParserDataList.pop_back();
	}

	//Уменьшаем размер последнего фрагмента данных на размер остатка сигнатуры
	if (!ParserDataList.empty())
		ParserDataList.back().Size -= sign_counter;
}
//---------------------------------------------------------------------
