#include "WaveFrontElement.h"

WaveFrontElement::WaveFrontElement()
{
	Name = nullptr;
	Smoothing = 0;

	VertexPositionList = nullptr;
	VertexPositonListSize = 0;

	TextureCoordinateList = nullptr;
	TextureCoordinateListSize = 0;

	VertexNormalPositionList = nullptr;
	VertexNormalPositionListSize = 0;

	VertexParameterList = nullptr;
	VertexParameterListSize = 0;

	FaceElementList = nullptr;
	FaceElementListSize = 0;
}

WaveFrontElement::~WaveFrontElement()
{
	Deallocate();
}

void WaveFrontElement::Allocate()
{
	if (VertexPositonListSize > 0)
		VertexPositionList = new Position[VertexPositonListSize];

	if (TextureCoordinateListSize > 0)
		TextureCoordinateList = new Point[TextureCoordinateListSize];

	if (VertexNormalPositionListSize > 0)
		VertexNormalPositionList = new Position[VertexNormalPositionListSize];

	if (VertexParameterListSize > 0)
		VertexParameterList = new Position[VertexParameterListSize];

	if (FaceElementListSize > 0)
		FaceElementList = new IndexPosition[FaceElementListSize];
}

void WaveFrontElement::Deallocate()
{
	if (VertexPositionList != nullptr) 
		delete[] VertexPositionList;

	if (TextureCoordinateList != nullptr) 		
		delete[] TextureCoordinateList;

	if (VertexNormalPositionList != nullptr) 
		delete[] VertexNormalPositionList;

	if (VertexParameterList != nullptr) 
		delete[] VertexParameterList;

	if (FaceElementList != nullptr) 
		delete[] FaceElementList;
}