#pragma once

#include "MemoryManager.hpp"

#include <memory.h>
#include <stddef.h>

namespace RTR {
    extern MemoryManager* g_pMemoryManager;
    class Buffer {
    public:
        Buffer() : m_pData(nullptr), m_szSize(0), m_szAlignment(alignof(uint32_t)) {}
        Buffer(size_t size, size_t alignment = 4) : m_szSize(size), m_szAlignment(alignment) { m_pData = reinterpret_cast<uint8_t*>(g_pMemoryManager->Allocate(size, alignment)); }
        ~Buffer() { if (m_pData) g_pMemoryManager->Free(m_pData, m_szSize); m_pData = nullptr; }

		Buffer(const Buffer& rhs) {
			if (rhs.m_pData != nullptr)
			{
				m_pData = reinterpret_cast<uint8_t*>(g_pMemoryManager->Allocate(rhs.m_szSize, rhs.m_szAlignment));
				memcpy(m_pData, rhs.m_pData, rhs.m_szSize);
			}
			else {
				m_pData = nullptr;
			}
			
			m_szSize = rhs.m_szSize;
			m_szAlignment = rhs.m_szAlignment;
		}


		Buffer(Buffer&& rhs) {
			m_pData = rhs.m_pData;
			m_szSize = rhs.m_szSize;
			m_szAlignment = rhs.m_szAlignment;
			rhs.m_pData = nullptr;
			rhs.m_szSize = 0;
			rhs.m_szAlignment = 4;
		}

		Buffer& operator = (const Buffer& rhs) {
			if (m_szSize >= rhs.m_szSize && m_szAlignment == rhs.m_szAlignment) {
				memcpy(m_pData, rhs.m_pData, rhs.m_szSize);
			}
			else {
				if (m_pData) g_pMemoryManager->Free(m_pData, m_szSize);
				m_pData = reinterpret_cast<uint8_t*>(g_pMemoryManager->Allocate(rhs.m_szSize, rhs.m_szAlignment));
				memcpy(m_pData, rhs.m_pData, rhs.m_szSize);
				m_szSize = rhs.m_szSize;
				m_szAlignment = rhs.m_szAlignment;
			}
			return *this;
		}
    
		Buffer& operator = (Buffer&& rhs) {
			if (m_pData) g_pMemoryManager->Free(m_pData, m_szSize);
			m_pData = rhs.m_pData;
			m_szSize = rhs.m_szSize;
			m_szAlignment = rhs.m_szAlignment;
			rhs.m_pData = nullptr;
			rhs.m_szSize = 0;
			rhs.m_szAlignment = 4;
			return *this;
		}




    public:
        uint8_t* m_pData;
        size_t m_szSize;
        size_t m_szAlignment;
    };
}

