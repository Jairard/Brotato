#ifndef __POT_WINDOWS_CALLSTACK__
#define __POT_WINDOWS_CALLSTACK__

#include <Core/compil.hpp>

#if defined(POT_PLATFORM_WINDOWS) && defined(POT_COMPILER_MSC)
#define POT_WINDOWS_CALLSTACK_SUPPORT
#endif

#ifdef POT_WINDOWS_CALLSTACK_SUPPORT
#include <sstream>
#include <string>
#include <DbgHelp.h>
#include <Debug/Callstack/AbstractCallstack.hpp>

namespace Pot { namespace Debug
{
class WindowsCallstack: public AbstractCallstack
{
#if defined(POT_ARCH_64)
	typedef DWORD64 Word;
	typedef PDWORD64 WordPtr;
	typedef IMAGEHLP_LINE64 Line;
	typedef PIMAGEHLP_LINE64 LinePtr;
	typedef IMAGEHLP_SYMBOL64 Symbol;
	typedef PIMAGEHLP_SYMBOL64 SymbolPtr;
	typedef IMAGEHLP_MODULE64 Module;
#define GetContextOffset(context) (context.Rip)
#define GetFrameOffset(context)   (context.Rsp)
#define GetStackOffset(context)   (context.Rsp)
#elif defined(POT_ARCH_32)
	typedef DWORD Word;
	typedef PDWORD WordPtr;
	typedef IMAGEHLP_LINE Line;
	typedef PIMAGEHLP_LINE LinePtr;
	typedef IMAGEHLP_SYMBOL Symbol;
	typedef PIMAGEHLP_SYMBOL SymbolPtr;
	typedef IMAGEHLP_MODULE Module;
#define GetContextOffset(context) (context.Eip)
#define GetFrameOffset(context)   (context.Ebp)
#define GetStackOffset(context)   (context.Esp)
#else
	typedef DWORD Word;
	typedef PDWORD WordPtr;
	typedef IMAGEHLP_LINE Line;
	typedef PIMAGEHLP_LINE LinePtr;
	typedef IMAGEHLP_SYMBOL Symbol;
	typedef PIMAGEHLP_SYMBOL SymbolPtr;
	typedef IMAGEHLP_MODULE Module;
#define GetContextOffset(context) (context.Eip)
#define GetFrameOffset(context)   (context.Ebp)
#define GetStackOffset(context)   (context.Esp)
#endif

	public:
		WindowsCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount, bool hasRealTimeConstraint = false);
		virtual ~WindowsCallstack();

		virtual const std::string& str() const;

	private:
		void fetchCallstack();

		void fetchSymbolName(const STACKFRAME& frame, const HANDLE& currentProcess, std::ostringstream& outStream) const;
		void fetchFileAndLine(const HANDLE& currentProcess, const Word& address, std::ostringstream& outStream) const;
		void fetchBinaryName(const HANDLE& currentProcess, const Word& address, std::ostringstream& outStream) const;

private:
	static const Word s_machineType;
		std::string m_trace;
};
}}
#endif

#endif
