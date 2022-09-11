#pragma once
class CBuffer
{
private:
	char** _Field;
	int _Width;
	int _Height;
public:
	CBuffer();
	~CBuffer();

	char** getField();
	int getWidth();
	int getHeight();

	void Init(int, int);
	void Clear();
	void updateBall(COORD);
	void updatePlayer(COORD);
	void Imitate(CBuffer*);
};

//==============================
//==============================
CBuffer::CBuffer()
{
	_Field = NULL;
	_Width = 0;
	_Height = 0;
}

CBuffer::~CBuffer()
{
	for (int Row = 0; Row < _Height; Row++)
		delete[] _Field[Row];

	delete[] _Field;
	_Field = NULL;
}

char** CBuffer::getField()
{
	return _Field;
}

int CBuffer::getWidth()
{
	return _Width;
}

int CBuffer::getHeight()
{
	return _Height;
}

void CBuffer::Init(int _width, int _height)
{
	_Width = _width;
	_Height = _height;
	_Field = new char* [_Height];

	for (int Row = 0; Row < _Height; Row++)
	{
		_Field[Row] = new char[_Width];

		for (int Col = 0; Col < _Width; Col++)
			_Field[Row][Col] = ' ';
	}
}

void CBuffer::Clear()
{
	for (int Row = 0; Row < _Height; Row++)
		for (int Col = 0; Col < _Width; Col++)
			_Field[Row][Col] = Col == 30 ? '\xB3' : ' ';
}

void CBuffer::updateBall(COORD _ballCoord)
{
	int Row = _ballCoord.Y;
	int Col = _ballCoord.X;

	_Field[Row][Col] = 'o';
}

void CBuffer::updatePlayer(COORD _playerCoord)
{
	int Row = _playerCoord.Y;
	int Col = _playerCoord.X;

	for (int i = 0; i < 4; i++)
		_Field[Row + i][Col] = '\xDB';
}

void CBuffer::Imitate(CBuffer* _pBuffer)
{
	for (int Row = 0; Row < _Height; Row++)
		for (int Col = 0; Col < _Width; Col++)
			_Field[Row][Col] = _pBuffer->_Field[Row][Col];
}