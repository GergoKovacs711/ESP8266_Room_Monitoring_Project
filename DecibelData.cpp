// 
// 
// 

#include "DecibelData.h"

DecibelData::DecibelData(const double *array, int arraySize) : _size(arraySize)
{
	for (int counter = 0; counter < arraySize; counter++)
	{
		_decibels[counter] = array[counter];
	}
}

double DecibelData::at(short place)
{
	if (place >= 0 && place < this->_size)
	{
		return _decibels[place];
	}
	else
		return 0.0;
}

int DecibelData::getSize(void)
{
	return _size;
}
