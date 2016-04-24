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
		m_processHandle(nullptr),
		m_threadHandle(nullptr),
		m_context(),
		m_stackFrame()
	{
		init();
		fetchCallstack();
		cleanUp();
	}

	WindowsCallstack::~WindowsCallstack()
	{}

	void WindowsCallstack::init()
	{
		AbstractCallstack::init();

		m_processHandle = GetCurrentProcess();
		SymInitialize(m_processHandle, nullptr, true);
		m_threadHandle = GetCurrentThread();

		memset(&m_context, 0, sizeof(CONTEXT));
		m_context.ContextFlags = CONTEXT_FULL;
		RtlCaptureContext(&m_context);

		memset(&m_stackFrame, 0, sizeof(STACKFRAME));
		// setup initial stack frame
		m_stackFrame.AddrPC.Offset = GetContextOffset(m_context);
		m_stackFrame.AddrPC.Mode = AddrModeFlat;
		m_stackFrame.AddrFrame.Offset = GetFrameOffset(m_context);
		m_stackFrame.AddrFrame.Mode = AddrModeFlat;
		m_stackFrame.AddrStack.Offset = GetStackOffset(m_context);
		m_stackFrame.AddrStack.Mode = AddrModeFlat;
	}

	void* WindowsCallstack::fetchNextEntry(const size_t index)
	{
		POT_UNUSED(index);

		if (!StackWalk(s_machineType, m_processHandle, m_threadHandle, &m_stackFrame, &m_context, nullptr, SymFunctionTableAccess, SymGetModuleBase, nullptr))
			return nullptr;

		return reinterpret_cast<void*>(m_stackFrame.AddrPC.Offset);
	}

	void WindowsCallstack::cleanUp()
	{
		AbstractCallstack::cleanUp();
		SymCleanup(m_processHandle);
	}

	bool WindowsCallstack::fetchSymbolName(const void* const address, std::string& outSymbolName) const
	{
		const Word wAddress = GetAdressAsWord(address);
		Word displacement = 0;

		const size_t nameSize = 256;
		potbyte symbolBuffer[sizeof(Symbol) + nameSize];
		memset(symbolBuffer, 0, sizeof(Symbol) + nameSize);
		// Cast it to a symbol struct:
		SymbolPtr pSymbol = reinterpret_cast<SymbolPtr>(symbolBuffer);
		pSymbol->SizeOfStruct = sizeof(Symbol) + nameSize;
		pSymbol->MaxNameLength = nameSize - 1;

		if (!SymGetSymFromAddr(m_processHandle, wAddress, &displacement, pSymbol))
			return false;

		outSymbolName = pSymbol->Name;
		return true;
	}

	bool WindowsCallstack::fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const
	{
		const Word wAddress = GetAdressAsWord(address);
		DWORD displacement = 0;

		Line lineInfo;
		memset(&lineInfo, 0, sizeof(lineInfo));
		lineInfo.SizeOfStruct = sizeof(lineInfo);

		if (!SymGetLineFromAddr(m_processHandle, wAddress, &displacement, &lineInfo))
			return false;

		const std::string fileName(lineInfo.FileName);
		const size_t lastSlash = fileName.find_last_of('\\');
		outFileName = fileName.substr(lastSlash + 1);
		outLine = lineInfo.LineNumber;

		return true;
	}

	bool WindowsCallstack::fetchBinaryName(const void* const address, std::string& outBinaryName) const
	{
		const Word wAddress = GetAdressAsWord(address);

		Module moduleInfo;
		memset(&moduleInfo, 0, sizeof(moduleInfo));
		moduleInfo.SizeOfStruct = sizeof(moduleInfo);

		if (!SymGetModuleInfo(m_processHandle, wAddress, &moduleInfo))
			return false;

		outBinaryName = moduleInfo.ModuleName;
		return true;
	}

	WindowsCallstack::Word WindowsCallstack::GetAdressAsWord(const void* const address) const
	{
		return reinterpret_cast<const Word>(address);
	}
}}
#endif
