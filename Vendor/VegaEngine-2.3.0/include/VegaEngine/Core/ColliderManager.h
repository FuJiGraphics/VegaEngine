#pragma once
#include "Core.h"
#include "Collider.h"

namespace fz {
	
	class ColliderManager
	{
		using iter = std::vector<Collider**>::iterator;
		using const_iter = std::vector<Collider**>::const_iterator;

	public:
		/*
		* @brief	Collider의 메모리를 할당받고 사용 등록합니다.
		* @details	
		* - Collider의 빈 포인터 주소를 매개인자로 받습니다.
		* - Collider의 빈 포인터 주소에 동적 할당해서 사용합니다.
		* - 메모리 관리는 ColliderManager에 종속됩니다.
		* @param[in]	Collider** collider: 메모리를 할당받아 사용할 collider 빈포인터 주소
		*/
		void			Attach(Collider** collider);
		/*
		* @brief	Collider의 메모리를 소멸시키고 사용 등록을 해제합니다.
		* @details
		* - 사용중인 Collider의 포인터 주소를 매개인자로 받습니다.
		* - 포인터를 소멸시키고 nullptr로 초기화합니다.
		* - 메모리 관리는 ColliderManager에 종속됩니다.
		* @param[in]	Collider** collider: 메모리를 소멸시키고 nullptr로 채울 collider 포인터
		*/
		void			Detach(Collider** collider);
		/*
		* @brief	ColliderManager에서 사용 등록된 Collider를 탐색합니다.
		* @details
		* - 사용중인 Collider의 포인터 주소를 매개인자로 받습니다.
		* - 사용 등록된 Collider를 반환합니다.
		* - 만약 찾을 수 없는 Collider일 경우 ColliderManager::end()를 반환합니다.
		* @param[in]	Collider** collider: 찾고자 하는 사용 등록된 포인터의 주소
		* @return		iter: 성공할 경우 대상 Collider의 iter, 실패할 경우 ColliderManager::end()
		*/
		iter			Find(Collider** target);

		iter			begin();
		iter			end();
		const_iter		begin() const;
		const_iter		end() const;
		
		static ColliderManager&		GetInstance();

	protected:
		explicit ColliderManager();
		virtual ~ColliderManager();

	private:
		std::vector<Collider**>		m_ColArray;
	};

} // namespace fz