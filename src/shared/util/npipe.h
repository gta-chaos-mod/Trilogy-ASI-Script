/*
Module : npipe.h
Purpose: Defines the interface for an C++ wrapper class for Win32 Named Pipes
Created: PJN / 2-08-1998
History: PJN / 21-02-2002 1. Updated copyright message in source code and documentation
						  2. Fixed a bug in Close method where the handle value was not being reset to INVALID_HANDLE_VALUE.
						  3. Tidied up the TRACE code
						  4. Tidied up build configurations for sample apps
		 PJN / 28-07-2002 1. Updated sample server app to do Flush of the pipe before we disconnect the client. Thanks to
						  "Martin" for spotting this problem.
		 PJN / 09-11-2002 1. ConnectClient now returns TRUE if the last error returns ERROR_PIPE_CONNECTED which indicates
						  that a client is already connected before we make the call. Thanks to Metrich Frederic for
						  reporting this.
		 PJN / 05-03-2003 1. Changed the class to use exceptions rather than SDK style return values
		 PJN / 12-11-2003 1. Attach now includes an AutoClose parameter. This allows control over whether the pipe handle
						  should be closed when the pipe object goes out of scope or CNamedPipe::Close is called. Thanks
						  to Metrich Frederic for reporting this issue.
		 PJN / 19-12-2003 1. Fixed ASSERT's at the start of most CNamedPipe functions which verify that the pipe handle
						  is valid. Thanks to Metrich Frederic for reporting this issue.
		 PJN / 15-07-2006 1. Updated copyright details.
						  2. Renamed AfxThrowNamedPipeException to ThrowNamedPipeException and made it part of the
						  CNamedPipe class.
						  3. CNamedPipe is no longer derived from CObject as it was not really required.
						  4. Optimized CNamedPipe constructor code.
						  5. Code now uses new C++ style casts rather than old style C casts where necessary.
						  6. Optimized CNamedPipeException constructor code
						  7. Removed the unnecessary CNamedPipeException destructor
						  8. Removed some unreferenced variables in the sample app.
						  9. Updated the code to clean compile on VC 2005
						  10. Updated documentation to use the same style as the web site.
						  11. Addition of a CNAMEDPIPE_EXT_CLASS macro to allow the classes to be easily added to an
						  extension dll.
		 PJN / 28-12-2007 1. Updated copyright details.
						  2. Updated the sample apps to clean compile on VC 2005
						  3. Sample client app now defaults to "." (meaning the current machine) as the server to connect to.
						  4. CNamedPipeException::GetErrorMessage now uses the FORMAT_MESSAGE_IGNORE_INSERTS flag. For more
						  information please see Raymond Chen's blog at
						  http://blogs.msdn.com/oldnewthing/archive/2007/11/28/6564257.aspx. Thanks to Alexey Kuznetsov for
						  reporting this issue.
						  5. CAppSettingsException::GetErrorMessage now uses Checked::tcsncpy_s if compiled using VC 2005 or
						  later.
						  6. Provision of new overloaded versions of the Peek, Write and Read methods which allows the
						  dwBytesRead/dwBytesWritten parameters to be returned as an output parameter as opposed to the return
						  value of the method. This helps resolve a situation where the underlying WriteFile / ReadFile call
						  fails but some data has actually been written / read from the pipe. Thanks to Gintautas Kisonas for
						  reporting this issue.
						  7. dwBytesRead, dwTotalBytesAvail and dwBytesLeftThisMessage parameters to Peek are now pointers rather
						  than references. Thanks to Gintautas Kisonas for reporting this issue.
		 PJN / 30-12-2007 1. Updated the sample apps to clean compile on VC 2008
		 PJN / 12-07-2008 1. Updated copyright details.
						  2. Updated sample app to clean compile on VC 2008
						  3. The code has now been updated to support VC 2005 or later only.
						  4. Code now compiles cleanly using Code Analysis (/analyze)
						  5. Removed the m_bAutoClose member variable and concept from class
		 PJN / 01-06-2015 1. Updated copyright details.
						  2. Updated the sample app project settings to more modern default values.
						  3. Reworked the class to make it a header only implementation.
						  4. Added SAL annotations to all the code
						  5. Removed the static Call method as it did not provide any C++ encapsulation of the underlying API call
						  6. Reworked the class to not be exception based. Now the class merely wraps the underlying API calls
						  in a RAII fashion.
						  7. Removed the static ServerAvailable method as it did not provide any C++ encapsulation of the
						  underlying API call.
						  8. Updated the code to compile without taking a dependency on MFC.
						  9. The methods which call WriteFileEx have been renamed to WriteEx.
						  10. The methods which call ReadFileEx have been renamed to ReadEx.
						  11. The ConnectClient method has been renamed to Connect.
						  12. The DisconnectClient method has been renamed to Disconnect.
						  13. Added support for GetNamedPipeComputerName, GetNamedPipeClientProcessId, GetNamedPipeClientSessionId,
						  GetNamedPipeServerProcessId, GetNamedPipeServerSessionId & ImpersonateNamedPipeClient APIs.
		 PJN / 19-12-2017 1. Updated copyright details
						  2. Replaced CString::operator LPC*STR() calls throughout the codebase with CString::GetString calls
						  3. Replaced NULL throughout the codebase with nullptr. This means that the minimum requirement for the framework is now
						  VC 2010.
						  4. GetNamedPipeClientProcessId, GetNamedPipeClientSessionId, GetNamedPipeServerProcessId & GetNamedPipeServerSessionId
						  API functions are now called directly rather than through GetProcAddress.
						  5. Verified there has been no further additions to Named Pipes from the latest Windows 10 SDK
		 PJN / 26-08-2018 1. Updated copyright details
						  2. Fixed a number of C++ core guidelines compiler warnings. These changes mean that the code will now only compile on
						  VC 2017 or later.
		 PJN / 02-06-2019 1. Updated copyright details.
						  2. Updated the code to clean compile on VC 2019

Copyright (c) 1998 - 2019 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise)
when your product is released in binary form. You are allowed to modify the source code in any way you want
except you cannot modify the copyright details at the top of each module. If you want to distribute source
code with your application, then you are only allowed to distribute versions released by the author. This is
to maintain a single distribution point for the source code.

*/

