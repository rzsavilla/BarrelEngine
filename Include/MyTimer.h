#pragma once

class MyTimer {
private:
	float m_fStart;	//!< Start time
public:
	MyTimer();

	void reset();
	float getElapsed();
};