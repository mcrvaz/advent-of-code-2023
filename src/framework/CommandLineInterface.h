#pragma once

namespace MyCLI
{
	enum class OperationType
	{
		execute,
		create
	};

	class Options
	{
	public:
		OperationType OpType;
		int Day;
		int Part;

		void Print();
	};

	class Parser
	{
	public:
		Parser(int argc, char** argv);
		Options Parse();
	private:
		int m_argc;
		char** m_argv;
	};
}