/////////////////////// Macros / Defines //////////////////////////////////////

#pragma once

#ifndef __NPIPE_H__
#define __NPIPE_H__

#ifndef CNAMEDPIPE_EXT_CLASS
#define CNAMEDPIPE_EXT_CLASS
#endif //#ifndef CNAMEDPIPE_EXT_CLASS

/////////////////////// Classes ///////////////////////////////////////////////

//Wrapper class to encapsulate a named pipe
class CNAMEDPIPE_EXT_CLASS CNamedPipe
{
public:
	//Constructors / Destructors
	CNamedPipe() noexcept : m_hPipe(INVALID_HANDLE_VALUE)
	{
	}

	~CNamedPipe() noexcept
	{
		Close();
	}

	CNamedPipe(_In_ const CNamedPipe&) = delete;

	CNamedPipe(_In_ CNamedPipe&& pipe) noexcept : m_hPipe(INVALID_HANDLE_VALUE)
	{
		Attach(pipe.Detach());
	}

	//Methods
	CNamedPipe& operator=(_In_ const CNamedPipe&) = delete;

	CNamedPipe& operator=(_In_ CNamedPipe&& prov) noexcept
	{
		if (m_hPipe != INVALID_HANDLE_VALUE)
			Close();
		Attach(prov.Detach());
		return *this;
	}

