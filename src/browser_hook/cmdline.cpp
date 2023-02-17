#include "stdafx.h"

namespace local {
	CmdLine::CmdLine() {
		Init();
	}
	CmdLine::~CmdLine() {
		UnInit();
	}

	void CmdLine::Init() {
		std::string decode_cmdline_json_data;
		do {
			auto pCmdline = ::GetCommandLineA();
			std::string cmdline = pCmdline ? pCmdline : "";
			if (cmdline.empty())
				break;
			auto found_memade_cmdline_identify = cmdline.find(R"(--memade=)");
			if (found_memade_cmdline_identify == std::string::npos)
				break;
			auto begin = found_memade_cmdline_identify + strlen("--memade=");
			auto end = cmdline.find(begin, ' ');
			if (end == std::string::npos)
				end = cmdline.find(begin, '\n');
			std::string memade_cmdline_value = cmdline.substr(begin, end - begin);
			decode_cmdline_json_data = shared::Encryption::base64::base64_decode(memade_cmdline_value);
		} while (0);
		/*
		{
		"Proxy":{
		"Enable":true,
				"ProxyAddress":"proxy.ipidea.io:2333",
		"ProxyAccount":"liyz888-zone-custom-region-us-session-86977717-sessTime-60",
		"ProxyPassword":"c646674de314d7f2"
		}

		}
		*/
		//CQl7CgkJIlByb3h5QWRkcmVzcyI6InByb3h5LmlwaWRlYS5pbzoyMzMzIiwKCQkiUHJveHlBY2NvdW50IjoibGl5ejg4OC16b25lLWN1c3RvbS1yZWdpb24tdXMtc2Vzc2lvbi04Njk3NzcxNy1zZXNzVGltZS02MCIsCgkJIlByb3h5UGFzc3dvcmQiOiJjNjQ2Njc0ZGUzMTRkN2YyIgoJCX0=
		do {
			if (decode_cmdline_json_data.empty())
				break;
			rapidjson::Document doc;
			if (doc.Parse(decode_cmdline_json_data.data(), decode_cmdline_json_data.size()).HasParseError())
				break;
			if (!doc.IsObject())
				break;
			if (doc.ObjectEmpty())
				break;

			//!@ Proxy
			//! 
			//! 
			if (doc.HasMember("Proxy") && doc["Proxy"].IsObject()) {
				auto& node = doc["Proxy"];
				if (node.HasMember("Enable") && node["Enable"].IsBool())
					m_EnableProxy = node["Enable"].GetBool();
				if (node.HasMember("ProxyAddress") && node["ProxyAddress"].IsString())
					m_ProxyAddress = node["ProxyAddress"].GetString();
				if (node.HasMember("ProxyAccount") && node["ProxyAccount"].IsString())
					m_ProxyAccount = node["ProxyAccount"].GetString();
				if (node.HasMember("ProxyPassword") && node["ProxyPassword"].IsString())
					m_ProxyPassword = node["ProxyPassword"].GetString();
			}

		} while (0);
	}

	void CmdLine::UnInit() {
		auto sk = 0;
	}
	const bool& CmdLine::ProxyEnable() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_EnableProxy;
	}
	const std::string CmdLine::ProxyAccount() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_ProxyAccount;
	}
	const std::string CmdLine::ProxyAddress() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_ProxyAddress;
	}
	const std::string CmdLine::ProxyPassword() const {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		return m_ProxyPassword;
	}
}///namespace local
