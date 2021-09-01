#pragma once
namespace BF
{
	struct GameTickData
	{
	private:
		unsigned int _deltaTimeIndex = 0;
		static const unsigned int _deltaTimeValues = 1;

		public:
		float DeltaTime[_deltaTimeValues];
		float ActiveTime;
		float FramesPerSecound;
		unsigned int FramesRendered;
		double LastTimeCheck;
		
		GameTickData();

		void CalcualteFramesPerSecounds(double time);

		float GetSmoothDeltaTime();
	};
}