﻿//------------------------------------------------------------------------
// * @filename: BufferAllocator.h
// *
// * @brief: buffer分配器(线程安全的)
// *
// * @author: XGM
// * @date: 2017/08/24
//------------------------------------------------------------------------
#pragma once

#include <list>
#include <string>
#include <memory>
#include <mutex>
#include <stdint.h>

namespace evpp {
	class Buffer;
}

// 缓存使用状态
class MemState
{
public:
	MemState(uint64_t nInterval) : m_nIntervalTime(nInterval) {}
	//------------------------------------------------------------------------
	// 增加
	//------------------------------------------------------------------------
	void Inc();
	//------------------------------------------------------------------------
	// 减少
	//------------------------------------------------------------------------
	void Dec();
	//------------------------------------------------------------------------
	// 获得使用计数
	//------------------------------------------------------------------------
	uint64_t Count();
	//------------------------------------------------------------------------
	// 是否超时
	//------------------------------------------------------------------------
	bool IsTimeout();
	//------------------------------------------------------------------------
	// 重置
	//------------------------------------------------------------------------
	void Reset();

	//------------------------------------------------------------------------
	// 获得内部成员信息
	//------------------------------------------------------------------------
	uint64_t GetNewCount() { return m_nNewCount; }
	uint64_t GetDelCount() { return m_nDelCount; }
	uint64_t GetStartTime() { return m_nStartTime; }
	uint64_t GetIntervalTime() { return m_nIntervalTime; }

private:
	uint64_t m_nNewCount = 0; // 分配次数
	uint64_t m_nDelCount = 0; // 回收次数
	uint64_t m_nStartTime = 0; // 开始时间
	uint64_t m_nIntervalTime = 0; // 间隔时间
};

class BufferAllocator
{
public:
	using BufferPtr = std::unique_ptr<evpp::Buffer, std::function<void(evpp::Buffer*)>>;
public:
	BufferAllocator(uint32_t nInitCapacity);
	~BufferAllocator();

	//------------------------------------------------------------------------
	// 获得分配信息
	//------------------------------------------------------------------------
	std::string GetAllocInfo();

	//------------------------------------------------------------------------
	// 获得缓存size
	//------------------------------------------------------------------------
	uint64_t GetCacheSize();

	//------------------------------------------------------------------------
	// 分配一个Buffer
	//------------------------------------------------------------------------
	BufferPtr Alloc();

protected:
	//------------------------------------------------------------------------
	// 回收一个Buffer
	//------------------------------------------------------------------------
	void Recover(evpp::Buffer* pBuffer);

private:
	// 同步锁
	std::mutex m_aMutex;
	// 可用的Buffer列表
	std::list<evpp::Buffer*> m_listBuffer;
	// 5分钟内使用状态
	MemState m_aMemState5m = { 5 * 60 };
};
