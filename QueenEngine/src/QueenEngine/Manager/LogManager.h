#pragma once

#include <unordered_map>

#include "Manager.h"
#include "../Utils/Singleton.h"
#include "../Logger/Log.h"

class LogManager : public Manager, public Singleton<LogManager>
{

	friend class Singleton<LogManager>;

public:

	void Start() override;
	void Shutdown() override;

	void CreateLog(const char* name);
	inline Log GetLog(const char* name) { return m_loggers[name]; }

private:

	LogManager();
	~LogManager();

	Log m_logger;
	std::unordered_map<const char*, Log> m_loggers;
};

