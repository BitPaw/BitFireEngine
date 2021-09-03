#pragma once

namespace BF
{
	template<class FunctionPonter>
	class Event
	{
		private:
		unsigned int SubscriberListSize;
		FunctionPonter SubscriberList[10];

		public:
		Event()
		{
			SubscriberListSize = 0;
			//SubscriberList = nullptr;
		}

		void operator+=(FunctionPonter functionPonter)
		{
			SubscriberList[SubscriberListSize] = functionPonter;
			SubscriberListSize++;
		}

		void operator-=(FunctionPonter functionPonter)
		{
			SubscriberList[SubscriberListSize] = functionPonter;
			SubscriberListSize--;
		}

		void Call()
		{
			for (unsigned int i = 0; i < SubscriberListSize; i++)
			{
				FunctionPonter& functionPonter = SubscriberList[i];

				functionPonter();
			}
		}
	};

	/*
	template<class FunctionPonter, class FunctionParameter>
	class Event
	{
		private:
		unsigned int SubscriberListSize;
		FunctionPonter SubscriberList[10];

		public:
		Event()
		{
			SubscriberListSize = 0;
			SubscriberList = nullptr;
		}
		
		void operator+=(FunctionPonter functionPonter)
		{
			SubscriberList[SubscriberListSize] = functionPonter;
			SubscriberListSize++;
		}

		void operator-=(FunctionPonter functionPonter)
		{
			SubscriberList[SubscriberListSize] = functionPonter;
			SubscriberListSize--;
		}

		void Call(FunctionParameter& functionParameter)
		{
			for (unsigned int i = 0; i < SubscriberListSize; i++)
			{
				FunctionPonter& functionPonter = SubscriberList[i];

				functionPonter(functionParameter);
			}
		}
	};*/
}