﻿#pragma once

#include <gtest/gtest.h>

#include <sstream>
#include <memory>
#include <vector>
#include <string>

namespace testing {
namespace internal {
// ReSharper disable once IdentifierTypo
void ColoredPrintf(GTestColor color, const char* fmt, ...);
}
}

namespace conemu {
namespace tests {
void InitConEmuPathVars();
void WaitDebugger(const std::string& label, const DWORD milliseconds = 15000);
extern std::vector<std::string> gTestArgs;

class GuiMacro final
{
	HMODULE m_ConEmuCD{nullptr};
	GuiMacro(const GuiMacro&) = delete;
	GuiMacro(GuiMacro&&) = delete;
	GuiMacro& operator=(const GuiMacro&) = delete;
	GuiMacro& operator=(GuiMacro&&) = delete;
public:
	GuiMacro();
	~GuiMacro();
	std::wstring Execute(const std::wstring& macro) const;
};
}  // namespace tests
}  // namespace conemu

struct wcdbg : public std::wostringstream
{
	wcdbg(const char* label = nullptr, const bool brackets = true) : m_brackets(brackets)
	{
		m_label = label ? label : "DEBUG";
		if (brackets)
			m_label.resize(8, ' ');
	}

	wcdbg(const wcdbg&) = delete;
	wcdbg(wcdbg&&) = delete;
	wcdbg& operator=(const wcdbg&) = delete;
	wcdbg& operator=(wcdbg&&) = delete;

	virtual ~wcdbg()
	{
		const auto data = this->str();
		std::string utf_data;
		const auto console_cp = GetConsoleOutputCP();
		const auto cp = console_cp ? console_cp : CP_UTF8;
		const int len = WideCharToMultiByte(cp, 0, data.c_str(), int(data.length()), nullptr, 0, nullptr, nullptr);
		utf_data.resize(len);
		WideCharToMultiByte(cp, 0, data.c_str(), int(data.length()), &(utf_data[0]), len, nullptr, nullptr);
		if (m_brackets)
			testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, "[ %s ] %s", m_label.c_str(), utf_data.c_str());
		else
			testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, "%s%s", m_label.c_str(), utf_data.c_str());
		static const bool in_color_mode = _isatty(_fileno(stdout)) != 0;
		if (!in_color_mode)
			fflush(stdout);
	}

private:
	std::string m_label;
	const bool m_brackets;
};

struct cdbg : public std::ostringstream
{
	cdbg(const char* label = nullptr, const bool brackets = true) : m_brackets(brackets)
	{
		m_label = label ? label : "DEBUG";
		if (brackets)
			m_label.resize(8, ' ');
	}
	cdbg(const cdbg&) = delete;
	cdbg(cdbg&&) = delete;
	cdbg& operator=(const cdbg&) = delete;
	cdbg& operator=(cdbg&&) = delete;

	virtual ~cdbg()
	{
		const auto data = this->str();
		if (m_brackets)
			testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, "[ %s ] %s", m_label.c_str(), data.c_str());
		else
			testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, "%s%s", m_label.c_str(), data.c_str());
		static const bool in_color_mode = _isatty(_fileno(stdout)) != 0;
		if (!in_color_mode)
			fflush(stdout);
	}

private:
	std::string m_label;
	const bool m_brackets;
};
