typedef uint8_t* MemReturnType;
typedef uint16_t MemSizeType;

typedef struct MemHandlerType
{
    uint8_t* MemStart;
    uint8_t* MemEnd;
    uint8_t* CurrAddr;
    uint8_t* FreeBytes;
} MemHandlerType;