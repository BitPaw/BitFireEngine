#pragma once

#include <functional>

#include "../../../ResourceSystem/Source/Container/LinkedList.hpp"

namespace BF
{
    template<typename Function, typename Parameter>
    class DataEvent
    {
        protected:
        LinkedList<Function> _delegateList;
        
        public:
        // void operator()(T parameter);     

        void operator+=(Function function)
        {
            AddListener(function);
        }

        void operator-=(Function function)
        {
            RemoveListener(function);
        }       
                
        void AddListener(Function function)
        {
            _delegateList.Add(function);
        }

        void RemoveListener(Function function)
        {
           
        }

        void Trigger(Parameter parameter)
        {
            for (unsigned int i = 0; i < _delegateList.Size(); i++)
            {
                LinkedListNode<Function>* functionNode = _delegateList[i];
               
                (functionNode->Element)(parameter);
            }
        }
    };
}