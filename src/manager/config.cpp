#include "stdafx.h"

namespace local {

	Config::Config() {
		Init();
	}
	Config::~Config() {
		UnInit();
	}
	void Config::Init() {
		do {
			m_ConfigFilePathname = shared::Win::GetModulePathA() + "config.json";
			m_ConfigBuffer = shared::Win::File::Read(m_ConfigFilePathname);
			if (m_ConfigBuffer.empty())
				break;

			rapidjson::Document doc;
			if (doc.Parse(m_ConfigBuffer.data(), m_ConfigBuffer.size()).HasParseError())
				break;



		} while (0);

		m_IsOpen.store(true);
		m_Threads.emplace_back([this]() {Process(); });
	}
	void Config::UnInit() {
		m_IsOpen.store(false);
		for (auto& t : m_Threads)
			t.join();
		m_Threads.clear();
	}
	void Config::RemoveBrowserConfig(const std::uint64_t& identify) {
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		auto found = m_BrowserConfigs.find(identify);
		if (found != m_BrowserConfigs.end())
			m_BrowserConfigs.erase(found);
	}
	bool Config::AppendBrowserConfig(const std::string& json_node) {
		bool result = false;
		std::lock_guard<std::mutex> lock{ *m_Mutex };
		do {
			if (json_node.empty())
				break;
			rapidjson::Document doc;
			if (doc.Parse(json_node.data(), json_node.size()).HasParseError())
				break;
			if (!doc.HasMember("identify"))
				break;
			if (!doc["identify"].IsNumber())
				break;
			m_BrowserConfigs.emplace(doc["identify"].GetUint64(), shared::Json::toString(doc));
			result = true;
		} while (0);
		return result;
	}













	void Config::Process() {
		do {




			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			if (!m_IsOpen.load())
				break;
		} while (1);
	}
}///namespace local