﻿//------------------------------------------------------------------------
// * @filename: DBClient.h
// *
// * @brief: 数据库客户端
// *
// * @author: XGM
// * @date: 2017/08/16
//------------------------------------------------------------------------
#pragma once

#include <string>

class DBClient
{
public:
	DBClient() {}
	virtual ~DBClient() {}

	//------------------------------------------------------------------------
	// 初始化
	//------------------------------------------------------------------------
	virtual bool Init(std::string strHost/*ip:port*/,
		std::string strUserName,
		std::string strPassword) = 0;

	//------------------------------------------------------------------------
	// 启动服务
	//------------------------------------------------------------------------
	virtual bool Start() = 0;

	//------------------------------------------------------------------------
	// 停止服务
	//------------------------------------------------------------------------
	virtual bool Stop() = 0;
};
