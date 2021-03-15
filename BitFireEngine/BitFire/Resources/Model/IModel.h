#pragma once

#include "../../Mathematic/Geometry/Position.hpp"

namespace BF
{
	class IModel
	{
		public:	
		/**
			Move object in a specific direction in this worldspace.
			@param Direction in which this object should be moved in.
		*/
		virtual void Move(float x, float y, float z) = 0;
		virtual void Move(Position<float> position) = 0;

		/**
			Move to specific location in this worldspace.
			@param Position where this object should be moved to.
		*/
		virtual void MoveTo(float x, float y, float z) = 0;
		virtual void MoveTo(Position<float> position) = 0;


		/**
			Rotate the object around itself.
			@param Rotation, how much each axis should be rotated.
		*/
		virtual void Rotate(float x, float y, float z) = 0;
		virtual void Rotate(Position<float> rotation) = 0;

		virtual void RotateTo(float x, float y, float z) = 0;
		virtual void RotateTo(Position<float> rotation) = 0;

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		virtual void Orbit(float x, float y, float z) = 0;
		virtual void Orbit(Position<float> rotation) = 0;

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		virtual void Orbit(Position<float> rotation, Position<float> ancerPosition) = 0;
	
		/**
		Change the size of this object in this worldspace.
		@param Scalefactor, how much each axis should be Scaled. 1 => no change.
		*/

		virtual void Scale(float x, float y, float z) = 0;
		virtual void Scale(Position<float> scaleFactor) = 0;
	};
}