#pragma once

class BindScriptBase
{
public:
	virtual void Bind() = 0;
};

extern std::vector<BindScriptBase*> s_BindScriptBase;
