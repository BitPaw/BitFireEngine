#pragma once

enum class MessagePriorityType
{
	// Unimported log message
	Info,

	// State changed
	Notfication,

	// Some error accured but it can be igrnored
	Warning,

	// Something went wrong.
	Error,

	// Something failed.
	Failure
};