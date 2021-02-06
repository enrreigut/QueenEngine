#include "BaseEnity.h"

namespace Queen
{
	namespace Entity
	{

		BaseEnity* base_entity = nullptr;

		BaseEnity::BaseEnity()
		{
			if(base_entity == nullptr)
				base_entity = this;
		}

		BaseEnity::~BaseEnity()
		{
			delete base_entity;
		}

	}
}