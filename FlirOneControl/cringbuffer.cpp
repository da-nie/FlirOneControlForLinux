//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cringbuffer.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CRingBuffer::CRingBuffer(uint32_t size)
{
 Buffer=new uint8_t[size+1];
 Reset();
 Size=size;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CRingBuffer::~CRingBuffer()
{
 delete[](Buffer);
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//добавить байт в кольцевой буфер
//----------------------------------------------------------------------------------------------------
void CRingBuffer::PushByte(uint8_t b)
{
 Buffer[Head]=b;
 Head++;
 if (Head==Size) Head=0;
 if (Head==Tail) Tail++;
 if (Tail==Size) Tail=0;
}
//----------------------------------------------------------------------------------------------------
//забрать байт из кольцевого буфера
//----------------------------------------------------------------------------------------------------
bool CRingBuffer::PopByte(uint8_t *b)
{
 if (Head==Tail) return(false);
 *b=Buffer[Tail];
 Tail++;
 if (Tail==Size) Tail=0;
 return(true);
}

//----------------------------------------------------------------------------------------------------
//забрать два байта из кольцевого буфера
//----------------------------------------------------------------------------------------------------
bool CRingBuffer::PopShort(uint16_t *s)
{
 if (PopByte((uint8_t*)(s)+0)==false) return(false);
 if (PopByte((uint8_t*)(s)+1)==false) return(false);
 return(true);
}

//----------------------------------------------------------------------------------------------------
//получить сколько байт в кольцевом буфере
//----------------------------------------------------------------------------------------------------
uint32_t CRingBuffer::GetDataSize(void) const
{
 if (Head<Tail) return(Size-Tail+Head);
 return(Head-Tail);
}
//----------------------------------------------------------------------------------------------------
//получить позицию головы буфера
//----------------------------------------------------------------------------------------------------
uint32_t CRingBuffer::GetHeadPos(void) const
{
 return(Head);
}
//----------------------------------------------------------------------------------------------------
//получить позицию хвоста буфера
//----------------------------------------------------------------------------------------------------
uint32_t CRingBuffer::GetTailPos(void) const
{
 return(Tail);
}
//----------------------------------------------------------------------------------------------------
//получить общий размер буфера
//----------------------------------------------------------------------------------------------------
uint32_t CRingBuffer::GetBufferSize(void) const
{
 return(Size);
}
//----------------------------------------------------------------------------------------------------
//удалить данные из буфера
//----------------------------------------------------------------------------------------------------
void CRingBuffer::Reset(void)
{
 Head=0;
 Tail=0;
}
//----------------------------------------------------------------------------------------------------
//получить значение из буфера
//----------------------------------------------------------------------------------------------------
uint8_t CRingBuffer::GetByte(uint32_t pos) const
{
 if (pos>=Size) return(0);
 return(Buffer[pos]);
}
//----------------------------------------------------------------------------------------------------
//задать позицию хвоста буфера
//----------------------------------------------------------------------------------------------------
void CRingBuffer::SetTailPos(uint32_t pos)
{
 if (pos>=Size) return;
 Tail=pos;
}
//----------------------------------------------------------------------------------------------------
//задать позицию головы буфера
//----------------------------------------------------------------------------------------------------
void CRingBuffer::SetHeadPos(uint32_t pos)
{
 if (pos>=Size) return;
 Head=pos;
}

