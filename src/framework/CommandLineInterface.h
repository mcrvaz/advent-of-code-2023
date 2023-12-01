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
		const OperationType OpType;
		const int Day;
		const int Part;

		void Print() const;
	};

	class Parser
	{
	public:
		Parser(int argc, char** argv) noexcept;
		Options Parse() const;
	private:
		const int m_argc;
		const char *const *m_argv;
	};
}
