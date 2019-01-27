//placeholders are for experiments

#ifdef Placeholder

#pragma once
//#include <string>
#include <iostream>     
#include <sstream>
#include <Windows.h>
//#include <sdkddkver.h>

//#define _WIN32_WINNT 0x0601 // target Windows 7 or later

/*#ifndef FULL_WINTARD //if FULL_WINTARD is not defined earlier
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE
#endif*/

class IPException
{
public:
	IPException(const wchar_t* file, unsigned int line, const std::wstring& msg = L"") :
		file_(file),
		line_(line),
		msg_(msg)
	{
		ShowMsgInDebugOutput();
	}
	

	const std::wstring& GetFile() const
	{
		return file_;
	}

	unsigned int GetLine() const
	{
		return line_;
	}

	const std::wstring& GetMsg() const
	{
		return msg_;
	}


	const void ShowMsgInDebugOutput() const
	{
		_CrtDbgReportW(_CRT_ASSERT, file_.c_str(), line_, NULL, L"%ls", msg_.c_str());
	}
	
	
	
	
private:
	std::wstring file_;
	unsigned int line_;
	std::wstring msg_;
};

#endif Placeholder
