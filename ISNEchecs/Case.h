#pragma once


class Case
{
public:
	Case(int px, int py);
	~Case();
	bool isEmpty() { return m_Empty; }


private:
	int m_sx;
	int m_sy;
	int m_px;
	int m_py;
	bool m_Empty;
};

