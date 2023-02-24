#include "stdafx.h"

namespace local {
	Extensions::Extensions() {
		Init();
	}
	Extensions::~Extensions() {
		UnInit();
	}

	void Extensions::Init() {
		do {//!@ AutoProxy
			if (!__gpCmdline->ProxyEnable())
				break;
			std::string auto_proxy_path;
#if _DEBUG
			auto_proxy_path = R"(D:\github\ChromiumBrowserRelease\Browser\Extensions\AutoProxy\)";
#else
			auto_proxy_path = shared::Win::GetModulePathA() + "Extensions\\AutoProxy\\";
#endif
			if (!shared::Win::AccessA(auto_proxy_path))
				break;
			std::string change_target_file = auto_proxy_path + "bg.js";
			if (!shared::Win::AccessA(change_target_file))
				break;
			std::string change_target_file_buffer = shared::Win::File::Read(change_target_file);
			if (change_target_file_buffer.empty())
				break;
			do {
				auto begin = change_target_file_buffer.find(R"(var login=")");
				if (begin == std::string::npos)
					break;
				auto end = change_target_file_buffer.find(";", begin);
				std::string code_line = change_target_file_buffer.substr(begin, end - begin);
				std::string login = std::format(R"(var login="{}")", __gpCmdline->ProxyAccount());
				change_target_file_buffer.replace(begin, code_line.size(), login);
			} while (0);

			do {
				auto begin = change_target_file_buffer.find(R"(var password=")");
				if (begin == std::string::npos)
					break;
				auto end = change_target_file_buffer.find(";", begin);
				std::string code_line = change_target_file_buffer.substr(begin, end - begin);
				std::string password = std::format(R"(var password="{}")", __gpCmdline->ProxyPassword());
				change_target_file_buffer.replace(begin, code_line.size(), password);
			} while (0);
			shared::Win::File::Write(change_target_file, change_target_file_buffer);
		} while (0);
	}

	void Extensions::UnInit() {
		auto sk = 0;
	}

}///namespace local
