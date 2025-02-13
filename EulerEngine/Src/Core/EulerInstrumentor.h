#pragma once
#include<string>
#include<chrono>
#include<algorithm>
#include<fstream>
#include<thread>
namespace EulerEngine {
	struct ProfileResult {
		const char* Name;
		long long Start;
		long long End;
		unsigned int ThreadID;
	};

	struct InstrumentationSession {
		std::string name;
	};

	class EulerInstrumentor {
	private:
		InstrumentationSession* m_Session;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	public:
		EulerInstrumentor():m_Session(nullptr), m_ProfileCount(0) {
		}
		void BeginSession(const std::string& name, const std::string& filepath = "results.json") {
			m_OutputStream.open(filepath);
			WriteHeader();
			m_Session = new InstrumentationSession{name};
		}
		void EndSession() {
			WriteFooter();
			m_OutputStream.close();
			delete m_Session;
			m_Session = nullptr;
			m_ProfileCount = 0;
		}
		void WriteProfile(const ProfileResult& result) {
			if (m_ProfileCount++ > 0) {
				m_OutputStream << ",";
			}
			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');
			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ",";
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}
		void WriteHeader() {
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}
		void WriteFooter() {
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}
		static EulerInstrumentor& Get()
		{
			static EulerInstrumentor instance;
			return instance;
		}
	};
	class InstrumentationTimer {
	public:
		InstrumentationTimer(const char* name) :m_Name(name), m_Stopped(false) {
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		};
		~InstrumentationTimer() {
			if (!m_Stopped) {
				Stop();
			}
		};
		void Stop() {
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			
			unsigned int threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			EulerInstrumentor::Get().WriteProfile({ m_Name, start, end, threadID });
			
			m_Stopped = true;
			float duration = (end - start) * 0.001f;
		}
	private:
		const char* m_Name;
		bool m_Stopped;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
	};
}
#define KINK_PROFILE 1
#if KINK_PROFILE
#define KINK_PROFILE_BEGIN_SESSION(name, filepath) ::EulerEngine::EulerInstrumentor::Get().BeginSession(name, filepath)
#define KINK_PROFILE_END_SESSION() ::EulerEngine::EulerInstrumentor::Get().EndSession()
#define KINK_PROFILE_FUNCTION() KINK_PROFILE_SCOPE(__FUNCSIG__)
#define KINK_PROFILE_SCOPE(name) ::EulerEngine::InstrumentationTimer timer##__LINE__(name)
#else
#define KINK_PROFILE_BEGIN_SESSION(name, filepath)
#define KINK_PROFILE_END_SESSION()
#define KINK_PROFILE_FUNCTION()
#define KINK_PROFILE_SCOPE(name)
#endif