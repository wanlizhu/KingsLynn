#pragma once

#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include <codecvt>
#include <type_traits>
#include "EngineConfig.h"

namespace GS
{
	class GS_API SZ
	{
	public:
		static bool StartsWith(const std::string& str, const std::string& prefix, bool nocase = false);
		static bool EndsWith(const std::string& str, const std::string& suffix, bool nocase = false);
		static std::vector<std::string> Split(const std::string& str, const std::string& delims);
		static std::string Trim(const std::string& str);
		static std::string Replace(const std::string& str, const std::string& src, const std::string& dst);
		static std::string Canonicalize(const std::string& path);
		static char GetPreferredSeparator();

		static std::string Join(const std::string& delim, const std::vector<std::string>& strs);
		template<typename... ARGS>
		static std::string Join(const std::string& delim, ARGS... args) 
		{
			static_assert((std::is_constructible_v<std::string, ARGS&&> && ...));
			std::vector<std::string> vec;
			(vec.push_back(std::forward<ARGS>(args)), ...);
			return Join(delim, vec);
		}
		template<typename... ARGS>
		static std::string JoinPath(ARGS... args)
		{
			static const char kSeparator[2] = { SZ::GetPreferredSeparator(), '\0' };
			return SZ::Canonicalize(SZ::Join<ARGS...>(kSeparator, std::forward<ARGS>(args)...));
		}

		template<typename T>
		static T GetNumber(const std::string& str, size_t* endpos = nullptr)
		{
			size_t offset = str.find_first_of("+-0123456789");
			char* end = 0;
			T res = T(0);

			if (offset != std::string::npos)
			{
				if constexpr (std::is_floating_point_v<T>)
					res = std::strtod(str.c_str() + offset, &end);
				else
					res = std::strtol(str.c_str() + offset, &end, 0);
			}

			if (endpos != nullptr)
			{
				if (offset == std::string::npos)
					*endpos = std::string::npos;
				else
					*endpos = end - str.c_str();
			}

			return res;
		}
		template<typename T>
		static std::vector<T> GetNumbers(const std::string& str)
		{
			size_t offset = str.find_first_of("+-0123456789");
			std::vector<T> res;

			while (offset != std::string::npos)
			{
				res.push_back(GetNumber<T>(str.c_str() + offset, &offset));
			}

			return res;
		}
		
		static inline std::string WStr2Str(const std::wstring& wstr) 
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
			return cvt.to_bytes(wstr);
		}
		static inline std::wstring Str2WStr(const std::string& str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
			return cvt.from_bytes(str);
		}
		static inline std::string ConvertUTF16(const uint16_t* wwstr)
		{
#ifdef _WIN32
			// This is a known issue, tracked by Visual Studio Team
			std::wstring_convert<std::codecvt_utf8<uint16_t>, uint16_t> cvt;
#else
			std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> cvt;
#endif
			return cvt.to_bytes(wwstr);
		}
		static inline std::string ConvertUTF32(const uint32_t* wwstr)
		{
#ifdef _WIN32
			// This is a known issue, tracked by Visual Studio Team
			std::wstring_convert<std::codecvt_utf8<uint32_t>, uint32_t> cvt;
#else
			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
#endif
			return cvt.to_bytes(wwstr);
		}
	};
}