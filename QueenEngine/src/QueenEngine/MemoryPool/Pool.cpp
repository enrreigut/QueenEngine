#include "Pool.h"

#include <iostream>

namespace Queen
{
	namespace Memory
	{
		Pool::Pool(size_t blocksPerPool)
			:m_BlocksPerPool(blocksPerPool)
		{

		}

		void* Pool::Allocate(size_t blockSize)
		{
			if (m_AllocPtr == nullptr)
				m_AllocPtr = AllocateBlock(blockSize);

			Block* freeBlock = m_AllocPtr;
			m_AllocPtr = m_AllocPtr->next;
			return freeBlock;
		}

		Block* Pool::AllocateBlock(size_t blockSize)
		{
			size_t poolSize = m_BlocksPerPool * blockSize;

			std::cout << "Allocating Pool of " << poolSize << " bytes" << std::endl;

			Block* beginBlock = (Block*)malloc(poolSize);

			Block* block = beginBlock;
			char* ptrAux = (char*)beginBlock;

			for (int i = 1; i < m_BlocksPerPool; ++i)
			{
				ptrAux += blockSize;
				block->next = (Block*)ptrAux;
				block = block->next;
			}

			block->next = nullptr;

			return beginBlock;
		}

		void Pool::Deallocate(void* block, size_t size)
		{
			Block* b = (Block*)block;
			b->next = m_AllocPtr;
			m_AllocPtr = (Block*)block;
		}
	}
}