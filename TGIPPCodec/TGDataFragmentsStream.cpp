#include "TGDataFragmentsStream.h"
//---------------------------------------------------------------------------

TGDataFragmentsStream::TGDataFragmentsStream(TGDataFragmentList& source)
{
	CurrentOffset = 0;
	Source = source;

	CurrentFragment = Source.begin();

	if (!Source.empty())
	{
		CurrentOffset = Source.front().StartOffset;
	}

	
}
//---------------------------------------------------------------------------

TGDataFragmentsStream::~TGDataFragmentsStream()
{

}
//---------------------------------------------------------------------------

JERRCODE TGDataFragmentsStream::Close()
{
	return JPEG_OK;
}
//---------------------------------------------------------------------------

JERRCODE TGDataFragmentsStream::Seek(long offset, int origin)
{
	JERRCODE jerr = JPEG_OK;

	/*uint32_t current_offset;;
	TGDataFragmentList::iterator current_fragment;
	bool move_back = (offset < 0);
	offset = abs(offset);

	switch(origin)
	{
	case UIC_SEEK_CUR:
		{
			current_offset = CurrentOffset;
			current_fragment = CurrentFragment;
		}
		break;

	case UIC_SEEK_SET:
		{
			current_fragment = Source.begin();
			current_offset = current_fragment->StartOffset;
		}
		break;

	case UIC_SEEK_END:
		{
			current_fragment = Source.end() - 1;
			current_offset = current_fragment->StartOffset + current_fragment->Size;
		}
		break;

	default:
		return JPEG_NOT_IMPLEMENTED;
	}

	while (offset != 0)
	{
		if (move_back)
		{
			uint32_t bytes_in_curr_fragment_left = current_offset - current_fragment->StartOffset;
			uint32_t bytes_to_seek = offset > bytes_in_curr_fragment_left ? bytes_in_curr_fragment_left : offset;
			offset -= bytes_to_seek;
			current_offset -= bytes_to_seek;
			if (offset == 0)
				break;

			if (current_fragment != Source.begin())
			{
				current_fragment--;
				current_offset = current_fragment->Size;
			}
			else
			{
				jerr = JPEG_ERR_BUFF;
				break;
			}
		}
		else
		{
			uint32_t bytes_in_curr_fragment_left = current_fragment->Size - current_offset + current_fragment->StartOffset;
			uint32_t bytes_to_seek = offset > bytes_in_curr_fragment_left ? bytes_in_curr_fragment_left : offset;
			offset -= bytes_to_seek;
			current_offset += bytes_to_seek;
			
			if (bytes_to_seek == bytes_in_curr_fragment_left)
			{
				current_fragment++;

				if (current_fragment != Source.end())
				{
					current_offset = current_fragment->StartOffset;
				}
				else
				{
					jerr = JPEG_ERR_BUFF;
					break;
				}
			}

			if (offset == 0)
				break;
			
		}
	}

	if (jerr == JPEG_OK)
	{
		CurrentFragment = current_fragment;
		CurrentOffset = current_offset;
	}*/

	return jerr;
}
//---------------------------------------------------------------------------

JERRCODE TGDataFragmentsStream::Read(void* buf, uic_size_t len, uic_size_t* cnt)
{
	JERRCODE jerr = JPEG_OK;

	/**cnt = 0;
	
	while (len)
	{
		if (CurrentFragment != Source.end())
		{
			uint32_t bytes_in_curr_fragment_left = CurrentFragment->Size - CurrentOffset + CurrentFragment->StartOffset;
			uint32_t bytes_to_read = len > bytes_in_curr_fragment_left ? bytes_in_curr_fragment_left : len;
			len -= bytes_to_read;
			memcpy(buf + cnt, CurrentFragment->Data + CurrentFragment, bytes_to_read);
			cnt += bytes_to_read;

			if (len == 0)
				break;

			jerr = Seek(bytes_to_read, UIC_SEEK_CUR);
			if (jerr != JPEG_OK)
				break;

		}
	}*/

	return jerr;
}
//---------------------------------------------------------------------------

JERRCODE TGDataFragmentsStream::TellPos(long* pos)
{
	*pos = 0;

	*pos += CurrentOffset + CurrentFragment->StartOffset;


	return JPEG_OK;
}