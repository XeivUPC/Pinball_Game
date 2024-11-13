#pragma once
class ScreenProgram
{
public:
	ScreenProgram();
	~ScreenProgram();
	virtual ScreenProgram* Activate();
	virtual void StartProgram();
	virtual void Logic();
	virtual void Render();
	virtual void EndProgram();
};