	BOOL Create(_In_ LPCTSTR lpName, _In_ DWORD dwOpenMode, _In_ DWORD dwPipeMode, _In_ DWORD dwMaxInstances, _In_ DWORD dwOutBufferSize,
		_In_ DWORD dwInBufferSize, _In_ DWORD dwDefaultTimeOut, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(!IsOpen());

		m_hPipe = CreateNamedPipe(lpName, dwOpenMode, dwPipeMode, dwMaxInstances, dwOutBufferSize, dwInBufferSize, dwDefaultTimeOut, lpSecurityAttributes);
		return (m_hPipe != INVALID_HANDLE_VALUE);
	}

	BOOL Open(_In_ LPCTSTR lpName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr, DWORD dwFlagsAndAttributes = 0) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(!IsOpen());

		m_hPipe = CreateFile(lpName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, OPEN_EXISTING, dwFlagsAndAttributes, nullptr);
		return (m_hPipe != INVALID_HANDLE_VALUE);
	}

	operator HANDLE() const noexcept
	{
		return m_hPipe;
	}

	void Close() noexcept
	{
		if (m_hPipe != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hPipe);
			m_hPipe = INVALID_HANDLE_VALUE;
		}
	}

	void Attach(_In_opt_ HANDLE hPipe) noexcept
	{
		Close();
		m_hPipe = hPipe;
	}

	HANDLE Detach() noexcept
	{
		HANDLE hReturn = m_hPipe;
		m_hPipe = INVALID_HANDLE_VALUE;
		return hReturn;
	}

	BOOL IsOpen() const noexcept
	{
		return (m_hPipe != INVALID_HANDLE_VALUE);
	}

	BOOL Connect(_Inout_opt_ LPOVERLAPPED lpOverlapped = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return ConnectNamedPipe(m_hPipe, lpOverlapped);
	}

	BOOL Disconnect() noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return DisconnectNamedPipe(m_hPipe);
	}

	BOOL Flush() noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return FlushFileBuffers(m_hPipe);
	}

	BOOL Write(_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer, _In_ DWORD nNumberOfBytesToWrite, _Out_opt_ LPDWORD lpNumberOfBytesWritten = nullptr, _Inout_opt_ LPOVERLAPPED lpOverlapped = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return WriteFile(m_hPipe, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	}

	BOOL WriteEx(_In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer, _In_ DWORD nNumberOfBytesToWrite, _Inout_ LPOVERLAPPED lpOverlapped, _In_ LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return WriteFileEx(m_hPipe, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, lpCompletionRoutine);
	}

	BOOL Read(_Out_writes_bytes_to_opt_(nNumberOfBytesToRead, *lpNumberOfBytesRead) __out_data_source(FILE) LPVOID lpBuffer, _In_ DWORD nNumberOfBytesToRead, _Out_opt_ LPDWORD lpNumberOfBytesRead = nullptr, _Inout_opt_ LPOVERLAPPED lpOverlapped = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return ReadFile(m_hPipe, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
	}

	BOOL ReadEx(_Out_writes_bytes_opt_(nNumberOfBytesToRead) __out_data_source(FILE) LPVOID lpBuffer, _In_ DWORD nNumberOfBytesToRead, _Inout_ LPOVERLAPPED lpOverlapped, _In_ LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return ReadFileEx(m_hPipe, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);
	}

	BOOL Peek(_Out_writes_bytes_to_opt_(nBufferSize, *lpBytesRead) LPVOID lpBuffer, _In_ DWORD nBufferSize, _Out_opt_ LPDWORD lpBytesRead = nullptr, _Out_opt_ LPDWORD lpTotalBytesAvail = nullptr, _Out_opt_ LPDWORD lpBytesLeftThisMessage = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return PeekNamedPipe(m_hPipe, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);
	}

	BOOL Transact(_In_reads_bytes_opt_(nInBufferSize) LPVOID lpInBuffer, _In_ DWORD nInBufferSize, _Out_writes_bytes_to_opt_(nOutBufferSize, *lpBytesRead) LPVOID lpOutBuffer, _In_ DWORD nOutBufferSize, _Out_ LPDWORD lpBytesRead, _Inout_opt_ LPOVERLAPPED lpOverlapped = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return TransactNamedPipe(m_hPipe, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesRead, lpOverlapped);
	}

	BOOL GetState(_Out_opt_ LPDWORD lpState, _Out_opt_ LPDWORD lpCurInstances, _Out_opt_ LPDWORD lpMaxCollectionCount, _Out_opt_ LPDWORD lpCollectDataTimeout, _Out_writes_opt_(nMaxUserNameSize) LPTSTR lpUserName, _In_ DWORD nMaxUserNameSize) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return GetNamedPipeHandleState(m_hPipe, lpState, lpCurInstances, lpMaxCollectionCount, lpCollectDataTimeout, lpUserName, nMaxUserNameSize);
	}

	BOOL GetInfo(_Out_opt_ LPDWORD lpFlags, _Out_opt_ LPDWORD lpOutBufferSize = nullptr, _Out_opt_ LPDWORD lpInBufferSize = nullptr, _Out_opt_ LPDWORD lpMaxInstances = nullptr) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return GetNamedPipeInfo(m_hPipe, lpFlags, lpOutBufferSize, lpInBufferSize, lpMaxInstances);
	}

	BOOL SetState(_In_opt_ LPDWORD lpMode, _In_opt_ LPDWORD lpMaxCollectionCount, _In_opt_ LPDWORD lpCollectDataTimeout) noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return SetNamedPipeHandleState(m_hPipe, lpMode, lpMaxCollectionCount, lpCollectDataTimeout);
	}

	__if_exists(SetNamedPipeHandleState)
	{
		_Success_(return != 0)
			BOOL GetClientComputerName(_Out_writes_bytes_(ClientComputerNameLength) LPTSTR ClientComputerName, _In_ ULONG ClientComputerNameLength) noexcept
		{
			//Validate our parameters
#pragma warning(suppress: 26477)
			assert(IsOpen()); //Pipe must be open

			return GetNamedPipeClientComputerName(m_hPipe, ClientComputerName, ClientComputerNameLength);
		}
	}

	__if_exists(GetNamedPipeClientProcessId)
	{
		_Success_(return != 0)
			BOOL GetClientProcessId(_Out_ PULONG ClientProcessId) noexcept
		{
			//Validate our parameters
#pragma warning(suppress: 26477)
			assert(IsOpen()); //Pipe must be open

			return GetNamedPipeClientProcessId(m_hPipe, ClientProcessId);
		}
	}

	__if_exists(GetNamedPipeClientSessionId)
	{
		_Success_(return != 0)
			BOOL GetClientSessionId(_Out_ PULONG ClientSessionId) noexcept
		{
			//Validate our parameters
#pragma warning(suppress: 26477)
			assert(IsOpen()); //Pipe must be open

			return GetNamedPipeClientSessionId(m_hPipe, ClientSessionId);
		}
	}

	__if_exists(GetNamedPipeServerProcessId)
	{
		_Success_(return != 0)
			BOOL GetServerProcessId(_Out_ PULONG ServerProcessId) noexcept
		{
			//Validate our parameters
#pragma warning(suppress: 26477)
			assert(IsOpen()); //Pipe must be open

			return GetNamedPipeServerProcessId(m_hPipe, ServerProcessId);
		}
	}

	__if_exists(GetNamedPipeServerSessionId)
	{
		_Success_(return != 0)
			BOOL GetServerSessionId(_Out_ PULONG ServerSessionId) noexcept
		{
			//Validate our parameters
#pragma warning(suppress: 26477)
			assert(IsOpen()); //Pipe must be open

			return GetNamedPipeServerSessionId(m_hPipe, ServerSessionId);
		}
	}

	BOOL ImpersonateClient() noexcept
	{
		//Validate our parameters
#pragma warning(suppress: 26477)
		assert(IsOpen()); //Pipe must be open

		return ImpersonateNamedPipeClient(m_hPipe);
	}

protected:
	//Member variables
	HANDLE m_hPipe;
};

#endif //#ifndef __NPIPE_H__
