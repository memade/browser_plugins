#include "stdafx.h"

namespace local {
	ChromiumPlugin::ChromiumPlugin() {
		Init();
	}
	ChromiumPlugin::~ChromiumPlugin() {
		UnInit();
	}
	void ChromiumPlugin::Init() {
		m_pConfig = new Config();

		LPSTR pCmdline = ::GetCommandLineA();

		std::string cmdline = pCmdline ? pCmdline : "";

		if (cmdline.find("--type=") == std::string::npos) {
			m_ProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_MAIN;
		}
		else if (cmdline.find("--type=gpu-process ") != std::string::npos) {
			m_ProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_GPU;
		}
		else if (cmdline.find("--type=renderer ") != std::string::npos) {
			m_ProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_RENDERER;
		}
		else if (cmdline.find("--type=utility ") != std::string::npos) {
			m_ProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_UTILITY;
		}
		else if (cmdline.find("--type=crashpad-handler ") != std::string::npos) {
			m_ProcessType = EnBrowserProcessType::EN_PROCESS_TYPE_CRASHPAD;
		}
	}

	void ChromiumPlugin::UnInit() {
		SK_DELETE_PTR(m_pConfig);
	}

	Config* ChromiumPlugin::ConfigGet() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_pConfig;
	}
	const EnBrowserProcessType& ChromiumPlugin::BrowserProcessType() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_ProcessType;
	}
	static auto defCreateProcessW = [](
		_In_opt_ LPCWSTR lpApplicationName,
		_Inout_opt_ LPWSTR lpCommandLine,
		_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
		_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
		_In_ BOOL bInheritHandles,
		_In_ DWORD dwCreationFlags,
		_In_opt_ LPVOID lpEnvironment,
		_In_opt_ LPCWSTR lpCurrentDirectory,
		_In_ LPSTARTUPINFOW lpStartupInfo,
		_Out_ LPPROCESS_INFORMATION lpProcessInformation
		)->BOOL {
			LOGINFO("{} run on process({}),", "CreateProcessW", ::GetCurrentProcessId());
			return Global::PluginGet()->CreateProcessWLocal(
				lpApplicationName,
				lpCommandLine,
				lpProcessAttributes,
				lpThreadAttributes,
				bInheritHandles,
				dwCreationFlags,
				lpEnvironment,
				lpCurrentDirectory,
				lpStartupInfo,
				lpProcessInformation
			);
	};
	static auto defCreateProcessAsUserW = [](
		_In_opt_ HANDLE hToken,
		_In_opt_ LPCWSTR lpApplicationName,
		_Inout_opt_ LPWSTR lpCommandLine,
		_In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
		_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
		_In_ BOOL bInheritHandles,
		_In_ DWORD dwCreationFlags,
		_In_opt_ LPVOID lpEnvironment,
		_In_opt_ LPCWSTR lpCurrentDirectory,
		_In_ LPSTARTUPINFOW lpStartupInfo,
		_Out_ LPPROCESS_INFORMATION lpProcessInformation
		)->BOOL {
				LOGINFO("{} run on process({}),", "CreateProcessAsUserW", ::GetCurrentProcessId());
#if 0
				std::string cmd_string;
				do {
					if (!lpCommandLine)
						break;
					cmd_string = shared::IConv::WStringToMBytes(lpCommandLine);
				} while (0);
				//LOGINFO("{} run on process({}) and cmd({}).", "CreateProcessAsUserW", ::GetCurrentProcessId(), cmd_string.empty() ? "empty" : cmd_string);
#endif
				return Global::PluginGet()->CreateProcessAsUserWLocal(
					hToken,
					lpApplicationName,
					lpCommandLine,
					lpProcessAttributes,
					lpThreadAttributes,
					bInheritHandles,
					dwCreationFlags,
					lpEnvironment,
					lpCurrentDirectory,
					lpStartupInfo,
					lpProcessInformation
				);
			};

	static auto defGetNativeSystemInfo = [](
		_Out_ LPSYSTEM_INFO lpSystemInfo)->VOID {
			Global::PluginGet()->GetNativeSystemInfoLocal(lpSystemInfo);
#if 0
			if (lpSystemInfo->dwNumberOfProcessors > 2)
				lpSystemInfo->dwNumberOfProcessors -= 2;
#endif
	};

	static auto defGetSystemInfo = [](
		_Out_ LPSYSTEM_INFO lpSystemInfo)->VOID {
			Global::PluginGet()->GetSystemInfoLocal(lpSystemInfo);
	};

	static auto defGetProductInfo = [](
		_In_ DWORD dwOSMajorVersion,
		_In_ DWORD dwOSMinorVersion,
		_In_ DWORD dwSpMajorVersion,
		_In_ DWORD dwSpMinorVersion,
		_Out_ PDWORD pdwReturnedProductType)->BOOL {
			return Global::PluginGet()->GetProductInfoLocal(dwOSMajorVersion, dwOSMinorVersion, dwSpMajorVersion, dwSpMinorVersion, pdwReturnedProductType);
	};

	static auto defGetVersion = [](
		)->DWORD {
			return Global::PluginGet()->GetVersionLocal();
	};
	static auto defGetVersionExW = [](
		_Inout_ LPOSVERSIONINFOW lpVersionInformation
		)->BOOL {
			return Global::PluginGet()->GetVersionExWLocal(lpVersionInformation);
	};

	static auto defGetVersionExA = [](
		_Inout_ LPOSVERSIONINFOA lpVersionInformation
		)->BOOL {
			return Global::PluginGet()->GetVersionExALocal(lpVersionInformation);
	};

	static auto defEnumFontFamiliesExW = [](
		_In_ HDC hdc, _In_ LPLOGFONTW lpLogfont, _In_ FONTENUMPROCW lpProc, _In_ LPARAM lParam, _In_ DWORD dwFlags)->int {
			LOGINFO("Hook Api({}).", "EnumFontFamiliesExW");
			return Global::PluginGet()->EnumFontFamiliesExWLocal(
				hdc,
				lpLogfont,
				lpProc,
				lParam,
				dwFlags
			);
	};

	static auto defGetFontData = [](_In_ HDC hdc,
		_In_ DWORD   dwTable,
		_In_ DWORD   dwOffset,
		_Out_writes_bytes_to_opt_(cjBuffer, return) PVOID pvBuffer,
		_In_ DWORD   cjBuffer)->DWORD {
			LOGINFO("Hook Api({}).", "GetFontData");
			return Global::PluginGet()->GetFontDataLocal(
				hdc,
				dwTable,
				dwOffset,
				pvBuffer,
				cjBuffer
			);
	};
	bool ChromiumPlugin::Start() {
		do {
			if (m_IsOpen.load())
				break;
			switch (m_ProcessType) {
			case EnBrowserProcessType::EN_PROCESS_TYPE_MAIN: {
				CreateProcessWRemote = defCreateProcessW;
				m_DetoursDetourAttachMap.emplace(&(PVOID&)CreateProcessWLocal, CreateProcessWRemote);
				CreateProcessAsUserWRemote = defCreateProcessAsUserW;
				m_DetoursDetourAttachMap.emplace(&(PVOID&)CreateProcessAsUserWLocal, CreateProcessAsUserWRemote);
			}break;
			case EnBrowserProcessType::EN_PROCESS_TYPE_GPU: {
			} break;
			case EnBrowserProcessType::EN_PROCESS_TYPE_RENDERER: {
			}break;
			case EnBrowserProcessType::EN_PROCESS_TYPE_UTILITY: {
			}break;
			case EnBrowserProcessType::EN_PROCESS_TYPE_CRASHPAD: {
			}break;
				//default:
				// return false;
			}
			GetVersionRemote = defGetVersion;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetVersionLocal, GetVersionRemote);
			GetVersionExARemote = defGetVersionExA;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetVersionExALocal, GetVersionExARemote);
			GetVersionExWRemote = defGetVersionExW;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetVersionExWLocal, GetVersionExWRemote);
			GetSystemInfoRemote = defGetSystemInfo;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetSystemInfoLocal, GetSystemInfoRemote);
			GetNativeSystemInfoRemote = defGetNativeSystemInfo;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetNativeSystemInfoLocal, GetNativeSystemInfoRemote);
			GetProductInfoRemote = defGetProductInfo;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetProductInfoLocal, GetProductInfoRemote);
			GetFontDataRemote = defGetFontData;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)GetFontDataLocal, GetFontDataRemote);
			EnumFontFamiliesExWRemote = defEnumFontFamiliesExW;
			m_DetoursDetourAttachMap.emplace(&(PVOID&)EnumFontFamiliesExWLocal, EnumFontFamiliesExWRemote);
			DetoursDetourAttach();
			m_IsOpen.store(true);
		} while (0);
		return m_IsOpen.load();
	}

	void ChromiumPlugin::Stop() {
		do {
			if (!m_IsOpen.load())
				break;
			DetoursDetourDetach();
			m_IsOpen.store(false);
		} while (0);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//!@ Private method
	void ChromiumPlugin::DetoursDetourAttach() const {
		shared::detours::DetourRestoreAfterWith();
		shared::detours::DetourTransactionBegin();
		shared::detours::DetourUpdateThread(::GetCurrentThread());
		for (const auto& node : m_DetoursDetourAttachMap)
			shared::detours::DetourAttach(node.first, node.second);
		shared::detours::DetourTransactionCommit();
	}
	void ChromiumPlugin::DetoursDetourDetach() const {
		shared::detours::DetourTransactionBegin();
		shared::detours::DetourUpdateThread(::GetCurrentThread());
		for (const auto& node : m_DetoursDetourAttachMap)
			shared::detours::DetourDetach(node.first, node.second);
		shared::detours::DetourTransactionCommit();
	}

	}///namespace local
