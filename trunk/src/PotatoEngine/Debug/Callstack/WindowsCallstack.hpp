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

	protected:
		virtual void init();
		virtual void cleanUp();

		virtual void* fetchNextEntry(const size_t index);
		virtual bool fetchSymbolName(const void* const address, std::string& outSymbolName) const;
		virtual bool fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const;
		virtual bool fetchBinaryName(const void* const address, std::string& outBinaryName) const;

	private:
		Word GetAdressAsWord(const void* const address) const;

	private:
		static const Word s_machineType;
		HANDLE m_processHandle;
		HANDLE m_threadHandle;
		CONTEXT m_context;
		STACKFRAME m_stackFrame;
};
}}
#endif

#endif
