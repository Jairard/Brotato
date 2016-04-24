#include <stdafx.h>
#include "WindowsCallstack.hpp"

#ifdef POT_WINDOWS_CALLSTACK_SUPPORT
#include <iomanip>
#include <string>
#include <Debug/Logger.hpp>
#include <Core/types.hpp>

namespace Pot { namespace Debug
{
	// What about IMAGE_FILE_MACHINE_IA64 ?
#if defined(POT_ARCH_64)
	const WindowsCallstack::Word WindowsCallstack::s_machineType = IMAGE_FILE_MACHINE_AMD64;
#elif defined(POT_ARCH_32)
	const WindowsCallstack::Word WindowsCallstack::s_machineType = IMAGE_FILE_MACHINE_I386;
#else
	const WindowsCallstack::Word WindowsCallstack::s_machineType = IMAGE_FILE_MACHINE_I386;
#endif

	WindowsCallstack::WindowsCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
		AbstractCallstack(skippedFrameCount, hasRealTimeConstraint),
		m_trace()
	{
		fetchCallstack();
	}

	WindowsCallstack::~WindowsCallstack()
	{}

	const std::string& WindowsCallstack::str() const
	{
		return m_trace;
	}

	void WindowsCallstack::fetchCallstack()
	{
		const HANDLE process = GetCurrentProcess();
		SymInitialize(process, nullptr, true);

		CONTEXT context;
		memset(&context, 0, sizeof(CONTEXT));
		context.ContextFlags = CONTEXT_FULL;
		RtlCaptureContext(&context);

		const Word address = GetContextOffset(context);

		STACKFRAME frame;
		memset(&frame, 0, sizeof(STACKFRAME));
		// setup initial stack frame
		frame.AddrPC.Offset    = address;
		frame.AddrPC.Mode      = AddrModeFlat;
		frame.AddrFrame.Offset = GetFrameOffset(context);
		frame.AddrFrame.Mode   = AddrModeFlat;
		frame.AddrStack.Offset = GetStackOffset(context);
		frame.AddrStack.Mode   = AddrModeFlat;

		const HANDLE currentThread = GetCurrentThread();
		std::ostringstream oss;
		size_t frameCount = 0;

		for (size_t i = m_skippedFrameCount; i < c_maxFrameCount; ++i)
		{
			if (!StackWalk(s_machineType, process, currentThread, &frame, &context, nullptr, SymFunctionTableAccess, SymGetModuleBase, nullptr))
				break;

			if (i > m_skippedFrameCount)
				oss << std::endl;
			oss << "[" << std::setw(3) << std::right << i << "] ";

			fetchSymbolName(frame, process, oss);
			fetchFileAndLine(process, address, oss);
			fetchBinaryName(process, address, oss);
		}

		m_trace = oss.str();
		SymCleanup(process);
	}

	void WindowsCallstack::fetchSymbolName(const STACKFRAME& frame, const HANDLE& currentProcess, std::ostringstream& outStream) const
	{
		Word address = frame.AddrPC.Offset;
		Word displacement;

		const size_t symbolSize = sizeof(Symbol);
		const size_t nameSize = 256;
		potb symbolBuffer[symbolSize + nameSize];
		memset(symbolBuffer, 0, symbolSize + nameSize);
		// Cast it to a symbol struct:
		SymbolPtr pSymbol = reinterpret_cast<SymbolPtr>(symbolBuffer);
		// Need to set the first two fields of this symbol before obtaining name info:
		pSymbol->SizeOfStruct = symbolSize + nameSize;
		pSymbol->MaxNameLength = nameSize - 1;

		if (SymGetSymFromAddr(currentProcess, address, &displacement, pSymbol))
			outStream << pSymbol->Name;
		else
			outStream << "[no symbol found at " << address << "]";
	}

	void WindowsCallstack::fetchFileAndLine(const HANDLE& currentProcess, const Word& address, std::ostringstream& outStream) const
	{
		Line lineInfo;
		memset(&lineInfo, 0, sizeof(lineInfo));
		lineInfo.SizeOfStruct = sizeof(lineInfo);

		DWORD displacement = 0;
		size_t line = 0;

		outStream << " at ";
		if (SymGetLineFromAddr(currentProcess, address, &displacement, &lineInfo))
		{
			std::string fileName(lineInfo.FileName);
			size_t lastSlash = fileName.find_last_of('\\');
			outStream << fileName.substr(lastSlash + 1) << ":" << lineInfo.LineNumber;
		}
		else
			outStream << "[file name not available]:[line number not available]";
	}

	void WindowsCallstack::fetchBinaryName(const HANDLE& currentProcess, const Word& address, std::ostringstream& outStream) const
	{
		Module moduleInfo;
		memset(&moduleInfo, 0, sizeof(moduleInfo));
		moduleInfo.SizeOfStruct = sizeof(moduleInfo);

		outStream << " in ";
		if (SymGetModuleInfo(currentProcess, address, &moduleInfo))
			outStream << moduleInfo.ModuleName;
		else
			outStream << "[binary name not available]";
	}
}}
#endif
