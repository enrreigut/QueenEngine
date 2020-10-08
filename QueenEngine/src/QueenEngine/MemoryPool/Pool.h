#pragma once

#include <memory>

namespace Queen
{
	namespace Memory
	{
		struct Block
		{
			Block* next;
		};

		class Pool
		{
		public:

			Pool(size_t blocksPerPool);

			void* Allocate(size_t blockSize);
			void Deallocate(void* block, size_t size);

		private:
			size_t m_BlocksPerPool;
			Block* m_AllocPtr = nullptr;

			Block* AllocateBlock(size_t size);
		};
	}
}