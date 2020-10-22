#pragma once

#include "../../Mathematic/Geometry/Vector/Vector3.h"

namespace BF
{
	class IModel
	{
		public:	
		/**
			Change the size of this object in this worldspace.
			@param Scalefactor, how much each axis should be Scaled. 1 => no change.
		*/
		virtual void Scale(Vector3 size)
		{
			throw "Not implemented";
		}

		/**
			Move object in a specific direction in this worldspace.
			@param Direction in which this object should be moved in.
		*/
		virtual void MoveBy(Vector2 vector)
		{
			//throw "Not implemented";
		}

		/**
			Move object in a specific direction in this worldspace.
			@param Direction in which this object should be moved in.
		*/
		virtual void MoveBy(Vector3 vector)
		{
			throw "Not implemented";
		}

		/**
			Move to specific location in this worldspace.
			@param Position where this object should be moved to.
		*/
		virtual void MoveTo(Vector3 position)
		{
			throw "Not implemented";
		}


		/**
			Rotate the object around itself.
			@param Rotation, how much each axis should be rotated.
		*/
		virtual void Rotate(Vector3 rotation) 
		{
			throw "Not implemented";
		}

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		virtual void Orbit(Vector3 amount)
		{
			throw "Not implemented";
		}

		/**
			Rotate the object around the worldspace.
			@param Rotation, how much each axis should be rotated.
		*/
		virtual void Orbit(Vector3 amount, Vector3 ancerPoint)
		{
			throw "Not implemented";
		}
	};
}